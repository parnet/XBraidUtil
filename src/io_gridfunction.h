//
// Created by parnet on 20.09.21.
//

#ifndef XBRAIDUTIL_IOGRIDFUNCTION_H
#define XBRAIDUTIL_IOGRIDFUNCTION_H

#include <fstream>

#include "lib_disc/function_spaces/grid_function.h"
namespace ug {

    namespace XBraidUtil {
        template<typename TDomain, typename TAlgebra>
        class IOGridFunction {
        public:
            typedef ug::GridFunction<TDomain, TAlgebra> TGridFunction;
            typedef SmartPtr<TGridFunction> SPGridFunction;

            typedef typename TAlgebra::vector_type::value_type TVectorValueType;

            IOGridFunction() = default;

            ~IOGridFunction() = default;

            void write(SPGridFunction u, const char *path) {

                auto *u_ref = u.get();
                std::ofstream outfile;
                size_t szVector = u_ref->size();

                outfile.open(path, std::ios::binary | std::ios::out);
                outfile.write((const char *) &szVector, sizeof(size_t));
                // write the value for each gridpoint
                for (size_t i = 0; i < szVector; i++) {
                    outfile.write((const char *) &(*u_ref)[i], sizeof(TVectorValueType));
                }
                outfile.close();
            }

            void read(SPGridFunction u, const char *path) {
                auto *u_ref = u.get();
                std::ifstream infile;
                infile.open(path, std::ios::binary | std::ios::in);

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

#endif //XBRAIDUTIL_IOGRIDFUNCTION_H
