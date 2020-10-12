In my shell 
" To run the shell enter ./shell "


I implemented commands like 
(1) cd
	in this:
	(a) .  ./
	(b) ~ 
	(d) .. ../
	(c) Directory name

(2) pwd
(3) ls
	(a) ls 	-a 
			--all
	(b) ls -al 
		   -la
		   -a -l
			-a -l -l and so on
	(c)		directory name different flags
	(d)		flags directory name
(4) echo
(5) exit

Handled background and foreground processes seperately
When the background processes id initalised it specifies its pid and state to us.
also pinfo for shell and pinfo one flag.
pinfo includes pid ans memory status exectuable path too.


bg , fg ,setenv , unsetenv , overkill are implmented.
with constraints at arguments.