cmake_minimum_required(VERSION 3.21)
project(PreditorFleeFire VERSION 1.0.0 LANGUAGES CXX)

find_package(CommonLibSSE REQUIRED)

# Point to SKSE Menu Framework headers (also holds PCH.h and the other project headers)
set(SKSEMENUFRAMEWORK_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/include")

add_commonlibsse_plugin(${PROJECT_NAME} NAME "Preditor Flee Fire" SOURCES
    main.cpp
    Settings.cpp
    Events.cpp
    Menu.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${SKSEMENUFRAMEWORK_INCLUDE_DIRS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
target_compile_options(${PROJECT_NAME} PRIVATE /Zc:preprocessor)
target_compile_definitions(${PROJECT_NAME} PRIVATE UNICODE _UNICODE)
target_precompile_headers(${PROJECT_NAME} PRIVATE include/PCH.h)
