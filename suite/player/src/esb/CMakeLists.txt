file(GLOB ESB_SRC "*.cpp" "actor/*.cpp" "package/*.cpp" "presentation/*.cpp" "stage/*.cpp")
add_library(ESB STATIC ${ESB_SRC})