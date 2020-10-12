#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <limits.h>
#include<string.h>
#include<errno.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include <sys/types.h>
#include<sys/stat.h>
#include<dirent.h>
#include<time.h>
#include<pwd.h>
#include<grp.h>
#include<signal.h>
#include<ctype.h>

#define pm PATH_MAX

char pwdis[pm+2],now[pm+2];  char* CUR_FGis;char*s_is;
char *lsdir[pm+2]; char **cinp; 
char shell_h[pm+2]; char *arr_pid[10000000];
pid_t CUR_FG;extern int ind,cind,bg,pipo;
extern char cp_cinp[MAX_INPUT+1];

//parse_trim.c
char** parse(char * cmnd, char* breakat);
char* clearstring(char *cmd);
//my_comm.c
int perform(char*cmd);

//advan_comm.c
int advan_funs(char* cmnd);

//advan_perform.c
int run_unsetenv();
int run_setenv();
int run_jobs();
// perform_funs.c
int cd(char * flag);
int ls(char * flag,int see);
int pinf(int pid);
int direxists(char* dirname);
//shell.c
int is_bg();
int check_for_inp(char * folder);
void getnoww();
int is_mycomm(char *cmnd);
int is_advan(char* cmnd);

//pipe_comm.c
int pipe_comm();
char* clearstring(char *cmd);
//redirect_comm.c
char** redirect_handler (char* arg);
char** parse(char * cmnd, char* breakat);



struct any_process
{
  int  str_pid;
  char cmd[1024];
  int status; //status 1 shows running 0 shows stopped
}bg_here [1024];
extern int processp;
struct list_processes {
	char* cur_pid;
	char cur_name[1024];
	char cur_status[128];
	char cur_stime[128];
}jobs_are;
extern struct list_processes present_jobs[2221];int lim_jb;
