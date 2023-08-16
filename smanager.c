#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<signal.h>
int main(int argc, const char *argv[]){
	if (argc < 2){puts("err: too few arguments"); exit(1);}
	if (geteuid() != 0){puts("err: root privileges needed"); exit(1);}	
	for (int i = 1; i < argc; i++){
		if (!strcmp(argv[i], "enable")){
			if (i+1==argc){puts("enable: too few arguments for 'enable'");}
			for (int n = i+1; n < argc; n++){
				if (!strcmp(argv[n], "reboot") || !strcmp(argv[n], "poweroff") || !strcmp(argv[n], "disable")){
					if(!strcmp(argv[i],"enable")){
						puts("enable: too few arguments for 'enable'");
					}
					i = n - 1;	 
					break;
				}i = n;
				char a[277], c[277];
				snprintf(a, 277, "/etc/seethe/services/%s", argv[n]);
				snprintf(c, 277, "/etc/seethe/runlevel/%s", argv[n]);
				if (!access(a, F_OK)) {printf("enable: enabling service %s...\n", argv[n]);}
				else {printf("enable: '%s' could not be found\n", argv[n]); continue;}
				if (!access(c, F_OK)) {printf("enable: '%s' already enabled, enabling again...\n", argv[n]);}
				symlink(a, c);
			}
		}
		else if (!strcmp(argv[i], "disable")){
			if (i+1==argc){puts("disable: too few arguments for 'disable'");}
			for (int n = i+1; n < argc; n++){
				if (!strcmp(argv[n], "reboot") || !strcmp(argv[n], "poweroff") || !strcmp(argv[n], "enable")){
					if(!strcmp(argv[i],"disable")){
						puts("disable: too few arguments for 'disable'");
						break;
					} 
					i = n - 1;
					break;
				}i = n;
				char c[277];
				snprintf(c, 277, "/etc/seethe/runlevel/%s", argv[n]);
				if (access(c, F_OK)) {printf("disable: '%s' already disabled or removed, disabling again...\n", argv[n]);}
				else{printf("disable: disabling service %s...\n", argv[n]);}
				unlink(c);
			}
		}
		else if (!strcmp(argv[i], "reboot")){
			if (i+1<argc){
				if (!strcmp(argv[i+1], "now")){
					puts("rebooting NOW");
					kill(1, SIGRTMIN+1);
				}
			}
			puts("rebooting in ");
			for(int s = 3; s > 0; s--){
				sleep(1);
				printf("%d...\n", s);
			}
			puts("rebooting");
			kill(1, SIGRTMIN+1);
		}
		else if (!strcmp(argv[i], "poweroff")){
			if (i+1<argc){
				if (!strcmp(argv[i+1], "now")){
					puts("powering off NOW");
					kill(1, SIGRTMIN+2);
				}
			}
			puts("powering off in ");
			for(int s = 3; s > 0; s--){
				sleep(1);
				printf("%d...\n", s);
			}
			puts("powering off");
			kill(1, SIGRTMIN+2);
		}
		else {
			printf("unknown command '%s'\n", argv[i]);
		}
	}
	exit(0);
}
