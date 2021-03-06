project(ROMEO)
cmake_minimum_required(VERSION 2.8)

enable_testing()
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

FIND_PACKAGE ( ITK REQUIRED)
IF ( ITK_FOUND)
INCLUDE( ${USE_ITK_FILE} )
ENDIF( ITK_FOUND)
IF(NOT VTK_BINARY_DIR)
FIND_PACKAGE(VTK REQUIRED)
IF(NOT VTK_DIR)
  MESSAGE(FATAL_ERROR "Please set VTK_DIR.")
ENDIF(NOT VTK_DIR)
INCLUDE(${VTK_USE_FILE})
ENDIF(NOT VTK_BINARY_DIR)
FIND_PACKAGE(OpenCV REQUIRED)
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)

ADD_SUBDIRECTORY(config)
# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

FIND_PACKAGE(Qt5Widgets REQUIRED)
find_package(Qt5Xml REQUIRED)
find_package(Qt5XmlPatterns REQUIRED)



SET(romeo_SOURCES
 src/main.cpp
 src/romeo/view/dialogs/addsubjectdialog.cpp
 src/romeo/view/dialogs/executedialog.cpp
 src/romeo/view/dialogs/newalgorithmdialog.cpp
 src/romeo/view/dialogs/newfeaturedialog.cpp
 src/romeo/view/dialogs/protocoldialog.cpp
 src/romeo/view/dialogs/helpdialog.cpp
 src/romeo/view/dialogs/aboutdialog.cpp
 src/romeo/view/mainWindow/datasetpanel.cpp
 src/romeo/view/mainWindow/datasetsexplorer.cpp
 src/romeo/view/mainWindow/executepanel.cpp
 src/romeo/view/mainWindow/mainwindow.cpp
 src/romeo/view/mainWindow/explorer.cpp
 src/romeo/view/mainWindow/filesystemexplorer.cpp
 src/romeo/view/mainWindow/protocolspanel.cpp
 src/romeo/view/mainWindow/protocolsexplorer.cpp
 src/romeo/view/mainWindow/subjectspanel.cpp
 src/romeo/model/core/modelcore.cpp
 src/romeo/model/core/writer.cpp
 src/romeo/model/core/loader.cpp
 src/romeo/model/protocols/color.cpp
 src/romeo/model/protocols/abstractprotocol.cpp
 src/romeo/model/protocols/staticprotocol.cpp
 src/romeo/model/protocols/dynamicprotocol.cpp
 src/romeo/model/protocols/features/abstractfeature.cpp
 src/romeo/model/protocols/features/dynamicfeature.cpp
 src/romeo/model/protocols/features/abstractstaticfeature.cpp
 src/romeo/model/protocols/features/firstorderfeature.cpp
 src/romeo/model/protocols/features/secondorderfeature.cpp
 src/romeo/model/protocols/protocolslist.cpp
 src/romeo/model/protocols/features/featureslist.cpp
 src/romeo/model/protocols/algorithms/abstractalgorithm.cpp
 src/romeo/model/protocols/algorithms/algorithmslist.cpp
 src/romeo/model/protocols/algorithms/kmeans.cpp
 src/romeo/model/protocols/algorithms/fuzzycmeans.cpp
 src/romeo/model/protocols/algorithms/hierarchical.cpp
 src/romeo/model/protocols/algorithms/userdefinedalgorithm.cpp
 src/romeo/model/imageIO/handlerio.cpp
 src/romeo/model/imageIO/handleriostatic.cpp
 src/romeo/model/imageIO/handleriodynamic.cpp
 src/romeo/model/datasets/result.cpp
 src/romeo/model/datasets/abstractdataset.cpp
 src/romeo/model/datasets/datasetslist.cpp
 src/romeo/model/datasets/dataset2d.cpp
 src/romeo/model/datasets/dataset2dt.cpp
 src/romeo/model/datasets/dataset3d.cpp
 src/romeo/model/datasets/dataset3dt.cpp
 src/romeo/model/datasets/abstractsubject.cpp
 src/romeo/model/datasets/subject2d.cpp
 src/romeo/model/datasets/subject2dt.cpp
 src/romeo/model/datasets/subject3d.cpp
 src/romeo/model/datasets/subject3dt.cpp
 src/romeo/controller/controller.cpp
 src/romeo/view/dialogs/newdatasetdialog.cpp
 src/romeo/view/dialogs/featureslistdialog.cpp
 src/romeo/view/dialogs/algorithmslistdialog.cpp
 src/romeo/model/inputformats.h
 src/romeo/view/dialogs/parametervalueform.cpp
 src/romeo/view/dialogs/newalgorithmparameterform.cpp
 src/romeo/view/mainWindow/listwidget.cpp
 src/romeo/view/mainWindow/listview.cpp
 src/romeo/view/dialogs/associateprotocoldialog.cpp
 src/romeo/controller/analysiscontroller.cpp
 src/romeo/controller/protocolscontroller.cpp
 src/romeo/controller/abouthelpcontroller.cpp
 src/romeo/controller/featurescontroller.cpp
 src/romeo/controller/algorithmscontroller.cpp
)

