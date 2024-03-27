cmake_minimum_required(VERSION 3.17)
project(lab1_1)

set(CMAKE_CXX_STANDARD 20)

add_executable(lab1_1 main.cpp Supportive_Functions.h Tridiagonal_Matrix_Algorithm.h LU_Decomposition.h "Simple_Iteration_Method.h" Zeidel_Method.h Rotation_Method.h QR_Algorithm.h)