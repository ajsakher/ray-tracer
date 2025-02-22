set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(${BINARY}_clock-sim main.cpp)

target_link_libraries(${BINARY}_clock-sim ${CMAKE_PROJECT_NAME}_lib)
