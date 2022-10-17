//program to define the class user
#include <stdio.h>
#include <unistd.h>
#include<stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <sys/ipc.h>
#include <user.h>
#include <stdbool.h>
//#include "open.h"
	


//function to add data to the phonebook 
int ToAddData(char * input1 ,char * input2,char * filename)
{
      /*int r=addintofile (input1,input2,filename);
      return r;*/
      FILE * fp;
      char path[1024]="";
      char fname[200]="";
      strcpy(fname,filename);
      strcpy(path,"/home/upendra/Desktop/Phonebook/Cut/Code/db/");
      if(strcmp(fname,"")==0)
      {
      	strcat(path,"public group");
      }
      else
      {
      	strcat(path,fname);
      }
      strcat(path,".txt");
      fp=fopen(path,"a");
      if(fp==NULL)
      {
      	return 0;
      }
      else
      {
      	char nm[200]="",pno[200]="";
      	strcpy(nm,input1);
      	strcpy(pno,input2);
      	fputs(nm,fp);
      	fputs(",",fp);
      	fputs(pno,fp);
      	fputs("\n",fp);
      }
      fclose(fp);
      return 1;
}


//function to add data to the phonebook 
int ToAdminAddData(char * input1 ,char * input2,char * filename)
{
      /*int r = addintofile(input1,input2,filename);
      return r;*/
      FILE * fp;
      char path[1024]="";
      char fname[200]="";
      strcpy(fname,filename);
      strcpy(path,"/home/upendra/Desktop/Phonebook/Cut/Code/db/");
      if(strcmp(fname,"")==0)
      {
      	strcat(path,"public group");
      }
      else
      {
      	strcat(path,filename);
      }
      strcat(path,".txt");
      fp=fopen(path,"a");
      if(fp==NULL)
      {
      	return 0;
      }
      else
      {
      	char nm[200]="",pno[200]="";
      	strcpy(nm,input1);
      	strcpy(pno,input2);
      	fputs(nm,fp);
      	fputs(",",fp);
      	fputs(pno,fp);
      	fputs("\n",fp);
      }
      fclose(fp);
      return 1;
}



//function to remove contact from the phonebook
int ToRemoveContact(char * input,char * filename)
{
      printf("\nin Toremovecontact\n");
      //char f[200]="",i[200]="";
      //strcpy(f,filename);
      //strcpy(i,input);
      int result=removecontact(input, filename);
      printf("\nReturned value in ToRemovecContact:%d\n",result);
      /*if(result==1)
      {
      	strcpy(filename,f);
      }
      else
      {
      	strcpy(filename,"");
      }*/
      return result;
}



//function to change the group
void ToChgrp(char * filename,char *type)
{
        char grp[200]="";
        strcpy(grp,filename);
        printf("\ninside Tochgrp:%s\n",grp);	
        FILE *fp;
    	char * line="";
    	int size = 1024,flag=0;
    	line = (char *)malloc(size);
    	fp=fopen("/home/upendra/Desktop/Phonebook/Cut/Code/db/authentication.txt","r");
    	if(fp!=NULL)
    	{                                                                                //checking whether the file is opened
         	while(fgets(line,size,fp))
         	{
         		char t[1024]="";
         		strcpy(t,line);
         		t[strlen(t)-1]='\0';
         		char *tok="";
         		tok=strtok(t,":");
         		if(strcmp(tok,type)==0)
         		{
		     		printf("\ntok,type,t just after if in tochgrp:%s,%s",tok,type,t);
		     		tok=strtok(NULL,":");
		     		printf("\ntok just before while in tochgrp:%s",tok);
		     		tok=strtok(NULL,":");
		     		printf("\ntok,type just before while in tochgrp:%s",tok);
		     		while(tok!=NULL)
		     		{
		     			printf("\ntok,grp before if in chgrp:%s\n",tok,grp);
		     			if(strcmp(tok,grp)==0)
		     			{
		     				flag=1;
		     				printf("\ninside Tochgrp while:%s,%s\n",tok,grp);
		     				break;
		     			}
		     			tok=strtok(NULL,":");
		     		}
		     		break;
		     	}
         	}
    	}
    	if(flag==0)
    	{
    		strcpy(filename,"no");
    	} 
    	fclose(fp);
    	free(line);
}



//function to add group to the directory
int ToAddGrp(char * filename)
{
	int r=addgroup(filename);
	return r;
}



//function to remove group from the directory
int ToRemoveGrp(char * filename)
{
	int r=removegroup(filename);
	return r;
}

