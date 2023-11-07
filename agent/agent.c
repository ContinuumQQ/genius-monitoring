#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "agent.h"
#include "../string/strings.h"
#include "../config/files.h"


int main()
{
        int agentSocketfd = 0;
        char agentInfo[2048] = "";
        struct sockaddr_in agentAdress;
        struct serverInfo information;
        struct tm systemTime;
        time_t localTime = 0; 

        localTime = time(NULL);

        
        readConfig(&information, "config.txt");


        
        agentSocketBuilderaddr(&agentAdress, information.ip, information.port);


                while(1){
                        agentSocketfd = createServerSocket(PF_INET, SOCK_STREAM, 0);

                        if (connect(agentSocketfd, (struct sockaddr *) &agentAdress, sizeof(agentAdress)) >= 0){
                                getInfo(agentInfo, &systemTime, localTime);
                                send(agentSocketfd, agentInfo, sizeof(agentInfo), 0);
                                memset(agentInfo, 0, sizeof(agentInfo));
                                
                        }else {

                                perror("Connection error");
                                exit(1);

                        }

                        close(agentSocketfd);
                        sleep(1);
                }       

        
        
        
        
        
        return 0;
}

void agentSocketBuilderaddr(struct sockaddr_in *socketBuildAddr, char addr[], int port)
{
        
        memset(socketBuildAddr, 0, sizeof(*socketBuildAddr));

        socketBuildAddr -> sin_family = AF_INET;
        socketBuildAddr -> sin_addr.s_addr = inet_addr(addr);
        socketBuildAddr -> sin_port = htons(port);
        
}

int createServerSocket(int domain, int type, int protocol)
{
        int socketfd = socket(domain, type, protocol);
        
                if (socketfd < 0){
                        perror("Socket create error");
                        _exit(1);
                }
                else {
                        return socketfd;
                }
}

FILE * openFile(char filename[])
{
        FILE *configFile = fopen(filename, "r");
        if (configFile == NULL){
                perror("Open File");
                exit(1);
        }
        else 
                return configFile;

}

void removeSymbol(char str[], char symbol)
{
        size_t i = 0;

        for (i = 0; i < strlen(str); i++){
                if (str[i] == symbol){
                        memmove(&str[i], &str[i + 1], strlen(str) - i);
                        i--;
                }
        }
}

void infoCat(char *dst, char *src)
{
        strcat(src, ".");

        strcat(dst, src);
}

void getCpuInfo(char *info)
{
        FILE *cpuInfo = openFile("/proc/cpuinfo");
        char buffer[256] = "";
        char threads[32] = "";
        char *model = (char *) malloc(64 * sizeof(char));

        int count = 0;

        while(fgets(buffer, sizeof(buffer), cpuInfo)){

                if (strstr(buffer, "model name") != NULL && count == 0)
                {
                        strcat(info, "Processor name:");
                        __strtok_r(buffer, ":", &model);
                        infoCat(info, model);
                        removeSymbol(info, '\n');
                }
                

                if (strstr(buffer, "MHz") != NULL){
                        removeSymbol(buffer, ' ');
                        removeSymbol(buffer, '\n');
                        removeSymbol(buffer, '\t');
                        sprintf(threads, " Thread(%d)", count);
                        strcat(buffer, threads);
                        infoCat(info, buffer);
                        count++;
                }
                memset(buffer, 0, sizeof(buffer));
        }

        fclose(cpuInfo);
        model = NULL;
        free(model);

}



void getMemInfo(char *info)
{
        FILE *memInfo = openFile("/proc/meminfo");
        char buffer[256];

        while(fgets(buffer, sizeof(buffer), memInfo)){

                if (strstr(buffer, "Mem") != NULL){
                        removeSymbol(buffer, ' ');
                        removeSymbol(buffer, '\n');
                        infoCat(info, buffer);
                }

                memset(buffer, 0, sizeof(buffer));
        }

        fclose(memInfo);
}

void getInfo(char *info, struct tm *sysTime, time_t sTime)
{
        getSystemTime(info, sysTime, sTime);
        getCpuInfo(info);
        getMemInfo(info);
}

void readConfig(struct serverInfo *info, char fileName[])
{
        FILE *configFile = openFile(fileName);
        char buffer[64] = "";
        char strKey[32] = "";
        char *pstrKey = strKey;
       /*char *strKey = (char *) malloc(32 * sizeof(char));
        */
        int counter = 0;

        while(fgets(buffer, sizeof(buffer), configFile) != NULL){

                if (counter == 0)
                {
                        __strtok_r(buffer, "=", &pstrKey);

                        removeSymbol(pstrKey, ' ');
                        removeSymbol(pstrKey, '\n');
                        
                        strcpy(info -> ip, pstrKey);

                        memset(buffer, 0, sizeof(buffer));
                }

                if (counter == 1)
                {
                        __strtok_r(buffer, "=", &pstrKey);
                        info -> port = atoi(pstrKey);
                }

                counter++;
        }

        fclose(configFile);
}


void getSystemTime (char *info, struct tm *sysTime, time_t sTime)
{
        char formatTime[32] = "";

        sTime = time(NULL);
        sysTime = localtime(&sTime);
        
        sprintf(formatTime, "[%d/%d/%d %d:%02d:%02d] ",1900 + sysTime -> tm_year , sysTime -> tm_mon + 1, sysTime -> tm_mday, sysTime -> tm_hour, sysTime -> tm_min, sysTime -> tm_sec);

        strcat(info, formatTime);
        
}