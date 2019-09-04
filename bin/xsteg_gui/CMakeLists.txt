SET(XSTEG_GUI_SOURCES
	src/application_window.cpp
	src/encode_window.cpp
	src/fopen_window.cpp
	src/imgui_ctx.cpp
	src/imgui_window.cpp
	src/threshold_editor.cpp
	src/main.cpp
	src/window.cpp
)

add_executable(xsteg.gui ${XSTEG_GUI_SOURCES})
target_link_libraries(xsteg.gui xsteg.core imgui glfw)