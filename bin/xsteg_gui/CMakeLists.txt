SET(XSTEG_GUI_SOURCES
	src/imgui_ctx.cpp
	src/main.cpp
	src/window.cpp
)

add_executable(xsteg.gui ${XSTEG_GUI_SOURCES})
target_link_libraries(xsteg.gui xsteg.core imgui glfw)