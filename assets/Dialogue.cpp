#include <conio.h>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <sstream>

#include "../include/Dialogue.h"
#include "../include/EmbeddedData.h"

static std::vector<DialogueEntry> ParseDialogueJson(const Json::Value& root) {
	std::vector<DialogueEntry> dialogue;
	for (const Json::Value& entry : root) {
		std::string speaker = entry["speaker"].asString();
		std::string text;
		if (entry.isMember("lines")) {
			for (const Json::Value& line : entry["lines"]) {
				text += line.asString() + "\n";
			}
		} else {
			text = entry["text"].asString();
		}
		dialogue.push_back(DialogueEntry{ speaker, text });
	}
	return dialogue;
}

std::vector<DialogueEntry> LoadDialogue(const std::string& filepath) {
	Json::Value root;
	Json::Reader reader;

	// Try embedded data first
	const auto& embeddedData = GetEmbeddedDialogue();
	auto embedded = embeddedData.find(filepath);
	if (embedded != embeddedData.end()) {
		if (reader.parse(embedded->second, root)) {
			return ParseDialogueJson(root);
		}
		std::cerr << "Error: Failed to parse embedded dialogue for " << filepath << std::endl;
		return {};
	}

	// Fall back to file
	std::ifstream file(filepath);
	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << filepath << std::endl;
		return {};
	}

	if (!reader.parse(file, root)) {
		std::cerr << "Error: Failed to parse JSON file " << filepath << std::endl;
		return {};
	}

	return ParseDialogueJson(root);
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
