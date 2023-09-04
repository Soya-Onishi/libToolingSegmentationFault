set(LLVM_LINK_COMPONENTS
  Support
)

add_clang_library(astSyntaxTree
  ASTSyntaxTree.cpp
)

clang_target_link_libraries(astSyntaxTree
  PRIVATE
  clangBasic
  clangFrontend
  clangSerialization
  clangTooling
  clangToolingASTDiff
)
