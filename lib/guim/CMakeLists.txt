SET(GUIM_SOURCES
    src/traits/background_color.cpp
    src/traits/foreground_color.cpp
    src/appwindow.cpp
    src/button.cpp
    src/color.cpp
    src/container.cpp
    src/context.cpp
    src/frame.cpp
    src/msg_popup.cpp
    src/popup.cpp
    src/selectable.cpp
    src/text.cpp
    src/text_input.cpp
    src/texture.cpp
    src/widget.cpp
    src/window.cpp
)

SET(GUIM_HEADERS
    include/guim/traits/background_color.hpp
    include/guim/traits/border.hpp
    include/guim/traits/foreground_color.hpp
    include/guim/appwindow.hpp
    include/guim/button.hpp
    include/guim/color.hpp
    include/guim/container.hpp
    include/guim/context.hpp
    include/guim/frame.hpp
    include/guim/msg_popup.hpp
    include/guim/popup.hpp
    include/guim/selectable.hpp
    include/guim/text.hpp
    include/guim/text_input.hpp
    include/guim/texture.hpp
    include/guim/widget.hpp
    include/guim/window.hpp
)

if(MSVC)
    add_library(guim ${GUIM_SOURCES} ${GUIM_HEADERS})
else()
    add_library(guim ${GUIM_SOURCES})
endif()

target_include_directories(guim PUBLIC include)
target_link_libraries(guim stb imgui glfw)