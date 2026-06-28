project(long_number)

set(MY_SORT_LIB "long_numbers_lib2")
add_library(${MY_SORT_LIB} "")

add_subdirectory(src)
add_subdirectory(test)
