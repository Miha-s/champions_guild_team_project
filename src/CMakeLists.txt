file(GLOB_RECURSE GRAMMAR_LIB_HEADERS
                "algorithms/*.hpp"
                "grammar/*.hpp"
                "structures/*.hpp")

file(GLOB_RECURSE GRAMMAR_LIB_SOURCES
                "algorithms/*.cpp"
                "grammar/*.cpp"
                "structures/*.cpp")


add_library(grammar SHARED
                ${GRAMMAR_LIB_SOURCES}
                ${GRAMMAR_LIB_HEADERS}
        algorithms/algorithms.cpp)

set_property(TARGET grammar PROPERTY CXX_STANDARD 14)


target_include_directories(grammar PUBLIC ./ )

file(GLOB_RECURSE PARSING_LIB_HEADERS
                "lexer/*.hpp"
                "syntax_analyser/*.hpp")

file(GLOB_RECURSE PARSING_LIB_SOURCES
                "lexer/*.cpp"
                "syntax_analyser/*.cpp")

add_library(parsing SHARED
                ${PARSING_LIB_SOURCES}
                ${PARSING_LIB_HEADERS})

set_property(TARGET parsing PROPERTY CXX_STANDARD 14)


target_include_directories(parsing PUBLIC ./ )

target_link_libraries(parsing grammar)

file(GLOB_RECURSE HEADERS "lifecycle/*.hpp")

file(GLOB_RECURSE SOURCES "lifecycle/*.cpp")


add_executable(parser main.cpp ${SOURCES})

target_include_directories(parser PUBLIC ./ )

set_property(TARGET parser PROPERTY CXX_STANDARD 14)


target_link_libraries(parser grammar parsing)

