


SET(romeoTest_SOURCES
TestCheckValidity.cpp
)
SET(romeoTest_HEADERS
 TestCheckValidity.h
)


ADD_EXECUTABLE(romeoTest ${romeoTest_SOURCES}
    ${romeoTest_HEADERS_MOC}
)

QT5_USE_MODULES(romeoTest Widgets Xml XmlPatterns Test)
TARGET_LINK_LIBRARIES( romeoTest ${ITK_LIBRARIES}  ${VTK_LIBRARIES} )

