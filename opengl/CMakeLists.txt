cmake_minimum_required(VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

include(FetchContent)

FetchContent_Declare(
    glad
    GIT_REPOSITORY	https://github.com/Dav1dde/glad
    GIT_TAG			v2.0.8 
    GIT_SHALLOW		TRUE
    GIT_PROGRESS	TRUE
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
    message("-- Fetching glad")
    FetchContent_MakeAvailable(glad)

    add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
    glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6 EXTENSIONS GL_ARB_bindless_texture GL_EXT_texture_compression_s3tc)
endif()

FetchContent_Declare(
    SDL3
    GIT_REPOSITORY	https://github.com/libsdl-org/SDL.git
    GIT_TAG			release-3.2.0 
    GIT_SHALLOW		TRUE
    GIT_PROGRESS	TRUE
)

FetchContent_GetProperties(SDL3)
if(NOT SDL3_POPULATED)
	message("-- Fetching SDL3")
	FetchContent_MakeAvailable(SDL3)
endif()

FetchContent_Declare(
    glfw
    GIT_REPOSITORY	https://github.com/glfw/glfw
    GIT_TAG			3.4
    GIT_SHALLOW		TRUE
    GIT_PROGRESS	TRUE
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
	message("-- Fetching GLFW")
	FetchContent_MakeAvailable(glfw)
endif()

FetchContent_Declare(
    cglm
    GIT_REPOSITORY	https://github.com/recp/cglm
    GIT_TAG			v0.9.4
    GIT_SHALLOW		TRUE
    GIT_PROGRESS	TRUE
)

FetchContent_GetProperties(cglm)
if(NOT cglm_POPULATED)
	message("-- Fetching cglm")
    FetchContent_MakeAvailable(cglm)
endif()

FetchContent_Declare(
	stb 
    GIT_REPOSITORY	https://github.com/nothings/stb
    GIT_SHALLOW		TRUE
    GIT_PROGRESS	TRUE
)

FetchContent_GetProperties(stb)
if(NOT stb_POPULATED)
	message("-- Fetching stb")
    FetchContent_MakeAvailable(stb)
endif()

project(opengl C)

set(
	SOURCES	
	# ${CMAKE_CURRENT_SOURCE_DIR}/opengl-backend-glfw.c
	${CMAKE_CURRENT_SOURCE_DIR}/opengl-backend-sdl.c
	${CMAKE_CURRENT_SOURCE_DIR}/opengl-renderer.c
	${CMAKE_CURRENT_SOURCE_DIR}/opengl-texture.c
	${CMAKE_CURRENT_SOURCE_DIR}/opengl-draw.c
	${CMAKE_CURRENT_SOURCE_DIR}/opengl.c
	# ...
)

set(
	INCLUDE_DIRECTORIES
	${CMAKE_CURRENT_SOURCE_DIR}
	${stb_SOURCE_DIR}
	# ...
)

set(
	LINK_LIBRARIES
	glad
	SDL3::SDL3
	glfw
	cglm
    # ...
)

add_library(${PROJECT_NAME} ${SOURCES})
target_compile_definitions(${PROJECT_NAME} PUBLIC ${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PUBLIC ${INCLUDE_DIRECTORIES})
target_link_libraries(${PROJECT_NAME} PUBLIC ${LINK_LIBRARIES})
