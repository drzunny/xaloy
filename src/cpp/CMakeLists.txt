SET(LIBRARY_OUTPUT_PATH "${PROJECT_BINARY_DIR}/lib/")

SET(XALOY_CPP_SRC xaloyflow.cc xaloyprinter.cc xaloytest.cc)
ADD_LIBRARY(xaloy STATIC ${XALOY_CPP_SRC})