int Tolistcontact(char * input, char * filename,char * concat)
{
	  char nm[200]="";
	  strcpy(nm,input);
	  FILE * fp1,* fp2;
      char path1[1024]="";
      //char path2[1024]="";
      char fname[200]="";
      strcpy(fname,filename);
      strcpy(path1,"/home/upendra/Desktop/Phonebook/Cut/Code/db/");
      //strcpy(path2,"/home/upendra/Desktop/Phonebook/Cut/Code/db/");     
      strcat(path1,filename);
      //strcat(path2,"temp");
      //strcat(path2,filename);
      //strcat(path2,"_temp");
      strcat(path1,".txt");
      //strcat(path2,".txt");
      fp1=fopen(path1,"r");
      //fp2=fopen(path2,"w");
      if (fp1 == NULL)
	  {
	  	//strcpy(filename,"");
		return 0;
	  }
	  char concat1[1024]="";
	  bool keep_reading = true;
	  do 
	  { 
	  	char buffer[1024];
		fgets(buffer, 1024, fp1);
		if (feof(fp1)) 
		keep_reading = false;
		else if (strncmp(buffer, nm,strlen(nm))== 0)
		  strcat(concat1,buffer);
	  } while (keep_reading);
	  fclose(fp1);
	  //fclose(fp2);
	  //char p[1024]="";
	  //strcpy(p,path1);
	 // remove(path1);
	  //rename(path2,path1);
	  //printf("\n%s\n",concat);
	  if(strlen(concat1)==0)
	  return 0;
	  strcpy(concat,concat1);
	  return 1;
}


/*int addintofile(char* name,char* phone,char* filename)
{
      FILE * fp;
      char path[1024]="";
      char fname[200]="";
      strcpy(fname,filename);
      strcpy(path,"/home/upendra/Desktop/Phonebook/Cut/Code/db/");
      if(strcmp(fname,"")==0)
      {
      	strcat(path,"public group");
      }
      else
      {
      	strcat(path,filename);
      }
      strcat(path,".txt");
      fp=fopen(path,"a");
      if(fp==NULL)
      {
      	return 0;
      }
      else
      {
      	char nm[200]="",pno[200]="";
      	strcpy(nm,name);
      	strcpy(pno,phone);
      	fputs(nm,fp);
      	fputs(",",fp);
      	fputs(pno,fp);
      	fputs("\n",fp);
      }
      fclose(fp);
      return 1;
}*/


int addgroup(char * filename)
{
      FILE * fp;
      char path[1024]="";
      char fname[200]="";
      strcpy(fname,filename);
      strcpy(path,"/home/upendra/Desktop/Phonebook/Cut/Code/db/");
      strcat(path,fname);
      strcat(path,".txt");
      fp=fopen(path,"w");
      if(fp==NULL)
      {
      	return 0;
      }
      fclose(fp);
      return 1;
}

int removegroup(char * filename)
{
      char path[1024]="";
      char fname[100]="";
      strcpy(fname,filename);
      strcpy(path,"/home/upendra/Desktop/Phonebook/Cut/Code/db/");
      strcat(path,fname);
      strcat(path,".txt");
      if (remove(path) == 0)
      return 1;
      return 0;
}

int removecontact(char * input, char * filename)
{
	  char nm[200]="";
	  strcpy(nm,input);
	  FILE * fp1,* fp2;
      char path1[1024]="";
      char path2[1024]="";
      char fname[200]="";
      strcpy(fname,filename);
      strcpy(path1,"/home/upendra/Desktop/Phonebook/Cut/Code/db/");
      strcpy(path2,"/home/upendra/Desktop/Phonebook/Cut/Code/db/");     
      strcat(path1,filename);
      //strcat(path2,"temp");
      strcat(path2,filename);
      strcat(path2,"_temp");
      strcat(path1,".txt");
      strcat(path2,".txt");
      fp1=fopen(path1,"r");
      fp2=fopen(path2,"w");
      if (fp1 == NULL || fp2 == NULL)
	  {
	  	strcpy(filename,"");
		return 0;
	  }
	  int flag=0;
	  bool keep_reading = true;
	  do 
	  { 
	  	char buffer[1024];
		fgets(buffer, 1024, fp1);
		if (feof(fp1)) 
		keep_reading = false;
		else if (strncmp(buffer, nm,strlen(nm))!= 0)
		  fputs(buffer, fp2);
		else
		{
			printf("\ninside else of to remove contact\n");
			flag=1;
		}
	  } while (keep_reading);
	  fclose(fp1);
	  fclose(fp2);
	  //char p[1024]="";
	  //strcpy(p,path1);
	  remove(path1);
	  rename(path2,path1);
	  printf("\nflag in to remove contact:%d\n",flag);
	  return flag;
}
