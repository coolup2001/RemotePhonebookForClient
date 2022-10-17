//program to define the class client


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
//#include <limits.h>
#include <string.h>
#include <arpa/inet.h>
//#include <termios.h>
#include <signal.h>
#include <client.h>
#include <ctype.h>
int sockfd;                                             
struct sockaddr_in servaddr;
int portnumber,slen,mlen,connectfd;
char ip_address[130];

#define ADDRSERV "127.0.0.1"
#define MAX 1024
#define PORT 8028
      
void Client()
{
	connectfd = 0;
	mlen = 0 ;
	portnumber =0 ;
    memset(&servaddr,0,slen);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(ADDRSERV);
    servaddr.sin_port = htons(PORT);
    slen=sizeof(servaddr);
    sockfd=socket(AF_INET, SOCK_STREAM, 0);										
    if(sockfd < 0)
    {
	      //fputs("Socket can't be created ",stderr);
	      printf("Socket can't be created ");
          exit(EXIT_FAILURE);
    }
}


//function to get socket id
int ToGetSockfd()
{
	return sockfd ;
}


//function to credentials from the User
void ToGetCredentials(char * credentials)
{
      //char *res;
      //res=(char *)malloc(101);
      char uName[50]="" ;
      char password[50]="";
      printf("Enter the Username :") ;
      fgets(uName,50,stdin);
      if(strcmp(uName,"\n")==0)
      {
      	strcpy(uName,"");
      }
      else
      {
        uName[strlen(uName)-1]='\0';  
      }
      printf("Enter the password :") ;
      fgets(password,50,stdin);
      if(strcmp(password,"\n")==0)
      {
	      strcpy(password,"");
      }
      else
      {
        password[strlen(password)-1]='\0';  
      }
      //char concat[1024]="";
      strcpy(credentials,uName);
      strcat(credentials,":");
      strcat(credentials,password);
}


//function to connect to the server
int ToServerConnect()
{
	printf("before connect,ToServerConnect\n");
	connectfd=connect(sockfd,(struct sockaddr *)&servaddr,slen);
	printf("%d,ToServerConnect\n",connectfd);
    if(connectfd < 0)
    {
    	printf("Socket can't be created ");
        exit(EXIT_FAILURE);
    }
    return connectfd;
}


//function to senddata from the client
int ToSendData(char * str)
{
	/*char fname[100]="";
      int i=0;
      for (i=0; *(str+i) != '\0'; i++)
      {
        fname[i] = *(str+i);
      }
      fname[i]='\0';
	printf("inside:%s",str);*/
	//send(sockfd,str,strlen(str),0);
	char tem[200]="";
	strcpy(tem,str);
    /*if(strcmp(tolower(temp),"bye")==0)
    {												//checks for bye if bye close client conncetion
      	ToCloseClientConnections();
    }*/
    send(sockfd,tem,strlen(tem),0);
	return 0 ;
}



// function to receive the data from the server
/*char * CToRecvData()
{      
      char * res ="";
      char recvdata[1024] ;
      memset(recvdata,0,1024);
      mlen=recv(connectfd , recvdata,1024 , 0);
      if(mlen==0)
      {
      	ToCloseClientConnections();
      }
      res = recvdata;
      return res;
}*/
void CToRecvData(char * recvdata)
{
        char temp[200]="";
        //mlen=recv(connectfd ,temp,sizeof(temp), 0);
        mlen=recv(sockfd ,temp,sizeof(temp), 0);
        strcpy(recvdata,temp);
        if(mlen==0)
        {                  
                ToCloseClientConnections();
        }
}




