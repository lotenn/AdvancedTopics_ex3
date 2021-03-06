#include "RSPPlayer_204540710.h"
#include "AlgorithmRegistration.h"

//*******************************************Auto Algorithm*****************************************************
RSPPlayer_204540710::RSPPlayer_204540710(){
    resetKnownBoard();
}


REGISTER_ALGORITHM(204540710)

bool PossiblePieces::canMove(){
    return getPossiblePiece() == pROCK || getPossiblePiece() == pSCISSORS || getPossiblePiece() == pPAPER;
}

void RSPPlayer_204540710::resetKnownBoard(){
    for(int i=0; i<N; i++)
        for(int j=0; j<M; j++)
            for(int k=0; k<2; k++)
                knownBoard[i][j][k].reset();
}

void RSPPlayer_204540710::getInitialPositions(int player, std::vector<unique_ptr<PiecePosition>>& vectorToFill){
    this->player = intToPlayerEnum(player);
    vectorToFill.push_back(make_unique<PiecePositionImp>(2, 9, 'R', NO_JOKER_CHANGE_SYMBOL));
    this->knownBoard[8][1][PRIMARY].setOptFlag(false);
    this->knownBoard[8][1][PRIMARY].setPlayer(this->player);
    this->knownBoard[8][1][PRIMARY].setPossiblePiece(pROCK);
    vectorToFill.push_back(make_unique<PiecePositionImp>(5, 10, 'R', NO_JOKER_CHANGE_SYMBOL));
    this->knownBoard[9][4][PRIMARY].setOptFlag(false);
    this->knownBoard[9][4][PRIMARY].setPlayer(this->player);
    this->knownBoard[9][4][PRIMARY].setPossiblePiece(pROCK);
    vectorToFill.push_back(make_unique<PiecePositionImp>(1, 10, 'P', NO_JOKER_CHANGE_SYMBOL));
    this->knownBoard[9][0][PRIMARY].setOptFlag(false);
    this->knownBoard[9][0][PRIMARY].setPlayer(this->player);
    this->knownBoard[9][0][PRIMARY].setPossiblePiece(pPAPER);
    vectorToFill.push_back(make_unique<PiecePositionImp>(2, 2, 'P', NO_JOKER_CHANGE_SYMBOL));
    this->knownBoard[1][1][PRIMARY].setOptFlag(false);
    this->knownBoard[1][1][PRIMARY].setPlayer(this->player);
    this->knownBoard[1][1][PRIMARY].setPossiblePiece(pPAPER);
    vectorToFill.push_back(make_unique<PiecePositionImp>(4, 9, 'P', NO_JOKER_CHANGE_SYMBOL));
    this->knownBoard[8][3][PRIMARY].setOptFlag(false);
    this->knownBoard[8][3][PRIMARY].setPlayer(this->player);
    this->knownBoard[8][3][PRIMARY].setPossiblePiece(pPAPER);
    vectorToFill.push_back(make_unique<PiecePositionImp>(4, 7, 'P', NO_JOKER_CHANGE_SYMBOL));
    this->knownBoard[6][3][PRIMARY].setOptFlag(false);
    this->knownBoard[6][3][PRIMARY].setPlayer(this->player);
    this->knownBoard[6][3][PRIMARY].setPossiblePiece(pPAPER);
    vectorToFill.push_back(make_unique<PiecePositionImp>(10, 9, 'P', NO_JOKER_CHANGE_SYMBOL));
    this->knownBoard[8][9][PRIMARY].setOptFlag(false);
    this->knownBoard[8][9][PRIMARY].setPlayer(this->player);
    this->knownBoard[8][9][PRIMARY].setPossiblePiece(pPAPER);
    vectorToFill.push_back(make_unique<PiecePositionImp>(1, 1, 'B', NO_JOKER_CHANGE_SYMBOL));
    this->knownBoard[0][0][PRIMARY].setOptFlag(false);
    this->knownBoard[0][0][PRIMARY].setPlayer(this->player);
    this->knownBoard[0][0][PRIMARY].setPossiblePiece(pBOMB);
    vectorToFill.push_back(make_unique<PiecePositionImp>(10, 10, 'B', NO_JOKER_CHANGE_SYMBOL));
    this->knownBoard[9][9][PRIMARY].setOptFlag(false);
    this->knownBoard[9][9][PRIMARY].setPlayer(this->player);
    this->knownBoard[9][9][PRIMARY].setPossiblePiece(pBOMB);
    vectorToFill.push_back(make_unique<PiecePositionImp>(3, 10, 'F', NO_JOKER_CHANGE_SYMBOL));
    this->knownBoard[9][2][PRIMARY].setOptFlag(true);
    this->knownBoard[9][2][PRIMARY].setPlayer(this->player);
    this->knownBoard[9][2][PRIMARY].setPossiblePiece(pFLAG);
    vectorToFill.push_back(make_unique<PiecePositionImp>(1, 4, 'J', 'S'));
    this->knownBoard[3][0][PRIMARY].setOptFlag(false);
    this->knownBoard[3][0][PRIMARY].setPlayer(this->player);
    this->knownBoard[3][0][PRIMARY].setPossiblePiece(pSCISSORS);
    this->knownBoard[3][0][PRIMARY].setIsJoker(true);
    vectorToFill.push_back(make_unique<PiecePositionImp>(9, 8, 'J', 'S'));
    this->knownBoard[7][8][PRIMARY].setOptFlag(false);
    this->knownBoard[7][8][PRIMARY].setPlayer(this->player);
    this->knownBoard[7][8][PRIMARY].setPossiblePiece(pSCISSORS);
    this->knownBoard[7][8][PRIMARY].setIsJoker(true);
}

