command in use 

clang++ -g -O3 makeModule.cc `llvm-config --cxxflags --ldflags --system-libs --libs core` 