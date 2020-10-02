shell : shell.c my_comm.c perform_funs.c main.c pipe_comm.c redirect_comm.c
	    gcc -o shell shell.c my_comm.c perform_funs.c main.c pipe_comm.c redirect_comm.c