# Find all test files
file(GLOB TEST_FILES "${CMAKE_SOURCE_DIR}/tests/test_*.c")

# Loop through each test file to create an executable
foreach(TEST_FILE ${TEST_FILES})
  # Get the filename without extension
  get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

  # Create an executable for each test file
  add_executable(${TEST_NAME} ${TEST_FILE} ${SOURCE_FILES})

  # Optionally, you can add a target for running the test
  add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()
