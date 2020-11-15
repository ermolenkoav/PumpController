cmake_minimum_required(VERSION 3.16)

project(Odorator LANGUAGES C CXX)

include(cmake/options.cmake               REQUIRED)

include(cmake/cpack.cmake                 REQUIRED)

include(cmake/compilerDefOpt.cmake        REQUIRED)

include(cmake/dependencies.cmake          REQUIRED)

include(cmake/buildTargets.cmake          REQUIRED)

include(cmake/printInfo.cmake             REQUIRED)