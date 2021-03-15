#include <sys/socket.h> 
#include <netdb.h> 
#include <string.h> 
#include <unistd.h>
#include <netinet/in.h> 
#include <stdio.h> // for printf
#include <stdlib.h> // for exit
#define MAX 80 
#define PORT 12345
#define SA struct sockaddr 
  
void read_cmds(int sockfd) 
{ 
    char buff[MAX]; 
    bzero(buff, MAX); 
    for (;;) {  
        read(sockfd, buff, sizeof(buff));
    	printf(buff);
        bzero(buff, MAX);
        strcpy(buff, "Message received...");
        write(sockfd, buff, sizeof(buff)); 
        bzero (buff, MAX);
    } 
} 
  
int main() 
{ 

    int sockfd, connfd, len; 
    struct sockaddr_in servaddr, cli; 
  
    // socket create and verification 
    sockfd = socket(AF_INET, SOCK_STREAM, 0); 
    if (sockfd == -1) { 
        printf("socket creation failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully created..\n"); 

    bzero(&servaddr, sizeof(servaddr)); 
  
    // assign IP, PORT 
    servaddr.sin_family = AF_INET; 
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY); 
    servaddr.sin_port = htons(PORT); 
  
    // Binding newly created socket to given IP and verification 
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) { 
        printf("socket bind failed...\n"); 
        exit(0); 
    } 
    else
        printf("Socket successfully binded..\n"); 
  
    // Now server is ready to listen and verification 
    if ((listen(sockfd, 5)) != 0) { 
        printf("Listen failed...\n"); 
        exit(0); 
    } 
    else
        printf("Server listening..\n"); 
    
    len = sizeof(cli); 
  
    // Accept the data packet from client and verification 
    connfd = accept(sockfd, (SA*)&cli, &len); 
    if (connfd < 0) { 
        printf("server acccept failed...\n"); 
        exit(0); 
    } 
    else
        printf("server acccept the client...\n"); 
  
    read_cmds(connfd); 
  
    close(sockfd); 
} 
