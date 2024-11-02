#include "../includes/ft_malcolm.h"

void sigintHandler(int sig) {
    (void)sig;
    printf("SIGINT received\n");
    // TODO free memory
    // TODO not print ^C
}