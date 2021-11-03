//
// Created by maro on 03.11.21.
//

#ifndef UG_PLUGIN_XBRAIDUTIL_WORLD_MEMORY_H
#define UG_PLUGIN_XBRAIDUTIL_WORLD_MEMORY_H

#include "memory_observer.h"
#include <vector>
namespace ug {

    namespace XBraidUtil {


        unsigned long get_world_memory_consumed() {
            unsigned long world_memory = 0;
            auto this_proc_memory = get_physical_memory_consumed();

            MPI_Allreduce(&this_proc_memory,
                          &world_memory,
                          1, MPI_UNSIGNED_LONG, MPI_SUM,
                          MPI_COMM_WORLD);

            return world_memory;
        }

        unsigned long get_spatial_memory_consumed() {
            unsigned long world_memory = 0;
            auto this_proc_memory = get_physical_memory_consumed();

            MPI_Allreduce(&this_proc_memory,
                          &world_memory,
                          1, MPI_UNSIGNED_LONG, MPI_SUM,
                          PCL_COMM_WORLD);

            return world_memory;
        }


        std::vector<unsigned long> get_world_memory_distribution() {
            int size = 0;
            MPI_Comm_size(MPI_COMM_WORLD, &size);
            std::vector<unsigned long> distribution = std::vector<unsigned long>(size);

            unsigned long world_memory = 0;
            auto this_proc_memory = get_physical_memory_consumed();

            MPI_Allgather(&this_proc_memory, 1, MPI_UNSIGNED_LONG,
                           &distribution[0], 1, MPI_UNSIGNED_LONG,
                       MPI_COMM_WORLD);

            return distribution;
        }
    }}

#endif //UG_PLUGIN_XBRAIDUTIL_WORLD_MEMORY_H
