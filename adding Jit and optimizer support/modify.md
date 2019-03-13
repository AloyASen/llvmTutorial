command to test the changes out 

clang++ -g toy.cpp `llvm-config --cxxflags --ldflags --system-libs --libs core mcjit native` -O3 -o toy

after the llvm Ir is generated, this middleware can be relinked to form either a imterpretor with JIT abilites or a static installable compiler of its own (test code in another folder with appropriate naming conventions, will be tested out later some day)