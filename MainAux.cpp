#include "MainAux.h"

parsingArgsResult parseArguments(char *arg1, char *arg2, int &num_of_thread, char* &path){
    if(!strcmp(arg1, "-threads")){
        long converted_value = strtoul(arg2, NULL, 10);
        if(converted_value > INT_MAX || converted_value <= 0)
            return PARSE_FAILED;
        num_of_thread = converted_value;
        return PARSE_THREAD;
    }
    else if(!strcmp(arg1, "-path")){
        path = arg2;
        return PARSE_PATH;
    }
    else
        return PARSE_FAILED;
}