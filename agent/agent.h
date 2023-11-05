void agentSocketBuilderaddr(struct sockaddr_in *socketBuildAddr, char addr[], int port);
int createServerSocket(int domain, int type, int protocol);
void getCpuInfo(char *info);
void getMemInfo(char *info);
void getInfo(char *info, struct tm *sysTime, time_t sTime);
void getSystemTime(char *info, struct tm *sysTime, time_t sTime);
