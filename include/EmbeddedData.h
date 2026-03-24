#pragma once
#include <string>
#include <unordered_map>

inline const std::unordered_map<std::string, std::string>& GetEmbeddedDialogue() {
	static const std::unordered_map<std::string, std::string> data = {
{"data/ending.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "The harbour was quiet when Barry returned. The merchant ships had gone to anchor for the night. The quay was empty save for the gulls and the last of the chandler's fires, burning low."
  },
  {
    "speaker": "NARRATOR",
    "text": "He carried the bench up the harbour road, past the market square, past the place where cobblestone gave way to packed earth, and up the gentle climb toward the workshops."
  },
  {
    "speaker": "NARRATOR",
    "text": "The broad oak was still there. His door was still there. The cat, as always, had not moved."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry set the bench down on his porch, properly covered overhead, just outside the workshop door, where the ground was level and the view opened west toward the harbour and the water beyond it."
  },
  {
    "speaker": "NARRATOR",
    "text": "He sat down."
  },
  {
    "speaker": "NARRATOR",
    "text": "The sun was going down over the harbour. The light came in low and gold across the water, catching the masts of the moored ships and the stone edge of the quay."
  },
  {
    "speaker": "NARRATOR",
    "text": "The cat emerged from the workshop, considered the bench, considered Barry, and jumped up beside him. It curled into a knot against his leg and began to purr."
  },
  {
    "speaker": "BARRY",
    "text": "I'm keeping it."
  },
  {
    "speaker": "NARRATOR",
    "text": "The cat did not object."
  },
  {
    "speaker": "BARRY",
    "text": "No lord. No commission. No offer. I don't care what they'd pay."
  },
  {
    "speaker": "BARRY",
    "text": "This one's mine."
  },
  {
    "speaker": "NARRATOR",
    "text": "The last of the light touched the carvings along the bench's edge, the ones Barry had spent three months on alone, and for a moment they looked like something more than woodwork."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry leaned back. He breathed in: salt air, pine shavings from the workshop behind him, and the faintest trace of linseed oil still rising from the bench beneath him."
  },
  {
    "speaker": "NARRATOR",
    "text": "He was still a bench maker. That had not changed. But the man sitting on this bench was not the same man who had built it."
  },
  {
    "speaker": "NARRATOR",
    "text": "The sun dropped below the harbour line. The sky dimmed to violet, then to blue, then to the kind of dark that makes everything feel close and quiet."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry stayed where he was."
  },
  {
    "speaker": "NARRATOR",
    "lines": [
      "",
      "",
      "    ╔══════════════════════════════════════════════╗",
      "    ║                                              ║",
      "    ║                    T H E                     ║",
      "    ║                                              ║",
      "    ║                    E N D                     ║",
      "    ║                                              ║",
      "    ╚══════════════════════════════════════════════╝",
      ""
    ]
  }
]
)json"},

