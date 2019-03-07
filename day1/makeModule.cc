#include "llvm/IR/Module.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/Support/raw_os_ostream.h"
using namespace llvm;

int main(int argc, char const *argv[])
{
    static LLVMContext TheContext;
    static std::unique_ptr<Module> TheModule;
    TheModule = llvm::make_unique<Module>("my cool jit", TheContext);
    TheModule->print(errs(), nullptr);
    return 0;
}
