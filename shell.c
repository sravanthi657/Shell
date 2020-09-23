#include"allin_header.h"
int ind=0,cind=0,processp=0;

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

int store_cmdline(char * folder)
{
	char *mainlem=strtok(folder,"\n");
	mainlem=strtok(folder," ");cind=0;
	while(mainlem!=0)
	{
		cinp[cind]=mainlem;cind++;
		mainlem=strtok(0," ");
	}
	if((strcmp(cinp[cind-1],"&")==0)){ cinp[cind-1]=NULL;return 1;}
	return 0;
}

void check_for_inp(char * folder)
{
	ind=0,cind=0;int already=0;
	int bg=store_cmdline(folder);
	if((strcmp("cd",cinp[0])==0)||(strcmp("pwd",cinp[0])==0)||(strcmp("echo",cinp[0])==0)||(strcmp("ls",cinp[0])==0)||(strcmp("exit",cinp[0])==0)){perform(cinp[0]);is_bg();return;}
	if(cind!=0)
	{
		pid_t str_pid,wai_pid;
		str_pid=fork();int status=0;
		if(str_pid==0)
		{
			int check=execvp(cinp[0],cinp);
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
	else
		perror("Input is nothing or space ");
	is_bg();
	return;
}