{"data/opening.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "The port of Greyna woke before the sun did. The first sounds each morning were ropes pulled taut against wooden cleats, hulls groaning as the tide shifted beneath them, and the low calls of dockworkers carrying across the water."
  },
  {
    "speaker": "NARRATOR",
    "text": "By midday the harbour was another thing entirely. Merchant galleons from the eastern kingdoms jostled for berth space, crates of iron, spice, and dyed cloth stacked three high along the stone quay. The air was thick with salt and tar from the chandler's fires."
  },
  {
    "speaker": "NARRATOR",
    "text": "Greyna lived off what passed through it. Cloth, timber, salted fish, woodwork, all of which had to come from somewhere."
  },
  {
    "speaker": "NARRATOR",
    "text": "Past the market square, where the cobblestone gave way to packed earth and the noise of the harbour faded behind the tree line, the road climbed gently toward the workshops."
  },
  {
    "speaker": "NARRATOR",
    "text": "One of them, set back from the road beneath a broad oak, belonged to the bench maker, to Barry."
  },
  {
    "speaker": "NARRATOR",
    "text": "Inside, the workshop smelled of pine shavings and linseed oil. Tools lined the walls in careful rows: chisels, planes, axes, mallets, each worn smooth from years of steady use. A cat slept on a pile of offcuts in the corner, undisturbed by anything."
  },
  {
    "speaker": "NARRATOR",
    "text": "And there, where the light fell cleanest, sat a bench."
  },
  {
    "speaker": "NARRATOR",
    "lines": [
      "",
      "",
      "  *               *        *     *                  *",
      "        *    *                          *    *   *",
      "",
      "          ╔══════════════════════════════╗",
      "          ║  ❧   · · · · · · · · ·   ❧   ║",
      "          ╚═════╦══════════════════╦═════╝",
      "                ║                  ║",
      "                ║                  ║",
      "          ══════╩══════════════════╩══════",
      "",
      "     *    *   *                  *         *",
      "  *          *         *   *                   *",
      ""
    ]
  },
  {
    "speaker": "BARRY",
    "text": "Leg joints."
  },
  {
    "speaker": "BARRY",
    "text": "Flush. All four. Indistinguishable."
  },
  {
    "speaker": "BARRY",
    "text": "Grain."
  },
  {
    "speaker": "BARRY",
    "text": "Unbroken. Full length. Pristine."
  },
  {
    "speaker": "BARRY",
    "text": "Sanding."
  },
  {
    "speaker": "BARRY",
    "text": "It's..."
  },
  {
    "speaker": "BARRY",
    "text": "No, can't be."
  },
  {
    "speaker": "BARRY",
    "text": "Carvings."
  },
  {
    "speaker": "BARRY",
    "text": "Clean. Well-Formed..."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry gasped, then hopped to his feet. He walked around the bench a few times, inspecting it with the highest level of scrutiny."
  },
  {
    "speaker": "BARRY",
    "text": "It really is. It's perfect, at last."
  },
  {
    "speaker": "NARRATOR",
    "text": "Every evening for three years, after the day's work was done, Barry had come back to this project. Now it was finished."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry's workshop stood quiet for the first time in a long while. Even his cat perked its head, sensing Barry's bewilderment."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry stood thinking, wondering how his hands were capable of crafting such a masterpiece when a sharp knock at his door broke the silence."
  },
  {
    "speaker": "NARRATOR",
    "text": "A courier, young and out of breath, wearing the colours of a lord's house, held out a letter sealed in dark wax and left without waiting for a reply."
  },
  {
    "speaker": "NARRATOR",
    "text": "The seal bore the crest of Crane's Reach, a tower on high stone, the seat of Lord Harwick Crane, whose name moved through Greyna's trading halls with the weight of old money and older land."
  },
  {
    "speaker": "NARRATOR",
    "lines": [
      "",
      "",
      "          ┌─────────────────────────────────┐",
      "          │                                 │",
      "          │          C R A N E ' S          │",
      "          │            R E A C H            │",
      "          │                                 │",
      "          │               ▓▓▓               │",
      "          │            ▓▓▓▓▓▓▓▓▓            │",
      "          │               ▓▓▓               │",
      "          │                                 │",
      "          └─────────────────────────────────┘",
      ""
    ]
  },
  {
    "speaker": "LORD CRANE",
    "text": "Word of your craft has reached me. I will have the bench. Name a sum befitting the work, and deliver it to Crane's Reach before the month's end. — H. Crane"
  },
  {
    "speaker": "BARRY",
    "text": "...Sell it?"
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry looked around the workshop that had suited him well for so many years. The tools were good, some inherited from his father, some earned bench by bench over a lifetime of careful work. His name was known along the harbour and in the ports beyond."
  },
  {
    "speaker": "NARRATOR",
    "text": "But a man who worked alone earned slowly. Each bench was months of labour: the selection of the wood, the drying, the shaping, the finishing. The coin came, but it came at the pace of the craft."
  },
  {
    "speaker": "NARRATOR",
    "text": "The winters in Greyna were long and they were not gentle. The hearth in Barry's home burned through firewood faster than he could keep it stocked. The workshop roof leaked in the northeast corner when the wind blew right. The walls of his house could stand to be mended before the next cold season."
  },
  {
    "speaker": "NARRATOR",
    "text": "A lord's commission was not market coin. A lord's commission could mend the walls, replace the roof, fill the stores for a year. Several perhaps."
  },
  {
    "speaker": "BARRY",
    "text": "I can always make another."
  },
  {
    "speaker": "NARRATOR",
    "text": "Though in his heart, Barry knew he could never again make a bench near as beautiful nor as perfect."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry spent the evening wrapping the bench in oiled cloth, binding it with rope at each joint. He laid out the cart fittings by the door and checked the bindings twice before turning in."
  },
  {
    "speaker": "NARRATOR",
    "text": "The following morning, Barry opened the workshop door. The air was still and cool. Light fell across the floor in a wide band from the window, and in that light there was nothing."
  },
  {
    "speaker": "NARRATOR",
    "lines": [
      "",
      "",
      "              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄",
      "              ┆                              ┆",
      "              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄",
      "                    ┆                  ┆",
      "                    ┆                  ┆",
      "              ┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄┄",
      ""
    ]
  },
  {
    "speaker": "NARRATOR",
    "text": "The oiled cloth lay folded on the workbench, unused. The rope bindings sat coiled beside it, untouched. The cart fittings were still by the door where he had left them. The space in the centre of the room was empty."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry checked the back room. He checked the yard behind the workshop. He moved crates he knew were far too small to hide anything. He checked the back room again. He stood in the doorway of the yard and looked out at the road as if the bench might be sitting there, waiting."
  },
  {
    "speaker": "NARRATOR",
    "text": "The workshop door had not been forced. The lock was untouched. The windows were latched from inside."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry stood in the centre of the room, in the exact place the bench had been, and dared not move for a long time."
  },
  {
    "speaker": "NARRATOR",
    "text": "In the silence, Barry's senses seemed to return to him, where he was able to pick out a smell. Beneath the familiar smell of pine shavings and linseed, something else. Faint. Damp earth and sulphur mixed with the kind of smell that only comes after weeks of not washing oneself, settled into the floorboards where the bench once stood."
  },
  {
    "speaker": "BARRY",
    "text": "...Goblin."
  },
  {
    "speaker": "NARRATOR",
    "text": "Every child in Greyna knew the smell. It drifted down from Ashpeak on certain nights when the wind turned, the mountain north of town, where stone gave way to deep tunnels and deeper halls. The goblin kingdom beneath the rock."
  },
  {
    "speaker": "NARRATOR",
    "text": "They kept to themselves, unless, of course, someone paid them enough not to."
  },
  {
    "speaker": "BARRY",
    "text": "Right."
  },
  {
    "speaker": "NARRATOR",
    "text": "The road from Greyna to Ashpeak climbed north through the pine forest and into thinning air."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry knew what he must do and began to prepare for the journey ahead."
  },
  {
    "speaker": "NARRATOR",
    "lines": [
      "",
      "",
      "    ╔══════════════════════════════════════════════╗",
      "    ║                                              ║",
      "    ║              B · A · R · R · Y               ║",
      "    ║                                              ║",
      "    ║                    T H E                     ║",
      "    ║                                              ║",
      "    ║            B E N C H   M A K E R             ║",
      "    ║                                              ║",
      "    ╚══════════════════════════════════════════════╝",
      ""
    ]
  }
]
)json"},

