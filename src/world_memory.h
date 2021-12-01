//
// Created by maro on 03.11.21.
//

#ifndef UG_PLUGIN_XBRAIDUTIL_WORLD_MEMORY_H
#define UG_PLUGIN_XBRAIDUTIL_WORLD_MEMORY_H

#include "memory_observer.h"
#include <vector>
#include "lib_disc/function_spaces/grid_function.h"
#include "lib_disc/time_disc/time_integrator_observers/time_integrator_observer_interface.h"

namespace ug {
    namespace XBraidUtil {

        unsigned long get_world_memory_consumed();

        unsigned long get_world_memory_peak();

        unsigned long get_spatial_memory_consumed();

        void get_world_memory_distribution();

        void get_spatial_memory_distribution();
    }
}

#endif //UG_PLUGIN_XBRAIDUTIL_WORLD_MEMORY_H
