# CMake generated Testfile for 
# Source directory: D:/study/OPPPO/Prac1_MikhKY1/plant_project/tests
# Build directory: D:/study/OPPPO/Prac1_MikhKY1/plant_project/build/tests
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if(CTEST_CONFIGURATION_TYPE MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test([=[PlantTests]=] "D:/study/OPPPO/Prac1_MikhKY1/plant_project/build/tests/Debug/runTests.exe")
  set_tests_properties([=[PlantTests]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/study/OPPPO/Prac1_MikhKY1/plant_project/tests/CMakeLists.txt;11;add_test;D:/study/OPPPO/Prac1_MikhKY1/plant_project/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test([=[PlantTests]=] "D:/study/OPPPO/Prac1_MikhKY1/plant_project/build/tests/Release/runTests.exe")
  set_tests_properties([=[PlantTests]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/study/OPPPO/Prac1_MikhKY1/plant_project/tests/CMakeLists.txt;11;add_test;D:/study/OPPPO/Prac1_MikhKY1/plant_project/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test([=[PlantTests]=] "D:/study/OPPPO/Prac1_MikhKY1/plant_project/build/tests/MinSizeRel/runTests.exe")
  set_tests_properties([=[PlantTests]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/study/OPPPO/Prac1_MikhKY1/plant_project/tests/CMakeLists.txt;11;add_test;D:/study/OPPPO/Prac1_MikhKY1/plant_project/tests/CMakeLists.txt;0;")
elseif(CTEST_CONFIGURATION_TYPE MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test([=[PlantTests]=] "D:/study/OPPPO/Prac1_MikhKY1/plant_project/build/tests/RelWithDebInfo/runTests.exe")
  set_tests_properties([=[PlantTests]=] PROPERTIES  _BACKTRACE_TRIPLES "D:/study/OPPPO/Prac1_MikhKY1/plant_project/tests/CMakeLists.txt;11;add_test;D:/study/OPPPO/Prac1_MikhKY1/plant_project/tests/CMakeLists.txt;0;")
else()
  add_test([=[PlantTests]=] NOT_AVAILABLE)
endif()
