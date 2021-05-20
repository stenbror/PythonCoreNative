
file(GLOB SOURCES_TESTS Parser/*.cc
                        *.cc)


add_executable(TestPythonCore ${SOURCES_TESTS})
target_link_libraries(TestPythonCore PRIVATE Catch2::Catch2
                      ${PROJECT_NAME})
