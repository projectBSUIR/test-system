#include <unistd.h>
#include <sys/types.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>

void processMemUsage(double& vmUsage, double& residentSet,pid_t pid);