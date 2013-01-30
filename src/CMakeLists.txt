PROJECT(xaloy)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

IF(WIN32)
    ADD_DEFINITIONS(-DXALOY_PLATFORM_WINDOWS)
    SET(LUA_INCLUDE_DIR CACHE FILEPATH "folder of Lua's include files")
    SET(LUA_LIBRARY_DIR CACHE FILEPATH "folder of Lua's library files")
ENDIF()

OPTION(BUILD_TEST_FEATURE "Build Test Suite" ON)
OPTION(BUILD_BUILDER_FEATURE "Build the build tools" OFF)

# Set Base file
SET(SOURCE_ROOT ${PROJECT_SOURCE_DIR}/src)

SET(BASE_SRC 
    "${SOURCE_ROOT}/base/common.cc"
    "${SOURCE_ROOT}/base/filestream.cc"
    "${SOURCE_ROOT}/base/printer.cc"
)

IF(BUILD_TEST_FEATURE)
    SET(TEST_FEATURE_SRC ${BASE_SRC}
        "${SOURCE_ROOT}/tester/reporter.cc"
        "${SOURCE_ROOT}/tester/testprocess.cc"
    )
    ADD_LIBRARY(xaloytest STATIC ${TEST_FEATURE_SRC})

    # build demo
    SET(TESTSUITE_DEMO ${TEST_FEATURE_SRC}
        "${PROJECT_SOURCE_DIR}/demo/testsuite_demo.cc"
    )
    ADD_EXECUTABLE(testsuite_demo ${TESTSUITE_DEMO})
ENDIF()

IF(BUILD_BUILDER_FEATURE)
    SET(BUILDER_FEATURE_SRC ${BASE_SRC}
    )
    INCLUDE_DIRECTORIES(${LUA_INCLUDE_DIR})
    LINK_DIRECTORIES(${LUA_LIBRARY_DIR})

    ADD_EXECUTABLE(xbuild ${BUILDER_FEATURE_SRC})
    TARGET_LINK_LIBRARIES(xbuild lua)    
ENDIF()

