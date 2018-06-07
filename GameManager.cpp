#include "GameManager.h"

//********************************************************************************************

GameManager::GameManager(unique_ptr<PlayerAlgorithm> _player1, unique_ptr<PlayerAlgorithm> _player2){
    this->player1 = move(_player1);
    this->player2 = move(_player2);

    //creating the game pieces
    int toolIndex = 0;
    for(int i=toolIndex; toolIndex < (i+NUM_OF_R); toolIndex++){
        player1Pieces.push_back(make_shared<RockPiece>(PLAYER_1));
        player2Pieces.push_back(make_shared<RockPiece>(PLAYER_2));
    }

    for(int i=toolIndex; toolIndex < (i+NUM_OF_P); toolIndex++){
        player1Pieces.push_back(make_shared<PaperPiece>(PLAYER_1));
        player2Pieces.push_back(make_shared<PaperPiece>(PLAYER_2));
    }

    for(int i=toolIndex; toolIndex < (i+NUM_OF_S); toolIndex++){
        player1Pieces.push_back(make_shared<ScissorsPiece>(PLAYER_1));
        player2Pieces.push_back(make_shared<ScissorsPiece>(PLAYER_2));
    }

    for(int i=toolIndex; toolIndex < (i+NUM_OF_B); toolIndex++){
        player1Pieces.push_back(make_shared<BombPiece>(PLAYER_1));
        player2Pieces.push_back(make_shared<BombPiece>(PLAYER_2));
    }

    for(int i=toolIndex; toolIndex < (i+NUM_OF_J); toolIndex++){
        player1Pieces.push_back(make_shared<JokerPiece>(PLAYER_1));
        player2Pieces.push_back(make_shared<JokerPiece>(PLAYER_2));
    }

    for(int i=toolIndex; toolIndex < (i+NUM_OF_F); toolIndex++){
        player1Pieces.push_back(make_shared<FlagPiece>(PLAYER_1));
        player2Pieces.push_back(make_shared<FlagPiece>(PLAYER_2));
    }
}

bool GameManager::performBattle(const Point& point, shared_ptr<Piece> source, shared_ptr<Piece> target){
    bool wasFight = false, sourceWin = source->canCapture(target), targetWin = target->canCapture(source);
    char player1Piece = '#', player2Piece = '#';
    playerEnum winner = NO_PLAYER;
    if((source->getPlayer() == PLAYER_1 && target->getPlayer() == PLAYER_2) ||
       (source->getPlayer() == PLAYER_2 && target->getPlayer() == PLAYER_1)){
        wasFight = true;
        player1Piece = source->getPlayer() == PLAYER_1 ?
                       pieceTypeToChar(source->getType()) : pieceTypeToChar(target->getType());
        player2Piece = target->getPlayer() == PLAYER_2 ?
                       pieceTypeToChar(target->getType()) : pieceTypeToChar(source->getType());
    }
    if(sourceWin && targetWin){
        source->removePiece();
        target->removePiece();
        board.setPiece(point, board.getEmptyPiece());
    }
    else if(sourceWin){
        source->placePiece();
        target->removePiece();
        winner = source->getPlayer();
        board.setPiece(point, source);
    }
    else{
        target->placePiece();
        source->removePiece();
        winner = target->getPlayer();
        board.setPiece(point, target);
    }
    fightInfo.setPosition(point.getX(), point.getY());
    fightInfo.setPlayer1Piece(player1Piece);
    fightInfo.setPlayer2Piece(player2Piece);
    fightInfo.setWinner(winner);
    return wasFight;
}

