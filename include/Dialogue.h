#pragma once
#include <string>
#include <vector>

struct DialogueEntry {
	std::string speaker;
	std::string text;
};

std::vector<DialogueEntry> LoadDialogue(const std::string& filepath);
void PlayDialogue(const std::vector<DialogueEntry>& dialogue);
