include (CPM)


# ---
# INCLUDE ONLY
# ---


if (NOT ${MARGS_LOCALLY})

	message (STATUS "DISABLED - Locally library MARGS")
	
	FetchContent_Declare (
		margs
		GIT_REPOSITORY https://github.com/MAIPA01/margs.git
		GIT_TAG main
	)
	
	FetchContent_MakeAvailable (margs)

else ()

	message (STATUS "ENABLED - Locally library MARGS")

	# --- Define 'mstd'
	set (MSTD_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/mstd/include)
	add_library (mstd INTERFACE)
	target_include_directories (mstd INTERFACE ${MSTD_INC_DIR})

	# --- Define 'margs'
	set (MARGS_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/margs/include)
	add_library (margs INTERFACE)
	target_link_libraries (margs INTERFACE mstd)
	target_include_directories (margs INTERFACE ${MARGS_INC_DIR})

endif ()


# ---
# Static libraries
# ---


if (NOT ${OPUS_SHARED_LIBRARY})

	message (STATUS "DISABLED - Shared library OPUS")

	# --- Define 'OPUS'
	set (OPUS_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/opus/include)
	add_library (OPUS STATIC IMPORTED GLOBAL)
	set_property (TARGET OPUS PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/opus/static/release/opus.lib)
	set_property (TARGET OPUS PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/opus/static/debug/opus.lib)
	target_include_directories (OPUS INTERFACE ${OPUS_INC_DIR})

endif ()


if (NOT ${OGG_SHARED_LIBRARY})

	message (STATUS "DISABLED - Shared library OGG")

	# --- Define 'OGG'
	set (OGG_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/ogg/include)
	add_library (OGG STATIC IMPORTED GLOBAL)
	set_property (TARGET OGG PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/ogg/static/release/ogg.lib)
	set_property (TARGET OGG PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/ogg/static/debug/ogg.lib)
	target_include_directories (OGG INTERFACE ${OGG_INC_DIR})

endif ()


if (NOT ${OPUSFILE_SHARED_LIBRARY})

	message (STATUS "DISABLED - Shared library OPUSFILE")

	# --- Define 'OPUSFILE'
	set (OPUSFILE_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/opusfile/include)
	add_library (OPUSFILE STATIC IMPORTED GLOBAL)
	set_property (TARGET OPUSFILE PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/opusfile/static/release/opusfile.lib)
	set_property (TARGET OPUSFILE PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/opusfile/static/debug/opusfile.lib)
	target_include_directories (OPUSFILE INTERFACE ${OPUSFILE_INC_DIR})

endif ()


# TODO
if (NOT ${OPENAL_SHARED_LIBRARY})

	message (STATUS "DISABLED - Shared library OPENAL")

	# --- Define 'OPENAL'
	set (OPENAL_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/openal/include)
	add_library (OPENAL STATIC IMPORTED GLOBAL)
	set_property (TARGET OPENAL PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/openal/static/release/OpenAL32.lib)
	set_property (TARGET OPENAL PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/openal/static/debug/OpenAL32.lib)
	target_include_directories (OPENAL INTERFACE ${OPENAL_INC_DIR})

	# Specify the required libraries
	set ( OPENAL_REQUIRED_LIBS
		avrt.lib   # Audio-Visual Real-Time API for WASAPI
		ole32.lib  # OLE (Object Linking and Embedding)
		imm32.lib  # Input Method Manager API
		winmm.lib  # Windows Multimedia API for audio playback
	)

	target_link_libraries (OPENAL INTERFACE ${OPENAL_REQUIRED_LIBS})

endif ()


# ---
# Dynamic libraries
# ---


if (${OPUS_SHARED_LIBRARY})

	message (STATUS "ENABLED - Shared library OPUS")

	# --- Define 'OPUS'
	set (OPUS_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/opus/include)
	add_library (OPUS SHARED IMPORTED GLOBAL)
	set_property (TARGET OPUS PROPERTY IMPORTED_IMPLIB_RELEASE ${CMAKE_CURRENT_LIST_DIR}/opus/shared/libopus-0.lib)
	set_property (TARGET OPUS PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/opus/shared/libopus-0.dll)
	set_property (TARGET OPUS PROPERTY IMPORTED_IMPLIB_DEBUG ${CMAKE_CURRENT_LIST_DIR}/opus/shared/libopus-0.lib)
	set_property (TARGET OPUS PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/opus/shared/libopus-0.dll)
	target_include_directories (OPUS INTERFACE ${OPUS_INC_DIR})

endif ()


if (${OGG_SHARED_LIBRARY})

	message (STATUS "ENABLED - Shared library OGG")

	# --- Define 'OGG'
	set (OGG_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/ogg/include)
	add_library (OGG SHARED IMPORTED GLOBAL)
	set_property (TARGET OGG PROPERTY IMPORTED_IMPLIB_RELEASE ${CMAKE_CURRENT_LIST_DIR}/ogg/shared/release/ogg.lib)
	set_property (TARGET OGG PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/ogg/shared/release/ogg.dll)
	set_property (TARGET OGG PROPERTY IMPORTED_IMPLIB_DEBUG ${CMAKE_CURRENT_LIST_DIR}/ogg/shared/debug/ogg.lib)
	set_property (TARGET OGG PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/ogg/shared/debug/ogg.dll)
	target_include_directories (OGG INTERFACE ${OGG_INC_DIR})

endif ()


if (${OPUSFILE_SHARED_LIBRARY})

	message (STATUS "ENABLED - Shared library OPUSFILE")

	# --- Define 'OPUSFILE'
	set (OPUSFILE_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/opusfile/include)
	add_library (OPUSFILE SHARED IMPORTED GLOBAL)
	set_property (TARGET OPUSFILE PROPERTY IMPORTED_IMPLIB_RELEASE ${CMAKE_CURRENT_LIST_DIR}/opusfile/shared/opusfile.lib)
	set_property (TARGET OPUSFILE PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/opusfile/shared/opusfile.dll)
	set_property (TARGET OPUSFILE PROPERTY IMPORTED_IMPLIB_DEBUG ${CMAKE_CURRENT_LIST_DIR}/opusfile/shared/opusfile.lib)
	set_property (TARGET OPUSFILE PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/opusfile/shared/opusfile.dll)
	target_include_directories (OPUSFILE INTERFACE ${OPUSFILE_INC_DIR})

endif ()


if (${OPENAL_SHARED_LIBRARY})

	message (STATUS "ENABLED - Shared library OPENAL")

	# --- Define 'OPENAL'
	set (OPENAL_INC_DIR ${CMAKE_CURRENT_LIST_DIR}/openal/include)
	add_library (OPENAL SHARED IMPORTED GLOBAL)
	set_property (TARGET OPENAL PROPERTY IMPORTED_IMPLIB_RELEASE ${CMAKE_CURRENT_LIST_DIR}/openal/shared/release/OpenAL32.lib)
	set_property (TARGET OPENAL PROPERTY IMPORTED_LOCATION_RELEASE ${CMAKE_CURRENT_LIST_DIR}/openal/shared/release/OpenAL32.dll)
	set_property (TARGET OPENAL PROPERTY IMPORTED_IMPLIB_DEBUG ${CMAKE_CURRENT_LIST_DIR}/openal/shared/debug/OpenAL32.lib)
	set_property (TARGET OPENAL PROPERTY IMPORTED_LOCATION_DEBUG ${CMAKE_CURRENT_LIST_DIR}/openal/shared/debug/OpenAL32.dll)
	target_include_directories (OPENAL INTERFACE ${OPENAL_INC_DIR})

endif ()
