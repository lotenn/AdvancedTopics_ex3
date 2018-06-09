#ifndef ADVANCEDTOPICS2_ENUMUTILS_H
#define ADVANCEDTOPICS2_ENUMUTILS_H

#include <string>
#include <map>
using namespace std;

//************************Player Enum ****************************************************
enum playerEnum {
    PLAYER_1 = 1,
    PLAYER_2 = 2,
    NO_PLAYER = 0
};

//************************End Game Reason Enum ****************************************************
enum endGameReason{
    NO_REASON = 0,
    NO_MORE_FLAGS = 1,
    NO_MOVING_PIECES = 2,
    NO_POSITIONING_FILE = 3,
    BAD_POSITIONING_FILE_INVALID = 4,
    BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS = 5,
    BAD_POSITIONING_FILE_TOO_MANY_PIECES = 6,
    BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION = 7,
    NO_MORE_MOVES = 8,
    BAD_MOVE_FILE_NOT_YOUR_PIECE = 9,
    BAD_MOVE_FILE_TOOL_CANT_MOVE = 10,
    BAD_MOVE_FILE_CELL_OCCUPIED = 11,
    BAD_MOVE_FILE_NOT_JOKER = 12,
    BAD_MOVE_FILE_INVALID = 13,
    DRAW_REACHED_MAX_NUM_OF_TURNS_WITH_NO_FIGHTS = 14,
    DRAW_POSITIONING_ENDED_WITH_NO_FLAGS = 15,
    DRAW_POSITIONING_ENDED_WITH_NO_MOVING_PIECES = 16,
    DRAW_BAD_POSITIONING_FILE_BOTH_PLAYERS = 17
};

int playerEnumToInt(playerEnum player);

playerEnum intToPlayerEnum(int player);

playerEnum getOpposite(playerEnum player);

#endif //ADVANCEDTOPICS2_ENUMUTILS_H
