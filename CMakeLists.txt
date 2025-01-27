cmake_minimum_required(VERSION 3.29)
project(bruteforce)

set(CMAKE_CXX_STANDARD 20)

add_executable(bruteforce main.cpp
        MainFrame.cpp
        MainFrame.h
        MainMenuPanel.cpp
        MainMenuPanel.h
        GamePanel.cpp
        GamePanel.h
        HighscorePanel.cpp
        HighscorePanel.h
        RankEntryPanel.cpp
        RankEntryPanel.h
        PasswordInputCtrl.cpp
        PasswordInputCtrl.h
        PasswordGenerator.cpp
        PasswordGenerator.h
        HighscoreManager.cpp
        HighscoreManager.h
)

find_package(wxWidgets)
target_link_libraries(bruteforce wxWidgets::wxWidgets)