bool GameManager::executeMove(unique_ptr<Move> move){
    //No more moves for this player
    if(move->getFrom().getX() == INVALID_COORD){
        gameStatus.setGameOff();
        gameStatus.setMainReason(NO_MORE_MOVES);
        return false;
    }

    const Point *sourcePoint = &move->getFrom(), *targetPoint = &move->getTo();
    shared_ptr<Piece> sourcePiece = board.getPiece(*sourcePoint), targetPiece = board.getPiece(*targetPoint);
    if(sourcePiece->getPlayer() != this->currentPlayer){
        gameStatus.setGameOff();
        gameStatus.setMainReason(BAD_MOVE_FILE_NOT_YOUR_PIECE);
         return false;
    }
    else if(!sourcePiece->canMove(*sourcePoint, *targetPoint)){
        gameStatus.setGameOff();
        gameStatus.setMainReason(BAD_MOVE_FILE_TOOL_CANT_MOVE);
        return false;
    }
    else if(sourcePiece->getPlayer() == targetPiece->getPlayer()){
        gameStatus.setGameOff();
        gameStatus.setMainReason(BAD_MOVE_FILE_CELL_OCCUPIED);
        return false;
    }
    else{
        board.setPiece(*sourcePoint, board.getEmptyPiece());
        return performBattle(*targetPoint, sourcePiece, targetPiece);
    }
}

void GameManager::executeJoker(unique_ptr<JokerChange> jokerChange){
    if(jokerChange == nullptr){return;}  //no joker command in this line
    pieceType joker_new_type = charToPieceType(jokerChange->getJokerNewRep());
    shared_ptr<Piece> jokerPiece = board.getPiece(jokerChange->getJokerChangePosition());
    jokerPiece->setJoker(joker_new_type, gameStatus);
}

void GameManager::validatePositioningVector(playerEnum player, vector<unique_ptr<PiecePosition>>&  piecePositions){
    //No positioning file or empty file
    if (piecePositions.empty()) {
        gameStatus.setGameOff();
        gameStatus.setMainReason(NO_POSITIONING_FILE);
        gameStatus.setLoser(player);
        return;
    }

    bool alreadyPositioned[N][M];
    memset(alreadyPositioned, 0, sizeof(bool) * M * N);
    int rockCounter = NUM_OF_R,
            scissorsCounter = NUM_OF_S,
            paperCounter = NUM_OF_P,
            flagCounter = NUM_OF_F,
            bombCounter = NUM_OF_B,
            jokerCounter = NUM_OF_J;
    //iterating through the vector
   for(int i=0; i<(int)piecePositions.size(); i++) {
       //Invalid command
       if (piecePositions[i] == nullptr) {
           player == PLAYER_1 ? gameStatus.setReason1(BAD_POSITIONING_FILE_INVALID)
                              : gameStatus.setReason2(BAD_POSITIONING_FILE_INVALID);
           gameStatus.setGameOff();
           return;
       }

       int row = PointUtils::getRow(piecePositions[i]->getPosition());
       int col = PointUtils::getCol(piecePositions[i]->getPosition());

       //current point already contains same winner's tool
       if (alreadyPositioned[row][col]) {
           player == PLAYER_1 ? gameStatus.setReason1(BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION)
                              : gameStatus.setReason2(BAD_POSITIONING_FILE_DUPLICATE_CELL_POSITION);
           gameStatus.setGameOff();
           return;
       }
       //regular command
       if (piecePositions[i]->getJokerRep() == NO_JOKER_CHANGE_SYMBOL) {
           switch (piecePositions[i]->getPiece()) {
               case 'R':
                   rockCounter--;
                   break;
               case 'S':
                   scissorsCounter--;
                   break;
               case 'P':
                   paperCounter--;
                   break;
               case 'F':
                   flagCounter--;
                   break;
               default:
                   bombCounter--;
                   break;
           }

           //out of tools
           if (rockCounter < 0 || scissorsCounter < 0 || paperCounter < 0 || flagCounter < 0 || bombCounter < 0) {
               player == PLAYER_1 ? gameStatus.setReason1(BAD_POSITIONING_FILE_TOO_MANY_PIECES)
                                  : gameStatus.setReason2(BAD_POSITIONING_FILE_TOO_MANY_PIECES);
               gameStatus.setGameOff();
               return;
           }
       }
       //joker command
       else {
           jokerCounter--;
           //out of tools
           if (jokerCounter < 0) {
               player == PLAYER_1 ? gameStatus.setReason1(BAD_POSITIONING_FILE_TOO_MANY_PIECES)
                                  : gameStatus.setReason2(BAD_POSITIONING_FILE_TOO_MANY_PIECES);
               gameStatus.setGameOff();
               return;
           }
       }
       alreadyPositioned[row][col] = true;
   }
    //vector ended with not enough flags positioned
    if (flagCounter != 0) {
        player == PLAYER_1 ? gameStatus.setReason1(BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS)
                           : gameStatus.setReason2(BAD_POSITIONING_FILE_NOT_ENOUGH_FLAGS);
        gameStatus.setGameOff();
    }
}

