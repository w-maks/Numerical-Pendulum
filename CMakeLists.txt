cmake_minimum_required(VERSION 3.29)
project(Numerical_Pendulum C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Numerical_Pendulum
    analytical_pendulum.c
    analytical_pendulum.h
    main.c
    pendulum.c
    pendulum.h
    rk4.c
    rk4.h)
target_link_libraries(Numerical_Pendulum m)   # <- libm
