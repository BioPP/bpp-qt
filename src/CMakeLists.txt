# CMake script for Bio++ Qt
# Authors:
#   Julien Dutheil
#   Francois Gindraud (2017)
# Created: 22/08/2009

# File list
set (CPP_FILES
  Bpp/Qt/QtGraphicDevice.cpp
  Bpp/Qt/QtOutputStream.cpp
  Bpp/Qt/Tree/TreeCanvas.cpp
  Bpp/Qt/Tree/TreeCanvasControlers.cpp
  Bpp/Qt/Tree/TreeStatisticsBox.cpp
  )
set (H_MOC_FILES
  Bpp/Qt/Tree/TreeCanvas.h
  Bpp/Qt/Tree/TreeCanvasControlers.h
  Bpp/Qt/Tree/TreeStatisticsBox.h
  )
qt4_wrap_cpp (CPP_MOC_FILES ${H_MOC_FILES})

# Build the static lib
add_library (${PROJECT_NAME}-static STATIC ${CPP_FILES} ${CPP_MOC_FILES})
target_include_directories (${PROJECT_NAME}-static PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
  )
set_target_properties (${PROJECT_NAME}-static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
target_link_libraries (${PROJECT_NAME}-static ${BPP_LIBS_STATIC} ${qt-libs})
target_compile_options (${PROJECT_NAME}-static
  PUBLIC ${public-compile-options}
  PRIVATE ${private-compile-options}
  )

# Build the shared lib
add_library (${PROJECT_NAME}-shared SHARED ${CPP_FILES} ${CPP_MOC_FILES})
target_include_directories (${PROJECT_NAME}-shared PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
  $<INSTALL_INTERFACE:include>
  )
set_target_properties (${PROJECT_NAME}-shared
  PROPERTIES OUTPUT_NAME ${PROJECT_NAME}
  MACOSX_RPATH 1
  VERSION ${${PROJECT_NAME}_VERSION}
  SOVERSION ${${PROJECT_NAME}_VERSION_MAJOR}
  )
target_link_libraries (${PROJECT_NAME}-shared ${BPP_LIBS_SHARED} ${qt-libs})
target_compile_options (${PROJECT_NAME}-shared
  PUBLIC ${public-compile-options}
  PRIVATE ${private-compile-options}
  )

# Install libs and headers
install (
  TARGETS ${PROJECT_NAME}-static ${PROJECT_NAME}-shared
  EXPORT ${PROJECT_NAME}-targets
  LIBRARY DESTINATION lib${LIB_SUFFIX}
  ARCHIVE DESTINATION lib${LIB_SUFFIX}
  )
install (
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/Bpp
  DESTINATION include
  FILES_MATCHING PATTERN "*.h"
  )
# Install cmake file representing targets
install (EXPORT ${PROJECT_NAME}-targets DESTINATION ${cmake-package-location})