{"data/postBear.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "The bear lay still among the broken undergrowth. The forest, which had held its breath, slowly began to exhale. A bird resumed its call somewhere in the canopy. Wind moved through the pines again."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry stood over the creature, breathing hard, his sword still raised. His hands were shaking. It took him a moment to realise the fight was over."
  },
  {
    "speaker": "NARRATOR",
    "text": "He lowered the sword. His legs felt uncertain beneath him, the way they did after standing too long at the workbench, except worse in every way. He sat down on a fallen trunk and stayed there for a while."
  },
  {
    "speaker": "BARRY",
    "text": "...Right. Okay."
  },
  {
    "speaker": "BARRY",
    "text": "If there are bears in this forest, there will be worse things further up the mountain. I need to keep my guard up."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry wiped the blade on the moss and sheathed it. He looked up the trail where it climbed toward the thinning tree line and the grey stone of Ashpeak beyond."
  },
  {
    "speaker": "NARRATOR",
    "text": "The trail markers pointed to Kelsa, a small timber town nestled at the base of the mountain where the forest gave way to rock. Loggers, trappers, and the odd merchant passed through on their way north. It was the last stop before the climb."
  },
  {
    "speaker": "BARRY",
    "text": "Kelsa. I can resupply there."
  },
  {
    "speaker": "NARRATOR",
    "text": "A bench maker who killed a bear. His father would have had something to say about that. Probably would have told him to check the grain on its teeth."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry allowed himself a small smile, adjusted his pack, and continued up the trail toward Kelsa."
  }
]
)json"},

