#include<stdio.h>
#include<signal.h>
#include<sys/reboot.h>  
#include<unistd.h>
enum halt{
	REBOOT=1,
	POWEROFF=2
};
void sig_handle(int signal, void (*handler)(int)){
    struct sigaction sa;
    sa.sa_handler = handler;
    sigaction(signal, &sa, NULL);
}
void poweroff(){
	reboot(RB_POWER_OFF);	
}
void restart(){
	reboot(RB_AUTOBOOT);
}
int main(int argc, char *argv[]){
	pid_t pid = fork();
	if (pid == 0) {
		execv("/etc/seethe/1", &argv[0]);
	}
	sig_handle(SIGRTMIN+REBOOT, restart);
	sig_handle(SIGRTMIN+POWEROFF, poweroff);
	while(1)
		pause();
	return 0;
}
