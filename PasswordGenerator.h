//
// Created by Dominik Lechl on 24.01.25.
//

#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <string>

class PasswordGenerator {
public:
    static std::string GeneratePassword(int level);
    static std::string GenerateHint(const std::string& password);
private:
    static int GetPasswordLength(int level);
    static std::string GetCharacterPool(int level);

    static std::string join(const std::vector<std::string>& elements, const std::string& delimiter);
};

#endif //PASSWORDGENERATOR_H
