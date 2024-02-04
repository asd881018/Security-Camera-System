#ifndef UTILS_H_
#define UTILS_H_

#include <stdio.h>
#include <stdbool.h>

bool runCommand(char *command); 
void sleepForMs(long long delayInMs);
long long getTimeInMs();

#endif
