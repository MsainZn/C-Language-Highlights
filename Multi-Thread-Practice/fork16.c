#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <signal.h>

void handle_SIGTSTP(int aig)
{
    printf("\nSignal cannot be stoped but for you i stop!\n");
    fflush(stdout);
}

void handle_SIGCONT(int sig)
{
    printf("Please Enter a number: ");    
    fflush(stdout);
}

int main(int argc, char *argv[])
{
    // struct sigaction sa_SIGTSTP;
    // sa_SIGTSTP.sa_handler = handle_SIGTSTP;
    // sa_SIGTSTP.sa_flags = SA_RESTART;
    // sigaction(SIGTSTP, &sa_SIGTSTP, NULL);

    struct sigaction sa_SIGCONT;
    sa_SIGCONT.sa_handler = handle_SIGCONT;
    sa_SIGCONT.sa_flags = SA_RESTART;
    sigaction(SIGCONT, &sa_SIGCONT, NULL);

    int d;
    printf("Please Enter a number: ");
    scanf(" %d", &d);
    printf("The Result is: %d\n", d * 3);

    return 0;
}