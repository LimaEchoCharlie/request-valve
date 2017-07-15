add_executable(tbucket_app
    test_tbucket.c
)
 

target_link_libraries(tbucket_app
    Throttle
    Unity
)
 
enable_testing()

add_test(tbucket_test tbucket_app)

