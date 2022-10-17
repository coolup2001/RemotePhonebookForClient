//program to define the server main function
#include <stdio.h>
#include <signal.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"
int sockid ;
void signalHandler(int signal)
{
        if(signal==SIGINT)
        {
                send(sockid,"bye",3,0);
                exit(0);
        }
}

//main function to execute client class

int main () 
{
        signal(SIGINT,signalHandler);						//signal to cut the client from server
        char recvdata[200]="",credentials[200]="",commands[200]="";
        Client();								//creating a object of client
        sockid=ToGetSockfd();						//calling the getsockfd of client class
        ToGetCredentials(credentials);		//calling the getcredentials functions of client class
        //printf("%s,aftercredentials\n",credentials);
        ToServerConnect() ;				//calling the serverconnect function to connect to the server
        //printf("%s,beforesenddata\n",credentials);
        ToSendData(credentials);						//sending the credentials to server 
        CToRecvData(recvdata);			//receiving the message from the server using recvData function
        printf("%s,afterCToRecvData\n",recvdata);
        char type[200]="";
        strcpy(type,recvdata);							
        ToDisplayRecvData(recvdata);					//calling the funtion to display the data
        while(1)
        {
                strcpy(commands,"");
                int d =ToGetUserCommands(type,commands) ;		//calling the function to get the usercommands
                printf("inside while:%d",d);
                if(strcmp("",commands)!=0)
                {
               	   printf("inside while:%s",commands);
               	   ToSendData(commands);					//sending the user commands to the server
                   //recvdata = CToRecvData();				//receiving the data from the server
                   CToRecvData(recvdata);
                   ToDisplayRecvData(recvdata);			//displaying the received data from the server
                }
                else
                {
                        printf("Subcommand can't be Null");
                        continue;
                }
        }
        return 0;
}

