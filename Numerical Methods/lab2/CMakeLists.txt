cmake_minimum_required(VERSION 3.21)
project(h_Met_Lab2)

set(CMAKE_CXX_STANDARD 20)

add_executable(h_Met_Lab2 main.cpp SimpleIterations.h Functions.h NewtonMethod.h systemOfequations.h SystemSimpleIterations.h SF.h SystemNewtonMethod.h LU_Decomposition.h)
