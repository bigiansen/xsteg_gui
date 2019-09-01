SET(IMGUI_SOURCES
	src/glad.cpp
	src/imgui.cpp
	src/imgui_demo.cpp
	src/imgui_draw.cpp
	src/imgui_impl_glfw.cpp
	src/imgui_impl_opengl3.cpp
	src/imgui_stdlib.cpp
	src/imgui_widgets.cpp
)

add_library(imgui ${IMGUI_SOURCES})
target_link_libraries(imgui glfw)
target_include_directories(imgui PUBLIC include)