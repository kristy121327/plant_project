find_package(GTest CONFIG REQUIRED)

add_executable(runTests test_plants.cpp)

target_link_libraries(runTests
    plants
    GTest::gtest
    GTest::gtest_main
)

add_test(
    NAME PlantTests
    COMMAND runTests
)
