if(MSVC)
	add_definitions(/W0)
else()
	add_definitions(-w)
endif()

add_subdirectory(imgui)

option(GLFW_BUILD_EXAMPLES "Build the GLFW example programs" OFF)
option(GLFW_BUILD_TESTS "Build the GLFW test programs" OFF)
option(GLFW_BUILD_DOCS "Build the GLFW documentation" OFF)
option(GLFW_INSTALL "Generate installation target" OFF)
option(GLFW_VULKAN_STATIC "Use the Vulkan loader statically linked into application" OFF)
add_subdirectory(glfw)