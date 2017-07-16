set(LIB_SOURCE_FILES
        tbucket.c
        valve.c)

add_library(Valve  STATIC ${LIB_SOURCE_FILES})

target_include_directories(Valve PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