{"data/postCrane.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "The second guard hit the stone and did not rise. His sword skidded across the balcony and came to rest against the railing."
  },
  {
    "speaker": "NARRATOR",
    "text": "Lord Crane backed against the bench, one hand raised, the other gripping the armrest behind him as though it might protect him. The composure was gone."
  },
  {
    "speaker": "LORD CRANE",
    "text": "You— you dare not defile me. I am Lord of Crane's Reach. I have allies. Connections across every port on this coast."
  },
  {
    "speaker": "BARRY",
    "text": "Move."
  },
  {
    "speaker": "NARRATOR",
    "text": "Crane moved."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry looked at the bench. It was unharmed. The joints were flush. The grain unbroken. The carvings caught the fading light the same way they had in his workshop. Three years of work, sitting on a lord's balcony like a piece of scenery."
  },
  {
    "speaker": "BARRY",
    "text": "You didn't even provide a covering. Lucky it didn't rain or you'd be smashed against the rocks right now."
  },
  {
    "speaker": "LORD CRANE",
    "text": "There would've been no sunlight. It deserved—"
  },
  {
    "speaker": "BARRY",
    "text": "Don't."
  },
  {
    "speaker": "NARRATOR",
    "text": "Crane shut his mouth."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry stepped past him and through the archway into the tower. The corridor led to a wide study, its walls lined with shelves and cabinets. A desk sat beneath the window, buried in ledgers and sealed correspondence."
  },
  {
    "speaker": "NARRATOR",
    "text": "He was not looking for anything in particular. But what he found stopped him."
  },
  {
    "speaker": "NARRATOR",
    "text": "A cabinet, glass-fronted, locked. Inside: a silversmith's hand mirror engraved with initials that were not Crane's. A set of carving knives with another's mark stamped into the handles. A lute, its neck inlaid with pearl, with a shipping label from a port three kingdoms east still tied to the tuning pegs."
  },
  {
    "speaker": "NARRATOR",
    "text": "Beside each piece, a small card in Crane's handwriting. The silversmith's name. The carver's name. The luthier's name. Dates. Locations."
  },
  {
    "speaker": "NARRATOR",
    "text": "Trophies."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry opened a ledger on the desk. Columns of figures. Names of craftsmen down the left margin. Beside each name, a sum, always less than what the work was worth, and a method. Some said purchased. Most did not."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry's name was at the bottom. Beside it: Goblin contract — settled."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry walked back to the balcony. Crane had not moved."
  },
  {
    "speaker": "BARRY",
    "text": "How many?"
  },
  {
    "speaker": "NARRATOR",
    "text": "Crane said nothing for a moment. Barry drew his blade once again."
  },
  {
    "speaker": "LORD CRANE",
    "text": "You wouldn't understand. Common tradesmen don't appreciate what they make. They sell to whoever comes first. Merchants. Tavern keepers. People who'd set a masterwork beside a spittoon and call it furnished."
  },
  {
    "speaker": "LORD CRANE",
    "text": "I preserve them."
  },
  {
    "speaker": "BARRY",
    "text": "That ledger of yours. The names, the dates, the methods. I imagine the harbourmasters along this coast would find it interesting reading."
  },
  {
    "speaker": "NARRATOR",
    "text": "Crane's face went white."
  },
  {
    "speaker": "LORD CRANE",
    "text": "You wouldn't dare."
  },
  {
    "speaker": "BARRY",
    "text": "I'm a bench maker, Lord Crane. I don't have allies or connections across every port. But I know craftsmen in all of them. And craftsmen talk."
  },
  {
    "speaker": "NARRATOR",
    "text": "Crane opened his mouth. Closed it. Opened it again. For the first time, nothing came out."
  },
  {
    "speaker": "BARRY",
    "text": "You'll return what you've taken. All of it. Every piece in that cabinet, back to the hands that made it."
  },
  {
    "speaker": "BARRY",
    "text": "Or the ledger finds its way to people who will care more than I do about what's written in it."
  },
  {
    "speaker": "NARRATOR",
    "text": "The evening wind came in off the sea. Crane's hair moved. His guards lay still on the stone."
  },
  {
    "speaker": "NARRATOR",
    "text": "Crane said nothing. He did not need to. The answer was in his silence."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry lifted the bench. It was heavier than he remembered, or perhaps he was more tired than he knew. He carried it through the archway, down the stairs, and out of Crane's Reach."
  }
]
)json"},

{"data/postGoblin.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "The last goblin hit the ground and did not get up. The chamber went quiet, the kind of quiet that follows something no one expected."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry stood in the centre of the room, breathing hard, sword slick and shaking in his grip. Around him, the bodies of the goblins who had stepped forward lay crumpled and still."
  },
  {
    "speaker": "NARRATOR",
    "text": "The crowd had pulled back. The chatter was gone. Dozens of black eyes stared at him from the edges of the chamber, wide and unblinking."
  },
  {
    "speaker": "NARRATOR",
    "text": "On his throne, the Goblin King sat upright. The practised ease was gone. He leaned forward, both hands on his knees, studying Barry the way one studies a tool that just did something it wasn't built for."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "...Huh."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "That was not what I expected."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "You fight like someone who learned last week and got angry about it. No form. No finesse. And yet here you stand and there they don't. Interesting."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king tilted his head. Something between amusement and genuine curiosity had replaced the smugness."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "So. A human who climbs the mountain on purpose, camps in our doorstep, and puts down five of my subjects before breakfast. You have my attention. Why are you here?"
  },
  {
    "speaker": "BARRY",
    "text": "You know why I'm here."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "Do I?"
  },
  {
    "speaker": "BARRY",
    "text": "Your goblins broke into my workshop. Locked doors. Latched windows. Nothing forced. Nothing missing but the one thing worth taking."
  },
  {
    "speaker": "BARRY",
    "text": "Three years of my life sat in that room. A bench painstakingly crafted. Perfect. The best thing I have ever made."
  },
  {
    "speaker": "BARRY",
    "text": "And you took it."
  },
  {
    "speaker": "NARRATOR",
    "text": "The chamber was silent. Barry's voice carried to every wall."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king held Barry's gaze for a long moment. Then the corner of his mouth twitched, not quite a smile, closer to the expression of someone deciding how much of a card to play."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "A bench. You came all this way, through the forest, up the mountain, into the dark, for a bench."
  },
  {
    "speaker": "BARRY",
    "text": "Yes."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "Hm."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king leaned back. He drummed his fingers once on the arm of his throne."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "My goblins are skilled at what they do. Getting in and out without a trace, that's what they're paid for. But they don't act on their own initiative. They're not thieves. They're contractors."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "Someone wanted your bench badly enough to pay my price for it. And my prices are not gentle."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king paused. Something behind his eyes shifted. A quiet wondering about what, exactly, the bench was worth, if it was cheaper to have it stolen."
  },
  {
    "speaker": "BARRY",
    "text": "Who?"
  },
  {
    "speaker": "GOBLIN KING",
    "text": "Now that is the question, isn't it."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king stood. He was shorter than Barry expected, but he carried himself like something much larger. The crowd shifted. The energy in the room changed."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "I am a king, bench maker. Information is currency down here, same as gold, same as cake, same as the fear that keeps the tunnels in order. I don't give it away."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "You want a name? Earn it."
  }
]
)json"},

