command to get this codes running

1. 
clang++ -g -O3 emitSimpleArithInBBlock.cc `llvm-config --cxxflags --ldflags --system-libs --libs core` -o emitSimpleArithInBBlock.out

@dated 13.03.2019
note the code in this folder has not been executed 
and showing segmentation falut (core dumped )

@dated 01.04.2019
case closed
- the problem had been showing up with the values that were being passed on to the 
- system for coding the multiplier engine 