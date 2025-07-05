cmake_minimum_required(VERSION 3.13)
project(ToyTableGen LANGUAGES CXX)

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

add_executable(my_tblgen my_tblgen.cpp)
target_link_libraries(my_tblgen PRIVATE LLVMTableGen LLVMSupport)

add_custom_command(
  OUTPUT ${CMAKE_CURRENT_SOURCE_DIR}/include/ToyInstrs.inc
  COMMAND my_tblgen ${CMAKE_CURRENT_SOURCE_DIR}/ToyInstrs.td
                    -o ${CMAKE_CURRENT_SOURCE_DIR}/include/ToyInstrs.inc
  DEPENDS ToyInstrs.td my_tblgen
  COMMENT "Running my_tblgen"
)

add_custom_target(run-tablegen ALL DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/include/ToyInstrs.inc)

add_executable(test_main test/test_main.cpp)
add_dependencies(test_main run-tablegen)

