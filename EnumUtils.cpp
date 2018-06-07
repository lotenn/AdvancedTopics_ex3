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