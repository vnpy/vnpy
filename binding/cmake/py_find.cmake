# try to find python use : user_defined_path, FindPython3 and FindPythonLibs
# outputs: PY_LIBRARIES PY_INCLUDE_DIRS

# check if user supplied path
if(USER_PYTHON_LIBRARIY AND USER_PYTHON_INCLUDE_DIRS)
    set(PY_LIBRARIES ${USER_PYTHON_LIBRARIY})
    set(PY_INCLUDE_DIRS ${USER_PYTHON_INCLUDE_DIRS})
    message("use user supplied python paths")
    return()
endif()

if (${CMAKE_VERSION} VERSION_GREATER "3.12.0")
    find_package(Python3)

    if(${Python3_LIBRARIES} AND ${Python3_INCLUDE_DIRS})
        set(PY_LIBRARIES ${Python3_LIBRARIES})
        set(PY_INCLUDE_DIRS ${Python3_INCLUDE_DIRS})
        message("use FindPython3 found python paths")
        return()
    endif()
endif()

find_package(PythonLibs 3)

if(PYTHON_LIBRARIES AND PYTHON_INCLUDE_DIRS)
    set(PY_LIBRARIES ${PYTHON_LIBRARIES})
    set(PY_INCLUDE_DIRS ${PYTHON_INCLUDE_DIRS})
    message("use FindPythonLibs found python paths")
    return()
endif()

message(WARNING "no python path found!")