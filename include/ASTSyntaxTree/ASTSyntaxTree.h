#ifndef ASTDIFFFROMTWOFILES_H_
#define ASTDIFFFROMTWOFILES_H_

#include "clang/Tooling/CompilationDatabase.h"
#include "clang/Tooling/ASTDiff/ASTDiff.h"
#include "clang/Tooling/Tooling.h"

using namespace clang;
using namespace clang::tooling;

std::unique_ptr<diff::SyntaxTree> getASTSyntaxTree(
    const std::string &filepath,
    const std::unique_ptr<CompilationDatabase> &defaultCompilation
);

#endif