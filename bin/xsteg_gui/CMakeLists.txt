SET(XSTEG_GUI_SOURCES
	src/application.cpp
	src/encode_window.cpp
	src/main.cpp
	src/main_window.cpp
)

add_executable(xsteg.gui ${XSTEG_GUI_SOURCES})
target_link_libraries(xsteg.gui xsteg.core guim)

FILE(COPY res DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})