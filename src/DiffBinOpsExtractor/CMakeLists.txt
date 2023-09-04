include_directories(${CMAKE_SOURCE_DIR}/include)

set(LLVM_LINK_COMPONENTS
  Support
)

add_clang_executable(diff-binops
  main.cpp
)

clang_target_link_libraries(diff-binops
  PRIVATE
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  clangToolingASTDiff
)

target_link_libraries(diff-binops
  PRIVATE
  astSyntaxTree
)
