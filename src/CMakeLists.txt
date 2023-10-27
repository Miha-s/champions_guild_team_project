SET(LIB_NAME parsing_utilites)

file(GLOB_RECURSE LIB_HEADERS "algorithms/*.hpp"
                              "grammar/*.hpp"
                              "structures/*.hpp")

file(GLOB_RECURSE LIB_SOURCES "algorithms/*.cpp"
                              "grammar/*.cpp"
                              "structures/*.cpp")


add_library(${LIB_NAME} SHARED
                ${LIB_SOURCES}
                ${LIB_HEADERS})

set_property(TARGET ${LIB_NAME} PROPERTY CXX_STANDARD 14)


target_include_directories(${LIB_NAME}
	PUBLIC
	./
)

file(GLOB_RECURSE HEADERS "lexer/*.hpp"
                          "syntax_analyser/*.hpp"
                          "lifecycle/*.hpp")

file(GLOB_RECURSE SOURCES "lexer/*.cpp"
                          "syntax_analyser/*.cpp"
                          "lifecycle/*.cpp")


add_executable(parser main.cpp ${SOURCES})

target_include_directories(parser
    PUBLIC
    ./
)

set_property(TARGET parser PROPERTY CXX_STANDARD 14)


target_link_libraries(parser ${LIB_NAME})

