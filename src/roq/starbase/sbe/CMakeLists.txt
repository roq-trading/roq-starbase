set(TARGET_NAME ${PROJECT_NAME}-sbe)

set(SOURCES frame.cpp map.cpp parser.cpp parser_2.cpp)

add_library(${TARGET_NAME} OBJECT ${SOURCES})

target_link_libraries(${TARGET_NAME} PRIVATE roq-core::roq-core roq-codec::roq-codec roq-logging::roq-logging fmt::fmt)
