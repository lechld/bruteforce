//
// Created by Dominik Lechl on 24.01.25.
//

#include "HighscoreManager.h"
#include <fstream>
#include <sstream>

constexpr int MAX_HIGHSCORES = 10;

void HighscoreManager::AddHighscore(const std::string &name, int score) {
    highscores.push_back({name, score});

    std::sort(highscores.begin(), highscores.end());

    if (highscores.size() > MAX_HIGHSCORES) {
        highscores.resize(MAX_HIGHSCORES);
    }
}

std::vector<HighscoreEntry> &HighscoreManager::GetHighscores() {
    return highscores;
}

bool HighscoreManager::LoadFromFile(const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    highscores.clear();
    std::string line;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string name;
        int score;

        if (std::getline(ss, name, ',') && (ss >> score)) {
            highscores.push_back({name, score});
        }
    }

    file.close();

    std::sort(highscores.begin(), highscores.end());
    if (highscores.size() > MAX_HIGHSCORES) {
        highscores.resize(MAX_HIGHSCORES);
    }

    return true;
}

bool HighscoreManager::SaveToFile(const std::string &filename) const {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (const auto &entry: highscores) {
        file << entry.name << "," << entry.score << "\n";
    }

    file.close();
    return true;
}
