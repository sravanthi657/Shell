#include"allin_header.h"
char *folder;int what_now=0;
void handle_ctrlC(int sig_num)
{
    if(CUR_FG==-1)
        return;
    kill(CUR_FG,SIGINT);
	fflush(stdout);
}
void handle_ctrlZ(int sig_num)
{
    if(CUR_FG==-1)
        return;
    kill(CUR_FG,SIGTSTP);
    bg_here[processp].str_pid = CUR_FG;
    bg_here[processp].status = 0;
    strcpy(bg_here[processp].cmd,CUR_FGis);
    processp++;
    printf("[+] %s [%d]\n",CUR_FGis,CUR_FG);
	fflush(stdout);
}


int main()
{
	
	char hostis[HOST_NAME_MAX+2];
	char useris[LOGIN_NAME_MAX+2];
	
	if(gethostname(hostis,HOST_NAME_MAX+2)!=0)perror("Hostname ");
	if(getlogin_r(useris,LOGIN_NAME_MAX+2)!=0)perror("login ");
	getcwd(shell_h,pm+2);strcpy(now,"~");
	size_t fold_sz=MAX_INPUT+1;folder=NULL;int read_inp;
	char *just="$";strcat(now,just);
	while(1)
	{
		getnoww(); 
		printf("\033[1;32m%s@%s:\033[1;35m%s ",useris,hostis,now);CUR_FG=-1;CUR_FGis=NULL;printf("\033[0m");
		signal(SIGINT,handle_ctrlC);signal(SIGTSTP,handle_ctrlZ);
		read_inp=getline(&folder,&fold_sz,stdin);
		if(read_inp){what_now=check_for_inp(folder);
			if(what_now==-1)exit(0);}
		is_bg();
	}
	return 0;
}
