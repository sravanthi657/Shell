#include"allin_header.h"

int ind=0,cind=0,processp=0,pipo=0,bg=0;
char cp_cinp[MAX_INPUT+1];char** arg;char** cmd_parse;
char* my_comm[]={"cd","pwd","ls","pinfo","quit"};
char* advan_comm[]={"setenv","unsetenv","jobs","kjob","fg","bg","overkill"};

char** handler_ctrl(char* pt)
{
    char** comd=malloc(MAX_INPUT*sizeof(char*));
    char *sep = ";\n";
    int count = 0;
    comd[count++] = strtok(pt,sep);
    while(comd[count-1])
        comd[count++] = strtok(NULL,sep);
    comd[count++] = NULL;
    return comd;
}
void check_cmndbg(int i)
{
	for (int j=0; cmd_parse[i][j]; ++j)
			if (cmd_parse[i][j] == '&'){
				cmd_parse[i][j] = '\0';bg = 1;return;}
	return;
}
int is_mycomm(char *cmnd)
{
	int comm_sz= sizeof(my_comm)/sizeof(char*);
	for(int i=0;i<comm_sz;i++)
	{
		if(strcmp(cmnd,my_comm[i])==0)return i;
	}
	return -1;
}
int is_advan(char* cmnd)
{
	int comm_sz= sizeof(advan_comm)/sizeof(char*);
	for(int i=0;i<comm_sz;i++)
	{
		if(strcmp(cmnd,advan_comm[i])==0)return i;
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
	if(strcmp(folde,"\0")==0)return 3;
	if(strlen(folde)>MAX_INPUT){puts("Exceeded the MAX_INPUT "); _Exit(1);}
	char* doit=strdup(folde);
	char** comd=handler_ctrl(doit);int ioo=0;
	while(comd[ioo]!=NULL){ioo++;break;}
	if(ioo==0)return -1;
	char*mainlem=strtok(folde,"\n");char*cp_mainlem=strdup(mainlem);
	if(mainlem==NULL)return -1;
	cmd_parse=parse(cp_mainlem,";");
	strcpy(cp_cinp,mainlem);
	mainlem=strtok(folde," ");
	return 0;
}

int check_for_inp(char* folde)
{
	ind=0;cind=0;int already=0;pipo=0;
	int ret=store_cmdline(folde);
	if(ret==-1) return 1;
	else if(ret==3)return -1;
	for(int i=0;cmd_parse[i]!=NULL;++i)
	{
		bg=0;int piped=pipe_comm(cmd_parse[i]);if(piped!=-1)continue ;
		check_cmndbg(i);
		char*cp_cmnd=strdup(cmd_parse[i]);
		cinp=parse(cp_cmnd," &\n\t\v\f\r\a"); 
		for(int j=0;cinp[j]!=NULL;j++,cind++);
		if(is_mycomm(cinp[0])>=0)
		{
			perform(cinp[0]);is_bg();continue;
		}
		else if(is_advan(cinp[0])>=0)
		{
			int indo=is_advan(cinp[0]);
			if((indo>1)&&(ind<6))advan_funs("jobs");
			else advan_funs(cinp[0]);
			is_bg();continue;
		}
		pid_t str_pid,wai_pid;
		str_pid=fork();int status=0;
		if(str_pid==0)
		{
			if (bg) setpgid(0, 0);
			arg = redirect_handler(cmd_parse[i]);int check=is_mycomm(cinp[0]);
			if(!arg)exit(0);
			if(strcmp(cinp[0],"echo")==0)perform(cinp[0]);
			else if(check>=0){bg=0;perform(cinp[0]);}
			else{
			 check=execvp(arg[0],arg);if(check<0){perror("");_Exit(1);} }
			exit(0);
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
		free(cp_cmnd);
	}
	is_bg();
	return 0;
}

