if(EXISTS "/Users/user/unv/champions_guild_team_project/tests/cmake-build-debug/LexerTest[1]_tests.cmake")
  include("/Users/user/unv/champions_guild_team_project/tests/cmake-build-debug/LexerTest[1]_tests.cmake")
else()
  add_test(LexerTest_NOT_BUILT LexerTest_NOT_BUILT)
endif()
