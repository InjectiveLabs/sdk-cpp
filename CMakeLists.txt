cmake_minimum_required(VERSION 3.14...3.22)

# ---- Project ----

# Note: update this to your new project's name and version
project(
        InjectiveSDK
        VERSION 1.0
        LANGUAGES CXX
)

# ---- Include guards ----

if (PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(
            FATAL_ERROR
            "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there."
    )
endif ()

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage("gh:TheLartians/PackageProject.cmake@1.8.0")

# Add fmt package
CPMAddPackage(
        NAME fmt
        GIT_TAG 8.1.1
        GITHUB_REPOSITORY fmtlib/fmt
        OPTIONS "FMT_INSTALL YES" # create an installable target
)

# Add Bech32 package
CPMAddPackage(
        NAME bech32
        GITHUB_REPOSITORY dcdpr/libbech32
        GIT_TAG master
)

# Add libsodium package
CPMAddPackage(
        NAME libsodium
        GITHUB_REPOSITORY jedisct1/libsodium
        GIT_TAG 1.0.18-RELEASE
        DOWNLOAD_ONLY True
)
if (libsodium_ADDED)
    add_library(libsodium STATIC IMPORTED GLOBAL)
    set_target_properties(libsodium PROPERTIES
            IMPORTED_LOCATION "${libsodium_SOURCE_DIR}/src/libsodium/.libs/libsodium.a"
            INTERFACE_INCLUDE_DIRECTORIES "${libsodium_SOURCE_DIR}/src/libsodium/include"
            )
endif ()

# Add libbitcoin package
CPMAddPackage(
        NAME libbitcoin
        GITHUB_REPOSITORY libbitcoin/libbitcoin-system
        GIT_TAG v3.6.0
)
include_directories(${libbitcoin_SOURCE_DIR}/include)
include_directories(${libbitcoin_SOURCE_DIR}/include/bitcoin)

# Find Protobuf installation
# Looks for protobuf-config.cmake file installed by Protobuf's cmake installation.
set(protobuf_MODULE_COMPATIBLE TRUE)
find_package(Protobuf CONFIG REQUIRED)
message(STATUS "Using protobuf ${Protobuf_VERSION}")

set(_PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(_REFLECTION gRPC::grpc++_reflection)
if (CMAKE_CROSSCOMPILING)
    find_program(_PROTOBUF_PROTOC protoc)
else ()
    set(_PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)
endif ()

# Find gRPC installation
# Looks for gRPCConfig.cmake file installed by gRPC's cmake installation.
find_package(gRPC CONFIG REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(_GRPC_GRPCPP gRPC::grpc++)
if (CMAKE_CROSSCOMPILING)
    find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin)
else ()
    set(_GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
endif ()

# CPMAddPackage(
#   NAME grpc
#   GIT_TAG v1.50.0
#   GITHUB_REPOSITORY grpc/grpc
#   OPTIONS "ABSL_PROPAGATE_CXX_STD ON"
# )
# if (grpc_ADDED)
#   message(STATUS "grpc added ${grpc_SOURCE_DIR}")
#   message(STATUS "grpc added ${grpc_BINARY_DIR}")
#   message(STATUS "grpc added ${CPM_LAST_PACKAGE_NAME}")
# endif()


# Proto file
#get_filename_component(hw_proto "./protos/helloworld.proto" ABSOLUTE)
#get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generated sources
#set(hw_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.cc")
#set(hw_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.pb.h")
#set(hw_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.cc")
#set(hw_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/helloworld.grpc.pb.h")
#add_custom_command(
#      OUTPUT "${hw_proto_srcs}" "${hw_proto_hdrs}" "${hw_grpc_srcs}" "${hw_grpc_hdrs}"
#      COMMAND ${_PROTOBUF_PROTOC}
#      ARGS --grpc_out "${CMAKE_CURRENT_BINARY_DIR}"
#        --cpp_out "${CMAKE_CURRENT_BINARY_DIR}"
#        -I "${hw_proto_path}"
#        --plugin=protoc-gen-grpc="${_GRPC_CPP_PLUGIN_EXECUTABLE}"
#        "${hw_proto}"
#      DEPENDS "${hw_proto}")

# Include generated *.pb.h files
include_directories("${CMAKE_CURRENT_BINARY_DIR}")

# # hw_grpc_proto
# add_library(hw_grpc_proto
#   ${hw_grpc_srcs}
#   ${hw_grpc_hdrs}
#   ${hw_proto_srcs}
#   ${hw_proto_hdrs})
# target_link_libraries(hw_grpc_proto
#   ${_REFLECTION}
#   ${_GRPC_GRPCPP}
#   ${_PROTOBUF_LIBPROTOBUF})
#message(STATUS ${hw_proto_srcs})


# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files
# automatically. Keep that in mind when changing files, or explicitly mention them here.
file(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h")
file(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface
# target: add_library(${PROJECT_NAME} INTERFACE)
add_library(${PROJECT_NAME}
        ${headers}
        ${sources}
        #  ${hw_grpc_srcs}
        #  ${hw_grpc_hdrs}
        #  ${hw_proto_srcs}
        #  ${hw_proto_hdrs}
        source/chain_client.cpp include/injective/wallet.cpp include/injective/wallet.h)
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 17)

# being a cross-platform target, we enforce standards conformance on MSVC
target_compile_options(${PROJECT_NAME} PUBLIC "$<$<COMPILE_LANG_AND_ID:CXX,MSVC>:/permissive->")

# Link dependencies
target_link_libraries(${PROJECT_NAME}
        PRIVATE
            fmt::fmt
            bech32
            libsodium
            libbitcoin-system
            ${_REFLECTION} ${_GRPC_GRPCPP} ${_PROTOBUF_LIBPROTOBUF}
)

target_include_directories(
        ${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

# the location where the project's version header will be placed should match the project's regular
# header paths
string(TOLOWER ${PROJECT_NAME}/version.h VERSION_HEADER_LOCATION)

packageProject(
        NAME ${PROJECT_NAME}
        VERSION ${PROJECT_VERSION}
        NAMESPACE ${PROJECT_NAME}
        BINARY_DIR ${PROJECT_BINARY_DIR}
        INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
        INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
        VERSION_HEADER "${VERSION_HEADER_LOCATION}"
        COMPATIBILITY SameMajorVersion
        DEPENDENCIES "fmt 8.1.1"
)
