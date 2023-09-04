#include "clang/Tooling/CompilationDatabase.h"
#include "clang/Tooling/ASTDiff/ASTDiff.h"
#include "clang/Tooling/Tooling.h"

using namespace clang;
using namespace clang::tooling;

static std::unique_ptr<ASTUnit>
getAST(
    const std::unique_ptr<CompilationDatabase> &compilation,
    const std::string &filename
) {
    std::array<std::string, 1> files = {{filename}};
    ClangTool tool(*compilation, files);
    std::vector<std::unique_ptr<ASTUnit>> ASTs;
    tool.buildASTs(ASTs);
    if(ASTs.size() != files.size()) {
        return nullptr;
    }

    return std::move(ASTs[0]);
}

std::unique_ptr<diff::SyntaxTree> getASTSyntaxTree(
    const std::string &filepath,
    const std::unique_ptr<CompilationDatabase> &defaultCompilation
) { 
    std::unique_ptr<ASTUnit> ast = getAST(defaultCompilation, filepath);
    std::unique_ptr<diff::SyntaxTree> syntaxTree = std::make_unique<diff::SyntaxTree>(ast->getASTContext());

    return syntaxTree;
}