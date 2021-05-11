Include(FetchContent)

SET (CMAKE_CXX_FLAGS                "-Wall -std=c++14 -fPIC")

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v2.13.1)

FetchContent_MakeAvailable(Catch2)