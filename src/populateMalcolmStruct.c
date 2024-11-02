#include "../includes/ft_malcolm.h"

void populateMalcolmStruct(char **argv, t_malcolm *malcolm_struct){
  malcolm_struct->sourceIp = argv[1];
  malcolm_struct->sourceMacAddress = argv[2];
  malcolm_struct->targetIp = argv[3];
  malcolm_struct->targetMacAddress = argv[4];
}