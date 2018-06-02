#include <cstring>
#include "Piece.h"

//***************************************Utility Functions**************************

pieceType charToPieceType(char c) {
    switch (c) {
        case 'R':
            return ROCK;
        case 'P':
            return PAPER;
        case 'S':
            return SCISSORS;
        case 'B':
            return BOMB;
        case 'F':
            return FLAG;
        default:
            return EMPTY;
    }
}

char pieceTypeToChar(pieceType _pieceType){
    switch (_pieceType) {
        case ROCK:
            return 'R';
        case PAPER:
            return 'P';
        case SCISSORS:
            return 'S';
        case BOMB:
            return 'B';
        case FLAG:
            return 'F';
        default:
            return 'E';
    }
}

possiblePieceType charToPossiblePieceType(char c){
    switch (c) {
        case 'R':
            return pROCK;
        case 'P':
            return pPAPER;
        case 'S':
            return pSCISSORS;
        case 'B':
            return pBOMB;
        case 'F':
            return pFLAG;
        default:
            return pEMPTY;
    }
}

char possiblePieceTypeToChar(possiblePieceType _pPieceType){
    switch (_pPieceType) {
        case pROCK:
            return 'R';
        case pPAPER:
            return 'P';
        case pSCISSORS:
            return 'S';
        case pBOMB:
            return 'B';
        case pFLAG:
            return 'F';
        case pUNKNOWN:
            return 'U';
        default:
            return 'E';
    }
}


pieceType possiblePieceTypeToPieceType(possiblePieceType _possiblePiece){
    switch (_possiblePiece) {
        case pROCK:
            return ROCK;
        case pPAPER:
            return PAPER;
        case pSCISSORS:
            return SCISSORS;
        case pBOMB:
            return BOMB;
        case pFLAG:
            return FLAG;
        default:
            return EMPTY;
    }
}

bool isNumInRange(char* str, int rangeStart, int rangeEnd) {
    if (str == NULL || strlen(str)==0) {
        return false;
    }
    int n = strlen(str);
    for (int i = 0; i < n; i++) {
        //not valid digits
        if (!('0' <= str[i] && str[i] <= '9')) return false;
    }
    //str in a number
    int num = atoi(str);

    return (num >= rangeStart && num <= rangeEnd);
}

bool isValidPieceType(char Piece){
    switch (Piece) {
        case 'R':
        case 'P':
        case 'S':
        case 'B':
        case 'F':
        case 'J':
            return true;
        default:
            return false;
    }
}

bool isCharArrValidPieceType(char *c) {
    if(c == NULL) return false;
    if(strlen(c)==1){
        char tool = *c;
        return isValidPieceType(tool);
    }
    return false;
}

bool isValidJokerPieceType(char tool){
    switch (tool) {
        case 'R':
        case 'P':
        case 'S':
        case 'B':
            return true;
        default:
            return false;
    }
}

bool isCharArrValidJokerPieceType(char *c) {
    if(c == NULL) return false;
    if(strlen(c)==1){
        char tool = *c;
        return isValidJokerPieceType(tool);
    }
    return false;
}

//***************************************Member Functions**************************

bool Piece::canCapture(shared_ptr<Piece> other) {
    vector<pieceType> weakerPieces = this->getWeakerPieces();
    pieceType otherType = other->getType();
    for(pieceType weakPiece: weakerPieces){
        if(weakPiece == otherType)
            return true;
    }
    return false;
}