#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "server.h"
#include "../config/files.h"

int main()
{
        struct sockaddr_in serverAdress;
        struct serverInfo information;
        int serverSocketfd = 0;
        int serverAcceptfd = 0;
        char getAgentInformation[2048] = "";

        readConfig(&information, "config.txt");
        serverSocketfd = createServerSocket(PF_INET, SOCK_STREAM, 0);
        serverSocketBuilder(serverSocketfd, &serverAdress, information.ip, information.port, 100);
        

                
                while (1)
                {
                        serverAcceptfd = accept(serverSocketfd, NULL, NULL);

                        if(serverAcceptfd > 0){
                                recv(serverAcceptfd, getAgentInformation, sizeof(getAgentInformation), 0);
                                saveAgentInfo(getAgentInformation, "log.txt");
                                memset(getAgentInformation, 0, sizeof(getAgentInformation));
                        }

                        close(serverAcceptfd);
                }
                


                

        return 0;
}

void serverSocketBuilder(int socketBuildfd, struct sockaddr_in *socketBuildAddr, char addr[], uint16_t port, int countConnections)
{
        memset(socketBuildAddr, 0, sizeof(*socketBuildAddr));

        socketBuildAddr -> sin_family = AF_INET;
        socketBuildAddr -> sin_addr.s_addr = inet_addr(addr);
        socketBuildAddr -> sin_port = htons(port);

        bindServerSocket(socketBuildfd, socketBuildAddr);
        listenServerSocket(socketBuildfd, countConnections);
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

void bindServerSocket(int socketfd, struct sockaddr_in *socketAddr)
{
        if (bind(socketfd, (struct sockaddr *) socketAddr, sizeof(*socketAddr)) < 0){
                perror("Bind socket error");
                _exit(1);
        }
}

void listenServerSocket(int socketfd, int countConnections)
{
        if (listen(socketfd, countConnections) < 0){
                perror("Listening error");
                _exit(1);
        }      
}

void saveAgentInfo(char info[], char nameLogFile[])
{
        FILE *log = openFileWrite(nameLogFile);

        fputs(info, log);
        fputs("\n", log);
        fflush(log);

        fclose(log);
}