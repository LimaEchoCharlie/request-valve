set(LIB_SOURCE_FILES
        tbucket.c)

add_library(Throttle  STATIC ${LIB_SOURCE_FILES})

target_include_directories(Throttle PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)
