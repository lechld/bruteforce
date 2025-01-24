//
// Created by Dominik Lechl on 24.01.25.
//

#include "PasswordGenerator.h"

#include <random>

std::string PasswordGenerator::GeneratePassword(int level) {
    int passwordLength = GetPasswordLength(level);
    std::string characterPool = GetCharacterPool(level);

    std::string password;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, characterPool.size() - 1);

    for (int i = 0; i < passwordLength; ++i) {
        password += characterPool[dist(generator)];
    }

    return password;
}

int PasswordGenerator::GetPasswordLength(const int level) {
    return level + 4;
}

std::string PasswordGenerator::GetCharacterPool(int level) {
    std::string digits = "0123456789";
    std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    std::string special = "!@#$%^&*()-_=+<>?";

    std::string pool;
    if (level == 1) {
        pool = digits;
    } else if (level == 2) {
        pool = lowercase;
    } else if (level == 3) {
        pool = digits + lowercase;
    } else if (level == 4) {
        pool = digits + lowercase + uppercase;
    } else if (level >= 5) {
        pool = digits + lowercase + uppercase + special;
    }

    return pool;
}

