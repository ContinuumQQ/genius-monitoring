void serverSocketBuilder(int socketBuildfd, struct sockaddr_in *socketBuildAddr, char addr[], uint16_t port, int countConnections);
int createServerSocket(int domain, int type, int protocol);
void bindServerSocket(int socketfd, struct sockaddr_in *socketAddr);
void listenServerSocket(int socketfd, int countConnections);
void saveAgentInfo(char info[], char nameLogFile[]);


