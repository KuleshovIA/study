target_sources(${MY_SORT_LIB}
	PRIVATE
		bubble_sort.cpp
	PUBLIC
		bubble_sort.hpp
)

target_include_directories(${MY_SORT_LIB} PUBLIC
	"${CURRENT_SOURCE_DIR}"
)
