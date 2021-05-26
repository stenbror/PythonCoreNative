
file(GLOB SOURCES_CONSOLE src/*.cc)


add_executable(PythonCoreConsole ${SOURCES_CONSOLE})
target_link_libraries(PythonCoreConsole PythonCoreNative)
