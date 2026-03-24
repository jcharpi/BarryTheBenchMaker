"""
Pre-build script: reads all .json files from data/ and generates
include/EmbeddedData.h with their contents as raw string literals.
"""

import hashlib
import os
import sys

SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
PROJECT_ROOT = os.path.dirname(SCRIPT_DIR)
DATA_DIR = os.path.join(PROJECT_ROOT, "data")
OUTPUT_FILE = os.path.join(PROJECT_ROOT, "include", "EmbeddedData.h")

HEADER = """#pragma once
#include <string>
#include <unordered_map>

inline const std::unordered_map<std::string, std::string>& GetEmbeddedDialogue() {
\tstatic const std::unordered_map<std::string, std::string> data = {
"""

FOOTER = """
\t};

\treturn data;
}
"""

def main():
    entries = []

    for filename in sorted(os.listdir(DATA_DIR)):
        if not filename.endswith(".json"):
            continue
        # values.json is a reference doc, not dialogue
        if filename == "values.json":
            continue

        filepath = os.path.join(DATA_DIR, filename)
        with open(filepath, "r", encoding="utf-8") as f:
            content = f.read()

        # Use data/ prefix to match how the game references these files
        key = f"data/{filename}"
        entries.append(f'{{\"{key}\", R"json({content})json"}}')

    new_content = HEADER + ",\n\n".join(entries) + FOOTER

    # Only write if content actually changed, so MSBuild sees the new timestamp
    old_content = ""
    if os.path.exists(OUTPUT_FILE):
        with open(OUTPUT_FILE, "r", encoding="utf-8") as f:
            old_content = f.read()

    if new_content != old_content:
        with open(OUTPUT_FILE, "w", encoding="utf-8") as f:
            f.write(new_content)
        print(f"Generated {OUTPUT_FILE} with {len(entries)} dialogue files.")
    else:
        print(f"EmbeddedData.h is up to date ({len(entries)} dialogue files).")

if __name__ == "__main__":
    main()
