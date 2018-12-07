//
// Created by 闫传麒 on 2018/12/1.
//
#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>

#ifndef MCRAWL_PARSING_H
#define MCRAWL_PARSING_H

struct parg {
    int maxFlow;
    char hostname[128];
    int portnum;
    char localDirectory[128];
}parg;

int analyzeparameter(int argc, char *argv[], struct parg* args);

int error(char* msg);


#endif //MCRAWL_PARSING_H
