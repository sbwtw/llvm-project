//
// Created by sbw on 1/16/22.
//

#include "llvm/MC/MCSOFFObjectWriter.h"
#include "llvm/MC/MCValue.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCCodeEmitter.h"

using namespace llvm;

MCSOFFObjectWriter::MCSOFFObjectWriter(raw_pwrite_stream &OS)
    : W(OS, support::little)
{

}

void MCSOFFObjectWriter::executePostLayoutBinding(MCAssembler &Asm,
                                                  const MCAsmLayout &Layout)
{

}
void MCSOFFObjectWriter::recordRelocation(MCAssembler &Asm,
                                          const MCAsmLayout &Layout,
                                          const MCFragment *Fragment,
                                          const MCFixup &Fixup, MCValue Target,
                                          uint64_t &FixedValue)
{

}

uint64_t MCSOFFObjectWriter::writeObject(MCAssembler &Asm,
                                         const MCAsmLayout &Layout)
{
  auto StartOffset = W.OS.tell();

  for (auto &Section : Asm)
  {
    llvm::outs() << Section.getName() << '\n';
  }

  return 4;
}

std::unique_ptr<MCObjectWriter>
llvm::createSOFFObjectWriter(raw_pwrite_stream &OS) {
  return std::make_unique<MCSOFFObjectWriter>(OS);
}
