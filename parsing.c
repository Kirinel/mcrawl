//
// Created by 闫传麒 on 2018/12/1.
//

#include "parsing.h"

int error(char* msg) {
    fprintf(stderr, "%s\n", msg);
    return 0;
}

char* const short_options = "n:h:p:f:";

struct option long_options[] = {
        {"number", 1, NULL, 'n'},
        {"hostname", 1, NULL, 'h'},
        {"port", 1, NULL, 'p' },
        {"localdirectory", 1, NULL, 'f'},
        {NULL, 0, NULL, 0 }
};

int analyzeparameter(int argc, char *argv[], struct parg* args) {
    int c;
    while ((c = getopt_long(argc, argv, short_options, long_options, NULL)) != -1) {
        switch (c) {
            case 'n':
                args->maxFlow = atoi(optarg);
                break;
            case 'h':
                strcpy(args->hostname, optarg);
                break;
            case 'p':
                args->portnum = atoi(optarg);
                break;
            case 'f':
                strcpy(args->localDirectory, optarg);
                break;
            default:
                error("invalid argument!");
                exit(1);
        }
    }
}