void RSPPlayer_204540710::notifyOnInitialBoard(const Board& b, const std::vector<unique_ptr<FightInfo>>& fights){
    int opponentPlayer_int = playerEnumToInt(getOpposite(this->player));
    int row, col;

    //finding opponent player & update.
    for(int x=1; x <= M; x++){
        for(int y=1; y <= N; y++){
            PointImp point(x,y);
            if(b.getPlayer(point) == opponentPlayer_int){
                row = PointUtils::getRow(point);
                col = PointUtils::getCol(point);
                knownBoard[row][col][PRIMARY].reset();    //In case current position includes this player's piece
                knownBoard[row][col][PRIMARY].setPlayer(getOpposite(this->player));
                knownBoard[row][col][PRIMARY].setPossiblePiece(pUNKNOWN);
                knownBoard[row][col][PRIMARY].setOptFlag(true);
            }
        }
    }
    /*
     * Iterating through fights vector
     * If this->player won the fight, knownBoard is already updated
     * else, we update known board according to the winner (opponent or both lose)
     */
    int winner_int;
    char opponentPiece_char;
    for(int i=0; i < (int)fights.size(); i++){
        winner_int = fights[i]->getWinner();
        row = PointUtils::getRow(fights[i]->getPosition());
        col = PointUtils::getCol(fights[i]->getPosition());
        opponentPiece_char = fights[i]->getPiece(opponentPlayer_int);

        //opponent won
        if(winner_int == opponentPlayer_int) {
            knownBoard[row][col][PRIMARY].reset();
            knownBoard[row][col][PRIMARY].setPlayer(getOpposite(this->player));
            knownBoard[row][col][PRIMARY].setPossiblePiece(charToPossiblePieceType(opponentPiece_char));
            knownBoard[row][col][PRIMARY].setOptFlag(false);
        }
            //both lose
        else if(winner_int == playerEnumToInt(NO_PLAYER))
            knownBoard[row][col][PRIMARY].reset();
        else continue;  //this player won - known board is up2date
    }
}

void RSPPlayer_204540710::notifyOnOpponentMove(const Move& move){
    int fromCol, fromRow, toCol, toRow;
    fromRow = PointUtils::getRow(move.getFrom());
    fromCol = PointUtils::getCol(move.getFrom());
    toRow = PointUtils::getRow(move.getTo());
    toCol = PointUtils::getCol(move.getTo());

    //target point is empty
    if(knownBoard[toRow][toCol][PRIMARY].getPossiblePiece() == pEMPTY){
        knownBoard[toRow][toCol][PRIMARY] = knownBoard[fromRow][fromCol][PRIMARY];
        knownBoard[toRow][toCol][PRIMARY].setOptFlag(false);
    }
        //target point contains this player piece
    else{
        knownBoard[toRow][toCol][SECONDARY] = knownBoard[fromRow][fromCol][PRIMARY];
        knownBoard[toRow][toCol][SECONDARY].setOptFlag(false);
    }
    this->knownBoard[fromRow][fromCol][PRIMARY].reset();
}

