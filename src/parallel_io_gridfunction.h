//
// Created by parnet on 22.09.21.
//

#ifndef UG_PLUGIN_XBRAIDUTIL_PARALLEL_IO_GRIDFUNCTION_H
#define UG_PLUGIN_XBRAIDUTIL_PARALLEL_IO_GRIDFUNCTION_H

#include <fstream>

#include "lib_disc/function_spaces/grid_function.h"
namespace ug {

    namespace XBraidUtil {
        template<typename TDomain, typename TAlgebra>
        class PIOGridFunction {
        public:
            typedef ug::GridFunction<TDomain, TAlgebra> TGridFunction;
            typedef SmartPtr<TGridFunction> SPGridFunction;

            typedef typename TAlgebra::vector_type::value_type TVectorValueType;

            PIOGridFunction() = default;

            ~PIOGridFunction() = default;

            std::vector<number> times;

            void write(SPGridFunction u, const char *path) {

                int mpi_rank;
                MPI_Comm_rank(PCL_COMM_WORLD, &mpi_rank);

                auto *u_ref = u.get();
                std::ofstream outfile;
                size_t szVector = u_ref->size();

                std::stringstream ss;
                ss << path << "_p" << mpi_rank << ".gridfunction";

                outfile.open(ss.str().c_str(), std::ios::binary | std::ios::out);
                outfile.write((const char *) &szVector, sizeof(size_t));
                // write the value for each gridpoint
                for (size_t i = 0; i < szVector; i++) {
                    outfile.write((const char *) &(*u_ref)[i], sizeof(TVectorValueType));
                }
                outfile.close();
            }

            void read(SPGridFunction u, const char *path) {
                int mpi_rank;
                MPI_Comm_rank(PCL_COMM_WORLD, &mpi_rank);

                auto *u_ref = u.get();
                std::ifstream infile;

                std::stringstream ss;
                ss << path << "_p" << mpi_rank << ".gridfunction";
                infile.open(ss.str().c_str(), std::ios::binary | std::ios::in);

                // read number of gridpoints todo consistency check?
                size_t szVector = 0;
                infile.read((char *) &szVector, sizeof(size_t));

                // read the values for each gridpoint
                for (size_t i = 0; i < szVector; i++) {
                    TVectorValueType val = 0;
                    infile.read((char *) &val, sizeof(TVectorValueType));
                    (*u_ref)[i] = val;
                }
                infile.close();
            }
        };
    }}

#endif //UG_PLUGIN_XBRAIDUTIL_PARALLEL_IO_GRIDFUNCTION_H
