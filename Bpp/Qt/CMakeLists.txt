# CMake script for Bio++ Qt
# Author: Julien Dutheil
# Created: 22/08/2009

# File list
set(CPP_FILES
  QtGraphicDevice.cpp
  QtOutputStream.cpp
  TreeCanvas.cpp
  TreeCanvasControlers.cpp
  TreeStatisticsBox.cpp
  )
set(H_FILES
  QtGraphicDevice.h
  QtTools.h
  QtOutputStream.h
  TreeCanvas.h
  )
set(H_MOC_FILES
  TreeCanvasControlers.h
  TreeStatisticsBox.h
  )
qt4_wrap_cpp(CPP_MOC_FILES ${H_MOC_FILES})

# Build the static lib
add_library(bppqt-static STATIC ${CPP_FILES} ${CPP_MOC_FILES})
set_target_properties(bppqt-static
  PROPERTIES OUTPUT_NAME bpp-qt
  CLEAN_DIRECT_OUTPUT 1
  )
target_link_libraries(bppqt-static ${LIBS})

# Build the shared lib
add_library(bppqt-shared SHARED ${CPP_FILES} ${CPP_MOC_FILES})
set_target_properties(bppqt-shared
  PROPERTIES OUTPUT_NAME bpp-qt
  CLEAN_DIRECT_OUTPUT 1
  VERSION ${BPPQT_VERSION}
  SOVERSION ${BPPQT_VERSION_MAJOR}
  )
target_link_libraries(bppqt-shared ${LIBS})

# Install libs
install(TARGETS bppqt-static bppqt-shared DESTINATION lib)

# Install headers
install(FILES ${H_FILES} ${H_MOC_FILES} DESTINATION include/Bpp/Qt)