{"data/postGoblinKing.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "The Goblin King's blade clattered to the stone. He dropped to one knee, not from ceremony but because his legs would no longer hold him."
  },
  {
    "speaker": "NARRATOR",
    "text": "The chamber was silent. The stamping had stopped. Every goblin in the room stood frozen, watching their king kneel before a bench maker from Greyna."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king looked up at Barry. There was no smugness left. No performance. What remained was something Barry had not expected to see in a goblin's face: respect."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "In all my years beneath this mountain, no human has set foot in my hall uninvited and left on their own terms. None."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "And now a bench maker walks in carrying cake and a rusty sword and handles it better than he has any right to."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "I don't understand you. But I don't need to."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king reached down and picked up his own blade. He held it out to Barry, hilt first."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "Take it. Goblin-forged steel. It won't dull and it won't break. You've earned more than a name tonight."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry took the blade. It was lighter than it looked, and warm, as though the metal remembered the forge."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "Your bench is not here. It passed through my halls, yes, but it didn't stay. My goblins were paid to take it and deliver it. The coin came sealed, same as the instructions. A wax seal on dark parchment."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry's jaw tightened."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "A tower on high stone."
  },
  {
    "speaker": "BARRY",
    "text": "Crane's Reach."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "I never said that. What I said is: the seal bore a tower. What you do with that is your business."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king waved a hand. Two attendants came forward carrying Barry's pack, refilled. Cake. Rope. Supplies enough for the road."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "Restock the bench maker. Full provisions. He's earned his passage and then some."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king settled back against the base of his throne, legs stretched out, looking like someone who had just witnessed something he would be telling stories about for years."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "One more thing, bench maker."
  },
  {
    "speaker": "BARRY",
    "text": "What."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "If you survive whatever's waiting for you out there, come back sometime. Bring cake. My goblins won't touch you."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry sheathed both blades, shouldered his pack, and turned toward the tunnel that led up and out of the mountain."
  },
  {
    "speaker": "NARRATOR",
    "text": "He did not look back."
  },
  {
    "speaker": "NARRATOR",
    "lines": [
      "",
      "",
      "          · · · · · · · · · · · · · · ·",
      "",
      ""
    ]
  },
  {
    "speaker": "NARRATOR",
    "text": "The workshop was as he had left it. Tools in their rows. The cat in its corner. The oiled cloth still folded on the bench, the rope coiled beside it."
  },
  {
    "speaker": "NARRATOR",
    "text": "The empty space in the centre of the room had not changed."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry set his pack down and stood in the doorway for a moment. His shoulders ached. His hands were bruised in places he had not noticed until now. Outside, the harbour moved with its usual indifference."
  },
  {
    "speaker": "BARRY",
    "text": "Crane's Reach."
  },
  {
    "speaker": "NARRATOR",
    "text": "He said it the way a man says something he's been turning over for days. Not with anger. Not yet."
  },
  {
    "speaker": "NARRATOR",
    "text": "Crane's Reach sat on the coast, north and east of Greyna, on a promontory of old stone where the land ran out and the open sea began. There was no road that reached it, not directly. The cliffs made sure of that. The only reliable way in was by water."
  },
  {
    "speaker": "BARRY",
    "text": "A ship."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry pulled a stool to the workbench and sat. He thought about the harbour. The boats he knew well, the small ones, the fishing skiffs and the timber ferries, were not built for open water. A crossing to Crane's Reach meant weather, current, and the kind of sea that did not care what it broke."
  },
  {
    "speaker": "NARRATOR",
    "text": "A vessel that could make the crossing and hold together on the other side was not something easily acquired. It was something bought. The more coin he could bring to the chandler's yard, the more ship he would walk away with."
  },
  {
    "speaker": "BARRY",
    "text": "Right."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry looked at his hands. Then at the empty space in the room."
  },
  {
    "speaker": "BARRY",
    "text": "Time to buy a ship."
  }
]
)json"},

{"data/postShip.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "The hull groaned one last time as the keel scraped stone. Barry looked up. The cliffs of Crane's Reach rose above him, dark and wind-worn, and at the top, a tower."
  },
  {
    "speaker": "NARRATOR",
    "text": "The ship listed against the rocks, battered but whole. Water sloshed in the lower hold, but the planks had held. Barely."
  },
  {
    "speaker": "BARRY",
    "text": "Made it."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry climbed the stone steps cut into the cliff face, each one older than the last. The tower waited above, patient as it had always been."
  },
  {
    "speaker": "NARRATOR",
    "text": "Somewhere inside was a bench. His bench."
  }
]
)json"},

