#include<stdio.h>
#include<signal.h>
#include<string.h>
enum halt{
	REBOOT=1,
	POWEROFF
};
int main(int argc, char const *argv[]){
	for (int i = 0; i < argc ; i++){
		if (strcmp(argv[i], "reboot") == 0){
			kill(1, SIGRTMIN+REBOOT);
		}
		if (strcmp(argv[i], "poweroff") == 0){
			kill(1, SIGRTMIN+POWEROFF);
		}
	}
}

