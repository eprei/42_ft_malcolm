#include "../includes/ft_malcolm.h"

void populate_malcolm_struct(char **argv, t_malcolm *malcolm_struct){
  malcolm_struct->source_ip = argv[1];
  malcolm_struct->source_mac_address = argv[2];
  malcolm_struct->targetIp = argv[3];
  malcolm_struct->targetMacAddress = argv[4];
}