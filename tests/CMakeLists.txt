enable_testing()

add_executable(
  LexerTest
  lexer/LexerTest.cpp
)
target_link_libraries(
  LexerTest
  parsing
  GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(LexerTest)
