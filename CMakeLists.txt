cmake_minimum_required(VERSION 3.21.1)

option(LINK_INSIGHT "Link Qt Insight Tracker library" ON)
option(BUILD_QDS_COMPONENTS "Build design studio components" ON)

set(CMAKE_INSTALL_PREFIX "~/.local/lib" CACHE PATH "Install path prefix, prepended onto install directories.")
set(CMAKE_TOOLCHAIN_FILE $ENV{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake)
set(CMAKE_PREFIX_PATH $ENV{VCPKG_ROOT}/installed/x64-linux)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

project(chatRoomApp LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_definitions(LN_DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast")
endif ()

include_directories(include)

set(SOURCE_FILES
        "src/main.cpp"
        "src/Entity/Room.cpp"
        "src/Entity/Peer.cpp"
        "src/Managers/ServerManager.cpp"
        "src/Managers/ClientManager.cpp"
        "src/Entity/Message.cpp"
)

set(chat_proto_path "${CMAKE_SOURCE_DIR}/../protos/chat.proto")
cmake_path(GET chat_proto_path PARENT_PATH proto_dir)
set(chat_proto_srcs "${CMAKE_CURRENT_BINARY_DIR}/chat.pb.cc")
set(chat_grpc_srcs "${CMAKE_CURRENT_BINARY_DIR}/chat.grpc.pb.cc")
set(chat_proto_hdrs "${CMAKE_CURRENT_BINARY_DIR}/chat.pb.h")
set(chat_grpc_hdrs "${CMAKE_CURRENT_BINARY_DIR}/chat.grpc.pb.h")
set(vcpkg_tools "$ENV{VCPKG_ROOT}/installed/x64-linux/tools")
set(protoc_path "${vcpkg_tools}/protobuf/protoc")
set(grpc_plugin_path "${vcpkg_tools}/grpc/grpc_cpp_plugin")


add_custom_command(
        OUTPUT "${chat_proto_srcs}" "${chat_proto_hdrs}" "${chat_grpc_srcs}"
        "${chat_grpc_hdrs}"
        COMMAND
        ${protoc_path} ARGS --grpc_out="${CMAKE_CURRENT_BINARY_DIR}"
        --cpp_out="${CMAKE_CURRENT_BINARY_DIR}" -I "${proto_dir}"
        --plugin=protoc-gen-grpc=${grpc_plugin_path} "${chat_proto_path}"
        DEPENDS "${chat_proto_path}")

add_library(chat_rpc ${chat_proto_srcs} ${chat_grpc_srcs}
        "RpcClient/RpcClient.cpp")

target_include_directories(
        chat_rpc
        PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>)

find_package(gRPC CONFIG REQUIRED)
find_package(absl CONFIG REQUIRED)
find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Qml Quick)
if (Qt6_VERSION VERSION_GREATER_EQUAL 6.3)
    qt_standard_project_setup()
endif()

target_link_libraries(chat_rpc PUBLIC gRPC::gpr gRPC::grpc gRPC::grpc++
        gRPC::grpc++_alts)
target_link_libraries(chat_rpc PRIVATE absl::strings absl::flags_parse)

enable_testing()
add_executable(test_rpc_client RpcClient/test_rpc_client.cpp)
target_link_libraries(test_rpc_client chat_rpc)

add_test(NAME ChatClientTest COMMAND test_rpc_client)

qt_add_executable(chatRoomApp ${SOURCE_FILES})

qt_add_resources(chatRoomApp "configuration"
    PREFIX "/"
    FILES
        qtquickcontrols2.conf
)

target_link_libraries(chat_client PRIVATE chat_rpc)
target_link_libraries(chatRoomApp PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
)



set(QT_QML_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/qml)
set(QML_IMPORT_PATH ${QT_QML_OUTPUT_DIRECTORY}
    CACHE STRING "Import paths for Qt Creator's code model"
    FORCE
)

if (BUILD_QDS_COMPONENTS)
    include(${CMAKE_CURRENT_SOURCE_DIR}/qmlcomponents)
endif()

include(${CMAKE_CURRENT_SOURCE_DIR}/qmlmodules)

if (LINK_INSIGHT)
    include(${CMAKE_CURRENT_SOURCE_DIR}/insight)
endif ()

include(GNUInstallDirs)
install(TARGETS chatRoomApp
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

# make IDEs aware of the QML import path
set(QML_IMPORT_PATH ${PROJECT_BINARY_DIR}/qml CACHE PATH
    "Path to the custom QML components defined by the project")
