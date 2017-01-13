add_cirkit_library(
  NAME cirkit_random
  AUTO_DIRS src
  USE
    cirkit_classical
  INCLUDE
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/src
  DEFINE
    PUBLIC ADDON_RANDOM
  COMMANDS
    classical/cli/commands/random_commands.hpp
)
