#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Verifier.h"
#include <vector>
using namespace llvm;
// the updated llvm context -- different from the oriely book
static LLVMContext Context;
static Module *ModuleOb = new Module("my compiler", Context);
static std::vector<std::string> FunArgs;

Function *createFunc(IRBuilder<> &Builder, std::string Name) {
  Type *u32Ty = Type::getInt32Ty(Context);
  Type *vecTy = VectorType::get(u32Ty, 2);
  Type *ptrTy = vecTy->getPointerTo(0);
  FunctionType *funcType =
      FunctionType::get(Builder.getInt32Ty(), ptrTy, false);
  Function *fooFunc =
      Function::Create(funcType, Function::ExternalLinkage, Name, ModuleOb);
  return fooFunc;
}

void setFuncArgs(Function *fooFunc, std::vector<std::string> FunArgs) {
  unsigned Idx = 0;
  Function::arg_iterator AI, AE;
  for (AI = fooFunc->arg_begin(), AE = fooFunc->arg_end(); AI != AE;
       ++AI, ++Idx)
    AI->setName(FunArgs[Idx]);
}

BasicBlock *createBB(Function *fooFunc, std::string Name) {
  return BasicBlock::Create(Context, Name, fooFunc);
}

Value *getGEP(IRBuilder<> &Builder, Value *Base, Value *Offset) {
  return Builder.CreateGEP(Builder.getInt32Ty(), Base, Offset, "a1");
}

int main(int argc, char *argv[]) {
  FunArgs.push_back("a");
  static IRBuilder<> Builder(Context);
  Function *fooFunc = createFunc(Builder, "foo");
  setFuncArgs(fooFunc, FunArgs);
  Value *Base = fooFunc->arg_begin();
  BasicBlock *entry = createBB(fooFunc, "entry");
  Builder.SetInsertPoint(entry);
  Value *gep = getGEP(Builder, Base, Builder.getInt32(1));
  Builder.CreateRet(Builder.getInt32(0));
  verifyFunction(*fooFunc);
// the upgraded module system
  ModuleOb->print(errs(), nullptr);
  return 0;
}
