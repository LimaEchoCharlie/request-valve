add_library(Unity STATIC
    unity/unity.c
    unity/unity_fixture.c
)
 
target_include_directories(Unity PUBLIC
    Unity/src
)
