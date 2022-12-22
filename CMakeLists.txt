# specify version of cmake
cmake_minimum_required(VERSION 3.15)


project(param
        VERSION 1.0
        LANGUAGES CXX)

# This is used to avoid empty path. 
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# define shared library
add_library(param
            SHARED
            param.cpp
            )
# Define parameters for convenience. 
set(include_dest_param "include/param")
set(main_lib_dest_param "lib/param")

# specify the programming language 
set_target_properties(param PROPERTIES LINKER_LANGUAGE CXX)

# specify the include directories. We need to specify the current directory . with BUILD_INTERFACE 
# 
target_include_directories(
    param 
    INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}> # this one include the current directory. with BUILD_INTERFACE guard
    $<INSTALL_INTERFACE:include> # it can be anything for this project.
)


# install so file
install(
    TARGETS param 
    EXPORT param
    DESTINATION "${main_lib_dest_param}")

# install header file
install(FILES param.hpp DESTINATION "${include_dest_param}")

# for macro
include(GNUInstallDirs)

# install cmake files
install(
    EXPORT param
    FILE param.cmake
    NAMESPACE param::
    DESTINATION lib/cmake/param
    )
    
include(CMakePackageConfigHelpers)
# create config file
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/paramConfig.cmake.in
"${CMAKE_CURRENT_BINARY_DIR}/paramConfig.cmake"
INSTALL_DESTINATION "lib/cmake/"
NO_SET_AND_CHECK_MACRO
NO_CHECK_REQUIRED_COMPONENTS_MACRO
)
# create version file
write_basic_package_version_file(
"${CMAKE_CURRENT_BINARY_DIR}/paramConfigVersion.cmake"
# VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
COMPATIBILITY AnyNewerVersion
)
  
  
set(CMAKE_EXPORT_PACKAGE_REGISTRY ON)
# export param cmake file
export(
    TARGETS param
    NAMESPACE param::
    FILE param.cmake
)
# export so file
export(PACKAGE param)
  
