#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
int main(int argc, const char *argv[]){
	if (argc < 2){puts("It needs some flags to work properly, unfortunately this program can't understand what you want by mind reading."); exit(1);}
	for (int i = 0; i < argc; i++){
		if (!strcmp(argv[i], "enable")){
			for (int b = i+1; b < argc; b++){
				if (!strcmp(argv[b], "reboot") || !strcmp(argv[b], "poweroff" || !strcmp(argv[b], "disable")){i = b; break;}
				char a[277], c[277];
				snprintf(a, 277, "/etc/seethe/services/%s", argv[b]);
				snprintf(c, 277, "/etc/seethe/runlevel/%s", argv[b]);
				symlink(a, c);
			}
		}
		if (!strcmp(argv[i], "disable")){
			for (int n = i+1; n < argc; n++){
				char c[277];
				snprintf(c, 277, "/etc/seethe/runlevel/%s", argv[b]); 
				unlink(c); break;
			}
		}
		else if (!strcmp(argv[i], "reboot")){kill(1, SIGRTMIN+1);}
		else if (!strcmp(argv[i], "poweroff")){kill(1, SIGRTMIN+2);}
	}
	exit(0);
}
