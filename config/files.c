#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../string/strings.h"
#include "files.h"

void readConfig(struct serverInfo *info, char fileName[])
{
        FILE *configFile = openFile(fileName);
        char buffer[64] = "";
        char strKey[32] = "";
        char *pstrKey = strKey;
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

FILE * openFileWrite(char filename[])
{
        FILE *writeFile = fopen(filename, "a");
        if (writeFile == NULL){
                perror("Write File");
                exit(1);
        }
        else 
                return writeFile;

}