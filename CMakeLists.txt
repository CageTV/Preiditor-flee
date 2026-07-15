cmake_minimum_required(VERSION 3.21)
project(TMD_PredatorFleeFire VERSION 1.0.0 LANGUAGES CXX)

find_package(CommonLibSSE REQUIRED)

# Point to SKSE Menu Framework headers
set(SKSEMENUFRAMEWORK_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/SKSE/include")

add_commonlibsse_plugin(${PROJECT_NAME} SOURCES
    main.cpp
    Settings.cpp
    Events.cpp
    Menu.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${SKSEMENUFRAMEWORK_INCLUDE_DIRS})
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_23)
