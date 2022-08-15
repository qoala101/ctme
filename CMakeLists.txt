cmake_minimum_required(VERSION 3.18)

# Generates compile_commands.json which should be included
# in .vscode/c_cpp_properties.json so that VS Code IntelliSence
# can find external library headeds
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  "ctmm"
  VERSION 0.0.1
  LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(tests
  tests.cc
)