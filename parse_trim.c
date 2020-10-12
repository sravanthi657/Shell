#include "allin_header.h"

char** parse(char * cmnd, char* breakat)
{
	char **ma=(char**)malloc(MAX_INPUT*sizeof(char*));
	if(strlen(cmnd)>MAX_INPUT){puts("Shell: Exceeded the MAX_INPUT");_Exit(1);}
	char*cp_cmnd=cmnd;
	char* token=strtok(cp_cmnd,breakat);int i=0;
	while(token!=NULL)
	{
		if(i>=MAX_INPUT){puts("Shell: Exceeded the MAX_INPUT");_Exit(1);}
		ma[i]=token;
		token=strtok(0,breakat);i++;
	}
	ma[i]=NULL;
	return ma;
}
char* clearstring(char *cmd)
{
	char*cleared=strdup(cmd);int temp=0 ,i, len = 0;
	for (i=0; cmd[i] !='\0';i++,len++);int j=len-1;
	for (i=0; i<len; ++i)
		if (isspace(cmd[i])==0)
			break;
	while(j>=0)
	{
		if (isspace(cmd[j])==0)break;
		j--;
	}
	for (temp=0; i<=j;i++,temp++)
		cleared[temp] = cmd[i];
	cleared[temp] = '\0';
    return cleared;
}
