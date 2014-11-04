# CMake version.
cmake_minimum_required(VERSION 2.6)

# Project.
project(EnhancedSoundBoxPlayer)

# Directories.
include_directories(${EnhancedSoundBoxPlayer_SOURCE_DIR}/include)
include_directories(${EnhancedSoundBoxPlayer_SOURCE_DIR}/glew-1.11.0/include)
add_subdirectory(src)
#link_directories(${EnhancedSoundBoxPlayer_SOURCE_DIR}/src)

# Exec, link, install.
add_executable(EnhancedSoundBoxPlayer src/main.cpp)
target_link_libraries(EnhancedSoundBoxPlayer ${SDL2_LIBRARY} ESB ${OPENGL_LIBRARIES} LAZYFOO)
install(TARGETS EnhancedSoundBoxPlayer RUNTIME DESTINATION ${BIN_DIR})