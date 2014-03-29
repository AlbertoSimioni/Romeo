


SET(romeoTest_SOURCES
testparametervalueform.cpp
testnewalgorithmdialog.cpp
testnewfeaturedialog.cpp
testnewdatasetdialog.cpp
testprotocoldialog.cpp
testabstractalgorithm.cpp
testalgorithmslist.cpp
testdynamicprotocol.cpp
teststaticprotocol.cpp
testprotocolslist.cpp
testdynamicfeature.cpp
testfirstorderfeature.cpp
testsecondorderfeature.cpp
testfeatureslist.cpp
testwriter.cpp
testuserdefinedalgorithm.cpp
testcontroller.cpp
testprotocolscontroller.cpp
testfeaturescontroller.cpp
testalgorithmscontroller.cpp
testnewalgorithmparameterform.cpp
testprotocolspanel.cpp
testcolor.cpp
testexecutepanel.cpp
testfilesystemexplorer.cpp
testprotocolsexplorer.cpp
testmainwindow.cpp
testfeatureslistdialog.cpp
testmain.cpp
 testdataset2d.cpp
 testdataset2dt.cpp
 testdataset3d.cpp
 testdataset3dt.cpp
 testsubject2d.cpp
 testsubject2dt.cpp
 testsubject3d.cpp
 testsubject3dt.cpp
 testresult.cpp
 testdatasetslist.cpp
 testabstractsubject.cpp
 testabstractdataset.cpp
 testexecutedialog.cpp
 testaddsubjectdialog.cpp
 ../src/romeo/view/dialogs/newdatasetdialog.ui
 ../src/romeo/view/dialogs/addsubjectdialog.cpp
 ../src/romeo/view/dialogs/executedialog.cpp
  ../src/romeo/view/dialogs/newalgorithmdialog.cpp
  ../src/romeo/view/dialogs/newfeaturedialog.cpp
  ../src/romeo/view/dialogs/protocoldialog.cpp
  ../src/romeo/view/dialogs/helpdialog.cpp
  ../src/romeo/view/dialogs/aboutdialog.cpp
  ../src/romeo/view/mainWindow/datasetpanel.cpp
  ../src/romeo/view/mainWindow/datasetsexplorer.cpp
  ../src/romeo/view/mainWindow/executepanel.cpp
  ../src/romeo/view/mainWindow/mainwindow.cpp
  ../src/romeo/view/mainWindow/explorer.cpp
  ../src/romeo/view/mainWindow/filesystemexplorer.cpp
  ../src/romeo/view/mainWindow/protocolspanel.cpp
  ../src/romeo/view/mainWindow/protocolsexplorer.cpp
  ../src/romeo/view/mainWindow/subjectspanel.cpp
  ../src/romeo/model/core/modelcore.cpp
  ../src/romeo/model/core/writer.cpp
  ../src/romeo/model/core/loader.cpp
  ../src/romeo/model/protocols/color.cpp
  ../src/romeo/model/protocols/abstractprotocol.cpp
  ../src/romeo/model/protocols/staticprotocol.cpp
  ../src/romeo/model/protocols/dynamicprotocol.cpp
  ../src/romeo/model/protocols/features/abstractfeature.cpp
  ../src/romeo/model/protocols/features/dynamicfeature.cpp
  ../src/romeo/model/protocols/features/abstractstaticfeature.cpp
  ../src/romeo/model/protocols/features/firstorderfeature.cpp
  ../src/romeo/model/protocols/features/secondorderfeature.cpp
  ../src/romeo/model/protocols/protocolslist.cpp
  ../src/romeo/model/protocols/features/featureslist.cpp
  ../src/romeo/model/protocols/algorithms/abstractalgorithm.cpp
  ../src/romeo/model/protocols/algorithms/algorithmslist.cpp
  ../src/romeo/model/protocols/algorithms/kmeans.cpp
  ../src/romeo/model/protocols/algorithms/fuzzycmeans.cpp
  ../src/romeo/model/protocols/algorithms/hierarchical.cpp
  ../src/romeo/model/protocols/algorithms/userdefinedalgorithm.cpp
  ../src/romeo/model/imageIO/handlerio.cpp
  ../src/romeo/model/imageIO/handleriostatic.cpp
  ../src/romeo/model/imageIO/handleriodynamic.cpp
  ../src/romeo/model/datasets/result.cpp
  ../src/romeo/model/datasets/abstractdataset.cpp
  ../src/romeo/model/datasets/datasetslist.cpp
  ../src/romeo/model/datasets/dataset2d.cpp
  ../src/romeo/model/datasets/dataset2dt.cpp
  ../src/romeo/model/datasets/dataset3d.cpp
  ../src/romeo/model/datasets/dataset3dt.cpp
  ../src/romeo/model/datasets/abstractsubject.cpp
  ../src/romeo/model/datasets/subject2d.cpp
  ../src/romeo/model/datasets/subject2dt.cpp
  ../src/romeo/model/datasets/subject3d.cpp
  ../src/romeo/model/datasets/subject3dt.cpp
  ../src/romeo/controller/controller.cpp
  ../src/romeo/controller/abouthelpcontroller.cpp
  ../src/romeo/controller/algorithmscontroller.cpp
  ../src/romeo/controller/analysiscontroller.cpp
  ../src/romeo/controller/featurescontroller.cpp
  ../src/romeo/controller/protocolscontroller.cpp
  ../src/romeo/view/dialogs/newdatasetdialog.cpp
  ../src/romeo/view/dialogs/featureslistdialog.cpp
  ../src/romeo/view/dialogs/algorithmslistdialog.cpp
  ../src/romeo/model/inputformats.h
  ../src/romeo/view/dialogs/parametervalueform.cpp
  ../src/romeo/view/dialogs/newalgorithmparameterform.cpp
  ../src/romeo/view/mainWindow/listwidget.cpp
  ../src/romeo/view/mainWindow/listview.cpp
  ../src/romeo/view/dialogs/associateprotocoldialog.cpp
)
SET(romeoTest_HEADERS
testparametervalueform.h
testnewalgorithmdialog.h
testnewfeaturedialog.h
testnewdatasetdialog.h
testprotocoldialog.h
testabstractalgorithm.h
testalgorithmslist.h
testdynamicprotocol.h
teststaticprotocol.h
testprotocolslist.h
testdynamicfeature.h
testfirstorderfeature.h
testsecondorderfeature.h
testfeatureslist.h
testwriter.h
testuserdefinedalgorithm.h
testcontroller.h
testprotocolscontroller.h
testfeaturescontroller.h
testalgorithmscontroller.h
testnewalgorithmparameterform.h
testprotocolspanel.h
testcolor.h
testmain.h
 testdataset2d.h
 testdataset2dt.h
 testdataset3d.h
 testdataset3dt.h
 testsubject2d.h
 testsubject2dt.h
 testsubject3d.h
 testsubject3dt.h
 testresult.h
 testdatasetslist.h
 testabstractsubject.h
 testabstractdataset.h
 testexecutedialog.h
 testaddsubjectdialog.h
)