//function to get the subcommands from the use
int ToGetUserCommands(char * type,char * commands)
{
	while(1)
	{
      	    char subcommand[200]="";
            printf("\nEnter the subcommand :") ;
            fgets(subcommand,200,stdin);
            printf("%s\n",subcommand);
            subcommand[strlen(subcommand)-1]='\0';
            char copysubcommand[200]="";
            strcpy(copysubcommand,subcommand);
            //copysubcommand[strlen(copysubcommand)-1]='\0';
            printf("cp:%s\n",copysubcommand);
            char temp[200]="";
            strcpy(temp,type);
            printf("temp:%s,type=%s\n",temp,type);
	    	if(strcmp(temp,"authenticated user")==0)
	    	{			
            	  char comm[200]="";
            	  char *input1="",*input2="",*input3="";
            	  char * tok;
            	  tok=strtok(subcommand," ");
            	  strcpy(comm,tok);
            	  input1=strtok(NULL,",");
            	  input2=strtok(NULL,",");
                  printf("Hi: %s,%s,%s\n",comm,input1,input2);
                  if(strcmp(comm,"ADD")==0)
                  {											
                  	if(input1!=NULL && input2!=NULL)
                  	{
                        	printf("inside authenticated add\n");
                        	strcpy(commands,copysubcommand);
                        	break;
                    }
                    else
                    {
                    	printf("ADD command should have two fields\n");
                        continue;
					}
                 }
                 else if(strcmp(comm,"rm")==0)
                 {											//checks for remove command
                   	if(input1!=NULL && input2==NULL)
                   	{
                        	strcpy(commands,copysubcommand);
                        	break;
                    }
                    else
                    {
                        printf("Remove command should have only one field"); 
                        continue;
                    }
                 }
                 else if(strcmp(comm,"list")==0)
                 {											//checks for list command
                   	if(input1!=NULL && input2==NULL)
                   	{
                   		strcpy(commands,copysubcommand);
                        break;
                    }
                    else
                    {
                    	printf("List command should have only one field");
                        continue;
                    }
                }
                else if(strcmp(comm,"chgrp")==0)
                {											//checks for the chgrp command
                   	if(input1!=NULL && input2==NULL)
                   	{
                   		strcpy(commands,copysubcommand);
                        break;
                   	}
                   	else
                   	{
                   		printf("Enter only Groupname");
                   		continue;
                    }
                }
                else if(strcmp(comm,"list")==0)
                {											//checks for the chgrp command
                   	if(input1!=NULL && input2==NULL)
                   	{
                   		strcpy(commands,copysubcommand);
                        break;
                   	}
                   	else
                   	{
                   		printf("Enter only pattern");
                   		continue;
                    }
                }
                else if(strcmp(comm,"bye")==0)
                {	
                   	if(input1==NULL && input2==NULL)
                   	{
                   		strcpy(commands,copysubcommand);
                        break;
                    }
                    else
                    {
                    	printf("No inputs with bye/Bye");
                        continue;
                    }
                }
                else
                {
                	printf("You can only use ADD,rm,list,chgrp and bye/Bye subcommands");
                	continue;
                }
	      }
	      
	      if(strcmp(temp,"admin")==0)
	      {													//checks for the type admin
            	  printf("Inside admin\n");
            	  char comm[200]="";
            	  char *input1="",*input2="",*input3="";
            	  char * tok;
            	  tok=strtok(subcommand," ");
            	  strcpy(comm,tok);
            	  input1=strtok(NULL,",");
            	  input2=strtok(NULL,",");
            	  input3=strtok(NULL,",");
                  printf("Hi: %s,%s,%s,%s\n",comm,input1,input2,input3);
                  if(strcmp(comm,"addgrp")==0)
                  {											//checks for the ADD command
            	      if(input1!=NULL&&input2==NULL)
            	      {
                  	      strcpy(commands,copysubcommand);
                          break;
                      }
                      else
                      {
                          printf("Enter groupname only");
                          continue;
                      }
                   }
                   else if(strcmp(comm,"rmgrp")==0)
                   {											//checks for the remove command
                   		if(input1!=NULL && input2==NULL)
                   		{
                        	strcpy(commands,copysubcommand);
                        	break;
                        }
                        else
                        {
                        	printf("Enter groupname only");
							continue;
                        }
                    }
                    else if(strcmp(comm,"ADD")==0)
                    {											//checks for ADD command
                  		if(input1!=NULL && input2!=NULL && input3!=NULL)
                  		{
                        	strcpy(commands,copysubcommand);
                        	printf("inside ADD:%s",commands);
                        	return 1;
                        }
                        else
                        {
                        	printf("Provide three inputs name,phonenumber,filename ");
                            continue;
                        }
                    }
                    
                    else if(strcmp(comm,"bye")==0)
                	{									//checks for bye command 
		               	if(input1==NULL && input2==NULL)
		               	{
		               		strcpy(commands,copysubcommand);
                        	break;
		                }
		                else
		                {
		                	printf("No inputs with bye/Bye");
		                    continue;
		                }
		            }
                    else
                    {
                     	printf("Enter addgrp , rmgrp or ADD  subcommand only");
                        continue;
                    }
               }
			   if(strcmp(temp,"anonymous user")==0)
			   {											//checks for anonymous user
		              char comm[200]="";
		        	  char *input1="",*input2="";
		        	  char * tok="";
		        	  tok=strtok(subcommand," ");
		        	  strcpy(comm,tok);
		        	  input1=strtok(NULL,",");
		        	  input2=strtok(NULL,",");
		              printf("Hi: %s,%s,%s\n",comm,input1,input2);
		              if(strcmp(comm,"ADD")==0)
		              {											
				          	if(input1!=NULL && input2!=NULL)
				          	{
				                strcpy(commands,copysubcommand);
                        		break;
				            }
				            else
				            {
				            	printf("ADD command should have two fields\n");
				                continue;
							}
		              }
		              else if(strcmp(comm,"bye")==0)
		              {									//checks for bye command 
				           	if(input1==NULL && input2==NULL)
				           	{
				           		strcpy(commands,copysubcommand);
                        		break;
				            }
				            else
				            {
				            	printf("No inputs with bye/Bye");
				                continue;
				            }
				      }
		              else
		              {
		               	printf("User should provide only ADD subcommand") ;
		                 continue;
		              }
		       }
	}
	printf("after while");
	return 1;
}



//function to display data received from server
void ToDisplayRecvData(char * recvData)
{
	printf("%s\n",recvData);
}



//function to close connection from the server
int ToCloseClientConnections()
{
      close(sockfd);
      exit(0);
}



