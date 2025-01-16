#include "ft_malcolm.h"

extern volatile sig_atomic_t running;

void signal_handler(const int signal) {
    if (SIGINT == signal) {
        printf("Signal received: SIGINT\n");
        running = 0;
    }
}
