#include "GameManager.h"
using namespace std;

int main(int argc, char* argv[]) {

    if(argc != 2){
        cout << "Invalid Command Line Arguments: Wrong num of arguments" << endl;
        return 0;
    }
    playerMode player1mode;
    playerMode player2mode;
    if(!GameManager::parsePlayerModes(argv[1], player1mode, player2mode)){
        cout << "Invalid Command Line Arguments: Wrong Format" << endl;
        return 0;
    }

    GameManager gameManager(player1mode, player2mode);
    gameManager.initGame();
    gameManager.positioningStage();
    if(!gameManager.getGameStatus().isGameOn()){
        gameManager.endGame();
        return 0;
    }
    gameManager.moveStage();
    gameManager.endGame();
    return 0;
}