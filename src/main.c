#include "../includes/ft_malcolm.h"

int main (const int argc, char **argv){
  t_malcolm malcolmStruct;

  signal(SIGINT, sigintHandler);

  if (!validArguments(argc, argv)) {
    return -1;
  }

  populateMalcolmStruct(argv, &malcolmStruct);

  return launchAttack(malcolmStruct);
}
