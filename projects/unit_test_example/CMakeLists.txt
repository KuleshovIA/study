project(unit_test_example)

set(MY_SORT_LIB "bubble_sort_lib2")
add_library(${MY_SORT_LIB} "")

add_subdirectory(src)
add_subdirectory(test)
