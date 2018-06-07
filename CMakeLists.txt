cmake_minimum_required(VERSION 3.9.1)
project(AdvancedTopics3)

set(CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -Werror -pedantic-errors -DNDEBUG")

set (CMAKE_EXE_LINKER_FLAGS "-Wl,--no-as-needed -ldl -pthread")

add_executable(AdvancedTopics3 main.cpp Board.cpp Point.h FightInfo.cpp JokerChange.cpp Piece.cpp Piece.h PlayerAlgorithm.cpp PlayerAlgorithm.h GameManager.cpp GameManager.h GameStatus.cpp GameStatus.h EnumUtils.cpp EnumUtils.h PiecePosition.h Move.h AlgorithmRegistration.h AlgorithmRegistration.cpp TournamentManager.cpp TournamentManager.h MainAux.cpp MainAux.h)