//
// Created by root on 6/5/18.
//

#ifndef ADVANCEDTOPICS3_MAINAUX_H
#define ADVANCEDTOPICS3_MAINAUX_H

enum parsingArgsResult {
    PARSE_THREAD,
    PARSE_PATH,
    PARSE_FAILED
};

void parseArguments(char *arg, int *num_of_thread, char *path);

#endif //ADVANCEDTOPICS3_MAINAUX_H
