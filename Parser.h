
#ifndef ADVANCEDTOPICS2_PARSER_H
#define ADVANCEDTOPICS2_PARSER_H

#include <string>
#include <string.h>
#include <vector>
#include <sstream>
#include "Move.h"
//#include "PlayerAlgorithm.h"
#include "FightInfo.h"


using namespace std;

class Parser {
public:
	Parser()= default;
	Parser(const Parser&)= delete;
	Parser& operator=(const Parser&)= delete;

    unique_ptr<PiecePosition> parsePiecePosition(string commandLine);
	void parseMoveCommand(string commandLine, vector<unique_ptr<Move>>& moves, vector<unique_ptr<JokerChange>>& jokerChanges);

};


#endif //ADVANCEDTOPICS2_PARSER_H
