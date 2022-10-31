cmake_minimum_required(VERSION 3.14...3.22)

project(0_LocalOrderHash LANGUAGES CXX)

# --- Import tools ----

include(../../../cmake/tools.cmake)

# ---- Dependencies ----

include(../../../cmake/CPM.cmake)

CPMAddPackage(
  GITHUB_REPOSITORY jarro2783/cxxopts
  VERSION 3.0.0
  OPTIONS "CXXOPTS_BUILD_EXAMPLES NO" "CXXOPTS_BUILD_TESTS NO" "CXXOPTS_ENABLE_INSTALL YES"
)

CPMAddPackage(NAME InjectiveSDK SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/..)

find_package(restc-cpp REQUIRED)
find_package(ZLIB REQUIRED)
find_package(OpenSSL REQUIRED)
find_package(Boost REQUIRED COMPONENTS
    system
    program_options
    filesystem
    date_time
    context
    coroutine
    chrono
    log
    )

#CPMAddPackage(
#  NAME Boost
#  VERSION 1.80.0
#  GITHUB_REPOSITORY "boostorg/boost"
#  GIT_TAG "boost-1.80.0"
#)
#
#set(CPM_LOCAL_PACKAGES_ONLY TRUE)
#
#CPMAddPackage(
#  NAME restc-cpp
#  GIT_TAG v0.94.0-rc1
#  GITHUB_REPOSITORY jgaa/restc-cpp
#)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(${PROJECT_NAME} ${sources})

set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17 OUTPUT_NAME "0_LocalOrderHash")

target_link_libraries(${PROJECT_NAME} 
  PRIVATE
  InjectiveSDK::InjectiveSDK 
  cxxopts 
  ${RESTC_CPP_LIBRARIES}
  ${Boost_LIBRARIES}
  ${ZLIB_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  #restc-cpp 
)
