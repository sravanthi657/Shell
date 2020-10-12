#include "allin_header.h"

int advan_funs(char* cmnd)
{
	if(strcmp("setenv",cmnd)==0)
	{
		run_setenv();
	}
	else if(strcmp("unsetenv",cmnd)==0)
	{
		run_unsetenv();
	}
	else if(strcmp("jobs",cmnd)==0){
		run_jobs();
	}
	else if(strcmp("overkill",cmnd)==0)
	{
		for(int i=0;i<processp;i++)
		{
			kill(bg_here[i].str_pid,9);
			bg_here[i].status=0;
		}
	}
	return 0;
}