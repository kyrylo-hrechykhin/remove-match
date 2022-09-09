cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)

project (remove-match)

file(GLOB SRC src/*)

add_executable(remove-match ${SRC})

add_custom_command(TARGET remove-match PRE_BUILD
                   COMMAND ${CMAKE_COMMAND} -E copy_directory
                       ${CMAKE_SOURCE_DIR}/testing/ $<TARGET_FILE_DIR:remove-match>/testing)

set_target_properties(remove-match PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "$<TARGET_FILE_DIR:remove-match>")
