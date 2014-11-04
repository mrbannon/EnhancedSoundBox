file(GLOB ESB_SRC "*.cpp" "actor/*.cpp" "presentation/*.cpp" "stage/*.cpp")
add_library(ESB STATIC ${ESB_SRC})