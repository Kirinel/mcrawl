#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <strings.h>
#include "parsing.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <pthread.h>
#define BUFLEN (1024*1024)

int main(int argc, char *argv[]) {
    char writeBuf[BUFLEN] ;
    char readBuf[BUFLEN];
    char name[BUFLEN];
    struct parg input;
    analyzeparameter(argc, argv, &input);
    struct sockaddr_in serv_addr;
    int sockfd;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        error("ERROR opening socket");
        exit(1);
    }

    struct hostent *server_addr = gethostbyname(input.hostname);
    if (server_addr == NULL) {
        error("ERROR, no such host");
        exit(1);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server_addr->h_addr,
          (char *)&serv_addr.sin_addr.s_addr,
          server_addr->h_length);
    serv_addr.sin_port = htons(input.portnum);
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0) {
        error("ERROR connecting");
        exit(1);
    }
    printf("connected\n");
    bzero(writeBuf, BUFLEN);
//    sprintf(writeBuf, "GET /\r\n");
    sprintf(writeBuf, "GET /index.html HTTP/1.1\r\n"
//                      images/favicon.ico
                      "Host: %s\r\n"
                      "Accept: */*\r\n"
//                      "Cookie: 431425562842515b4dd25f3-660d-42d5-96ba-c7c9d738c6e4"
                      "Connection: Keep-Alive\r\n"
                      "\r\n", input.hostname);
    send(sockfd, writeBuf, strlen(writeBuf), 0);

    FILE* file = fopen("index.html", "a+");

    bzero(readBuf, BUFLEN);
    while (recv(sockfd, readBuf, BUFLEN, 0) > 0) {
        fprintf(file, "%s", readBuf);
        bzero(readBuf, BUFLEN);
    }
//    return 0;
    file = fopen("index.html", "r");
    while(!feof(file)) {
        bzero(name, BUFLEN);
        fgets(readBuf, BUFLEN, file);
        char *p, *q;
        if (strstr(readBuf, "src")) {
            p = strstr(readBuf, "src");
            p = strstr(p, "\"") + 1;
            q = strstr(p, "\"");
            bzero(name, BUFLEN);
            int i = 0;
            while (p != q) {
                name[i] = *p;
                p++;
                i++;
            }
            printf("name: %s\n", name);
        } else if (strstr(readBuf, "SRC")) {
            p = strstr(readBuf, "SRC");
            p = strstr(p, "\"") + 1;
            q = strstr(p, "\"");
            bzero(name, BUFLEN);
            int i = 0;
            while (p != q) {
                name[i] = *p;
                p++;
                i++;
            }
            printf("name: %s\n", name);
        } else if (strstr(readBuf, "href")) {
            p = strstr(readBuf, "href");
            p = strstr(p, "\"") + 1;
            q = strstr(p, "\"");
            bzero(name, BUFLEN);
            int i = 0;
            while (p != q) {
                name[i] = *p;
                p++;
                i++;
            }
            printf("name: %s\n", name);
        } else if (strstr(readBuf, "HREF")) {
            p = strstr(readBuf, "HREF");
            p = strstr(p, "\"") + 1;
            q = strstr(p, "\"");
            bzero(name, BUFLEN);
            int i = 0;
            while (p != q) {
                name[i] = *p;
                p++;
                i++;
            }
            printf("name: %s\n", name);
        }
        if (name[0] && (!(name[0] == 'h' && name[1] == 't') || name[0]!= '#')) {
            printf("name: %s\n", name);
            bzero(writeBuf, BUFLEN);
//    sprintf(writeBuf, "GET /\r\n");
            sprintf(writeBuf, "GET /%s HTTP/1.1\r\n"
                          "Host: %s\r\n"
                          "Accept: */*\r\n"
                          //"Cookie: 431425562842515b4dd25f3-660d-42d5-96ba-c7c9d738c6e4"
                          "Connection: Keep-Alive\r\n"
                          "\r\n", name, input.hostname);
            send(sockfd, writeBuf, strlen(writeBuf), 0);

            FILE *file = fopen(name, "a+");

            bzero(readBuf, BUFLEN);
            while (recv(sockfd, readBuf, BUFLEN, 0) > 0) {
                fprintf(file, "%s", readBuf);
                bzero(readBuf, BUFLEN);
            }
        }
    }


    return 0;
}