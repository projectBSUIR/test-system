#include <unistd.h>
#include <sys/types.h>
#include <ios>
#include <iostream>
#include <fstream>
#include <string>
#include <pthread.h>

#include "thirdparty/processmemusage.h"

void processMemUsage(double& vmUsage, double& residentSet,pid_t pid){
   vmUsage     = 0.0;
   residentSet = 0.0;
   std::string path="/proc/"+std::to_string(pid)+"/stat";
   std::ifstream stat_stream(path,std::ios_base::in);

   std::string dummy;

   unsigned long vsize=0;
   long rss=0;

    for(int i=0;i<22;i++){
        stat_stream>>dummy;
    }
    stat_stream>>vsize;
    stat_stream>>rss;
    /*
   stat_stream >> pid >> comm >> state >> ppid >> pgrp >> session >> tty_nr//7
               >> tpgid >> flags >> minflt >> cminflt >> majflt >> cmajflt//13
               >> utime >> stime >> cutime >> cstime >> priority >> nice//19
               >> O >> itrealvalue >> starttime >> vsize >> rss; // don't care about the rest*/

   stat_stream.close();

   long page_size_kb = sysconf(_SC_PAGE_SIZE) / 1024; // in case x86-64 is configured to use 2MB pages
   vmUsage     = vsize / 1024.0;
   residentSet = rss * page_size_kb;
}
