#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
int main(int argc, const char *argv[]){
	if (argc < 3) exit(1);
	if (!strcmp(argv[1], "enable")) {
		for (int i = 2; i < argc; i++) {
			char b[277], a[277];
			snprintf(b, 277, "/etc/seethe/services/%s", argv[i]);
			snprintf(a, 277, "/etc/seethe/runlevel/%s", argv[i]);
			symlink(b, a);
		}
	}
	else if (!strcmp(argv[1], "reboot")){kill(1, SIGRTMIN+1);}
	else if (!strcmp(argv[1], "poweroff")){kill(1, SIGRTMIN+2);}
	exit(0);
}
