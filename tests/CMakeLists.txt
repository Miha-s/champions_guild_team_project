enable_testing()

add_executable(
  LexerTest
  lexer/LexerTest.cpp
        algorithms/ArlgorithmsTest.cpp
        algorithms/ArlgorithmsTest.h
)
target_link_libraries(
  LexerTest
  parsing
  GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(LexerTest)
