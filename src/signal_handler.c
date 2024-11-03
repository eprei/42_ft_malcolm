#include "../includes/ft_malcolm.h"

void sigint_handler(int sig) {
    (void)sig;
    printf("SIGINT received\n");
    // TODO free memory and ressources
    // TODO not print ^C
}