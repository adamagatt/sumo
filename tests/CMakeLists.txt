
# Find and make use of GTest library
find_package(GTest REQUIRED)

# Executable for running tests, with include and links
add_executable(runTestVector2d util/test_vec2d.cpp)
target_include_directories(runTestVector2d PRIVATE ${GTEST_INCLUDE_DIRS} include)
target_link_libraries(runTestVector2d ${GTEST_LIBRARIES} vec2d pthread) # pthread needed for gtest