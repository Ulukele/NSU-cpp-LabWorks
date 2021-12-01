cmake_minimum_required(VERSION 3.19)
project(3_SimplifiedMVC)

set(CMAKE_CXX_STANDARD 14)

set(
        PROJECT_FILES_
        main.cpp
        Models/BasePlayer.h Models/Card.h Models/BasePlayer.cpp Models/HumanPlayer.cpp Models/HumanPlayer.h View/Screen.cpp View/Screen.h Models/Board.h Control/Game.cpp Control/Game.h Models/EquityBotPlayer.cpp Models/EquityBotPlayer.h Models/Board.cpp View/Updater.cpp View/Updater.h Models/BaseModel.h)

add_executable(3_SimplifiedMVC ${PROJECT_FILES_})