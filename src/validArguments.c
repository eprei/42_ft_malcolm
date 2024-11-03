#include "../includes/ft_malcolm.h"

bool printUsage(){
  printf("%s: Usage: %s <source ip> <source mac address> <target ip> <target mac address>\n", PROGRAM_NAME, PROGRAM_NAME);
  return false;
}

bool printInvalidIpAddress(char *ipAddress){
  printf(RED "%s: unknown host or invalid IP address: %s\n" RESET, PROGRAM_NAME, ipAddress);
  return false;
}

bool printInvalidMacAddr(char *macAddress){
  printf(RED "%s: invalid mac address: %s\n" RESET, PROGRAM_NAME, macAddress);
  return false;
}

bool correctNumberOfArgs(const int argc){
  return argc == EXPECTED_NUMBER_OF_ARGUMENTS ? true : printUsage();
}

bool isIPv4(char *ipAddr){
  struct sockaddr_in sa;

  if (ipAddr == NULL){
    return printInvalidIpAddress(ipAddr);
  }

  const int result = inet_pton(AF_INET, ipAddr, &(sa.sin_addr));
  return result == 1 ? true : printInvalidIpAddress(ipAddr);
}

bool isHexDigit(char macDigit) {
  return (macDigit >= '0' && macDigit <= '9') ||
    (ft_tolower(macDigit) >= 'a' && ft_tolower(macDigit) <= 'f');
}

bool isValidMacAddr(char *macAddr){
  bool isValid = true;
  int i = 0;

  if (macAddr == NULL){
    return printInvalidMacAddr(macAddr);
  }

  while (isValid && macAddr[i] != 0 && macAddr[i]) {
    if (i == 2 || i == 5 || i == 8 || i == 11 || i == 14) {
      isValid = macAddr[i] == ':';
    } else {
      isValid = isHexDigit(macAddr[i]);
    }
    ++i;
  }

  return isValid && i == MAC_ADDRESS_LENGTH ? true : printInvalidMacAddr(macAddr);
}

bool validArguments(const int argc, char **argv){
  return correctNumberOfArgs(argc) &&
    isIPv4(argv[1]) && isValidMacAddr(argv[2]) &&
    isIPv4(argv[3]) && isValidMacAddr(argv[4]);
}

