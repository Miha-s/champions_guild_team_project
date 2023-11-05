enable_testing()

add_executable(
        LexerTest
        lexer/LexerTest.cpp
)


add_executable(
        AlgorithmsTest
        algorithms/AlgorithmsTest.cpp
        parser/LL1Test.cpp
        parser/RecursiveTest.cpp
)


add_executable(
        LL1Test
        parser/LL1Test.cpp
        )

target_link_libraries(
        LexerTest
        parsing
        GTest::gtest_main
)

target_link_libraries(
        AlgorithmsTest
        parsing
        GTest::gtest_main
)

target_link_libraries(
        LL1Test
        parsing
        GTest::gtest_main
        )

include(GoogleTest)

gtest_discover_tests(LexerTest)
gtest_discover_tests(AlgorithmsTest)
