set(TARGET_NAME ${PROJECT_NAME})

add_subdirectory(flags)
add_subdirectory(tools)
add_subdirectory(sbe)

add_subdirectory(dump)

set(SOURCES
    account.cpp
    api.cpp
    application.cpp
    channel.cpp
    config.cpp
    gateway.cpp
    instrument.cpp
    order_entry.cpp
    settings.cpp
    shared.cpp
    market_data.cpp
    market_data_snapshot.cpp
    main.cpp)

include(RoqAutogen)

roq_gitignore(OUTPUT .gitignore SOURCES ${TARGET_NAME})

add_executable(${TARGET_NAME} ${SOURCES})

target_link_libraries(
  ${TARGET_NAME}
  PRIVATE ${PROJECT_NAME}-flags
          ${PROJECT_NAME}-sbe
          ${PROJECT_NAME}-tools
          roq-api::roq-api
          roq-core::roq-core
          roq-codec::roq-codec
          roq-flags::roq-flags
          roq-io::roq-io
          roq-logging::roq-logging
          roq-logging::roq-logging-flags
          roq-market::roq-market
          roq-server::roq-server
          roq-server::roq-server-flags
          roq-utils::roq-utils
          roq-web::roq-web
          unordered_dense::unordered_dense)

if(ROQ_BUILD_TYPE STREQUAL "Release")
  set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)
endif()

target_compile_definitions(
  ${TARGET_NAME} PRIVATE ROQ_PACKAGE_NAME="${TARGET_NAME}" ROQ_HOST="${ROQ_HOST}" ROQ_BUILD_VERSION="${GIT_REPO_VERSION}"
                         ROQ_GIT_DESCRIBE_HASH="${GIT_DESCRIBE_HASH}" ROQ_BUILD_NUMBER="${ROQ_BUILD_NUMBER}" ROQ_BUILD_TYPE="${ROQ_BUILD_TYPE}")

install(TARGETS ${TARGET_NAME})

if(BUILD_DOCS)

  install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
    DESTINATION ${CMAKE_INSTALL_DATADIR}/doc/${PROJECT_NAME}
    FILES_MATCHING
    PATTERN "*.rst*"
    PATTERN "CMakeFiles" EXCLUDE)

endif()
