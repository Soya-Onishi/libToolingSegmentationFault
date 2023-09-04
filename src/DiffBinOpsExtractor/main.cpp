// [ ] ASTのDiffのうち、BinaryOperatorのDiffを抽出する
// [ ] 抽出したASTとその子ノードに対応するコードを表示する

#include <iostream>
#include "clang/Tooling/Tooling.h"
#include "clang/Tooling/CompilationDatabase.h"
#include "clang/Tooling/ASTDiff/ASTDiff.h"
#include "ASTSyntaxTree/ASTSyntaxTree.h"
#include "clang/AST/Expr.h"

using namespace clang;
using namespace clang::tooling;

static void printNode(
    const std::unique_ptr<diff::SyntaxTree> &tree,
    const diff::NodeId& nodeID
) {
    std::cout << tree->getNode(nodeID).getTypeLabel().str();
    std::string value = tree->getNodeValue(nodeID);
    if(!value.empty()) {
        std::cout << ": " << value; 
    }
    std::cout << "(" << nodeID << ")";

    return;
}

static bool isBinOpNode(const diff::Node &node) {
    return node.getType().isSame(ASTNodeKind::getFromNodeKind<BinaryOperator>());
}

static std::unique_ptr<std::vector<diff::NodeId>> explorerBinaryOperator(
    const std::unique_ptr<diff::SyntaxTree> &dstTree,
    const diff::NodeId &dstID
) {
    auto nodes = std::make_unique<std::vector<diff::NodeId>>();
    const diff::Node &dstNode = dstTree->getNode(dstID);

    if(isBinOpNode(dstNode)) {
        nodes->push_back(diff::NodeId(dstID));
    }

    for(const diff::NodeId& childID : dstNode.Children) {
        auto childBinOps = explorerBinaryOperator(dstTree, dstID); 
        std::copy(childBinOps->begin(), childBinOps->end(), std::back_inserter(*nodes));
    }

    return nodes;
}

int main(int argc, char** argv) {
    if(argc < 3) {
        std::cerr << "error" << std::endl;
        return 1;
    }

    std::unique_ptr<CompilationDatabase> compilation = std::make_unique<FixedCompilationDatabase>(".", std::vector<std::string>());
    std::string srcFile(argv[1]);
    std::string dstFile(argv[2]);

    std::unique_ptr<diff::SyntaxTree> srcTree = getASTSyntaxTree(srcFile, compilation);
    std::unique_ptr<diff::SyntaxTree> dstTree = getASTSyntaxTree(dstFile, compilation);
    diff::ComparisonOptions options;
    diff::ASTDiff astDiff(*srcTree, *dstTree, options);

    auto binOpsNodeIDs = std::make_unique<std::vector<diff::NodeId>>();
    for(diff::NodeId dstID : *dstTree) {
        if(dstID.isInvalid()) {
            continue;
        }
        
        auto nodes = explorerBinaryOperator(dstTree, dstID);
        std::copy(nodes->begin(), nodes->end(), std::back_inserter(*binOpsNodeIDs));
    }

    for(const diff::NodeId& nodeID : *binOpsNodeIDs) {
        printNode(dstTree, nodeID);
    }
}