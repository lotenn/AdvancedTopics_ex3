//
// Created by loten on 12/05/2018.
//

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
    NO_REASON,
    NO_MORE_FLAGS,
    NO_MOVING_PIECES,
    NO_POSITIONING_FILE,
    BAD_POSITIONING_FILE_INVALID,
    BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS,
    BAD_POSITIONING_FILE_TOO_MANY_PIECES,
    BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION,
    NO_MORE_MOVES,
    BAD_MOVE_FILE_NOT_YOUR_PIECE,
    BAD_MOVE_FILE_TOOL_CANT_MOVE,
    BAD_MOVE_FILE_CELL_OCCUPIED,
    BAD_MOVE_FILE_NOT_JOKER,
    BAD_MOVE_FILE_INVALID,
    DRAW_REACHED_MAX_NUM_OF_TURNS_WITH_NO_FIGHTS,
    DRAW_POSITIONING_ENDED_WITH_NO_FLAGS,
    DRAW_POSITIONING_ENDED_WITH_NO_MOVING_PIECES,
    DRAW_BAD_POSITIONING_FILE_BOTH_PLAYERS
};



int playerEnumToInt(playerEnum player);

playerEnum intToPlayerEnum(int player);

playerEnum getOpposite(playerEnum player);

string playerEnumToString(playerEnum player);

enum playerMode{
    AUTO_PLAYER = 0,
    FILE_PLAYER = 1
};






#endif //ADVANCEDTOPICS2_ENUMUTILS_H
