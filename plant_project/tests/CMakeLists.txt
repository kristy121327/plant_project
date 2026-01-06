enable_testing()
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS} ../src)

add_executable(runTests test_plants.cpp)
target_link_libraries(runTests plants GTest::GTest GTest::Main)

add_test(NAME PlantTests COMMAND runTests)
