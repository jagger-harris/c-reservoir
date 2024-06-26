file(GLOB TEST_SOURCE_FILES *.h *.c)

add_executable(rsv_test ${TEST_SOURCE_FILES})

target_link_libraries(rsv_test ${SOURCE_FILES} m)

enable_testing()
add_test(NAME AllTests COMMAND rsv_test)
