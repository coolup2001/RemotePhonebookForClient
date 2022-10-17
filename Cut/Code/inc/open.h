#include <stdbool.h>
int addintofile(char* name,char* phone,char* filename)
{
      FILE * fp;
      char path[1024]="";
      char fname[200]="";
      strcpy(fname,filename);
      strcpy(path,"/home/kali/Desktop/remote_phonebook/db/");
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
}


int addgroup(char * filename)
{
      FILE * fp;
      char path[1024]="";
      char fname[200]="";
      strcpy(fname,filename);
      strcpy(path,"/home/kali/Desktop/remote_phonebook/db/");
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
      strcpy(path,"/home/kali/Desktop/remote_phonebook/db/");
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
      strcpy(path1,"/home/kali/Desktop/remote_phonebook/db/");
      strcpy(path2,"/home/kali/Desktop/remote_phonebook/db/");     
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

/*int Tolistcontact(char * input, char * filename,char * concat)
{
	  char nm[200]="";
	  strcpy(nm,input);
	  FILE * fp1,* fp2;
      char path1[1024]="";
      //char path2[1024]="";
      char fname[200]="";
      strcpy(fname,filename);
      strcpy(path1,"/home/kali/Desktop/remote_phonebook/db/");
      //strcpy(path2,"/home/kali/Desktop/remote_phonebook/db/");     
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
}*/
      
      
	
