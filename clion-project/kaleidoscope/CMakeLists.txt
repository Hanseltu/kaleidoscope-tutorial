cmake_minimum_required(VERSION 3.13)
project(kaleidoscope)

set(CMAKE_CXX_STANDARD 14)

#llvm-config --cxxflags
add_compile_options(-I/Users/tuhaoxin/LLVM/llvm/include -I/Users/tuhaoxin/LLVM/build/include -std=c++11
        -fno-exceptions -fno-rtti -D__STDC_CONSTANT_MACROS -D__STDC_FORMAT_MACROS -D__STDC_LIMIT_MACROS)

#llvm-config --ldflags
LINK_LIBRARIES(-L/Users/tuhaoxin/LLVM/build/lib -Wl,-search_paths_first -Wl,-headerpad_max_install_names)

#llvm-config --system-libs
LINK_LIBRARIES(-lz -lcurses -lm -lxml2)

#llvm-config --libs
LINK_LIBRARIES(-lLLVMSymbolize -lLLVMDebugInfoPDB -lLLVMCoverage -lLLVMDlltoolDriver -lLLVMOrcJIT -lLLVMTestingSupport
        -lLLVMMCA -lLLVMWindowsManifest -lLLVMTextAPI -lLLVMFuzzMutate -lLLVMMCJIT -lLLVMCoroutines -lLLVMRemarks -lLLVMLTO
        -lLLVMPasses -lLLVMObjCARCOpts -lLLVMTableGen -lLLVMXRay -lLLVMXCoreDisassembler -lLLVMXCoreCodeGen -lLLVMXCoreDesc
        -lLLVMXCoreInfo -lLLVMXCoreAsmPrinter -lLLVMX86Disassembler -lLLVMX86AsmParser -lLLVMX86CodeGen -lLLVMX86Desc -lLLVMX86Info
        -lLLVMX86AsmPrinter -lLLVMX86Utils -lLLVMWebAssemblyDisassembler -lLLVMWebAssemblyCodeGen -lLLVMWebAssemblyDesc
        -lLLVMWebAssemblyAsmPrinter -lLLVMWebAssemblyAsmParser -lLLVMWebAssemblyInfo -lLLVMSystemZDisassembler -lLLVMSystemZCodeGen
        -lLLVMSystemZAsmParser -lLLVMSystemZDesc -lLLVMSystemZInfo -lLLVMSystemZAsmPrinter -lLLVMSparcDisassembler -lLLVMSparcCodeGen
        -lLLVMSparcAsmParser -lLLVMSparcDesc -lLLVMSparcInfo -lLLVMSparcAsmPrinter -lLLVMPowerPCDisassembler -lLLVMPowerPCCodeGen
        -lLLVMPowerPCAsmParser -lLLVMPowerPCDesc -lLLVMPowerPCInfo -lLLVMPowerPCAsmPrinter -lLLVMNVPTXCodeGen -lLLVMNVPTXDesc -lLLVMNVPTXInfo
        -lLLVMNVPTXAsmPrinter -lLLVMMSP430Disassembler -lLLVMMSP430CodeGen -lLLVMMSP430AsmParser -lLLVMMSP430Desc -lLLVMMSP430Info -lLLVMMSP430AsmPrinter
        -lLLVMMipsDisassembler -lLLVMMipsCodeGen -lLLVMMipsAsmParser -lLLVMMipsDesc -lLLVMMipsInfo -lLLVMMipsAsmPrinter -lLLVMLanaiDisassembler
        -lLLVMLanaiCodeGen -lLLVMLanaiAsmParser -lLLVMLanaiDesc -lLLVMLanaiAsmPrinter -lLLVMLanaiInfo -lLLVMHexagonDisassembler -lLLVMHexagonCodeGen
        -lLLVMHexagonAsmParser -lLLVMHexagonDesc -lLLVMHexagonInfo -lLLVMBPFDisassembler -lLLVMBPFCodeGen -lLLVMBPFAsmParser -lLLVMBPFDesc -lLLVMBPFInfo
        -lLLVMBPFAsmPrinter -lLLVMARMDisassembler -lLLVMARMCodeGen -lLLVMARMAsmParser -lLLVMARMDesc -lLLVMARMInfo -lLLVMARMAsmPrinter -lLLVMARMUtils
        -lLLVMAMDGPUDisassembler -lLLVMAMDGPUCodeGen -lLLVMMIRParser -lLLVMipo -lLLVMInstrumentation -lLLVMVectorize -lLLVMLinker -lLLVMIRReader
        -lLLVMAsmParser -lLLVMAMDGPUAsmParser -lLLVMAMDGPUDesc -lLLVMAMDGPUInfo -lLLVMAMDGPUAsmPrinter -lLLVMAMDGPUUtils -lLLVMAArch64Disassembler
        -lLLVMMCDisassembler -lLLVMAArch64CodeGen -lLLVMGlobalISel -lLLVMSelectionDAG -lLLVMAsmPrinter -lLLVMDebugInfoDWARF -lLLVMAArch64AsmParser
        -lLLVMAArch64Desc -lLLVMAArch64Info -lLLVMAArch64AsmPrinter -lLLVMAArch64Utils -lLLVMObjectYAML -lLLVMLibDriver -lLLVMOption -lgtest_main
        -lgtest -lLLVMLineEditor -lLLVMInterpreter -lLLVMExecutionEngine -lLLVMRuntimeDyld -lLLVMCodeGen -lLLVMTarget -lLLVMScalarOpts -lLLVMInstCombine
        -lLLVMAggressiveInstCombine -lLLVMTransformUtils -lLLVMBitWriter -lLLVMAnalysis -lLLVMProfileData -lLLVMObject -lLLVMMCParser -lLLVMMC
        -lLLVMDebugInfoCodeView -lLLVMDebugInfoMSF -lLLVMBitReader -lLLVMCore -lLLVMBinaryFormat -lLLVMSupport -lLLVMDemangle)


#set(CMAKE_CXX_FLAGS -g)


add_executable(kaleidoscope chapter2-Implementing-a-Parser-and-AST.cpp)
#add_executable(kaleidoscope chapter3-Code-generation-to-LLVM-IR.cpp)
#add_executable(kaleidoscope chapter4-Adding-JIT-and-Optimizer-Support.cpp)
#add_executable(kaleidoscope chapter5-Extending-the-Language-Control-Flow.cpp)
#add_executable(kaleidoscope chapter6-Extending-the-language-User-defined-Operators.cpp)
#add_executable(kaleidoscope chapter7-Extending-the-Language-Mutable-Variables.cpp)
#add_executable(kaleidoscope chapter8-Compiling-to-Object-Code.cpp)
#add_executable(kaleidoscope chapter9-Adding-Debug-Information.cpp)