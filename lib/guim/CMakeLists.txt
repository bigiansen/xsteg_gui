SET(GUIM_SOURCES
    src/traits/background_color.cpp
    src/traits/foreground_color.cpp
    src/button.cpp
    src/color.cpp
    src/context.cpp
	src/text_input.cpp
    src/widget.cpp
    src/window.cpp)

SET(GUIM_HEADERS
    include/guim/traits/background_color.hpp
    include/guim/traits/foreground_color.hpp
    include/guim/button.hpp
	include/guim/color.hpp
    include/guim/context.hpp    
	include/guim/text_input.hpp
    include/guim/widget.hpp
    include/guim/window.hpp)

add_library(guim ${GUIM_SOURCES} ${GUIM_HEADERS})
target_include_directories(guim PUBLIC include)
target_link_libraries(guim stb imgui glfw)