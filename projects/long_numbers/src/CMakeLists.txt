target_sources(${MY_SORT_LIB}
	PRIVATE
		long_number.cpp
	PUBLIC
		long_number.hpp
)

target_include_directories(${MY_SORT_LIB} PUBLIC
	"${CURRENT_SOURCE_DIR}"
)
