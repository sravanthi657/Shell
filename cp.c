#include"allin_header.h"
int ind=0,cind=0,processp=0,pipo=0;
char cp_cinp[MAX_INPUT+1];char** arg;char** cmd_parse;
char* my_comm[]={"cd","pwd","echo","ls","pinfo","exit"};
int comm_sz= sizeof(my_comm)/sizeof(char*);
int is_mycomm(char *cmnd)
{
	for(int i=0;i<comm_sz;i++)
	{
		if(strcmp(cmnd,my_comm[i])==0)return i;
	}
	return -1;
}
void getnoww()
{
	getcwd(pwdis,pm+2);
	if(strcmp(pwdis,shell_h)==0){strcpy(now,"~");strcat(now,"$");}
	else if(strcmp(pwdis,shell_h)>0)
	{
		strcpy(now,"~");strcat(now,&pwdis[strlen(shell_h)]);strcat(now,"$");
	}
	else
	{	strcpy(now,pwdis);strcat(now,"$");}
	return ;
}
int is_bg()
{
    int wpid,status;
    for(int i=0;i<processp;i++)
    {
        if(bg_here[i].str_pid!=0)
        {
            wpid = waitpid(bg_here[i].str_pid,&status,WNOHANG);
            if(wpid==bg_here[i].str_pid)
            {
                printf("%s with pid %d exited with status %d\n",bg_here[i].cmd,wpid,WIFEXITED(status));
                bg_here[i].str_pid=0;
            }
        }
    }
    return 0;
}

int store_cmdline(char * folde)
{
	if(strlen(folde)>MAX_INPUT){puts("Shell: Exceeded the MAX_INPUT");_Exit(1);}
	char*mainlem=strtok(folde,";\n");if(mainlem==NULL) return -1;
	cmd_parse=parse(folde,";");
	printf("%s\n",cmd_parse[0]);
	strcpy(cp_cinp,mainlem);
	mainlem=strtok(folde," ");cind=0;
	while(mainlem!=0)
	{
		cinp[cind]=mainlem;
		cind++;mainlem=strtok(0," ");
	}
	if((strcmp(cinp[cind-1],"&")==0)){ cinp[cind-1]=NULL;return 1;}
	return 0;
}

void check_for_inp(char* folde)
{
	ind=0;cind=0;int already=0;pipo=0;
	int bg=store_cmdline(folde);
	if(bg==-1) return;
	int piped=pipe_comm(); printf("piped%d\n",piped); if(piped!=-1)return ;
	if(is_mycomm(cinp[0])>=0){perform(cinp[0]);is_bg();return;}
	for(int i=0;cmd_parse[i]!=NULL;i++)
	{
		pid_t str_pid,wai_pid;
		str_pid=fork();int status=0;
		if(str_pid==0)
		{
			printf("inpid=%s\n",cmd_parse[i]);
			arg = redirect_handler(cmd_parse[i]);
			//printf("args_interpret\n");			
			if(!arg)exit(0);
			printf("args=%s\n",arg[0]);
			int check=execvp(arg[0],arg);
			if(check<0){perror("");_Exit(1);}
		}
		else
		{
			if(str_pid<0){perror("");_Exit(1);}
			else if(!bg)
			{
				CUR_FG=str_pid;CUR_FGis=cinp[0];
				wai_pid=waitpid(str_pid,&status,WUNTRACED);
				if(wai_pid<0){perror("");}
			}
			else
			{
				kill(str_pid,SIGCONT);
				bg_here[processp].str_pid=str_pid;
				bg_here[processp].status=1;
				strcpy(bg_here[processp].cmd,cinp[0]);
				processp++;
				printf("[+] %s [%d]\n",cinp[0],str_pid);
			}
		}
	}
	if(cind)
		perror("Input is nothing or space ");
	is_bg();
	return;
}

