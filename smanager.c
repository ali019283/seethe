#include<stdio.h>
#include<signal.h>
#include<string.h>
#include<unistd.h>
enum halt{
	REBOOT=1,
	POWEROFF=2
};
int main(int argc, char const *argv[]){
	for (int i = 0; i < argc; i++){
		if (strcmp(argv[i], "reboot") == 0){
			kill(1, SIGRTMIN+REBOOT);
		}
		else if (strcmp(argv[i], "poweroff") == 0){
			kill(1, SIGRTMIN+POWEROFF);
		}
		else if (strcmp(argv[i], "enable") == 0){
			char b[120];
			sprintf(b, "/etc/seethe/services/%s", argv[i+1]);
			char a[120];
			sprintf(a, "/etc/seethe/runlevel/%s", argv[i+1]);
			symlink(b, a);
		}
	}
}

