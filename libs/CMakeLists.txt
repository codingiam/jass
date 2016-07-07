FILE(GLOB_RECURSE SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cc)

ADD_LIBRARY(libs ${SRC_FILES})

TARGET_INCLUDE_DIRECTORIES(libs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#   message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