{"data/preBear.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "Barry stood at the edge of Greyna where the cobblestone ended and the forest road began. He had his sword on his hip, his tools on his back, and the kind of determination that only comes from having something irreplaceable stolen."
  },
  {
    "speaker": "BARRY",
    "text": "A sword and some food."
  },
  {
    "speaker": "BARRY",
    "text": "That's all I need."
  },
  {
    "speaker": "NARRATOR",
    "text": "The pine forest closed in quickly. The road narrowed to a trail, then to something less than a trail, a suggestion between the trees where the undergrowth had been worn thin by deer and the occasional traveller foolish enough to head toward Ashpeak on foot."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry walked with purpose. Each step carried him further from the harbour, from the workshop, from the empty space where the bench had been. He did not look back."
  },
  {
    "speaker": "BARRY",
    "text": "Three years of work. Three years of selecting the grain, shaping the joints, sanding until my fingers forgot what rough felt like."
  },
  {
    "speaker": "BARRY",
    "text": "They will give it back or I will take it back."
  },
  {
    "speaker": "NARRATOR",
    "text": "The canopy thickened overhead and the light fell in narrow shafts between the branches. The air grew cooler. Somewhere above, the gentle song of a bird came to its end."
  },
  {
    "speaker": "NARRATOR",
    "text": "Then the forest went quiet. Not the gentle quiet of a still afternoon, but the held-breath quiet of something watching."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry heard it before he saw it. A low sound, not quite a growl, more like the earth itself exhaling through teeth. Branches snapped to his left. Then his right. Then directly ahead."
  },
  {
    "speaker": "NARRATOR",
    "text": "A shape broke through the undergrowth thirty paces up the trail. Enormous. Brown fur matted with pine needles and old mud. Shoulders as wide as Barry's workbench. Eyes small, black, and fixed entirely on him."
  },
  {
    "speaker": "NARRATOR",
    "text": "The bear lowered its head and charged."
  }
]
)json"},

{"data/preCrane.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "The stone steps ended at a wall of old mortar and iron bracing. Above it, the tower of Crane's Reach rose against a sky gone copper with the last of the day's light."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry pressed himself flat against the cliff face and listened. Wind. Gulls. The distant groan of the sea against rock. No voices. No footsteps."
  },
  {
    "speaker": "NARRATOR",
    "text": "He had learned, somewhere between the forest and the mountain, that silence was not the same thing as safety."
  },
  {
    "speaker": "BARRY",
    "text": "Last time I let my guard down, I woke up surrounded by goblins."
  },
  {
    "speaker": "BARRY",
    "text": "Not again."
  },
  {
    "speaker": "NARRATOR",
    "text": "He moved along the base of the tower where the stone met shadow. A service door, rusted at the hinges but unbarred, gave way without sound. Barry slipped inside."
  },
  {
    "speaker": "NARRATOR",
    "text": "The interior of Crane's Reach was cold and still. Tapestries lined the walls, old things depicting hunts and harbours. The floors were stone, the furniture heavy and dark. Everything in the tower looked expensive yet none of it looked loved."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry climbed. He kept to the inner wall where the stairs were narrowest, testing each step before committing his weight. The goblin-forged blade sat silent at his hip."
  },
  {
    "speaker": "NARRATOR",
    "text": "At the top of the stair, a corridor opened toward a wide stone archway. Through it, the evening sky. A balcony."
  },
  {
    "speaker": "NARRATOR",
    "text": "And on that balcony, facing the sea with his back to the door, a man sat on a bench."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry's bench."
  },
  {
    "speaker": "NARRATOR",
    "text": "Lord Harwick Crane sat with one leg crossed over the other, a glass of wine resting on the armrest as though the bench had been built for exactly this purpose. He looked out at the water the way a man looks at something he believes he owns."
  },
  {
    "speaker": "NARRATOR",
    "text": "Two guards flanked him, one on each side, armoured in the dark iron of Crane's house. They stood at ease but their hands were near their swords."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry stepped through the archway."
  },
  {
    "speaker": "NARRATOR",
    "text": "The guards saw him first. Steel cleared leather before Crane had even turned his head."
  },
  {
    "speaker": "LORD CRANE",
    "text": "What is—"
  },
  {
    "speaker": "NARRATOR",
    "text": "Crane stood. The wine glass toppled from the armrest and shattered on the stone. He looked Barry up and down with the expression of a man inspecting something that had wandered in from the street."
  },
  {
    "speaker": "LORD CRANE",
    "text": "Guards, seize him."
  },
  {
    "speaker": "NARRATOR",
    "text": "The guards began to move in. Barry looked past the guards, at the bench. His bench. Sitting on a lord's balcony like a mere piece of furniture."
  },
  {
    "speaker": "BARRY",
    "text": "That's a beautiful bench."
  },
  {
    "speaker": "NARRATOR",
    "text": "The guards moved ever closer. Crane remained still, refusing to acknowledge the vermin who had infiltrated his home."
  },
  {
    "speaker": "BARRY",
    "text": "My name is Barry. I'm a bench maker from Greyna."
  },
  {
    "speaker": "NARRATOR",
    "text": "Crane's face changed. A tinge of panic overcame him, then receded just as quickly."
  },
  {
    "speaker": "BARRY",
    "text": "You sent me a letter. Dark wax. Tower on high stone. Said you wanted to buy my work."
  },
  {
    "speaker": "BARRY",
    "text": "Then you stole it."
  },
  {
    "speaker": "LORD CRANE",
    "text": "Ah yes, the bench maker. I vaguely recall sending something inquiring about a bench. You never replied."
  },
  {
    "speaker": "BARRY",
    "text": "Hard to reply when the bench is gone before morning."
  },
  {
    "speaker": "LORD CRANE",
    "text": "I don't know what you're suggesting. I am a lord of this coast. I acquired this bench through perfectly legitimate means."
  },
  {
    "speaker": "BARRY",
    "text": "You acquired it through goblins. Dark wax seal. Tower on high stone. The Goblin King was happy to share."
  },
  {
    "speaker": "NARRATOR",
    "text": "Crane's composure cracked. He straightened."
  },
  {
    "speaker": "LORD CRANE",
    "text": "That bench is worth more than you understand. The craftsmanship, the grain, the carvings. I have collected fine things from every port on this coast, and nothing, nothing compares."
  },
  {
    "speaker": "LORD CRANE",
    "text": "I offered to pay. You would have asked too much. People like you always do. You'd have put some sentimental figure on it and I'd have been the fool for indulging you."
  },
  {
    "speaker": "BARRY",
    "text": "So you stole it."
  },
  {
    "speaker": "LORD CRANE",
    "text": "I acquired it. Efficiently."
  },
  {
    "speaker": "LORD CRANE",
    "text": "I have no buisness dealings with you. Now leave my tower before I have you thrown from it."
  },
  {
    "speaker": "NARRATOR",
    "text": "The guards stepped forward, nearly within arm's reach of Barry. The balcony suddenly felt smaller."
  },
  {
    "speaker": "BARRY",
    "text": "I've walked through a forest, killed a bear, been dragged into a mountain, fought a goblin king, and crossed a treacherous sea in a ship I couldn't afford to get here."
  },
  {
    "speaker": "BARRY",
    "text": "I'm not leaving without my bench."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry drew the goblin-forged blade. It caught the last light of the evening and held it."
  },
  {
    "speaker": "NARRATOR",
    "text": "The guards drew theirs."
  },
  {
    "speaker": "LORD CRANE",
    "text": "Remove him."
  }
]
)json"},

