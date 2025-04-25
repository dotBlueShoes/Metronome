# --- Define a 'subproject'
project (metronome VERSION 1.0.0 LANGUAGES C CXX)


# --- Add header files
file (GLOB_RECURSE HEADER_FILES
	${PROJECT_SOURCE_DIR}/inc/*.h
	${PROJECT_SOURCE_DIR}/inc/*.hpp
)


# --- Add needed DEFINE's
add_compile_definitions (_CRT_SECURE_NO_WARNINGS)


# --- OpenAL linked statically requires the following define also.
if (NOT ${OPENAL_SHARED_LIBRARY}) 

	add_compile_definitions (AL_LIBTYPE_STATIC)

endif ()


# --- Info Build Type
message (STATUS "Build type: ${CMAKE_BUILD_TYPE}")


if 		(${PROFILE} EQUAL 1)

	message (STATUS "Preset: DEBUG")
	add_compile_definitions (DEBUG_TYPE=${DEBUG_FLAG_LOGGING}+${DEBUG_FLAG_MEMORY})

elseif 	(${PROFILE} EQUAL 2)

	message (STATUS "Preset: RELEASE")
	add_compile_definitions (DEBUG_TYPE=0)

endif ()


# --- Define the executable
add_executable (
	${PROJECT_NAME} ${HEADER_FILES} 
	src/main.cpp
)


# --- Make this project 'headers' available to use.
target_include_directories (
	${PROJECT_NAME} PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/inc
)


# --- LIBS For shared by all presets.
target_link_libraries (${PROJECT_NAME} BLUELIB)
target_link_libraries (${PROJECT_NAME} OGG)
target_link_libraries (${PROJECT_NAME} OPUS)
target_link_libraries (${PROJECT_NAME} OPUSFILE)
target_link_libraries (${PROJECT_NAME} OPENAL)


# target_include_directories (
# 	${PROJECT_NAME} PRIVATE 
# 	${margs_SOURCE_DIR}/include
# )

#CPMAddPackage ("gh:MAIPA01/mstd#v1.0.0")
#CPMAddPackage ("gh:MAIPA01/margs#v1.0.0")
#target_link_libraries (${PROJECT_NAME} mstd)
#target_link_libraries (${PROJECT_NAME} margs)
#target_link_libraries (${PROJECT_NAME} INTERFACE mstd)
# - working one ->
#CPMAddPackage("gh:MAIPA01/mstd#main")
#
#if(mstd_ADDED)
#    include_directories(${mstd_SOURCE_DIR}/include)
#    message(STATUS "CMake added local mstd: ${mstd_SOURCE_DIR}")
#endif()
#
#CPMAddPackage("gh:MAIPA01/margs#main")
#
#if(margs_ADDED)
#    include_directories(${margs_SOURCE_DIR}/include)
#    message(STATUS "CMake added local margs: ${margs_SOURCE_DIR}")
#endif()


#
# --- Copy .dlls inside project build directory.
#


if (${OPENAL_SHARED_LIBRARY}) 

	add_custom_command ( 
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:OPENAL> 
		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)

endif ()


if (${OGG_SHARED_LIBRARY}) 

	add_custom_command ( 
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:OGG>
		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)

endif ()


if (${OPUS_SHARED_LIBRARY}) 

	add_custom_command ( 
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:OPUS>
		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
	
endif ()


if (${OPUSFILE_SHARED_LIBRARY}) 

	add_custom_command ( 
		TARGET ${PROJECT_NAME} POST_BUILD
		COMMAND ${CMAKE_COMMAND} -E copy_if_different
		$<TARGET_FILE:OPUSFILE> 
		$<TARGET_FILE_DIR:${PROJECT_NAME}>
	)
	
endif ()


# --- Creates a 'symlink' for resources in builds directory.
add_custom_command (
	TARGET ${PROJECT_NAME} POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E create_symlink
	${CMAKE_SOURCE_DIR}/project/${PROJECT_NAME}/res
	${CMAKE_CURRENT_BINARY_DIR}/res
)
