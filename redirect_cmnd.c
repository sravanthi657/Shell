#include "allin_header.h"
int r1 = -1, w1 = -1;

char** redirect_handler (char* arg)
{
	int flag = 0, arg_len = strlen(arg);
	for (int i=0; i<arg_len; ++i)
		if (arg[i] == '<' || arg[i] == '>')
		{
			flag = 1;
			break;
		}
	if(!flag){return parse(arg," &\n\t\v\f\r\a");}
	char* cmd = (char*)malloc(sizeof(char)*(arg_len+2));
	cmd[0] = '\0';
	int ind = 0, to_append = 0;
	while (arg[ind] != '<' && arg[ind] != '>' && ind < arg_len)
	{
		cmd[ind] = arg[ind];
		ind++;
	}
	cmd[ind] = '\0';
	char* read_inp = (char*)malloc(sizeof(char)*(arg_len+1));
	char* write_out = (char*)malloc(sizeof(char)*(arg_len+1));
	read_inp[0] = write_out[0] = '\0';
	for (int i=ind; i<arg_len;)
	{
		int j,k;
		if (arg[i] == '>' && arg[i+1] != '>')
		{
			j = i + 1;
			while (arg[j] != '<' && j < arg_len)
				j++;
			k = j;
			while (arg[k] != '>') k--;
			if (arg[k-1] == '>') to_append = 1;
			for (ind=k+1; ind<j; ++ind)
				write_out[ind-k-1] = arg[ind];
			write_out[j-k-1] = '\0';
			i = j;
			continue;
		}
		if (arg[i] == '>' && arg[i+1] == '>')
		{
			j = i + 2;
			while (arg[j] != '<' && j < arg_len)
				j++;
			k = j;
			while (arg[k] != '>') k--;
			if (arg[k-1] == '>') to_append = 1;
			for (ind=k+1; ind<j; ++ind)
				write_out[ind-k-1] = arg[ind];
			write_out[j-k-1] = '\0';
			i = j;
			continue;
		}
		if (arg[i] == '<')
		{
			j = i + 1;
			while (arg[j] != '>' && j < arg_len)
				j++;
			k = j;
			while (arg[k] != '<') k--;
			for (ind=k+1; ind<j; ++ind)
				read_inp[ind-k-1] = arg[ind];
			read_inp[j-k-1] = '\0';
			i = j;
			continue;
		}
	}
	char temp[arg_len];char emp[arg_len];
	char*s=strdup(read_inp);strcpy(temp,clearstring(s));strcpy(read_inp,temp);
	s=strdup(write_out);strcpy(emp,clearstring(s));strcpy(write_out,emp);free(s);
	int read_len = strlen(read_inp), len_write_out = strlen(write_out);
	if (len_write_out == 0 && read_len == 0)
	{
		fprintf(stderr, "Error: invalid format\n");
		return NULL;
	}
	struct stat st;r1 = -1, w1 = -1;
	if (read_len > 0)
	{
		if (stat(read_inp, &st) == -1)
		{
			fprintf(stderr, " \"%s\" %s\n",read_inp,strerror(errno));
			return NULL;	
		}
		if (!S_ISREG(st.st_mode))
		{
			fprintf(stderr, "Error: file to read from is not a regular file\n");
			return NULL;
		}
		r1 = open(read_inp, O_RDONLY);
		if (r1 == -1)
		{
			fprintf(stderr, "Error: failed to open file to read from\n");
			return NULL;
		}
		if (dup2(r1, 0) != 0)
		{
			fprintf(stderr, "Error: dup2 fail\n");
			return NULL;
		}
	}
	if (len_write_out > 0)
	{
		if (to_append)
			{w1 = open(write_out, O_WRONLY|O_CREAT|O_APPEND, 0644); }
		else w1 = open(write_out, O_WRONLY|O_CREAT|O_TRUNC, 0644);
		if (dup2(w1, 1) != 1)
		{
			fprintf(stderr, "Error: dup2 fail\n");
			return NULL;
		}
	}
	free(write_out);
	free(read_inp);
	return parse(cmd," &\n\t\v\f\r\a");
}
