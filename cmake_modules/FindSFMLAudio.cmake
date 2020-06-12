#
# A CMake module to find SFMLAudio for the project B-YEP-400 IndieStudio
#
# This CMake module is designed to work on Fedora28 and Windows10. We will not
# provide support for other distributions. We will use this module to compile
# your project during our tests.
#
# You must provide the path to this module to CMake by setting
# CMAKE_MODULE_PATH variable to its location.
#
# Once done this module will define:
#  SFMLAudio_FOUND - system has SFMLAudio
#  SFMLAudio_INCLUDE_DIRS - the SFMLAudio include directory
#  SFMLAudio_LIBRARIES - Link these to use SFMLAudio
#
# Author: Guillaume DEVOILLE <guillaume1.devoille@epitech.eu> (17/05/2019)
#

IF (NOT SFMLAudio_INCLUDE_DIRS OR NOT SFMLAudio_LIBRARIES)
  FIND_PATH(SFMLAudio_INCLUDE_DIRS
    NAMES
      Audio.hpp
    PATHS
      /usr/include/SFML/        # Default Fedora28 system include path
      /usr/local/include/SFML/  # Default Fedora28 local include path
      ${CMAKE_MODULE_PATH}/include/ # Expected to contain the path to this file for Windows10
      ${SFMLAudio_DIR}/include/      # SFMLAudio root directory (if provided)
  )

  IF (MSVC)     # Windows
    SET(CMAKE_FIND_LIBRARY_PREFIXES "")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".lib")
  ELSE (MSVC)   # Linux
    SET(CMAKE_FIND_LIBRARY_PREFIXES "lib")
    SET(CMAKE_FIND_LIBRARY_SUFFIXES ".so")
  ENDIF(MSVC)

  FIND_LIBRARY(SFMLAudio_LIBRARIES
    NAMES
      sfml-audio
    PATHS
      /usr/lib64/                   # Default Fedora28 library path
      /usr/lib/                     # Some more Linux library path
      /usr/lib/x86_64-linux-gnu/    # Some more Linux library path
      /usr/local/lib/               # Some more Linux library path
      /usr/local/lib64/             # Some more Linux library path
      ${CMAKE_MODULE_PATH}/         # Expected to contain the path to this file for Windows10
      ${SFMLAudio_DIR}/              # SFMLAudio root directory (if provided)
  )
ENDIF (NOT SFMLAudio_INCLUDE_DIRS OR NOT SFMLAudio_LIBRARIES)

IF (SFMLAudio_INCLUDE_DIRS AND SFMLAudio_LIBRARIES)
  SET(SFMLAudio_FOUND TRUE)
ELSE (SFMLAudio_INCLUDE_DIRS AND SFMLAudio_LIBRARIES)
  SET(SFMLAudio_FOUND FALSE)
ENDIF (SFMLAudio_INCLUDE_DIRS AND SFMLAudio_LIBRARIES)

IF (SFMLAudio_FIND_REQUIRED AND NOT SFMLAudio_FOUND)
  MESSAGE(FATAL_ERROR
    "  SFMLAudio not found.\n"
    "      Windows: Fill CMake variable CMAKE_MODULE_PATH to the provided directory.\n"
    "      Linux: Install SFMLAudio using your package manager ($> sudo dnf install sfml).\n"
  )
ENDIF (SFMLAudio_FIND_REQUIRED AND NOT SFMLAudio_FOUND)