SET(romeo_HEADERS
 src/romeo/view/dialogs/addsubjectdialog.h
 src/romeo/view/dialogs/executedialog.h
 src/romeo/view/dialogs/newalgorithmdialog.h
 src/romeo/view/dialogs/newfeaturedialog.h
 src/romeo/view/dialogs/protocoldialog.h
 src/romeo/view/dialogs/helpdialog.h
 src/romeo/view/dialogs/aboutdialog.h
 src/romeo/view/mainWindow/datasetpanel.h
 src/romeo/view/mainWindow/datasetsexplorer.h
 src/romeo/view/mainWindow/executepanel.h
 src/romeo/view/mainWindow/mainwindow.h
 src/romeo/view/mainWindow/explorer.h
 src/romeo/view/mainWindow/filesystemexplorer.h
 src/romeo/view/mainWindow/protocolspanel.h
 src/romeo/view/mainWindow/protocolsexplorer.h
 src/romeo/view/mainWindow/subjectspanel.h
 src/romeo/model/core/modelCore.h
 src/romeo/model/core/writer.h
 src/romeo/model/core/loader.h
 src/romeo/model/protocols/color.h
 src/romeo/model/protocols/abstractprotocol.h
 src/romeo/model/protocols/staticprotocol.h
 src/romeo/model/protocols/dynamicprotocol.h
 src/romeo/model/protocols/features/abstractfeature.h
 src/romeo/model/protocols/features/dynamicfeature.h
 src/romeo/model/protocols/features/abstractstaticfeature.h
 src/romeo/model/protocols/features/firstorderfeature.h
 src/romeo/model/protocols/features/secondorderfeature.h
 src/romeo/model/protocols/protocolslist.h
 src/romeo/model/protocols/features/featureslist.h
 src/romeo/model/protocols/algorithms/abstractalgorithm.h
 src/romeo/model/protocols/algorithms/algorithmslist.h
 src/romeo/model/protocols/algorithms/kmeans.h
 src/romeo/model/protocols/algorithms/fuzzycmeans.h
 src/romeo/model/protocols/algorithms/hierarchical.h
 src/romeo/model/protocols/algorithms/userdefinedalgorithm.h
 src/romeo/model/imageIO/handlerio.h
 src/romeo/model/imageIO/handleriostatic.h
 src/romeo/model/imageIO/handleriodynamic.h
 src/romeo/model/datasets/result.h
 src/romeo/model/datasets/abstractdataset.h
 src/romeo/model/datasets/datasetslist.h
 src/romeo/model/datasets/dataset2d.h
 src/romeo/model/datasets/dataset2dt.h
 src/romeo/model/datasets/dataset3d.h
 src/romeo/model/datasets/dataset3dt.h
 src/romeo/model/datasets/abstractsubject.h
 src/romeo/model/datasets/subject2d.h
 src/romeo/model/datasets/subject2dt.h
 src/romeo/model/datasets/subject3d.h
 src/romeo/model/datasets/subject3dt.h
 src/romeo/controller/controller.h
 src/romeo/view/dialogs/newdatasetdialog.h
 src/romeo/view/dialogs/featureslistdialog.h
 src/romeo/view/dialogs/algorithmslistdialog.h
 src/romeo/view/dialogs/parametervalueform.h
 src/romeo/view/dialogs/newalgorithmparameterform.h
 src/romeo/view/mainWindow/listwidget.h
 src/romeo/view/mainWindow/listview.h
 src/romeo/view/dialogs/associateprotocoldialog.h
 src/romeo/controller/analysiscontroller.h
 src/romeo/controller/protocolscontroller.h
 src/romeo/controller/abouthelpcontroller.h
 src/romeo/controller/algorithmscontroller.h
 src/romeo/controller/featurescontroller.h
)

