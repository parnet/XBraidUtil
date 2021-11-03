//
// Created by parnet on 08.10.21.
//

#ifndef UG_PLUGIN_XBRAIDUTIL_MEMORY_OBSERVER_H
#define UG_PLUGIN_XBRAIDUTIL_MEMORY_OBSERVER_H

#include "sys/types.h"
#include "sys/sysinfo.h"

#include <cstdlib>
#include <cstdio>
#include <cstring>


// basing on https://stackoverflow.com/questions/63166/how-to-determine-cpu-and-memory-consumption-from-inside-a-process
namespace ug {

    namespace XBraidUtil {

        unsigned long parseLine(char *line) {
            unsigned long i = strlen(line);
            const char *p = line;
            while (*p < '0' || *p > '9') p++;
            line[i - 3] = '\0';
            i = atoi(p);
            return i;
        }

            unsigned long get_virtual_memory_total() {
                struct sysinfo memInfo;
                sysinfo (&memInfo);
                unsigned long totalVirtualMem = memInfo.totalram;
                totalVirtualMem += memInfo.totalswap;
                totalVirtualMem *= memInfo.mem_unit;
                return totalVirtualMem;
            }

            unsigned long get_virtual_memory_used() {
                struct sysinfo memInfo;
                sysinfo (&memInfo);
                unsigned long virtualMemUsed = memInfo.totalram - memInfo.freeram;
                virtualMemUsed += memInfo.totalswap - memInfo.freeswap;
                virtualMemUsed *= memInfo.mem_unit;
                return virtualMemUsed;
            }


            unsigned long get_virtual_memory_consumed() {
                FILE *file = fopen("/proc/self/status", "r");
                unsigned long result = -1;
                char line[128];

                while (fgets(line, 128, file) != nullptr) {
                    if (strncmp(line, "VmSize:", 7) == 0) {
                        result = parseLine(line);
                        break;
                    }
                }
                fclose(file);
                return result;
            }

            unsigned long get_physical_memory_total() {
                struct sysinfo memInfo;
                unsigned long totalPhysMem = memInfo.totalram;
                totalPhysMem *= memInfo.mem_unit;
                return totalPhysMem;
            }

            unsigned long get_physical_memory_used() {
                struct sysinfo memInfo;
                unsigned long physMemUsed = memInfo.totalram - memInfo.freeram;
                physMemUsed *= memInfo.mem_unit;
                return physMemUsed;
            }

            unsigned long get_physical_memory_consumed() {
                FILE *file = fopen("/proc/self/status", "r");
                unsigned long result = -1;
                char line[128];

                while (fgets(line, 128, file) != nullptr) {
                    if (strncmp(line, "VmRSS:", 6) == 0) {
                        result = parseLine(line);
                        break;
                    }
                }
                fclose(file);
                return result;
            }


    }
}


#endif //UG_PLUGIN_XBRAIDUTIL_MEMORY_OBSERVER_H
