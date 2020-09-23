#include"allin_header.h"

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
	size_t fold_sz=256;char *folder=NULL;int read_inp;
	char *just="$";strcat(now,just);
	while(1)
	{
		getnoww(); signal(SIGINT,handle_ctrlC);signal(SIGTSTP,handle_ctrlZ);
		printf("%s@%s:%s ",useris,hostis,now);
		read_inp=getline(&folder,&fold_sz,stdin);
		if(read_inp)check_for_inp(folder);
		is_bg();
	}
	return 0;
}
