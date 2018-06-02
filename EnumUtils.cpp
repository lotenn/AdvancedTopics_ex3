//
// Created by loten on 12/05/2018.
//

#include "EnumUtils.h"



int playerEnumToInt(playerEnum player){
    switch(player){
        case PLAYER_1:
            return 1;
        case PLAYER_2:
            return 2;
        default:
            return 0;
    }
}

playerEnum getOpposite(playerEnum player){
    switch(player){
        case PLAYER_1:
            return PLAYER_2;
        case PLAYER_2:
            return PLAYER_1;
        default:
            return NO_PLAYER;
    }
}

string playerEnumToString(playerEnum player){
    map<playerEnum , string> strings;
    strings[PLAYER_1] = "player 1";
    strings[PLAYER_2] = "player 2";
    strings[NO_PLAYER] = "no player";
    auto str = strings.find(player);
    return str != strings.end() ? str->second : "";
}

playerEnum intToPlayerEnum(int player){
    switch(player){
        case 1:
            return PLAYER_1;
        case 2:
            return PLAYER_2;
        default:
            return NO_PLAYER;
    }
}