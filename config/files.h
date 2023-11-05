struct serverInfo
{
        char ip[16];
        int port;
};

void readConfig(struct serverInfo *info, char fileName[]);
FILE * openFile(char filename[]);
FILE * openFileWrite(char filename[]);