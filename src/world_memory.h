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


        void get_world_memory_distribution() ;

        void get_spatial_memory_distribution();


        template<class TDomain, class TAlgebra>
        class MemoryObserver
                : public ITimeIntegratorObserver<TDomain, TAlgebra> {
        public:
            typedef ITimeIntegratorObserver <TDomain, TAlgebra> base_type;
            typedef GridFunction<TDomain, TAlgebra> grid_function_type;

            MemoryObserver() {}

            virtual ~MemoryObserver() {  }

            virtual bool step_process(SmartPtr <grid_function_type> uNew, int step, number time, number dt) override{
                get_world_memory_distribution();
                return true;
            };
        };
    }}

#endif //UG_PLUGIN_XBRAIDUTIL_WORLD_MEMORY_H
