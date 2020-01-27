cmake_minimum_required(VERSION 3.15)

project(Odorator LANGUAGES CXX)

include(cmake/paths.cmake                 REQUIRED)

include(cmake/options.cmake               REQUIRED)

include(cmake/findDependencies.cmake      REQUIRED)

include(cmake/compilerDefOpt.cmake        REQUIRED)

include(cmake/buildTargets.cmake          REQUIRED)

include(cmake/printInfo.cmake             REQUIRED)

include(cmake/cpack.cmake                 REQUIRED)
