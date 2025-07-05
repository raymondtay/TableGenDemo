
#include "llvm/TableGen/Record.h"
#include "llvm/TableGen/Parser.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/MemoryBuffer.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/FileSystem.h"

using namespace llvm;

static cl::opt<std::string>
    InputFilename(cl::Positional, cl::desc("<input .td file>"), cl::Required);

static cl::opt<std::string>
    OutputFilename("o", cl::desc("Output filename"), cl::value_desc("filename"),
                   cl::init("-"));

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "My standalone TableGen backend\\n");

  // Load file
  auto FileOrErr = MemoryBuffer::getFile(InputFilename);
  if (!FileOrErr) {
    errs() << "Cannot open file: " << InputFilename << "\n";
    return 1;
  }

  SourceMgr SM;
  RecordKeeper Records;

    // Register the buffer with SourceMgr yourself!
  SM.AddNewSourceBuffer(std::move(*FileOrErr), SMLoc());

  if (TableGenParseFile(SM, Records)) {
    errs() << "TableGen parse failed\\n";
    return 1;
  }

  std::error_code EC;
  raw_fd_ostream OS(OutputFilename, EC, sys::fs::OF_Text);
  if (EC) {
    errs() << "Cannot open output: " << EC.message() << "\n";
    return 1;
  }

  // Generate output
  OS << "//=== Auto-generated ===//\n\n";

  auto Regs = Records.getAllDerivedDefinitions("Register");
  OS << "// Registers\n";
  for (const auto *Reg : Regs) {
    OS << "#define REG_" << Reg->getName() << " "
       << Reg->getValueAsInt("ID") << "\n";
  }
  OS << "\n";

  auto Instrs = Records.getAllDerivedDefinitions("Instruction");
  OS << "// Instructions\n";
  for (const auto *Instr : Instrs) {
    OS << "#define OPCODE_" << Instr->getName() << " "
       << Instr->getValueAsInt("Opcode") << "\n";
    auto Ops = Instr->getValueAsListOfDefs("Operands");
    OS << "#define OPERANDS_" << Instr->getName() << " \"";
    for (size_t i = 0; i < Ops.size(); ++i) {
      OS << "REG_" << Ops[i]->getName();
      if (i + 1 < Ops.size()) OS << ", ";
    }
    OS << "\"\n";
  }

  return 0;
}


