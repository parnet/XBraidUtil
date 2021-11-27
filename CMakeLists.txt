cmake_minimum_required(VERSION 2.8)

set(pluginName XBraidUtil)
project(UG_PLUGIN_${pluginName})

set(UG4_XBraidUtil_plugin_VERSION_MAJOR 0.1)
set(UG4_XBraidUtil_plugin_VERSION_MINOR 0.0)


set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS_INIT} -fPIC")

set(SOURCES src/xbraidutil_plugin.cpp
        src/io_gridfunction.h src/world_memory.h src/world_memory_impl.h)


if(UG_ROOT_CMAKE_PATH)
    MESSAGE("XBraidIntegrator UG_ROOT was found")
else(UG_ROOT_CMAKE_PATH)
    set(UG_ROOT_CMAKE_PATH /pro/ug/ugcore/cmake)
endif(UG_ROOT_CMAKE_PATH)

include(${UG_ROOT_CMAKE_PATH}/ug_plugin_includes.cmake)

if (buildEmbeddedPlugins)
    EXPORTSOURCES(${CMAKE_CURRENT_SOURCE_DIR} ${SOURCES})
else (buildEmbeddedPlugins)
    add_library(${pluginName} SHARED ${SOURCES})
    target_link_libraries(${pluginName} ug4)
    LINK_DIRECTORIES(${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
endif (buildEmbeddedPlugins)





