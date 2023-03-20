cmake_minimum_required(VERSION 3.14)

project(IVS-tests)

file(GLOB PROJECT_FILES
    "calc*.cpp"
)

FILE(GLOB UNIT_TESTS
    "tests/*.cpp"
)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.12.1
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_library(projectFiles ${PROJECT_FILES})

add_executable(tests-all ${UNIT_TESTS})
target_link_libraries(tests-all GTest::gtest_main)
target_link_libraries(tests-all projectFiles)

include (GoogleTest)
gtest_discover_tests(tests-all)

