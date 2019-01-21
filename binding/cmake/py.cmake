# try to find python use : user_defined_path, FindPython3 and FindPythonLibs
# outputs: USER_PYTHON_LIBRARIY USER_PYTHON_INCLUDE_DIRS


# ignore default input library in MSVC first
if (CMAKE_CXX_COMPILER_ID MATCHES MSVC)
    set(CMAKE_SHARED_LINKER_FLAGS_DEBUG "${CMAKE_SHARED_LINKER_FLAGS_DEBUG} /NODEFAULTLIB:\"python37_d.lib\"")
    set(CMAKE_SHARED_LINKER_FLAGS_RELEASE "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} /NODEFAULTLIB:\"python37.lib\"")
endif()

# define user options
set(USER_PYTHON_LIBRARIY ${USER_PYTHON_LIBRARIY} CACHE PATH "include dir for python3, eg: C:/Python37/include")
set(USER_PYTHON_INCLUDE_DIRS ${USER_PYTHON_INCLUDE_DIRS} CACHE FILEPATH "Helpstring, eg: C:/Python37/libs/python3.lib")

include(cmake/py_find.cmake)

set(USER_PYTHON_LIBRARIY ${PY_LIBRARIES} CACHE PATH "include dir for python3, eg: C:/Python37/include" FORCE)
set(USER_PYTHON_INCLUDE_DIRS ${PY_INCLUDE_DIRS} CACHE FILEPATH "Helpstring, eg: C:/Python37/libs/python3.lib" FORCE)

message("USER_PYTHON_LIBRARIY : ${USER_PYTHON_LIBRARIY}")
message("USER_PYTHON_INCLUDE_DIRS : ${USER_PYTHON_INCLUDE_DIRS}")

include_directories(${USER_PYTHON_INCLUDE_DIRS})
