SET(XSTEG_GUI_SOURCES
	src/main.cpp
)

add_executable(xsteg.gui ${XSTEG_GUI_SOURCES})
target_link_libraries(xsteg.gui xsteg.core imgui)