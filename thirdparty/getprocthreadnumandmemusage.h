#include <unistd.h>
#include <sys/types.h>
#include <ios>
#include <pthread.h>

#ifndef THIRDPARTY_THIRDPARTY_H
#define THIRDPARTY_THIRDPARTY_H

void getProcThreadNumAndMemUsage(int& threadNum,double& vmUsage, double& residentSet,pid_t pid);

#endif