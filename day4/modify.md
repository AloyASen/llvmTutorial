command:
1. clang++ -g -O3 emitGlobalVar.cc `llvm-config --cxxflags --ldflags --
system-libs --libs core` -o emitGlobalVar.out

2. clang++ -g -O3 emitRetunStatement.cc `llvm-config --cxxflags --ldflags --system-libs --libs core` -o emitRetunStatement

3. clang++ -g -O3 emitFuncArgs.cc `llvm-config --cxxflags --ldflags --s
ystem-libs --libs core` -o emitFuncArgs.out

- continuation from day 3 
- more intrinsic codes in day 5