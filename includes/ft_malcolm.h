#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include "libraries.h"
# include "macros.h"
# include "colours.h"
# include "packages.h"
# include "messages_to_print.h"

typedef struct s_malcolm
{
    char *source_ip;
    char *source_mac_address;
    char *targetIp;
    char *targetMacAddress;
}	t_malcolm;

int launch_attack(t_malcolm malcolmStruct);
bool valid_arguments(int argc, char **argv);
void populate_malcolm_struct(char ** argv, t_malcolm *malcolm_struct);

void sigint_handler(int sig);

#endif
