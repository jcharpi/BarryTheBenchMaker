# Combat System & First Story Arc - Implementation Plan

## Context

Barry has had his bench stolen by goblins. The opening sequence ends with him in Ashpeak preparing for the journey. The game currently has no combat, no story progression, and no way to upgrade tools. This plan adds the first third of the story: 3 encounters of increasing difficulty leading to the Goblin King boss fight, a turn-based chance-based combat system, tool upgrades for preparation, and cutscene-driven storytelling between fights.

---

## Story Flow

The player uses `continue` (always-available action) to advance. Each encounter = pre-battle cutscene -> combat -> post-battle dialogue.

1. **Forest Bear** - Barry enters the forest toward the goblin kingdom. A massive bear blocks the path. First fight, checks player preparation.
2. **Goblin Ambush (5 goblins)** - On the mountain, goblins drop from trees. All 5 attack each round (1vMany). Barry must target one at a time while weathering attacks from all.
3. **Goblin King Duel** - Barry confronts the king, demands the bench. King won't reveal who paid them. Barry challenges him. Boss fight (1v1).

Each encounter is a checkpoint. Losing encounter 3 restarts at encounter 3, not encounter 1.

---

## Combat System

### Turn Structure
1. Display combat HUD (enemy HP bars + player HP/sword/cake count)
2. Player chooses action
3. Enemy/enemies choose actions (weighted random: attack vs block)
4. Resolve simultaneously

### Player Actions
- **Attack [target]** - Deals sword damage to target if it hits. Base hit chance ~75%. Reduced by enemy block chance when enemy is blocking.
- **Block** - Halves all incoming enemy hit chances this turn.
- **Parry** - If the targeted enemy attacks, completely negates their attack AND reduces their block chance by 20% next turn. **If the enemy blocks instead, Barry stumbles** - the enemy gets a guaranteed/boosted hit next turn.
- **Eat** - Consumes cake, heals 25 HP. Barry is fully exposed to attacks (no defensive bonus).

### Enemy Actions (weighted random per enemy)
- **Attack** - Deals enemy damage if it hits. Hit chance varies by enemy type.
- **Block** - Increases chance of blocking player's attack.

### Multi-Enemy Combat (Goblin Ambush)
- All living enemies act each round
- Player must specify a target for Attack/Parry: e.g., `attack 3` targets Goblin 3
- Block and Eat affect all incoming (block halves ALL enemy hit chances, eat just heals)
- Display numbered enemies with HP bars:
  ```
  1. Goblin    [######----] 30/40
  2. Goblin    [##########] 40/40
  3. Goblin    [DEAD]
  4. Goblin    [########--] 35/40
  5. Goblin    [##########] 40/40
  ```

### Defeat Handling
- Lose 25% current gold (rounded down, floored at 0)
- Start retry with reduced current HP (encounter-specific penalty)
- Return to main game loop; `continue` remains available to retry
- Enemies fully reset on retry

---

## Upgrade System

New always-available action: `upgrade`

- Typing `upgrade` with no target shows available upgrades with costs
- `upgrade sword` / `upgrade axe` upgrades the tool one tier (max tier 3)
- **Costs** (to be tuned, rough starting point):
  - Sword Tier 2: 50 gold + 5 wood
  - Sword Tier 3: 150 gold + 15 wood
  - Axe Tier 2: 30 gold + 3 wood
  - Axe Tier 3: 80 gold + 10 wood
- Sword damage by tier: 25 / 50 / 100
- Axe chop time by tier: 4s / 2s / 1s

---

## Enemy Stats

| Enemy | HP | Damage | Hit% | Block% | Atk Weight | Blk Weight |
|-------|-----|--------|------|--------|------------|------------|
| Forest Bear | 120 | 20 | 65 | 20 | 80 | 20 |
| Goblin | 40 | 12 | 55 | 15 | 75 | 25 |
| Goblin King | 200 | 30 | 70 | 40 | 65 | 35 |

### Drops (chance-based, rolled on kill)
- **Bear Pelt** (75% chance) - Sellable for 50 gold
- **Goblin Ear** (50% chance per goblin) - Sellable for 15 gold each
- **Goblin Crown** (100% chance) - Sellable for 200 gold

---

## New Files to Create

