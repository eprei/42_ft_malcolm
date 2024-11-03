#include "../includes/ft_malcolm.h"

bool print_usage(){
  printf(USAGE_MSG);
  return false;
}

bool print_invalid_ip_address(const char *ip_address){
  printf(INVALID_IP_MSG, ip_address);
  return false;
}

bool print_invalid_mac_addr(char *mac_address){
  printf(INVALID_IP_MSG, mac_address);
  return false;
}

bool correct_number_of_args(const int argc){
  return argc == EXPECTED_NUMBER_OF_ARGUMENTS ? true : print_usage();
}

bool is_ip_v4(const char *ip_address){
  struct sockaddr_in sa;

  if (ip_address == NULL){
    return print_invalid_ip_address(ip_address);
  }

  const int result = inet_pton(AF_INET, ip_address, &(sa.sin_addr));
  return result == 1 ? true : print_invalid_ip_address(ip_address);
}

bool is_hex_digit(const char mac_digit) {
  return (mac_digit >= '0' && mac_digit <= '9') ||
    (ft_tolower(mac_digit) >= 'a' && ft_tolower(mac_digit) <= 'f');
}

bool is_valid_mac_addr(char *mac_address){
  bool is_valid = true;
  int i = 0;

  if (mac_address == NULL){
    return print_invalid_mac_addr(mac_address);
  }

  while (is_valid && mac_address[i] != 0 && mac_address[i]) {
    if (i == 2 || i == 5 || i == 8 || i == 11 || i == 14) {
      is_valid = mac_address[i] == ':';
    } else {
      is_valid = is_hex_digit(mac_address[i]);
    }
    ++i;
  }

  return is_valid && i == MAC_ADDRESS_LENGTH ? true : print_invalid_mac_addr(mac_address);
}

bool valid_arguments(const int argc, char **argv){
  return correct_number_of_args(argc) &&
    is_ip_v4(argv[1]) && is_valid_mac_addr(argv[2]) &&
    is_ip_v4(argv[3]) && is_valid_mac_addr(argv[4]);
}

