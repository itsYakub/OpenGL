cmake_minimum_required(VERSION 3.11)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

set(
	OPENGL_SAMPLES
	sample-window
	sample-renderer
	sample-renderer-textures
)

foreach(sample IN LISTS OPENGL_SAMPLES)

	add_executable(${sample} ${sample}.c)
	target_link_libraries(${sample} opengl)

    if (LINUX)

        target_link_options(${sample}	PRIVATE -static-libgcc -static-libstdc++)
        set_target_properties(${sample} PROPERTIES SUFFIX ".out")

    endif()

    if (WIN32)

        target_compile_options(${sample} PRIVATE -mwindows)
        target_link_options(${sample} PRIVATE -static)
        set_target_properties(${sample} PROPERTIES SUFFIX ".exe")

    endif()

    if (APPLE)

        target_link_libraries(${sample} "-framework IOKit")
        target_link_libraries(${sample} "-framework Cocoa")
        set_target_properties(${sample} PROPERTIES SUFFIX ".app")

    endif()

endforeach()
