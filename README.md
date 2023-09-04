# Problem Reproduction of libTooling

This is problem reproduction repository for a question posted [stackoverflow]().

The problem is segmentation fault is occured inside of libTooling binary, `clang::dif::SyntaxTree::Impl::getDeclValue`, and it may be from object calling virtual method has NULL vtable pointer.

## How to build and run

### Prerequisite

build LLVM and Clang from source tagged `llvmorg-16.0.6` and install it. Please follow [this instruction](https://clang.llvm.org/get_started.html).

### Build and Run this repo 

First, run cmake.
`<cmake dir path>` is `/usr/local/lib/cmake`, for example. its directory has `clang/ClangConfig.cmake` and `llvm/LLVMConfig.cmake`. 

```
CXX=<installed clang path> cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_PREFIX_PATH=<cmake dir path>
```

And, build by make in build dir.

```
cd build
make
```

run gdb.

```
cd <repository root>
gdb build/src/DiffBinOpsExtractor/diff-binops

(gdb) run ./example/a.c ./example/b.c
```

This will make same segmentation fault I said above.

