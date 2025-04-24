include (CPM)


# ---
# Static libraries
# ---


if (NOT ${OPUS_SHARED_LIBRARY})

	message (STATUS "DISABLED - Shared library OPUS")

	# --- Define 'OPUS'
	set (OPUS_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/opus/inc)
	add_library (OPUS STATIC IMPORTED GLOBAL)
	set_property (TARGET OPUS PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/opus/lib/release/opus.lib)
	set_property (TARGET OPUS PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/opus/lib/debug/opus.lib)
	target_include_directories (OPUS INTERFACE ${OPUS_INC_DIR})

endif ()


if (NOT ${OGG_SHARED_LIBRARY})

	message (STATUS "DISABLED - Shared library OGG")

	# --- Define 'OGG'
	set (OGG_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/ogg/inc)
	add_library (OGG STATIC IMPORTED GLOBAL)
	set_property (TARGET OGG PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/ogg/lib/release/ogg.lib)
	set_property (TARGET OGG PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/ogg/lib/debug/ogg.lib)
	target_include_directories (OGG INTERFACE ${OGG_INC_DIR})

endif ()


if (NOT ${OPUSFILE_SHARED_LIBRARY})

	message (STATUS "DISABLED - Shared library OPUSFILE")

	# --- Define 'OPUSFILE'
	set (OPUSFILE_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/opusfile/inc)
	add_library (OPUSFILE STATIC IMPORTED GLOBAL)
	set_property (TARGET OPUSFILE PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/opusfile/lib/release/opusfile.lib)
	set_property (TARGET OPUSFILE PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/opusfile/lib/debug/opusfile.lib)
	target_include_directories (OPUSFILE INTERFACE ${OPUSFILE_INC_DIR})

endif ()


# TODO
if (NOT ${OPENAL_SHARED_LIBRARY})

	message (STATUS "DISABLED - Shared library OPENAL")

endif ()


# ---
# Dynamic libraries
# ---


if (${OPUS_SHARED_LIBRARY})

	message (STATUS "ENABLED - Shared library OPUS")

	# --- Define 'OPUS'
	set (OPUS_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/opus/inc)
	add_library (OPUS SHARED IMPORTED GLOBAL)
	set_property (TARGET OPUS PROPERTY IMPORTED_IMPLIB_RELEASE ${CMAKE_CURRENT_LIST_DIR}/opus/bin/libopus-0.lib)
	set_property (TARGET OPUS PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/opus/bin/libopus-0.dll)
	set_property (TARGET OPUS PROPERTY IMPORTED_IMPLIB_DEBUG ${CMAKE_CURRENT_LIST_DIR}/opus/bin/libopus-0.lib)
	set_property (TARGET OPUS PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/opus/bin/libopus-0.dll)
	target_include_directories (OPUS INTERFACE ${OPUS_INC_DIR})

endif ()


if (${OGG_SHARED_LIBRARY})

	message (STATUS "ENABLED - Shared library OGG")

	# --- Define 'OGG'
	set (OGG_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/ogg/inc)
	add_library (OGG SHARED IMPORTED GLOBAL)
	set_property (TARGET OGG PROPERTY IMPORTED_IMPLIB_RELEASE ${CMAKE_CURRENT_LIST_DIR}/ogg/bin/release/ogg.lib)
	set_property (TARGET OGG PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/ogg/bin/release/ogg.dll)
	set_property (TARGET OGG PROPERTY IMPORTED_IMPLIB_DEBUG ${CMAKE_CURRENT_LIST_DIR}/ogg/bin/debug/ogg.lib)
	set_property (TARGET OGG PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/ogg/bin/debug/ogg.dll)
	target_include_directories (OGG INTERFACE ${OGG_INC_DIR})

endif ()


# TODO
if (${OPUSFILE_SHARED_LIBRARY})

	message (STATUS "ENABLED - Shared library OPUSFILE")

endif ()


if (${OPENAL_SHARED_LIBRARY})

	message (STATUS "ENABLED - Shared library OPENAL")

	# --- Define 'OPENAL'
	set (OPENAL_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/openal/include)
	add_library (OPENAL SHARED IMPORTED GLOBAL)
	set_property (TARGET OPENAL PROPERTY IMPORTED_IMPLIB_RELEASE ${CMAKE_CURRENT_LIST_DIR}/openal/lib/release/OpenAL32.lib)
	set_property (TARGET OPENAL PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/openal/bin/release/OpenAL32.dll)
	set_property (TARGET OPENAL PROPERTY IMPORTED_IMPLIB_DEBUG ${CMAKE_CURRENT_LIST_DIR}/openal/lib/debug/OpenAL32.lib)
	set_property (TARGET OPENAL PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/openal/bin/debug/OpenAL32.dll)
	target_include_directories (OPENAL INTERFACE ${OPENAL_INC_DIR})

endif ()


#FetchContent_Declare (
#	margs
#	GIT_REPOSITORY https://github.com/MAIPA01/margs.git
#	GIT_TAG main
#)
#FetchContent_MakeAvailable (margs)

#CPMAddPackage (
#    NAME margs
#    GIT_REPOSITORY https://github.com/MAIPA01/margs.git
#    GIT_TAG v1.0.0
#)

#target_compile_options (TracyClient PUBLIC -Wno-format)