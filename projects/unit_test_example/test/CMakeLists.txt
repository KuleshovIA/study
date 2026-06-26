set(SOURCES 
	test_bubble.cpp
)

add_executable(test_bubble ${SOURCES})
target_link_libraries(test_bubble 
	gtest_main 
	${MY_SORT_LIB}
	ucrt
)

#target_link_options(test_bubble PRIVATE "-static-libgcc" "-static-libstdc++")

#add_compile_definitions(_CRT_SECURE_NO_WARNINGS)

add_test(test_bubble test_bubble)

#