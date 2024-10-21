cmake_minimum_required(VERSION "3.19.2")

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project(dragonfruit LANGUAGES C CXX VERSION 1.0)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

add_executable(server 
  src/server/main.cpp
  )

add_executable(client
  src/client/main.cpp
  src/client/gameloop.cpp
  src/client/clientSocket.cpp
  src/client/followCamera.cpp
  src/client/player.cpp
  src/client/clock.cpp
  src/client/debug.cpp
  src/client/map.cpp
  src/client/tileset.cpp
  src/client/tile.cpp
  src/client/layer.cpp
  )

# comment when releasing
target_compile_definitions(server PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/server/" )
target_compile_definitions(server PUBLIC DEBUG=1)

target_compile_definitions(client PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/client/" )
target_compile_definitions(client PUBLIC DEBUG=1)

# uncomment when releasing
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC ASSETS_PATH="./assets/" )
# target_compile_definitions("${CMAKE_PROJECT_NAME}" PUBLIC DEBUG=0)

target_include_directories(server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/server/")
target_include_directories(server PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/common/")

target_include_directories(client PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/client/")
target_include_directories(client PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/common/")

# WinSock2
if(WIN32)
  target_link_libraries(server PRIVATE ws2_32)
  target_link_libraries(client PRIVATE ws2_32)
endif()

# Link raylib to client.exe
find_package(raylib CONFIG REQUIRED)
target_link_libraries(client PRIVATE raylib)

# Copy all dll files
# add_custom_command(TARGET server POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:server> $<TARGET_FILE_DIR:server>
#   COMMAND_EXPAND_LISTS
#   )
#
# add_custom_command(TARGET client POST_BUILD
#   COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:client> $<TARGET_FILE_DIR:client>
#   COMMAND_EXPAND_LISTS
#   )