void RSPPlayer_204540710::notifyFightResult(const FightInfo& fightInfo){
    int thisPlayer, opponentPlayer, col, row;
    thisPlayer = playerEnumToInt(this->player);
    opponentPlayer = playerEnumToInt(getOpposite(this->player));

    char opponentPiece = fightInfo.getPiece(opponentPlayer);
    row = PointUtils::getRow(fightInfo.getPosition());
    col = PointUtils::getCol(fightInfo.getPosition());

    //this player won the fight
    if(fightInfo.getWinner() == thisPlayer){
        if(knownBoard[row][col][PRIMARY].getPlayer() == this->player){
            knownBoard[row][col][SECONDARY].reset();
        }
        else{
            knownBoard[row][col][PRIMARY] = knownBoard[row][col][SECONDARY];
            knownBoard[row][col][SECONDARY].reset();
        }
    }
        //opponent won the fight
    else if(fightInfo.getWinner() == opponentPlayer){
        //primary contains losing piece
        if(knownBoard[row][col][PRIMARY].getPlayer() == this->player){
            knownBoard[row][col][PRIMARY] = this->knownBoard[row][col][SECONDARY];
            knownBoard[row][col][PRIMARY].setPossiblePiece(charToPossiblePieceType(opponentPiece));
            knownBoard[row][col][PRIMARY].setOptFlag(false);
            knownBoard[row][col][SECONDARY].reset();
        }
        else {    //secondary contains losing piece
            knownBoard[row][col][PRIMARY].setOptFlag(false);
			knownBoard[row][col][PRIMARY].setPossiblePiece(charToPossiblePieceType(opponentPiece));
            knownBoard[row][col][SECONDARY].reset();
        }
    }
        //both lose
    else{
        knownBoard[row][col][PRIMARY].reset();
        knownBoard[row][col][SECONDARY].reset();
    }
}

