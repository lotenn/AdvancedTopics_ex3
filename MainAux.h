#ifndef ADVANCEDTOPICS3_MAINAUX_H
#define ADVANCEDTOPICS3_MAINAUX_H

#include <cstring>
#include <cstdlib>
#include <climits>

using namespace std;

enum parsingArgsResult {
    PARSE_THREAD,
    PARSE_PATH,
    PARSE_FAILED
};

parsingArgsResult parseArguments(char *arg1, char *arg2, int &num_of_thread, char* &path);

#endif //ADVANCEDTOPICS3_MAINAUX_H