void GameManager::initGame(){
    currentPlayer = PLAYER_1;
    gameStatus.reset();
    board.clearBoard();
    for(shared_ptr<Piece> piece: player1Pieces)
        piece->removePiece();
    for(shared_ptr<Piece> piece: player2Pieces)
        piece->removePiece();
}

void GameManager::setPlayerPieces(const vector<unique_ptr<PiecePosition>> &piecePositions, playerEnum player,
                                  vector<unique_ptr<FightInfo>>& fights){
    vector<shared_ptr<Piece>> *playerPieces;
    if(player == PLAYER_1){playerPieces = &player1Pieces;}
    else{playerPieces = &player2Pieces;}

    for(int i=0; i < (int)piecePositions.size(); i++){
        bool wasFight = false;
        if(piecePositions[i]->getJokerRep() == NO_JOKER_CHANGE_SYMBOL){
            pieceType _pieceType = charToPieceType(piecePositions[i]->getPiece());
            for(shared_ptr<Piece> piece: *(playerPieces)){
                if(!piece->IsPositioned() && !piece->isJoker() && piece->getType() == _pieceType){
                    wasFight = performBattle(piecePositions[i]->getPosition(), piece,
                                             board.getPiece(piecePositions[i]->getPosition()));
                    if(wasFight)
                        fights.push_back(move(make_unique<FightInfoImp>(piecePositions[i]->getPosition(),
                                                                   fightInfo.getPiece(1),
                                                                   fightInfo.getPiece(2),
                                                                   fightInfo.getWinner() == 1 ? PLAYER_1 : PLAYER_2)));
                break;
                }
            }
        }
        else{
            pieceType _pieceType = charToPieceType(piecePositions[i]->getJokerRep());
            for(shared_ptr<Piece> piece: *(playerPieces)){
                if(!piece->IsPositioned() && piece->isJoker()){
                    piece->setJoker(_pieceType, gameStatus);
                    piece-> placePiece();
                    wasFight = performBattle(piecePositions[i]->getPosition(), piece,
                                             board.getPiece(piecePositions[i]->getPosition()));
                    if(wasFight)
                        fights.push_back(move(make_unique<FightInfoImp>(piecePositions[i]->getPosition(),
                                                                   fightInfo.getPiece(1),
                                                                   fightInfo.getPiece(2),
                                                                   fightInfo.getWinner() == 1 ? PLAYER_1 : PLAYER_2)));
                break;
                }
            }
        }
    }
}

bool GameManager::containsMovingPieces(vector<shared_ptr<Piece>>& playerPieces){
    for(shared_ptr<Piece> piece: playerPieces) {
        if (piece->IsPositioned() && piece->canMove())
            return true;
    }
    return false;
}

bool GameManager::containsFlags(vector<shared_ptr<Piece>>& playerPieces){
    for(shared_ptr<Piece> piece: playerPieces) {
        if (piece->IsPositioned() && piece->getType() == FLAG)
            return true;
    }
    return false;
}

