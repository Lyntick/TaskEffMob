set(TARGET BMPReader)
project(${TARGET})

set(HEADERS BMPReader.h)
set(SOURCES BMPReader.cpp)

add_library(${TARGET} STATIC ${HEADERS} ${SOURCES})