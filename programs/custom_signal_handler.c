#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Global variable to count signal triggers
volatile sig_atomic_t signal_count = 3;

void handle_sigint(int sig) { 
    signal_count--;
    printf("\tSIGINT handled\n");
}

int main() {
    struct sigaction sa;
    sa.sa_handler = handle_sigint;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        return -1;
    }

    printf("Program running (PID: %d). Try pressing Ctrl+C...\n", getpid());

    while (signal_count > 0) {
        sleep(1);
    }

    printf("received 3 SIGINT signals.\n");
    return 0;
}