void GameManager::positioningStage(){
    vector<unique_ptr<FightInfo>> fights;
    vector<unique_ptr<PiecePosition>> player1PiecePosition, player2PiecePosition;
    player1->getInitialPositions(1, player1PiecePosition);
    player2->getInitialPositions(2, player2PiecePosition);
    validatePositioningVector(PLAYER_1, player1PiecePosition);
    //no pos. file or empty pos. file
    if(gameStatus.getMainReason() == NO_POSITIONING_FILE){return;}

    validatePositioningVector(PLAYER_2, player2PiecePosition);
    //no pos. file or empty pos. file
    if(gameStatus.getMainReason() == NO_POSITIONING_FILE){return;}

    if(!gameStatus.isGameOn()){
        //if there was a problematic positioning file and the game ended.
        if(gameStatus.getReason1() != NO_REASON && gameStatus.getReason2() != NO_REASON) {
            gameStatus.setMainReason(DRAW_BAD_POSITIONING_FILE_BOTH_PLAYERS);
            return;
        }
        else if(gameStatus.getReason1() != NO_REASON){
            gameStatus.setMainReason(gameStatus.getReason1());
            gameStatus.setWinner(PLAYER_2);
            gameStatus.setLoser(PLAYER_1);
            return;
        }
        else{
            gameStatus.setMainReason(gameStatus.getReason2());
            gameStatus.setWinner(PLAYER_1);
            gameStatus.setLoser(PLAYER_2);
            return;
        }
    }
    setPlayerPieces(player1PiecePosition, PLAYER_1, fights);
    setPlayerPieces(player2PiecePosition, PLAYER_2, fights);

    positioningCheckGameEnd();

    if(gameStatus.isGameOn()){
       player1->notifyOnInitialBoard(board, fights);
       player2->notifyOnInitialBoard(board, fights);
    }
}

void GameManager::positioningCheckGameEnd() {
    bool player1HasFlags, player2HasFlags, player1HasMovingPieces, player2HasMovingPieces, player1Loss, player2Loss;
    player1HasFlags = containsFlags(player1Pieces);
    player1HasMovingPieces = containsMovingPieces(player1Pieces);
    player2HasFlags = containsFlags(player2Pieces);
    player2HasMovingPieces = containsMovingPieces(player2Pieces);
    player1Loss = !player1HasFlags || !player1HasMovingPieces;
    player2Loss = !player2HasFlags || !player2HasMovingPieces;

    // in case of draw
    if(player1Loss && player2Loss){
        gameStatus.setGameOff();
        if(!player1HasFlags){
            gameStatus.setMainReason(DRAW_POSITIONING_ENDED_WITH_NO_FLAGS);
            gameStatus.setReason1(NO_MORE_FLAGS);
            gameStatus.setReason2(NO_MORE_FLAGS);
        }
        else{
            gameStatus.setMainReason(DRAW_POSITIONING_ENDED_WITH_NO_MOVING_PIECES);
            gameStatus.setReason1(NO_MOVING_PIECES);
            gameStatus.setReason2(NO_MOVING_PIECES);
        }
        return;
    }
    //single winner
    else if(player1Loss) {
        gameStatus.setGameOff();
        gameStatus.setWinner(PLAYER_2);
        gameStatus.setLoser(PLAYER_1);
        if(!player1HasFlags){
            gameStatus.setMainReason(NO_MORE_FLAGS);
            gameStatus.setReason1(NO_MORE_FLAGS);
        }
        else{
            gameStatus.setMainReason(NO_MOVING_PIECES);
            gameStatus.setReason1(NO_MOVING_PIECES);
        }
        return;
    }
    else if(player2Loss){
        gameStatus.setGameOff();
        gameStatus.setWinner(PLAYER_1);
        gameStatus.setLoser(PLAYER_2);
        if(!player2HasFlags){
            gameStatus.setMainReason(NO_MORE_FLAGS);
            gameStatus.setReason2(NO_MORE_FLAGS);
        }
        else{
            gameStatus.setMainReason(NO_MOVING_PIECES);
            gameStatus.setReason2(NO_MOVING_PIECES);
        }
    }
}

