include_directories("../")

add_library(add SHARED add.cc)
add_library(square SHARED square.cc)

add_executable(filter_plugin main.cc)

target_link_libraries(filter_plugin dl)