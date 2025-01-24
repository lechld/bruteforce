//
// Created by Dominik Lechl on 24.01.25.
//

#ifndef HIGHSCOREMANAGER_H
#define HIGHSCOREMANAGER_H
#include <string>

struct HighscoreEntry {
    std::string name;
    int score;

    bool operator<(const HighscoreEntry &other) const {
        return score > other.score;
    }
};

class HighscoreManager {
public:
    static HighscoreManager& GetInstance() {
        static HighscoreManager instance;
        return instance;
    }

    void AddHighscore(const std::string &name, int score);

    std::vector<HighscoreEntry> &GetHighscores();

    bool LoadFromFile(const std::string &filename);

    bool SaveToFile(const std::string &filename) const;

private:
    HighscoreManager() = default;
    std::vector<HighscoreEntry> highscores = {};
};

#endif //HIGHSCOREMANAGER_H
