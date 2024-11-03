#include "../includes/ft_malcolm.h"

int main (const int argc, char **argv){
  t_malcolm malcolm_struct;

  signal(SIGINT, sigint_handler);

  if (!valid_arguments(argc, argv)) {
    return -1;
  }

  populate_malcolm_struct(argv, &malcolm_struct);

  return launch_attack(malcolm_struct);
}
