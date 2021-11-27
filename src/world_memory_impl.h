//
// Created by maro on 27.11.21.
//

#ifndef UG_PLUGIN_XBRAIDUTIL_WORLD_MEMORY_IMPL_H
#define UG_PLUGIN_XBRAIDUTIL_WORLD_MEMORY_IMPL_H

#include "world_memory.h"

namespace ug {
    namespace XBraidUtil {

        unsigned long get_world_memory_consumed(){
            unsigned long world_memory = 0;
            auto this_proc_memory = get_physical_memory_consumed();

            MPI_Allreduce(&this_proc_memory,
                          &world_memory,
                          1, MPI_UNSIGNED_LONG, MPI_SUM,
                          MPI_COMM_WORLD);

            return world_memory;
        }

        unsigned long get_world_memory_peak(){
            unsigned long world_memory = 0;
            auto this_proc_memory = get_physical_memory_peak();

            MPI_Allreduce(&this_proc_memory,
                          &world_memory,
                          1, MPI_UNSIGNED_LONG, MPI_SUM,
                          MPI_COMM_WORLD);

            return world_memory;
        }

        unsigned long get_spatial_memory_consumed(){
            unsigned long world_memory = 0;
            auto this_proc_memory = get_physical_memory_consumed();

            MPI_Allreduce(&this_proc_memory,
                          &world_memory,
                          1, MPI_UNSIGNED_LONG, MPI_SUM,
                          PCL_COMM_WORLD);

            return world_memory;
        }


        void get_world_memory_distribution() {
            int size = 0;
            MPI_Comm_size(MPI_COMM_WORLD, &size);
            std::vector<unsigned long> distribution = std::vector<unsigned long>();
            distribution.resize(size);

            unsigned long * sbuf = (unsigned long *)malloc(1*sizeof(unsigned long));
            unsigned long * rbuf = (unsigned long *)malloc(size*sizeof(unsigned long));
            sbuf[0] = get_physical_memory_consumed();

            MPI_Allgather(sbuf, 1, MPI_UNSIGNED_LONG,
                          rbuf, 1, MPI_UNSIGNED_LONG,
                          MPI_COMM_WORLD);

            unsigned long summ = 0.0;
            for (int i = 0; i < size; i++) {
                summ += rbuf[i];
                std::cout << i << ": " << rbuf[i] << std::endl;
            } // todo return for lua?
            std::cout << "Total : " << summ << std::endl;
            //return distribution;
        }

        void get_spatial_memory_distribution() {
            int size = 0;
            MPI_Comm_size(PCL_COMM_WORLD, &size);
            std::vector<unsigned long> distribution = std::vector<unsigned long>();
            distribution.resize(size);

            unsigned long * sbuf = (unsigned long *)malloc(1*sizeof(unsigned long));
            unsigned long * rbuf = (unsigned long *)malloc(size*sizeof(unsigned long));
            sbuf[0] = get_physical_memory_consumed();

            MPI_Allgather(sbuf, 1, MPI_UNSIGNED_LONG,
                          rbuf, 1, MPI_UNSIGNED_LONG,
                          PCL_COMM_WORLD);
            unsigned long summ = 0.0;
            for(int i = 0; i < size; i++){
                summ += rbuf[i];
                std::cout << i << ": " << rbuf[i] << std::endl;
            } // todo return for lua?
            std::cout << "Total : " << summ << std::endl;
        }




        template<class TDomain, class TAlgebra>
        class MemoryObserver<TDomain TAlgebra>
                : public ITimeIntegratorObserver<TDomain, TAlgebra> {
        public:
            typedef ITimeIntegratorObserver <TDomain, TAlgebra> base_type;
            typedef GridFunction<TDomain, TAlgebra> grid_function_type;

            MemoryObserver() {}

            virtual ~MemoryObserver() {  }

            virtual bool step_process(SmartPtr <grid_function_type> uNew, int step, number time, number dt) override
        };
    }
}


#endif //UG_PLUGIN_XBRAIDUTIL_WORLD_MEMORY_IMPL_H
