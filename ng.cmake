# PreditorFleeFire.dll on alandtse's CommonLibSSE-NG; included by E:/WorkSpace/ng-build/CMakeLists.txt (see ng_plugin there). Flat layout.
ng_plugin(TARGET PreditorFleeFire NAME PreditorFleeFire PLUGIN_NAME "Preditor Flee Fire" VERSION 1.0.1 ROOT "${CMAKE_CURRENT_LIST_DIR}"
    SOURCES main.cpp Settings.cpp Events.cpp Menu.cpp
    INCLUDES "${CMAKE_CURRENT_LIST_DIR}" "${CMAKE_CURRENT_LIST_DIR}/include"
    PCH "${CMAKE_CURRENT_LIST_DIR}/include/PCH.h" DEFINES UNICODE _UNICODE OPTIONS /Zc:preprocessor)
