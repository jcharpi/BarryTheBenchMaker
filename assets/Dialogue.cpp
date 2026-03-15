#include "../include/Dialogue.h"
#include <json/json.h>
#include <fstream>
#include <iostream>
#include <conio.h>

std::vector<DialogueEntry> LoadDialogue(const std::string& filepath) {
	std::vector<DialogueEntry> dialogue;
	std::ifstream file(filepath);

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filepath << std::endl;
		return dialogue;
	}

	Json::Value root;
	Json::Reader reader;

	if (!reader.parse(file, root)) {
		std::cerr << "Error: Failed to parse JSON file " << filepath << std::endl;
		return dialogue;
	}

	for (const Json::Value& entry : root) {
		std::string speaker = entry["speaker"].asString();
		std::string text = entry["text"].asString();
		dialogue.push_back(DialogueEntry{ speaker, text });
	}

	return dialogue;
}

void PlayDialogue(const std::vector<DialogueEntry>& dialogue) {
	for (const DialogueEntry& entry : dialogue) {
		system("cls");
		if (entry.speaker == "NARRATOR") {
			std::cout << "\n" << entry.text << "\n";
		} else {
			std::cout << "\n[" << entry.speaker << "]\n";
			std::cout << "\"" << entry.text << "\"\n";
		}

		std::cout << "\n\n[Press any key to continue]";
		(void)_getch();
	}

	system("cls");
}
