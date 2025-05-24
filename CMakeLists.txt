cmake_minimum_required(VERSION 3.27)
project(Raytracer)

set(CMAKE_CXX_STANDARD 11)

add_executable(Raytracer main.cpp
        hittable.h
        sphere.h
        hittable_list.h
        rtutil.h
        interval.h
        camera.h
        material.h
        threadpool.h)
