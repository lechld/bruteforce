//
// Created by Dominik Lechl on 24.01.25.
//

#include "PasswordGenerator.h"

#include <random>
#include <sstream>

std::string PasswordGenerator::GeneratePassword(const int level) {
    const int passwordLength = GetPasswordLength(level);
    const std::string characterPool = GetCharacterPool(level);

    std::string password;
    std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> dist(0, characterPool.size() - 1);

    for (int i = 0; i < passwordLength; ++i) {
        password += characterPool[dist(generator)];
    }

    return password;
}

std::string PasswordGenerator::GenerateHint(const std::string& password) {
    std::vector<std::string> components;

    if (std::ranges::any_of(password, ::isdigit)) {
        components.push_back("digits");
    }
    if (std::ranges::any_of(password, ::islower)) {
        components.push_back("lowercase characters");
    }
    if (std::ranges::any_of(password, ::isupper)) {
        components.push_back("uppercase characters");
    }
    if (std::ranges::any_of(password, [](char c) { return !isalnum(c); })) {
        components.push_back("special characters");
    }

    return  "Contains " + join(components, ", ");
}

int PasswordGenerator::GetPasswordLength(const int level) {
    return level + 4;
}

std::string PasswordGenerator::GetCharacterPool(const int level) {
    const std::string digits = "0123456789";
    const std::string lowercase = "abcdefghijklmnopqrstuvwxyz";
    const std::string uppercase = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const std::string special = "!@#$%^&*()-_=+<>?";

    std::string pool;
    if (level <= 3) {
        pool = digits;
    } else if (level <= 6) {
        pool = lowercase;
    } else if (level <= 8) {
        pool = digits + lowercase;
    } else if (level <= 10) {
        pool = digits + lowercase + uppercase;
    } else if (level >= 14) {
        pool = digits + lowercase + uppercase + special;
    }

    return pool;
}

std::string PasswordGenerator::join(const std::vector<std::string>& elements, const std::string& delimiter) {
    std::ostringstream result;
    for (size_t i = 0; i < elements.size(); ++i) {
        result << elements[i];
        if (i < elements.size() - 1) {
            result << delimiter;
        }
    }
    return result.str();
}