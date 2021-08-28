#-------------------------------------------------------------------------------
#						Search all libraries on the system
#-------------------------------------------------------------------------------
## Use cmake package to find module
if (Linux)
    find_package(PCAP)
    find_package(LibXml2)
endif()
find_package(Gettext) # translation tool
if(EXISTS ${PROJECT_SOURCE_DIR}/.git)
    find_package(Git)
endif()
find_package(LibLZMA)

# Using find_package OpenGL without either setting your opengl preference to GLVND or LEGACY
# is deprecated as of cmake 3.11.
set(OpenGL_GL_PREFERENCE GLVND)
find_package(OpenGL)
find_package(PNG)
set(wxWidgets_FOUND 1)
set(wxWidgets_USE_FILE 3rdparty/wxwidgets3.0/UsewxWidgets.cmake)
find_package(ZLIB)

## Use pcsx2 package to find module
if (NOT MSVC)
   include(FindLibc)
endif()

## Only needed by the extra plugins
if(EXTRA_PLUGINS)
    include(FindCg)
    include(FindGlew)
    find_package(JPEG)
endif()

## Use CheckLib package to find module
include(CheckLib)
if(Linux)
    check_lib(AIO aio libaio.h)
endif()

#----------------------------------------
#		    Use system include
#----------------------------------------
if(CG_FOUND)
	include_directories(${CG_INCLUDE_DIRS})
endif()

if(JPEG_FOUND)
	include_directories(${JPEG_INCLUDE_DIR})
endif()

if(GLEW_FOUND)
    include_directories(${GLEW_INCLUDE_DIR})
endif()

if(OPENGL_FOUND)
	include_directories(${OPENGL_INCLUDE_DIR})
endif()

if(wxWidgets_FOUND)
	include(${wxWidgets_USE_FILE})
endif()

if(PCAP_FOUND)
	include_directories(${PCAP_INCLUDE_DIR})
endif()

if(LIBXML2_FOUND)
	include_directories(${LIBXML2_INCLUDE_DIRS})
endif()

if(ZLIB_FOUND)
	include_directories(${ZLIB_INCLUDE_DIRS})
else()
   set(ZLIB_FOUND TRUE)
   set(ZLIB_LIBRARIES z)
   add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/zlib)
   include_directories(${CMAKE_SOURCE_DIR}/3rdparty)
   include_directories(${CMAKE_SOURCE_DIR}/3rdparty/zlib)
endif()

if(NOT LIBLZMA_FOUND)
   set(LIBLZMA_FOUND 1)
   add_definitions(-DLZMA_API_STATIC)
   set(LIBLZMA_LIBRARIES lzma)
   add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/xz)
endif()

if(MSVC)
   add_definitions(-DPTW32_STATIC_LIB)
#   add_definitions(-D__CLEANUP_SEH)
   add_subdirectory(${CMAKE_SOURCE_DIR}/3rdparty/pthreads4w)
   include_directories(${CMAKE_SOURCE_DIR}/3rdparty/pthreads4w/include)
endif()

#----------------------------------------
#  Use  project-wide include directories
#----------------------------------------
include_directories(${CMAKE_SOURCE_DIR}/common/include
					${CMAKE_SOURCE_DIR}/common/include/Utilities
					${CMAKE_SOURCE_DIR}/common/include/x86emitter
                    # File generated by Cmake
                    ${CMAKE_BINARY_DIR}/common/include
                    )

#----------------------------------------
# Check correctness of the parameter
# Note: wxWidgets_INCLUDE_DIRS must be defined
#----------------------------------------
include(ApiValidation)

# Blacklist bad GCC
if(GCC_VERSION VERSION_EQUAL "7.0" OR GCC_VERSION VERSION_EQUAL "7.1")
    GCC7_BUG()
endif()

if((GCC_VERSION VERSION_EQUAL "9.0" OR GCC_VERSION VERSION_GREATER "9.0") AND GCC_VERSION LESS "9.2")
    message(WARNING "
    It looks like you are compiling with 9.0.x or 9.1.x. Using these versions is not recommended,
    as there is a bug known to cause the compiler to segfault while compiling. See patch
    https://gitweb.gentoo.org/proj/gcc-patches.git/commit/?id=275ab714637a64672c6630cfd744af2c70957d5a
    Even with that patch, compiling with LTO may still segfault. Use at your own risk!
    This text being in a compile log in an open issue may cause it to be closed.")
endif()

add_subdirectory(3rdparty/libchdr EXCLUDE_FROM_ALL)
include_directories(3rdparty/libchdr/include)
add_subdirectory(3rdparty/yaml-cpp EXCLUDE_FROM_ALL)
include_directories(3rdparty/yaml-cpp/include)
