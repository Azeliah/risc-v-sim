cmake_minimum_required(VERSION 3.23)
project(risc_v_sim C)

set(CMAKE_C_STANDARD 11)

add_executable(risc_v_sim
        main.c
        controller/simulator.c controller/simulator.h
        model/processor.c model/processor.h
        model/memory.c model/memory.h
        model/components/register.c model/components/register.h
        model/components/alu.c model/components/alu.h
        model/components/aluControl.c model/components/aluControl.h
        model/components/control.c model/components/control.h)
