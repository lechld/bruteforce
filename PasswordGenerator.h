//
// Created by Dominik Lechl on 24.01.25.
//

#ifndef PASSWORDGENERATOR_H
#define PASSWORDGENERATOR_H
#include <string>

class PasswordGenerator {
public:
    static std::string GeneratePassword(int level);
private:
    static int GetPasswordLength(int level);
    static std::string GetCharacterPool(int level);
};

#endif //PASSWORDGENERATOR_H
