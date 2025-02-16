set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(${BINARY}_environment_sim main.cpp)

target_link_libraries(${BINARY}_environment_sim ${CMAKE_PROJECT_NAME}_lib)
