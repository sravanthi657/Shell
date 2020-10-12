# Shell

## " To begin the shell run ./shell " 
### " To quit from the shell enter quit "


I implemented commands like <br />
 (1) cd
	in this: <br />
	(a) .  ./ <br />
	(b) ~  <br />
	(d) .. ../ <br />
	(c) Directory name <br />
<br />
(2) pwd<br />
(3) ls<br />
	(a) ls 	-a <br />
			--all<br />
	(b) ls -al <br />
		   -la <br />
		   -a -l <br />
			-a -l -l and so on <br />
	(c)		directory name different flags <br />
	(d)		flags directory name <br />
(4) echo <br />
(5) exit <br />

Handled background and foreground processes seperately. <br />
When the background processes id initalised it specifies its pid and state to us. <br />
also pinfo for shell and pinfo one flag. <br />
pinfo includes pid ans memory status exectuable path too. <br />

## Few more commands are:
<br /> 
bg , fg ,setenv , unsetenv , overkill are implmented. <br />
with constraints at arguments.