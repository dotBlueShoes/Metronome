cmake_minimum_required (VERSION 3.27 FATAL_ERROR)

# --- Name, Version, Language compilers in use.
project (metronome-all VERSION 1.0.0 LANGUAGES C CXX)

# --- Includes
list (APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
include (properties)

# --- Configurable Properties
option (OPUS_SHARED_LIBRARY     "Link 'opus' as shared library"             OFF)
option (OGG_SHARED_LIBRARY      "Link 'ogg' as shared library"              OFF)
option (OPUSFILE_SHARED_LIBRARY "Link 'opusfile' as shared library"         OFF)
option (OPENAL_SHARED_LIBRARY   "Link 'openal' as shared library"           OFF)
option (MARGS_LOCALLY           "Link 'margs' sources from local cache"     OFF)
option (BLUELIB_LOCALLY         "Link 'bluelib' sources from local cache"   OFF)

# --- Dependencies
add_subdirectory (dependencies)

# --- Add 'defines' to all projects
add_compile_definitions (_CRT_SECURE_NO_WARNINGS)
add_compile_definitions (DEBUG_FLAG_LOGGING=${DEBUG_FLAG_LOGGING})
add_compile_definitions (DEBUG_FLAG_MEMORY=${DEBUG_FLAG_MEMORY})
add_compile_definitions (DEBUG_FLAG_CLOCKS=${DEBUG_FLAG_CLOCKS})
add_compile_definitions (DEBUG_FLAG_POSTLOGGING=${DEBUG_FLAG_POSTLOGGING})

# --- Project's sources
#add_subdirectory (project/bluelib)
add_subdirectory (project/metronome)
