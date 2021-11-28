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

        unsigned long parseLine(char *line);

        unsigned long get_virtual_memory_total();

        unsigned long get_virtual_memory_used();

        unsigned long get_virtual_memory_peak();

        unsigned long get_physical_memory_total();

        unsigned long get_physical_memory_used();

        unsigned long get_physical_memory_consumed();

        unsigned long get_physical_memory_peak();

        unsigned long get_virtual_memory_consumed();

        unsigned long get_virtual_memory_peak();

        unsigned long get_physical_memory_total();

        unsigned long get_physical_memory_used();

        unsigned long get_physical_memory_consumed();

        unsigned long get_physical_memory_peak();
    }
}


#endif //UG_PLUGIN_XBRAIDUTIL_MEMORY_OBSERVER_H
