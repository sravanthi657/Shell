#include<stdio.h>
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
#define pm PATH_MAX

char pwdis[pm+2],now[pm+2];  char* CUR_FGis;
char *lsdir[pm+2]; char *cinp[pm+2]; 
char shell_h[pm+2]; char *arr_pid[10000000];
pid_t CUR_FG;extern int ind,cind;
//my_comm.c
int perform(char*cmd);
// perform_funs.c
int cd(char * flag);
int ls(char * flag,int see);
int pinf(int pid);
int direxists(char* dirname);
//shell.c
int is_bg();
void check_for_inp(char * folder);
void getnoww();
struct any_process
{
  int  str_pid;
  char cmd[1024];
  int status; //status 1 shows running 0 shows stopped
}bg_here [1024];

extern int processp;
