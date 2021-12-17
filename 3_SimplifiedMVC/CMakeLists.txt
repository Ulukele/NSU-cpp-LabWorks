cmake_minimum_required(VERSION 3.19)
project(3_SimplifiedMVC)

set(CMAKE_CXX_STANDARD 17)

set(
        PROJECT_FILES_
        main.cpp
        Models/BasePlayer.h Models/Card.h Models/BasePlayer.cpp Models/HumanPlayer.cpp Models/HumanPlayer.h View/Screen.cpp View/Screen.h Models/Board.h Control/Game.cpp Control/Game.h Models/EquityBotPlayer.cpp Models/EquityBotPlayer.h Models/Board.cpp View/Updater.h Models/BaseModel.h Models/Combinations.h Common/Common.cpp Common/Common.h Models/Card.cpp Common/Montecarlo.cpp Common/Montecarlo.h Common/Exception.h Models/BaseModel.cpp)

add_executable(3_SimplifiedMVC ${PROJECT_FILES_})