void GameManager::moveStage(){
    int numOfTurnsWithNoFight = 0;

    while(numOfTurnsWithNoFight < MAX_TURNS_WITH_NO_FIGHTS){
        numOfTurnsWithNoFight++;

        //player 1 turn
        currentPlayer = PLAYER_1;
        //player 1 lost - no more moving pieces
        if(!containsMovingPieces(player1Pieces)){
            gameStatus.setGameOff();
            gameStatus.setWinner(PLAYER_2);
            gameStatus.setLoser(PLAYER_1);
            gameStatus.setMainReason(NO_MOVING_PIECES);
            return;
        }

        unique_ptr<Move> player1Move  = player1->getMove();
        if(player1Move == nullptr){
            gameStatus.setGameOff();
            gameStatus.setMainReason(BAD_MOVE_FILE_INVALID);
            gameStatus.setWinner(PLAYER_2);
            gameStatus.setLoser(PLAYER_1);
            return;
        }

        MoveImp currentMove = MoveImp(player1Move->getFrom().getX(),
                                   player1Move->getFrom().getY(),
                                   player1Move->getTo().getX(),
                                   player1Move->getTo().getY());

        bool wasFight = executeMove(move(player1Move));
        //player 1 lost - bad move file
        if(!gameStatus.isGameOn()){
            gameStatus.setWinner(PLAYER_2);
            gameStatus.setLoser(PLAYER_1);
            return;
        }
        player2->notifyOnOpponentMove(currentMove);
        if(wasFight){
            numOfTurnsWithNoFight = 0;
            player1->notifyFightResult(fightInfo);
            player2->notifyFightResult(fightInfo);
        }
        executeJoker(player1->getJokerChange());
        if(!gameStatus.isGameOn()){
            gameStatus.setWinner(PLAYER_2);
            gameStatus.setLoser(PLAYER_1);
            return;
        }
        //player1 has won
        if(!containsFlags(player2Pieces)){
            gameStatus.setGameOff();
            gameStatus.setWinner(PLAYER_1);
            gameStatus.setLoser(PLAYER_2);
            gameStatus.setMainReason(NO_MORE_FLAGS);
            return;
        }

        //player 2 turn
        currentPlayer = PLAYER_2;
        //player 2 lost - no more moving pieces
        if(!containsMovingPieces(player2Pieces)){
            gameStatus.setGameOff();
            gameStatus.setWinner(PLAYER_1);
            gameStatus.setLoser(PLAYER_2);
            gameStatus.setMainReason(NO_MOVING_PIECES);
            return;
        }

        unique_ptr<Move> player2Move  = player2->getMove();
        if(player2Move == nullptr){
            gameStatus.setGameOff();
            gameStatus.setMainReason(BAD_MOVE_FILE_INVALID);
            gameStatus.setWinner(PLAYER_1);
            gameStatus.setLoser(PLAYER_2);
            return;
        }

        currentMove = MoveImp(player2Move->getFrom().getX(),
                              player2Move->getFrom().getY(),
                              player2Move->getTo().getX(),
                              player2Move->getTo().getY());

        wasFight = executeMove(move(player2Move));
        //player 2 lost - bad move file
        if(!gameStatus.isGameOn()){
            gameStatus.setWinner(PLAYER_1);
            gameStatus.setLoser(PLAYER_2);
            gameStatus.setReason2(gameStatus.getMainReason());
            return;
        }
        player1->notifyOnOpponentMove(currentMove);
        if(wasFight){
            numOfTurnsWithNoFight = 0;
            player1->notifyFightResult(fightInfo);
            player2->notifyFightResult(fightInfo);
        }
        executeJoker(player2->getJokerChange());
        if(!gameStatus.isGameOn()){
            gameStatus.setWinner(PLAYER_1);
            gameStatus.setLoser(PLAYER_2);
            return;
        }
        //player2 has won - no more flags
        if(!containsFlags(player1Pieces)){
            gameStatus.setGameOff();
            gameStatus.setWinner(PLAYER_2);
            gameStatus.setLoser(PLAYER_1);
            gameStatus.setMainReason(NO_MORE_FLAGS);
            return;
        }
    }
    //reached max no-fight number
    gameStatus.setGameOff();
    gameStatus.setMainReason(DRAW_REACHED_MAX_NUM_OF_TURNS_WITH_NO_FIGHTS);
    gameStatus.setWinner(NO_PLAYER);
    gameStatus.setLoser(NO_PLAYER);
}

