//program to have user class header file
#include <stdio.h>
//#include <vector>
//#include<algorithm>
//#include <phonebook.h> 
//vector<string> group;
//vector<Phonebook> phonebooks ;

//bool  ToAuthenticate(User user);						//to autheticate the user
int ToAddData(char * input1 ,char * input2,char * filename);		//to add data to the phonebook
int ToRemoveContact(char * input,char * filename);			//to remove contact
int Tolistcontact(char * ,char *,char *);
//vector<string> ToListData(string input,string filename);			//to list the data from the group
//bool ToFindUser(string username);						//to find the user 
void ToChgrp(char * input,char * type);						//to change the groups
int ToAddGrp(char * filename);						//to add a group
int ToRemoveGrp(char * filename);						//to delete a group
int ToAdminAddData(char * input1 ,char * input2,char * filename);	//to add data to the phonebook from admin


