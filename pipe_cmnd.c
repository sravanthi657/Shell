#include "allin_header.h"
int fildes[2],prev,nex;
void check_pipe_arrangement(int index)
{
	if (index == 0){
			prev =0;nex = 1;}
	else if (index ==pipo){
			prev = 1;nex = 0;}
	else {nex =1; prev = 1;}
}

int pipe_comm(char* cmd)
{
	//printf("pipe_comm %s",cp_cinp);
	char*s=strdup(cmd);
	char** pipe_parsed=parse(s,"|");
	for(int i=0;pipe_parsed[i]!=NULL;i++){pipo++;}
	pipo--;
	if(pipo==0){free(s);return -1;}
	int input_f=dup(0);int output_f=dup(1);
	for (int i=0;i<=pipo;++i)
	{
		char** array;
		check_pipe_arrangement(i);
		if (prev)
		{
			close(fildes[1]);
			input_f = dup(0);
			if (dup2(fildes[0], 0) == -1)
				fprintf(stderr, "Error: dup2 failed\n");
			close(fildes[0]);
		}
		if (nex)
		{
			pipe(fildes);
			output_f = dup(1);
			if (dup2(fildes[1], 1) == -1)
				fprintf(stderr, "Error: dup2 failed\n");
		}
		//printf("till now ok\n");
		pid_t str_pid;int status;
		str_pid = fork();
		if (str_pid == 0)
		{
			array = redirect_handler(pipe_parsed[i]);
			//printf("from pipe\n");
			if (!array) exit(0);
			int x = is_mycomm(pipe_parsed[i]);
			if (x >= 0) perform(pipe_parsed[i]);
			else {execvp(array[0], array);}
			exit(EXIT_SUCCESS);
		}
		else 
		{
			waitpid(str_pid, &status, WUNTRACED);dup2(input_f,0);dup2(output_f,1);
		}

	}
	free(s);
	return 4;
}
