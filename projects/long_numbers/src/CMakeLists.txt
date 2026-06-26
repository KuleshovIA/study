project(long_number)

set(HEADERS
	long_number.hpp
)

set(SOURCES 
	main.cpp
	long_number.cpp
)

add_executable(${PROJECT_NAME} ${HEADERS} ${SOURCES})
