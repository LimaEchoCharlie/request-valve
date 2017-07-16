add_executable(tbucket_app
    test_tbucket.c
)
 
target_link_libraries(tbucket_app
    Valve
    Unity
)
 
add_executable(valve_app
    test_valve.c
)

target_link_libraries(valve_app
    Valve
    Unity
)

enable_testing()

add_test(tbucket_test tbucket_app)
add_test(valve_test valve_app)