SET(romeo_FORMS
 src/romeo/view/dialogs/addsubjectdialog.ui
 src/romeo/view/dialogs/executedialog.ui
 src/romeo/view/dialogs/newalgorithmdialog.ui
 src/romeo/view/dialogs/newfeaturedialog.ui
 src/romeo/view/dialogs/protocoldialog.ui
 src/romeo/view/mainWindow/datasetpanel.ui
 src/romeo/view/mainWindow/datasetsexplorer.ui
 src/romeo/view/mainWindow/executepanel.ui
 src/romeo/view/mainWindow/mainwindow.ui
 src/romeo/view/mainWindow/explorer.ui
 src/romeo/view/mainWindow/filesystemexplorer.ui
 src/romeo/view/mainWindow/protocolspanel.ui
 src/romeo/view/mainWindow/protocolsexplorer.ui
 src/romeo/view/mainWindow/subjectspanel.ui
 src/romeo/view/dialogs/newdatasetdialog.ui
 src/romeo/view/dialogs/featureslistdialog.ui
 src/romeo/view/dialogs/algorithmslistdialog.ui
 src/romeo/view/dialogs/parametervalueform.ui
 src/romeo/view/dialogs/newalgorithmparameterform.ui
 src/romeo/view/dialogs/associateprotocoldialog.ui
 src/romeo/view/dialogs/helpdialog.ui
 src/romeo/view/dialogs/aboutdialog.ui
)

SET(romeo_RESOURCES src/immagini.qrc)



INCLUDE_DIRECTORIES(
  ${Qt5Widgets_INCLUDE_DIRS}
  ${Qt5Declarative_INCLUDE_DIRS}
  ${CMAKE_CURRENT_BINARY_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}
)


#QT5_WRAP_CPP(romeo_HEADERS_MOC ${romeo_HEADERS})
QT5_WRAP_UI(romeo_FORMS_HEADERS ${romeo_FORMS} ${MainUI})
QT5_ADD_RESOURCES(romeo_RESOURCES_RCC ${romeo_RESOURCES})

#SOURCE_GROUP("Resources" FILES
#  ${romeo_FORMS}
#)
#SOURCE_GROUP("Generated" FILES
 # ${romeo_FORMS_HEADERS}
  #${MOCSrcs}
  #${RCS_SOURCES}
#)

SET(GCC_COVERAGE_COMPILE_FLAGS "-fPIC")
add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})


set(algorithms
    ext/cluster.h
    ext/cluster.cpp
)
add_library (core2 OBJECT ${algorithms})
add_library (algorithms STATIC $<TARGET_OBJECTS:core2>)

# Set some Win32 Specific Settings
IF(WIN32)
SET(GUI_TYPE WIN32)

IF( MINGW )
# resource compilation for MinGW
ADD_CUSTOM_COMMAND( OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/romeo.o
COMMAND windres.exe -i${CMAKE_CURRENT_SOURCE_DIR} -i${CMAKE_CURRENT_SOURCE_DIR}/src/romeo.rc -o ${CMAKE_CURRENT_BINARY_DIR}/romeo.o )
SET(romeo_SOURCES ${romeo_SOURCES} ${CMAKE_CURRENT_BINARY_DIR}/romeo.o)
ELSE( MINGW )
SET(romeo_SOURCES ${romeo_SOURCES} src/romeo.rc)
ENDIF( MINGW )

ENDIF(WIN32)
# Set some Apple MacOS Specific settings
IF (APPLE)
SET(GUI_TYPE MACOSX_BUNDLE)
ENDIF (APPLE)

ADD_EXECUTABLE( romeo ${GUI_TYPE} ${romeo_SOURCES}
    #${romeo_HEADERS_MOC}
    ${romeo_FORMS_HEADERS}
    ${romeo_RESOURCES_RCC}
    $<TARGET_OBJECTS:core2>
)


QT5_USE_MODULES(romeo Widgets Xml XmlPatterns Test)
TARGET_LINK_LIBRARIES( romeo ${ITK_LIBRARIES} ${VTK_LIBRARIES} ${OpenCV_LIBS} )

set(features
    ext/features.cpp
    ext/features.h
)

add_library (core OBJECT ${features})
add_library (features SHARED $<TARGET_OBJECTS:core>)
set_target_properties(features PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "features"
)

file(COPY data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

#ADD_SUBDIRECTORY(tests)

