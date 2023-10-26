SET(LIB_NAME parsing_utilites)

file(GLOB_RECURSE HEADERS "lexer/*.hpp"
			  "syntax_analyser/*.hpp")

file(GLOB_RECURSE SOURCES "lexer/*.cpp"
			  "syntax_analyser/*.hpp")

add_library(${LIB_NAME} SHARED
		${SOURCES}
		${HEADERS})

set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 14)


target_include_directories(${LIB_NAME}
	PUBLIC
	./
)

add_executable(parser main.cpp)

set_property(TARGET parser PROPERTY CXX_STANDARD 14)


target_link_libraries(parser ${LIB_NAME})

