//
// Created by loten on 20/04/2018.
//

#include "Board.h"

void BoardImp::clearBoard(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            board[i][j] = emptyPiece;
        }
    }
}

string BoardImp::boardToString(){
    string str;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < M; col++){
            str+= this->board[row][col]->toChar();
        }
        if(row != N-1)
            str+="\n";
    }
    return str;
}