| File | Purpose |
|------|---------|
| `include/Enemy.h` | Enemy class + EnemyDrop struct |
| `assets/Enemy.cpp` | Enemy implementation |
| `include/Combat.h` | CombatAction enum, CombatResult enum, RunCombat() |
| `assets/Combat.cpp` | Combat loop, HUD rendering, turn resolution |
| `include/Story.h` | Encounter struct, RunEncounter() |
| `assets/Story.cpp` | Encounter flow: cutscene -> combat -> dialogue -> drops |
| `data/encounter1_pre.json` | Forest approach, bear appears |
| `data/encounter1_post.json` | Bear defeated, continuing up mountain |
| `data/encounter2_pre.json` | Goblins ambush on the mountain |
| `data/encounter2_post.json` | Goblins defeated, reaching the tunnels |
| `data/encounter3_pre.json` | Confronting the Goblin King, bench demand, duel challenge |
| `data/encounter3_post.json` | King defeated, reveals someone paid them, cliffhanger |

## Existing Files to Modify

| File | Changes |
|------|---------|
| `include/interfaces/Item.h` | Add BearPelt, GoblinEar, GoblinCrown to ItemId enum |
| `include/Action.h` | Add `Continue` and `Upgrade` to Action enum |
| `assets/Action.cpp` | Parse "continue"/"upgrade", add to GetAvailableActions, ActionToString |
| `include/Player.h` | Add TakeDamage(), SetCurrentHealth(), LoseGold() methods |
| `assets/Player.cpp` | Implement new Player methods |
| `BarryTheBenchMaker.cpp` | Include new headers, construct enemies/encounters, handle Continue/Upgrade actions, track storyProgress int |
| `data/values.json` | Add enemies section, drop items, upgrade costs |
| `BarryTheBenchMaker.vcxproj` | Add new .cpp/.h files |
| `BarryTheBenchMaker.vcxproj.filters` | Add new files to filter groups |

---

## Build Order (Incremental, Testable Phases)

### Phase 1: Foundation
1. Add new ItemIds (BearPelt, GoblinEar, GoblinCrown) to enum
2. Add Continue + Upgrade to Action enum, wire parsing
3. Add TakeDamage/SetCurrentHealth/LoseGold to Player
4. Wire upgrade action in main loop (upgrade sword/axe with gold+wood cost)
5. **Test:** Game compiles, "upgrade" and "continue" are recognized, upgrade works

### Phase 2: Enemy & Combat Core
6. Create Enemy class (health, damage, hit/block chances, drops)
7. Create Combat module - HUD rendering + turn loop for 1v1
8. Implement action resolution matrix (attack/block/parry/eat vs attack/block)
9. **Test:** Hardcode a bear fight, test all combat actions work

### Phase 3: Multi-Enemy Combat
10. Extend RunCombat to handle vector of enemies (all act each round)
11. Add target selection for attack/parry (e.g., `attack 3`)
12. **Test:** Hardcode 5-goblin fight, verify targeting + multi-attack

### Phase 4: Story & Encounters
13. Create Story module (Encounter struct, RunEncounter flow)
14. Write all 6 dialogue JSON files (cutscenes)
15. Wire storyProgress tracking in main, connect `continue` to RunEncounter
16. Create drop items as Sellables, add to sellables list after combat
17. **Test:** Full playthrough of all 3 encounters

### Phase 5: Polish
18. Tune balance numbers from playtesting
19. Add defeat flavor text per encounter
20. Update .vcxproj and .vcxproj.filters
21. Ensure `continue` doesn't show after all 3 encounters are complete (or shows different message)

---

## Verification

1. **Compile check:** Build in Visual Studio after each phase
2. **Upgrade flow:** Start game -> chop wood -> sell -> upgrade sword -> verify damage increased
3. **Combat flow:** `continue` -> watch pre-cutscene -> fight bear -> win -> see post-cutscene -> get drops
4. **Defeat flow:** Intentionally lose -> verify gold loss + HP penalty -> retry same encounter
5. **Multi-enemy:** Fight 5 goblins, verify targeting, health carries through, all attack each round
6. **Boss fight:** Beat goblin king, verify crown drop + final cutscene cliffhanger
7. **Full arc:** Play from opening through all 3 encounters to completion
