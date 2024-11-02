#ifndef FT_MALCOLM_H
# define FT_MALCOLM_H

# include "libraries.h"
# include "macros.h"
# include "colours.h"

typedef struct s_malcolm
{
    char *sourceIp;
    char *sourceMacAddress;
    char *targetIp;
    char *targetMacAddress;
}	t_malcolm;

int launchAttack(t_malcolm malcolmStruct);
bool validArguments(int argc, char **argv);
void populateMalcolmStruct(char ** argv, t_malcolm *malcolm_struct);

void sigintHandler(int sig);

#endif
