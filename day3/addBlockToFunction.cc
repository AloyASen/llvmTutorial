#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_os_ostream.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/Verifier.h"
using namespace llvm;
//global copy of the module for this code insstance
    static LLVMContext TheContext;
    static Module *TheModule= new Module("my cool jit", TheContext);
    //TheModule = llvm::make_unique<Module>("my cool jit", TheContext);

//define te function that is to be created
Function *createFunc(IRBuilder<> &Builder, std::string Name){
    FunctionType *funcType = llvm::FunctionType::get(Builder.getInt32Ty(),false);
    Function *fooFunc = llvm::Function::Create(
        funcType, llvm::Function::ExternalLinkage, Name, TheModule
    );
    return fooFunc;
}
//the basic block named entry added to the function foo
BasicBlock *createBB(Function *fooFunc, std::string Name){
    return BasicBlock::Create(TheContext, Name, fooFunc);
}
int main(int argc, char const *argv[])
{
   //make a function within this running module scope
    static IRBuilder<> Builder(TheContext);
    Function *foofunc = createFunc(Builder,"foo");

    //make  a basic block and set its entrypount
    BasicBlock *entry = createBB(foofunc, "entry");
    Builder.SetInsertPoint(entry);
    // verify whether the function is valid
    verifyFunction(*foofunc);
    TheModule->print(errs(), nullptr);
    return 0;
}
