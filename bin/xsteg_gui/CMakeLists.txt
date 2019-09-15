SET(XSTEG_GUI_SOURCES
	src/application.cpp
	src/browse_popup.cpp
	src/encode_window.cpp
	src/main.cpp
	src/main_window.cpp
	src/threshold_editor.cpp
)

SET(XSTEG_GUI_HEADERS
	src/application.hpp
	src/browse_popup.hpp
	src/encode_window.hpp
	src/main_window.hpp
	src/std_filesystem.hpp
	src/threshold_editor.hpp
)

SET(XSTEG_GUI_ADDITIONAL_LIBS "")

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS 8.0)
		SET(XSTEG_GUI_ADDITIONAL_LIBS stdc++fs)
	endif()
endif()

add_executable(xsteg.gui ${XSTEG_GUI_SOURCES} ${XSTEG_GUI_HEADERS})
target_link_libraries(xsteg.gui xsteg.core guim ${XSTEG_GUI_ADDITIONAL_LIBS})

FILE(COPY res DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})