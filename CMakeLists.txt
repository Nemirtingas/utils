#CMAKE_TOOLCHAIN_FILE

project(utils)
cmake_minimum_required(VERSION 3.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(UTILS_EXPORT_LIBRARY "Export DllMain on Windows and call the user defined shared_library_load/shared_library_unload" OFF)

set(UTILS_HEADERS
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/class_enum.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/constexpr_count.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/endianness.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/istring.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/scoped_lock.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/strings.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/switchstr.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/utils_exports.h
  ${CMAKE_CURRENT_SOURCE_DIR}/include/utils/utils_osdetector.h
)

########################################
## Build library
if(UTILS_EXPORT_LIBRARY)
add_library(utils STATIC
	src/utils_exports.cpp
)

target_include_directories(utils
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

target_compile_definitions(utils
  PUBLIC
  $<$<BOOL:${UTILS_EXPORT_LIBRARY}>:UTILS_EXPORT_LIBRARY>
)

set_property(TARGET utils PROPERTY POSITION_INDEPENDENT_CODE ON)

else()
add_library(utils INTERFACE)

target_include_directories(utils
  INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)
endif()

set_target_properties(utils PROPERTIES EXPORT_NAME Utils)
add_library(Utils::Utils ALIAS utils)

##################
## Install rules
install(TARGETS utils EXPORT UtilsTargets
	RUNTIME DESTINATION bin
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
)

install(FILES ${UTILS_HEADERS}
	DESTINATION include/utils
)

# Export targets
install(
	EXPORT UtilsTargets
	FILE UtilsTargets.cmake
	NAMESPACE Utils::
	DESTINATION lib/cmake/Utils
)

# Export config
install(
	FILES ${CMAKE_CURRENT_SOURCE_DIR}/cmake/UtilsConfig.cmake
	DESTINATION lib/cmake/Utils
)