unique_ptr<Move> RSPPlayer_204540710::getMove(){
    //possible move of all this->player pieces
    int numOfMobilePieces = 0;
    vector<PointImp> possibleTargets[N][M];
    for(int i=0; i<N; i++) {
        for (int j = 0; j < M; j++) {
            if (knownBoard[i][j][PRIMARY].getPlayer() == this->player) {
                PointImp from(j+1,i+1);
                getPossibleTargets(from, possibleTargets[i][j], false);
                if(!possibleTargets[i][j].empty())
                    numOfMobilePieces++;
            }
        }
    }
    //looking to attack a possible-opponent-flag
    for(int i=0; i<N; i++) {
        for (int j = 0; j < M; j++) {
            if (!possibleTargets[i][j].empty()) {
                PointImp from(j + 1, i + 1);
                for (const auto &possibleTarget : possibleTargets[i][j]) {
                    int targetRow = PointUtils::getRow(possibleTarget), targetCol = PointUtils::getCol(possibleTarget);
                    if (knownBoard[targetRow][targetCol][PRIMARY].getPlayer() == getOpposite(this->player) &&
                        knownBoard[targetRow][targetCol][PRIMARY].isOptFlag()) {
                        performPlayerMove(from, possibleTarget);
                        return move(make_unique<MoveImp>(from.getX(), from.getY(), possibleTarget.getX(),
                                                         possibleTarget.getY()));
                    }
                }
            }
        }
    }

    //looking to attack a weaker piece of the opponent
    for(int i=0; i<N; i++) {
        for (int j = 0; j < M; j++) {
            if (!possibleTargets[i][j].empty()) {
                PointImp from(j + 1, i + 1);
                int fromRow = PointUtils::getRow(from), fromCol =  PointUtils::getCol(from);
                possiblePieceType playerPossiblePiece = knownBoard[fromRow][fromCol][PRIMARY].getPossiblePiece();

                for (const auto &possibleTarget : possibleTargets[i][j]) {
                    int targetRow = PointUtils::getRow(possibleTarget);
                    int targetCol = PointUtils::getCol(possibleTarget);
                    possiblePieceType opponentPossiblePiece = knownBoard[targetRow][targetCol][PRIMARY].getPossiblePiece();

                    if (knownBoard[targetRow][targetCol][PRIMARY].getPlayer() == getOpposite(this->player) &&
                        opponentPossiblePiece != pUNKNOWN &&
                        canCapture(playerPossiblePiece, opponentPossiblePiece))
                    {
                        performPlayerMove(from, possibleTarget);
                        return move(make_unique<MoveImp>(from.getX(), from.getY(), possibleTarget.getX(),
                                                         possibleTarget.getY()));
                    }
                }
            }
        }
    }

    //escaping possible attack of the opponent
    for(int i=0; i<N; i++) {
        for (int j = 0; j < M; j++) {
            if (possibleTargets[i][j].size()>1) {   //if there is a single move possible - no escape option available
                PointImp from(j + 1, i + 1);
                int fromRow = PointUtils::getRow(from), fromCol =  PointUtils::getCol(from);
                possiblePieceType playerPossiblePiece = knownBoard[fromRow][fromCol][PRIMARY].getPossiblePiece();

                for (const auto &possibleTarget : possibleTargets[i][j]) {
                    int targetRow = PointUtils::getRow(possibleTarget);
                    int targetCol = PointUtils::getCol(possibleTarget);
                    possiblePieceType opponentPossiblePiece = knownBoard[targetRow][targetCol][PRIMARY].getPossiblePiece();
                    //if opponent can capture this player's piece
                    if (knownBoard[targetRow][targetCol][PRIMARY].getPlayer() == getOpposite(this->player) &&
                        opponentPossiblePiece != pUNKNOWN &&
                        canCapture(opponentPossiblePiece, playerPossiblePiece))
                    {
                        //looking for empty point to escape to
                        for (const auto &possibleEscapeTarget : possibleTargets[i][j]){
                            int possibleEscapeTargetRow = PointUtils::getRow(possibleEscapeTarget);
                            int possibleEscapeTargetCol = PointUtils::getCol(possibleEscapeTarget);
                            if(knownBoard[possibleEscapeTargetRow][possibleEscapeTargetCol][PRIMARY].getPossiblePiece() == pEMPTY) {
                                performPlayerMove(from, possibleEscapeTarget);
                                return move(make_unique<MoveImp>(from.getX(), from.getY(), possibleEscapeTarget.getX(),
                                                                 possibleEscapeTarget.getY()));
                            }
                        }
                    }
                }
            }
        }
    }
    //randomly choose a mobile piece
    if(numOfMobilePieces != 0) {
        std::srand(std::time(nullptr));
        int randPieceNumber = rand() % numOfMobilePieces;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < M; j++) {
                if (!possibleTargets[i][j].empty()) {   //if the piece is mobile
                    if (randPieceNumber == 0) {            //reached random piece needed
                        int randMoveNumber = rand() % possibleTargets[i][j].size();
                        PointImp from(j + 1, i + 1);
                        PointImp *target = &possibleTargets[i][j][randMoveNumber];

                        performPlayerMove(from, *target);
                        return move(make_unique<MoveImp>(from.getX(), from.getY(), target->getX(),
                                                         target->getY()));
                    } else
                        randPieceNumber--;
                }
            }
        }
    }
    //no legal move
    return move(make_unique<MoveImp>(INVALID_COORD,INVALID_COORD,INVALID_COORD,INVALID_COORD));
}

void RSPPlayer_204540710::performPlayerMove(const PointImp &from, const PointImp &to) {
    int fromRow = PointUtils::getRow(from), fromCol = PointUtils::getCol(from);
    int targetRow = PointUtils::getRow(to), targetCol = PointUtils::getCol(to);
    int key = knownBoard[targetRow][targetCol][PRIMARY].getPossiblePiece() == pEMPTY ?
              PRIMARY : SECONDARY;
    knownBoard[targetRow][targetCol][key] = knownBoard[fromRow][fromCol][PRIMARY];
    knownBoard[fromRow][fromCol][PRIMARY].reset();
}

void RSPPlayer_204540710::getPossibleTargets(const PointImp& point, vector<PointImp>& targetsToFill, bool jokerChange){
    int row, col;
    row = PointUtils::getRow(point);
    col = PointUtils::getCol(point);

    //check if the piece can actually move
    if(!jokerChange && !(knownBoard[row][col]->canMove()))
        return;

    //left target
    if(col != LEFTMOST_COL){
        if(knownBoard[row][col-1]->getPlayer() != this->player)
            targetsToFill.emplace_back(point.getX()-1, point.getY());
    }
    //right target
    if(col != RIGHTMOST_COL){
        if(knownBoard[row][col+1]->getPlayer() != this->player)
            targetsToFill.emplace_back(point.getX()+1, point.getY());
    }
    //upper target
    if(row != UPMOST_ROW){
        if(knownBoard[row+1][col]->getPlayer() != this->player)
            targetsToFill.emplace_back(point.getX(), point.getY()+1);
    }
    //lower target
    if(row != DOWNMOST_ROW){
        if(knownBoard[row-1][col]->getPlayer() != this->player)
            targetsToFill.emplace_back(point.getX(), point.getY()-1);
    }
}


