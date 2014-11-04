project(EnhancedSoundBox-Player)
#add_executable(EnhancedSoundBox-Player src/main.cpp)
target_link_libraries(EnhancedSoundBox-Player ${SDL2_LIBRARY})
#install(TARGETS EnhancedSoundBox-Player RUNTIME DESTINATION ${BIN_DIR})