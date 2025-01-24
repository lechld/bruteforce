//
// Created by Dominik Lechl on 24.01.25.
//

#include "PasswordGenerator.h"

#include <random>
#include <sstream>

constexpr int LEVEL_DIGITS = 3;
constexpr int LEVEL_LOWERCASE = 6;
constexpr int LEVEL_DIGITS_LOWERCASE = 8;
constexpr int LEVEL_DIGITS_LOWERCASE_UPPERCASE = 10;
constexpr int LEVEL_ALL_CHARACTERS = 14;

const std::string DIGITS = "0123456789";
const std::string LOWERCASE = "abcdefghijklmnopqrstuvwxyz";
const std::string UPPERCASE = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const std::string SPECIAL = "!@#$%^&*()-_=+<>?";

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

std::string PasswordGenerator::GenerateHint(const std::string &password) {
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

    return "Hint: Contains only " + join(components, ", ");
}

int PasswordGenerator::GetPasswordLength(const int level) {
    return level + 4;
}

std::string PasswordGenerator::GetCharacterPool(const int level) {
    if (level <= LEVEL_DIGITS) {
        return DIGITS;
    }
    if (level <= LEVEL_LOWERCASE) {
        return LOWERCASE;
    }
    if (level <= LEVEL_DIGITS_LOWERCASE) {
        return DIGITS + LOWERCASE;
    }
    if (level <= LEVEL_DIGITS_LOWERCASE_UPPERCASE) {
        return DIGITS + LOWERCASE + UPPERCASE;
    }
    if (level >= LEVEL_ALL_CHARACTERS) {
        return DIGITS + LOWERCASE + UPPERCASE + SPECIAL;
    }

    return DIGITS;
}

int PasswordGenerator::GetTimeBonus(int level) {
    if (level <= LEVEL_DIGITS) {
        return 30;
    }
    if (level <= LEVEL_LOWERCASE) {
        return 60;
    }
    if (level <= LEVEL_DIGITS_LOWERCASE) {
        return 90;
    }
    if (level <= LEVEL_DIGITS_LOWERCASE_UPPERCASE) {
        return 120;
    }
    if (level >= LEVEL_ALL_CHARACTERS) {
        return 200;
    }
    return 30;
}


std::string PasswordGenerator::join(const std::vector<std::string> &elements, const std::string &delimiter) {
    std::ostringstream result;
    for (size_t i = 0; i < elements.size(); ++i) {
        result << elements[i];
        if (i < elements.size() - 1) {
            result << delimiter;
        }
    }
    return result.str();
}