bool RSPPlayer_204540710::canCapture(possiblePieceType _playerPiece, possiblePieceType _opponentPiece){
    pieceType playerPiece = possiblePieceTypeToPieceType(_playerPiece);
    pieceType opponentPiece = possiblePieceTypeToPieceType(_opponentPiece);
    vector<pieceType> playerWeakerPieces = getKnownWeakerPieces(playerPiece);
    vector<pieceType> opponentWeakerPieces = getKnownWeakerPieces(opponentPiece);

    for(int i=0; i<(int)playerWeakerPieces.size(); i++){             //looking for opponent piece in player's weakerPieces
        if(playerWeakerPieces[i] == opponentPiece){             //found that opponent piece is weaker than player's piece
            for(int j=0; j<(int)opponentWeakerPieces.size(); j++){   //looking for player's piece in opponents weaker
                if(opponentWeakerPieces[j] == playerPiece){     //player's piece is also weaker than opponent - battle will end with both lose
                    return false;
                }
            }
            return true;        //opponent is weaker than player
        }
    }
    return false;               //opponent piece is not in player's weaker pieces
}

vector<pieceType> RSPPlayer_204540710::getKnownWeakerPieces(pieceType playerPiece) const {
    switch(playerPiece){
        case SCISSORS:
            return ScissorsPiece(player).getWeakerPieces();
        case ROCK:
            return RockPiece(player).getWeakerPieces();
        case PAPER:
            return PaperPiece(player).getWeakerPieces();
        case FLAG:
            return FlagPiece(player).getWeakerPieces();
        case BOMB:
            return BombPiece(player).getWeakerPieces();
        default:
            return EmptyPiece().getWeakerPieces();
    }
}

unique_ptr<JokerChange> RSPPlayer_204540710::getJokerChange(){
    for(int i=0; i<N; i++){
        for(int j=0; j<M; j++){
            PossiblePieces *possibleJokerPiece = &knownBoard[i][j][PRIMARY];
            if(possibleJokerPiece->getPlayer() == this->player && possibleJokerPiece->IsJoker()){
                PointImp jokerPosition(j+1,i+1);
                vector<PointImp> possibleThreats;
                getPossibleTargets(jokerPosition, possibleThreats, true);
                if(!possibleThreats.empty()){
                    for(int k=0; k<(int)possibleThreats.size(); k++) {
                        int threatRow = PointUtils::getRow(possibleThreats[k]);
                        int threatCol = PointUtils::getCol(possibleThreats[k]);
                        possiblePieceType threatType = knownBoard[threatRow][threatCol][PRIMARY].getPossiblePiece();
                        playerEnum threatPlayer = knownBoard[threatRow][threatCol][PRIMARY].getPlayer();

                        if(threatPlayer == getOpposite(this->player)&& threatType != pUNKNOWN) {
                            possiblePieceType newJokerRep = getJokerRepStrongerThan(threatType);
                            possibleJokerPiece->setPossiblePiece(newJokerRep);
							return move(make_unique<JokerChangeImp>(jokerPosition.getX(),
                                                                    jokerPosition.getY(),
                                                                    possiblePieceTypeToChar(newJokerRep)));
                        }
                    }
                }
            }
        }
    }
    return nullptr;
}

possiblePieceType RSPPlayer_204540710::getJokerRepStrongerThan(const possiblePieceType &threatType) const {
    switch(threatType){
        case pPAPER:
            return pSCISSORS;
        case pSCISSORS:
            return pROCK;
        case pROCK:
            return pPAPER;
        default:
            return pEMPTY;
    }
}

//void RSPPlayer_204540710::printKnownBoard(){
//    string str;
//    for (int row = 0; row < N; row++) {
//        for (int col = 0; col < M; col++){
//			char pChar = possiblePieceTypeToChar(knownBoard[row][col][PRIMARY].getPossiblePiece());
//            str += (knownBoard[row][col][PRIMARY].getPlayer() == PLAYER_2 ? tolower(pChar) : pChar);
//			str+= " ";
//        }
//        if(row != N-1)
//            str+="\n";
//    }
//    cout << str << endl;
//}

