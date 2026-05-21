set(TARGET_NAME ${PROJECT_NAME}-dump-flags)

set(AUTOGEN_SCHEMAS flags.json)

include(RoqAutogen)

set(NAMESPACE "roq/cme/dump/flags")

if(BUILD_DOCS)

  roq_autogen_rst(
    OUTPUT
    AUTOGEN_DOCS
    SOURCES
    ${AUTOGEN_SCHEMAS}
    NAMESPACE
    ${NAMESPACE}
    TEMPLATE_DIR
    ${TEMPLATE_DIR}
    TEMPLATE_TYPE
    "doc")

  add_custom_target(dump-autogen-docs ALL DEPENDS ${AUTOGEN_DOCS})

endif()

roq_autogen_hpp(
  OUTPUT
  AUTOGEN_HEADERS
  SOURCES
  ${AUTOGEN_SCHEMAS}
  TEMPLATE_DIR
  ${TEMPLATE_DIR}
  TEMPLATE_TYPE
  "state")

add_custom_target(dump-autogen-headers ALL DEPENDS ${AUTOGEN_HEADERS})

roq_autogen_cpp(
  OUTPUT
  AUTOGEN_SOURCES
  SOURCES
  ${AUTOGEN_SCHEMAS}
  TEMPLATE_DIR
  ${TEMPLATE_DIR}
  TEMPLATE_TYPE
  "state")

roq_gitignore(
  OUTPUT
  .gitignore
  SOURCES
  ${TARGET_NAME}
  ${AUTOGEN_DOCS}
  ${AUTOGEN_HEADERS}
  ${AUTOGEN_SOURCES})

add_library(${TARGET_NAME} OBJECT ${AUTOGEN_SOURCES})

add_dependencies(${TARGET_NAME} dump-autogen-headers)

target_link_libraries(${TARGET_NAME} PRIVATE roq-api::roq-api absl::flags)

if(ROQ_BUILD_TYPE STREQUAL "Release")
  set_target_properties(${TARGET_NAME} PROPERTIES LINK_FLAGS_RELEASE -s)
endif()
