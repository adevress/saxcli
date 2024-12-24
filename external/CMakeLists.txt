

include(FetchContent)




##
##  doctest
##
FetchContent_Declare(
  doctest
  GIT_REPOSITORY https://github.com/onqtam/doctest.git
  GIT_TAG master
)

FetchContent_MakeAvailable(doctest)


##
## fmt
## 
## Try to include fmt if the target is not declared already

if(NOT TARGET fmt::fmt)

FetchContent_Declare(
  fmt
  GIT_REPOSITORY https://github.com/fmtlib/fmt.git
  GIT_TAG 11.0.2
)

FetchContent_MakeAvailable(fmt)


endif()

##
## TL expected
##
if(NOT TARGET expected)

set(EXPECTED_BUILD_TESTS FALSE FORCE)
set(EXPECTED_BUILD_PACKAGE_DEB FALSE FORCE)

FetchContent_Declare(
  expected
  GIT_REPOSITORY https://github.com/TartanLlama/expected.git
  GIT_TAG v1.1.0
)

FetchContent_MakeAvailable(expected)

endif()


