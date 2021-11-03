//
// Created by parnet on 20.09.21.
//


//
// Created by parnet on 09.06.21.
//

//
// Created by parnet on 09.06.21.
//

//  zzzzz
// Created by parnet on 12.05.19.
//


#include "bridge/util.h"
#include "bridge/util_domain_algebra_dependent.h"

#include "memory_observer.h"
#include "world_memory.h"
#include "io_gridfunction.h"
#include "parallel_io_gridfunction.h"

using namespace std;
using namespace ug::bridge;

namespace ug {
    namespace XBraidUtil {
        struct Functionality {
            template<typename TDomain, typename TAlgebra>
            static void DomainAlgebra(Registry &reg, string grp) {

                string suffix = GetDomainAlgebraSuffix<TDomain, TAlgebra>();
                string tag = GetDomainAlgebraTag<TDomain, TAlgebra>();


                {
                    typedef IOGridFunction<TDomain, TAlgebra> TIOGridFunction;
                    string name_gf = string("IOGridFunction").append(suffix);
                    reg.add_class_<TIOGridFunction>(name_gf, grp)
                            .add_constructor()
                            .add_method("write", &TIOGridFunction::write, "None", "verbose","set the level of verbose (true / false)")
                            .add_method("read", &TIOGridFunction::read, "None", "verbose","set the level of verbose (true / false)")
                                    //.add_method("set_adapt_convergence", &TBraidIntegrator::set_adapt_conv, "None", "initial time","set t0 as initial time")
                            .set_construct_as_smart_pointer(true);
                    reg.add_class_to_group(name_gf, "IOGridFunction", tag);
                }
                {
                    typedef PIOGridFunction<TDomain, TAlgebra> TIOGridFunction;
                    string name_gf = string("PIOGridFunction").append(suffix);
                    reg.add_class_<TIOGridFunction>(name_gf, grp)
                            .add_constructor()
                            .add_method("write", &TIOGridFunction::write, "None", "verbose","set the level of verbose (true / false)")
                            .add_method("read", &TIOGridFunction::read, "None", "verbose","set the level of verbose (true / false)")
                                    //.add_method("set_adapt_convergence", &TBraidIntegrator::set_adapt_conv, "None", "initial time","set t0 as initial time")
                            .set_construct_as_smart_pointer(true);
                    reg.add_class_to_group(name_gf, "PIOGridFunction", tag);
                }
            }


            template<typename TDomain>
            static void Domain(Registry &reg, string grp) {
                /*
                string suffix = GetDomainSuffix<TDomain>();
                string tag = GetDomainTag<TDomain>();
                 */

            }

            template<int dim>
            static void Dimension(Registry &reg, string grp) {
                /*
                string suffix = GetDimensionSuffix<dim>();
                string tag = GetDimensionTag<dim>();
                 */
            }

            template<typename TAlgebra>
            static void Algebra(Registry &reg, string grp) {
                string suffix = GetAlgebraSuffix<TAlgebra>();
                string tag = GetAlgebraTag<TAlgebra>();
            }

            static void Common(Registry &reg, string grp) {
                reg.add_function("get_virtual_memory_total",&XBraidUtil::get_virtual_memory_total,"","","");
                reg.add_function("get_virtual_memory_used",&XBraidUtil::get_virtual_memory_used,"","","");
                reg.add_function("get_virtual_memory_consumed",&XBraidUtil::get_virtual_memory_consumed,"","","");
                reg.add_function("get_physical_memory_total",&XBraidUtil::get_physical_memory_total,"","","");
                reg.add_function("get_physical_memory_used",&XBraidUtil::get_physical_memory_used,"","","");
                reg.add_function("get_physical_memory_consumed",&XBraidUtil::get_physical_memory_consumed,"","","");

                reg.add_function("get_world_memory_consumed",&XBraidUtil::get_world_memory_consumed,"","","");
                reg.add_function("get_spatial_memory_consumed",&XBraidUtil::get_spatial_memory_consumed,"","","");
                reg.add_function("get_world_memory_distribution",&XBraidUtil::get_world_memory_distribution,"","","");
                reg.add_function("get_spatial_memory_distribution",&XBraidUtil::get_spatial_memory_distribution,"","","");
            }

        };
    } // end namespace XBraidIntegrator


    struct FunctionalityFor2D
    {
        template <typename TDomain, typename TAlgebra>
        static void DomainAlgebra(Registry& reg, string grp)
        {

        }
    };





    extern "C" void
    InitUGPlugin_XBraidUtil(Registry *reg, string grp) {
        using namespace XBraidUtil;
        grp.append("XBraidUtil");
        // Space Time Communicator


        try {
            RegisterCommon<Functionality>(*reg, grp);
            RegisterDimensionDependent<Functionality>(*reg, grp);
            RegisterDomainDependent<Functionality>(*reg, grp);
            RegisterAlgebraDependent<Functionality>(*reg, grp);
            RegisterDomainAlgebraDependent<Functionality>(*reg, grp);
            RegisterDomain2dAlgebraDependent<FunctionalityFor2D>(*reg,grp);
        }
        UG_REGISTRY_CATCH_THROW(grp);

    }
}