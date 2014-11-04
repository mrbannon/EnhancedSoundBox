# Directories.
include_directories(${EnhancedSoundBoxPlayer_SOURCE_DIR}/include)
add_subdirectory(esb)
link_directories(${EnhancedSoundBoxPlayer_SOURCE_DIR}/src/esb)
add_subdirectory(lazyfoo)
link_directories(${EnhancedSoundBoxPlayer_SOURCE_DIR}/src/lazyfoo)