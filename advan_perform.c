#include "allin_header.h"

 struct list_processes present_jobs[2221];
int cmp (const void *a, const void *b)
{
	struct list_processes *aa = (struct list_processes*)a;
	struct list_processes *bb = (struct list_processes*)b;
	return atoi(aa->cur_stime) - atoi(bb->cur_stime);
}

int run_setenv()
{
	if(cind==1)fprintf(stderr, "Error: too few arguments to \"setenv\"\n");
	else if (cind > 3)
		fprintf(stderr, "Error: too many arguments to \"setenv\"\n");
	else if (cind == 2)
	{
		if (setenv(cinp[1], "", 1) != 0)
			fprintf(stderr, "Error: cannot set variable %s\n", cinp[1]);
	}
	else if (cind == 3)
	{
		if (setenv(cinp[1], cinp[2], 1) != 0)
			fprintf(stderr, "Error: cannot set variable %s\n", cinp[1]);
	}
	return 0;
}
 int run_unsetenv()
 {
 	if (cind == 0)
	{
		fprintf(stderr, "Error: too few arguments to \"insetenv\"\n");
	}
	else if (cind > 2)
	{
		fprintf(stderr, "Error: too many arguments to \"insetenv\"\n");}
	else if (cind == 2)
	{
		if (unsetenv(cinp[1]) != 0)
			fprintf(stderr, "Error: In unsetting the variable\n");
	}
	return 0;
 }
int proc_sz=512; 
int run_jobs()
 {
 	lim_jb=0; struct stat st;struct dirent *target;
 	DIR *dir = opendir("/proc");
	char path[2048], temp[2048];
	char* buff;int is_so=0;
	while (target = readdir(dir))
	{
		strcpy(path, "/proc/");
		strcat(path, target->d_name);stat(path, &st);
		//printf("path -> %s\n",path);
		if (S_ISDIR(st.st_mode) )
		{
			if((target->d_name[0] - '0' >= 1) && (target->d_name[0] - '0' <= 9))
			{
				present_jobs[lim_jb].cur_pid = target->d_name;
				strcpy(temp, present_jobs[lim_jb].cur_pid);
				char*t_temp=clearstring(temp);
				strcpy(present_jobs[lim_jb].cur_pid,t_temp);
				lim_jb++;
			}
		}
		is_so++;
	}
	for (int i=0; i<lim_jb; ++i)
	{
		strcpy(path, "");snprintf(path,2048,"/proc/%s/stat",present_jobs[i].cur_pid);
		int fd = open(path, O_RDONLY);
		char s[2048];
		read(fd, s, 10000);
		int j=0,ct= 0;
		while (ct < 21)
			if (isspace(s[j]))
			{
				++ct;
				++j;
			}
			else ++j;
		ct = 0;
		while (!isspace(s[j]))
			present_jobs[i].cur_stime[ct++] = s[j++];
		present_jobs[i].cur_stime[ct] = '\0';
		strcpy(temp, present_jobs[i].cur_stime);
		char* t_temp=clearstring(temp);
		strcpy(present_jobs[i].cur_stime,t_temp);
		strcpy(path, "");snprintf(path,2048,"/proc/%s/status",present_jobs[i].cur_pid);
		FILE* file = fopen(path, "r");
		if(file==NULL)
		{	perror("file path at jobs");return 1;}
	//printf("into file%d\n",file);
		size_t sz = 0;
		while (getline(&buff, &sz, file) != -1)
		{
			if (strncmp("Name",buff,4) == 0)
			{
				char*h_temp=clearstring(buff+5);
				strcpy(present_jobs[i].cur_name,h_temp);
				//printf("Name after trim => \t %s\n",present_jobs[i].cur_name);
			}
			else if (strncmp("State", buff,5) == 0)
			{
				char*h_temp=clearstring(buff+6); 
				strcpy(present_jobs[i].cur_status,h_temp);
				//printf("State after trim => \t %s\n",present_jobs[i].cur_status);
				break;
			}
		}
		fclose(file);
		close(fd);
	}
	//arrange from oldest to latest processes by using qsort
	qsort(present_jobs, lim_jb, sizeof(jobs_are), cmp);
	if (strcmp(cinp[0],"jobs")==0)
	{
		for (int i=0; i<lim_jb; ++i)
			printf("[%d]\t%s\t%s\t%s\t%s\n", i+1, present_jobs[i].cur_status, present_jobs[i].cur_name, present_jobs[i].cur_pid, present_jobs[i].cur_stime);
	}
	else
	{
		if(strcmp(cinp[0],"kjob")==0)
		{
			if(cind==3)
			{
				kill(atoi(present_jobs[atoi(cinp[1])].cur_pid),atoi(cinp[2])); return 0;
			}
			else{
				 fprintf(stderr, "Error: invalid input\n"); return 1;}

		}
		else if(strcmp(cinp[0],"fg")==0)
		{
			if(cind!=2){fprintf(stderr, "Error: invalid format\n");
				return 1 ;}
			int job_no=atoi(cinp[1]);
			if(job_no>lim_jb){fprintf(stderr, "Error: Provided invalid Job Nimber\n");
				return 1;}
			kill(atoi(present_jobs[job_no-1].cur_pid),SIGCONT);
			int status;
			waitpid(atoi(present_jobs[job_no-1].cur_pid),&status,WUNTRACED);
		}
		else if(strcmp(cinp[0],"bg")==0)
		{
			if(cind!=2){fprintf(stderr, "Error: invalid format\n");
				return 1 ;}
			int job_no=atoi(cinp[1]);
			if(job_no>lim_jb){fprintf(stderr, "Error: Provided invalid Job Nimber\n");
				return 1;}
			printf("[+] %s with pid [%d] started a BG process\n",present_jobs[job_no-1].cur_name,atoi(present_jobs[job_no-1].cur_pid));
			kill(atoi(present_jobs[job_no-1].cur_pid),SIGCONT);
		}
	}
	return 0;
 }

