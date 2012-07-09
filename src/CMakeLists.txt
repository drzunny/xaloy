PROJECT(XTOOLS)
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

SET(LUA_DIR "E:\\codes\\other\\library\\include")
SET(LUA_LIB "E:\\codes\\other\\library\\lib\\liblua.a")

INCLUDE_DIRECTORIES(${LUA_DIR})
ADD_LIBRARY(xtools SHARED xaloytools.c)
TARGET_LINK_LIBRARIES(xtools ${LUA_LIB})