SET(romeoTest_FORMS
 ../src/romeo/view/dialogs/addsubjectdialog.ui
 ../src/romeo/view/dialogs/executedialog.ui
 ../src/romeo/view/dialogs/newalgorithmdialog.ui
 ../src/romeo/view/dialogs/newfeaturedialog.ui
 ../src/romeo/view/dialogs/protocoldialog.ui
 ../src/romeo/view/mainWindow/datasetpanel.ui
 ../src/romeo/view/mainWindow/datasetsexplorer.ui
 ../src/romeo/view/mainWindow/executepanel.ui
 ../src/romeo/view/mainWindow/mainwindow.ui
 ../src/romeo/view/mainWindow/explorer.ui
 ../src/romeo/view/mainWindow/filesystemexplorer.ui
 ../src/romeo/view/mainWindow/protocolspanel.ui
 ../src/romeo/view/mainWindow/protocolsexplorer.ui
 ../src/romeo/view/mainWindow/subjectspanel.ui
 ../src/romeo/view/dialogs/newdatasetdialog.ui
 ../src/romeo/view/dialogs/featureslistdialog.ui
 ../src/romeo/view/dialogs/algorithmslistdialog.ui
 ../src/romeo/view/dialogs/parametervalueform.ui
 ../src/romeo/view/dialogs/newalgorithmparameterform.ui
 ../src/romeo/view/dialogs/associateprotocoldialog.ui
)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0 -Wall -W -Wshadow -Wunused-variable -Wunused-parameter -Wunused-function -Wunused -Wno-system-headers -Wno-deprecated -Woverloaded-virtual -Wwrite-strings -fprofile-arcs -ftest-coverage")

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -O0 -Wall -W -fprofile-arcs -ftest-coverage")

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fprofile-arcs -ftest-coverage")


ADD_EXECUTABLE(romeoTest ${romeoTest_SOURCES}
    ${romeoTest_HEADERS_MOC}
    ${romeoTest_FORMS_HEADERS}
    $<TARGET_OBJECTS:core2>
)

QT5_USE_MODULES(romeoTest Widgets Xml XmlPatterns Test WebKitWidgets)
TARGET_LINK_LIBRARIES( romeoTest ${ITK_LIBRARIES}  ${VTK_LIBRARIES} )

set(featuresTest
    ../ext/features.cpp
    ../ext/features.h
)

add_library (coreTest OBJECT ${featuresTest})
add_library (featuresTest SHARED $<TARGET_OBJECTS:coreTest>)
set_target_properties(featuresTest PROPERTIES
  LIBRARY_OUTPUT_DIRECTORY "features"
)

file(COPY ../tests/data DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_test(NAME RomeoTest COMMAND romeoTest)

