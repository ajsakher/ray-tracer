set(BINARY ${CMAKE_PROJECT_NAME})

add_executable(${BINARY}_unit_sphere_render main.cpp)

target_link_libraries(${BINARY}_unit_sphere_render ${CMAKE_PROJECT_NAME}_lib)