{"data/preGoblin.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "The road out of Kelsa turned to loose stone within the hour. The trees fell away behind him and the mountain opened up, grey and bare, its face scarred with old rockslides and the black mouths of shallow caves."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry climbed until the light began to fail. The wind at this height had teeth, and the trail ahead disappeared into shadow."
  },
  {
    "speaker": "NARRATOR",
    "text": "He found a cave set back from the path, shallow enough to see the rear wall, deep enough to break the wind. Scorch marks on the stone told him others had sheltered here before."
  },
  {
    "speaker": "BARRY",
    "text": "This'll do."
  },
  {
    "speaker": "NARRATOR",
    "text": "He built a small fire from the scrub wood he'd carried up from the tree line, ate a portion of cake, and sat with his back against the stone. The fire threw long shadows across the ceiling. Beyond it, the mountain was silent."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry slept. Not well, but he slept."
  },
  {
    "speaker": "NARRATOR",
    "text": "He woke to darkness. The fire had gone to embers. The wind had stopped."
  },
  {
    "speaker": "NARRATOR",
    "text": "That was what woke him. Not a sound, rather the absence of one."
  },
  {
    "speaker": "NARRATOR",
    "text": "From the darkness, Barry heard breathing. Not his own."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry reached for his sword and found a hand already on the scabbard. Strong. Cold. Green."
  },
  {
    "speaker": "NARRATOR",
    "text": "The cave mouth filled with shapes. Five of them, maybe six, low to the ground, moving with the kind of coordination that doesn't happen by accident. They had been waiting."
  },
  {
    "speaker": "BARRY",
    "text": "Get off m—"
  },
  {
    "speaker": "NARRATOR",
    "text": "Something struck him behind the ear. The cave ceiling spun once, then went dark."
  },
  {
    "speaker": "NARRATOR",
    "lines": [
      "",
      "",
      "          · · · · · · · · · · · · · · ·",
      "",
      ""
    ]
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry came to with his face against cold stone. The smell hit him before his vision cleared: the unmistakable stench of goblin. Concentrated. Everywhere."
  },
  {
    "speaker": "NARRATOR",
    "text": "He was underground. Deep underground. The ceiling above him was carved, not natural, and lined with crude iron sconces that burned with a greenish, guttering light. The air was thick... and wrong."
  },
  {
    "speaker": "NARRATOR",
    "text": "Rough hands hauled him upright and shoved him forward. The tunnel opened into a wide chamber, its walls cut from the living rock, its floor packed smooth by centuries of bare feet."
  },
  {
    "speaker": "NARRATOR",
    "text": "And at the far end, seated on a throne of scrap iron and stolen timber, legs crossed, chin resting on one fist with the practised ease of someone who enjoyed being looked at:"
  },
  {
    "speaker": "NARRATOR",
    "text": "The Goblin King."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "Well. This is new."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "A human. In my kingdom. Willingly, it would seem, since you came up the mountain with a pack full of cake and a sword you clearly don't know how to sleep with."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "Tell me, do you know where you are? This is not a friendly place for your kind. Most humans who come to Ashpeak don't come on purpose, and those who do tend to regret the trip."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king's voice carried easily through the chamber, smooth and unhurried. He spoke the way someone speaks when they've never once been interrupted."
  },
  {
    "speaker": "NARRATOR",
    "text": "Around the edges of the room, goblins gathered. Dozens of them. Most watched with the dull curiosity of spectators at a market fight. But a few, the ones nearest to Barry, weren't watching his face."
  },
  {
    "speaker": "NARRATOR",
    "text": "They were watching his pack. The cake. Their nostrils flared. One of them licked its teeth."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "You've drawn some attention, human. Can't blame them. You smell like a bakery walked into a forge."
  },
  {
    "speaker": "NARRATOR",
    "text": "Goblins all around Barry shifted forward. They hadn't been told to. Their hands were on crude blades. Their eyes hadn't left him since he was dragged in."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king did not stop them."
  },
  {
    "speaker": "NARRATOR",
    "text": "He watched."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "Now, now. If my subjects want a go at you, that's their business. But I am not without standards."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king raised one hand. A goblin attendant scurried forward and dropped Barry's sword at his feet."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "A human who walks into the mountain deserves the right to defend himself. Pick up your sword."
  },
  {
    "speaker": "NARRATOR",
    "text": "The goblins in the crowd pressed closer. The chamber buzzed with low chatter and the scrape of feet on stone. This was entertainment to them."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry looked at his sword on the ground. He looked at the goblins circling. He looked at the king, who had settled deeper into his throne with the expression of a man about to enjoy a show."
  },
  {
    "speaker": "BARRY",
    "text": "Fine."
  }
]
)json"},

