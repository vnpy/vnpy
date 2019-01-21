project(vnctp)

set(HEADERS
    class_generators.h
    dispatcher.hpp
    property_helper.hpp
    vnctptd.cpp
    wrappers.hpp
    wrapper_helper.hpp
    )


set(SOURCES
    classes_1.cpp
    classes_2.cpp
    classes_3.cpp
    classes_4.cpp
    vnctp.cpp
)

include_directories(${PY_INCLUDE_DIRS})
link_directories(${PY_LIBRARY_DIRS})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/api")
link_directories("${CMAKE_CURRENT_SOURCE_DIR}/api")


add_library(vnctp SHARED ${SOURCES})
target_link_libraries(vnctp ${PY_LIBRARIES})
target_link_libraries(vnctp thostmduserapi_se thosttraderapi_se)
