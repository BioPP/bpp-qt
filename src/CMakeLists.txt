# CMake script for Bio++ Qt
# Author: Julien Dutheil
# Created: 22/08/2009

# File list
set(CPP_FILES
  Bpp/Qt/QtGraphicDevice.cpp
  Bpp/Qt/QtOutputStream.cpp
  Bpp/Qt/Tree/TreeCanvas.cpp
  Bpp/Qt/Tree/TreeCanvasControlers.cpp
  Bpp/Qt/Tree/TreeStatisticsBox.cpp
  )
set(H_FILES
  Bpp/Qt/QtGraphicDevice.h
  Bpp/Qt/QtTools.h
  Bpp/Qt/QtOutputStream.h
  Bpp/Qt/MouseListener.h
  Bpp/Qt/MouseListeningWidget.h
  Bpp/Qt/Tree/TreeCanvas.h
  )
set(H_MOC_FILES
  Bpp/Qt/Tree/TreeCanvas.h
  Bpp/Qt/Tree/TreeCanvasControlers.h
  Bpp/Qt/Tree/TreeStatisticsBox.h
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
install(TARGETS bppqt-static bppqt-shared DESTINATION lib${LIB_SUFFIX})

# Install headers
install(DIRECTORY Bpp/ DESTINATION include/Bpp FILES_MATCHING PATTERN "*.h")

# Generate generic include files (.all)
INSTALL(CODE "EXECUTE_PROCESS(COMMAND ${CMAKE_SOURCE_DIR}/genIncludes.sh ${CMAKE_PREFIX_PATH}/include/Bpp)")
