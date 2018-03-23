set(core_SRCS
        ArkCLP.cpp)
add_library(core ${core_SRCS})
add_executable(arklibexe main.cpp)
target_link_libraries(arklibexe core)