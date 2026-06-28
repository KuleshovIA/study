set(SOURCES 
	test_long_numbers.cpp
)

add_executable(test_long_numbers ${SOURCES})
target_link_libraries(test_long_numbers 
	gtest
	${MY_SORT_LIB}
)

#target_link_options(test_bubble PRIVATE "-static-libgcc" "-static-libstdc++")

#add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

add_test(test_long_numbers test_long_numbers)

#