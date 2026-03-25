# Barry the Bench Maker

A text-based adventure game meant to be played in a single sitting. Expect around 45 minutes to an hour for a first playthrough.

Barry is a bench maker whose masterwork has been stolen. Craft benches to earn gold, gear up, and fight your way to getting it back.

> This game is a work in progress. If you run into anything strange, including game balance, please report it!

This game has no music yet, but to be fully immersed I recommend playing with some fantasy, medieval music off of YouTube.

## How to Play

You play by typing commands into the terminal. The game will show you what's available at any given moment.

**Outside of combat:**
- `chop` — gather wood (takes real time)
- `craft [item]` — build something from materials (takes real time)
- `buy [item]` / `sell [item]` — trade at the shop
- `upgrade [tool]` — improve your equipment
- `eat` — use a consumable to heal
- `inv` — check your inventory
- `continue` — advance the story
- `quit` — exit the game

**In combat:**
- `attack [#]` — swing at a target (also digests food)
- `block [#]` — brace against a specific enemy's attack, reducing their damage
- `eat` — heal mid-fight (increases fullness)

## Tips

- Crafting and chopping happen in real time. Upgrading your tools pays off.
- Gold management matters. Spend wisely.
- Combat rewards careful decision-making over button mashing.
- Prepare before you continue the story. You won't always get a second chance to stock up.

## Patch Notes

### v0.2

**Combat rework:**
- Removed parry. Combat actions are now attack, block, and eat.
- Block is now targeted — choose which enemy to brace against. Their damage is reduced based on your sword tier. Other enemies still hit at full strength.
- Added a fullness meter. Each cake eaten fills your stomach by 25%. At 100%, you can't eat until you attack to digest. Manage your stomach alongside your health.

**Quality of life:**
- Setting text now displays your current health and gold.
- Inventory shows your health.
- Story text updated to Barry's perspective (present tense).

**Under the hood:**
- Game state consolidated into a single World struct.
- Story progress uses a named enum instead of raw integers.
- Shared random engine across all systems.
- Removed unused item setters.
- Sword upgrade to tier 3 is now locked behind reaching Kelsa.