{"data/preGoblinKing.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "The Goblin King stepped down from his throne. The crowd parted for him without being told, the way water parts for a stone that has always been there."
  },
  {
    "speaker": "NARRATOR",
    "text": "He drew a short, blackened blade from beneath his cloak. The metal caught the green torchlight and held it like something alive."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "I'll admit, bench maker, you've impressed me. Freely and without reservation. A human who puts down my goblins with that little grace and that much fury is something I haven't seen in a long time."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "But impressing me and beating me are very different things."
  },
  {
    "speaker": "NARRATOR",
    "text": "The goblins pressed against the walls. The chamber became an arena. Somewhere in the crowd, a low rhythmic stamping began, feet against stone, building slowly. The sound filled the chamber like a second heartbeat."
  },
  {
    "speaker": "NARRATOR",
    "text": "The king rolled his shoulders and dropped into a stance that looked nothing like the lazy sprawl he'd worn on the throne. Low. Balanced. A fighter's stance, practised a thousand times over."
  },
  {
    "speaker": "GOBLIN KING",
    "text": "You want your bench. You want a name. Come and take them."
  },
  {
    "speaker": "BARRY",
    "text": "I didn't come here to impress anyone."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry raised his sword."
  }
]
)json"},

{"data/preShip.json", R"json([
  {
    "speaker": "NARRATOR",
    "text": "Barry walked the harbour road with a heavy purse and a heavier mind. The chandler's yard sat at the end of the quay, past the fish stalls and the rope-winders, where the smell of tar and salt replaced everything else."
  },
  {
    "speaker": "NARRATOR",
    "text": "The chandler was a striking woman with dark eyes and an easy posture, the kind of face Barry would have had trouble looking at directly on any other day. Today he barely noticed."
  },
  {
    "speaker": "CHANDLER",
    "text": "You're the bench maker. Off the road past the market."
  },
  {
    "speaker": "BARRY",
    "text": "I need a ship."
  },
  {
    "speaker": "NARRATOR",
    "text": "The chandler looked up from her ledger. A small breath left her nose, not quite a laugh."
  },
  {
    "speaker": "CHANDLER",
    "text": "A ship."
  },
  {
    "speaker": "BARRY",
    "text": "Crane's Reach."
  },
  {
    "speaker": "CHANDLER",
    "text": "Open water. Current pulls east, wind fights west, and the rocks along the approach have taken more ships than storms have."
  },
  {
    "speaker": "NARRATOR",
    "text": "She said it the way someone recites a thing they've said many times, not as a warning, just as fact. Then she held out her hand."
  },
  {
    "speaker": "CHANDLER",
    "text": "More gold, more hull. Simple as that."
  },
  {
    "speaker": "NARRATOR",
    "text": "Barry set his gold on the counter."
  }
])json"}
	};

	return data;
}
