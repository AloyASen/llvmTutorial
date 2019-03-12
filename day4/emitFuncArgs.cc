

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
    static std::vector<std::string> FunArgs;

//define te function that is to be created
Function *createFunc(IRBuilder<> &Builder, std::string Name){
    //add arguments to the function
    std::vector<Type *> Integers(FunArgs.size(), Type::getInt32Ty(TheContext));

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
//globals have a visibility of all functions within a module dependingon
// linkage types, alignment props and so on
GlobalVariable *createGlobal(IRBuilder<> &Builder, std::string Name){
    TheModule->getOrInsertGlobal(Name, Builder.getInt32Ty());
    GlobalVariable *gVar = TheModule->getNamedGlobal(Name);
    gVar->setLinkage(GlobalValue::CommonLinkage);
    gVar->setAlignment(4);
    return gVar;
}

//set the function agruments to the new function created
void setFuncArgs(Function *fooFunc, std::vector<std::string> FunArgs){
    unsigned Idx = 0;
    Function::arg_iterator AI, AE;
    for(AI=fooFunc->arg_begin(), AE = fooFunc->arg_end() ; AI != AE ; ++AI, ++Idx)
    {
        AI->setName(FunArgs[Idx]);
    }
    
}
// here the code begins execution
int main(int argc, char const *argv[])
{
   //make a function within this running module scope
    static IRBuilder<> Builder(TheContext);
    Function *foofunc = createFunc(Builder,"foo");

    //make a global variable and link it to the module head
    GlobalVariable *gVar = createGlobal(Builder, "x");

    //make  a basic block and set its entrypount
    BasicBlock *entry = createBB(foofunc, "entry");
    Builder.SetInsertPoint(entry);
    
    // create return statement for the function
    Builder.CreateRet(Builder.getInt32(0));
    
    // verify whether the function is valid
    verifyFunction(*foofunc);
    TheModule->print(errs(), nullptr);
    return 0;
}
