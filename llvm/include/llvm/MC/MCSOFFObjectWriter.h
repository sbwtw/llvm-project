//
// Created by sbw on 1/16/22.
//

#ifndef LLVM_MCSOFFOBJECTWRITER_H
#define LLVM_MCSOFFOBJECTWRITER_H

#include "llvm/MC/MCObjectWriter.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/EndianStream.h"

namespace llvm {

class MCSOFFObjectWriter : public MCObjectWriter {
public:
  MCSOFFObjectWriter(raw_pwrite_stream &OS);

  void executePostLayoutBinding(MCAssembler &Asm,
                                        const MCAsmLayout &Layout) override;
  void recordRelocation(MCAssembler &Asm, const MCAsmLayout &Layout,
                                const MCFragment *Fragment,
                                const MCFixup &Fixup, MCValue Target,
                                uint64_t &FixedValue) override;
  uint64_t writeObject(MCAssembler &Asm, const MCAsmLayout &Layout) override;

private:
  support::endian::Writer W;
};

std::unique_ptr<MCObjectWriter> createSOFFObjectWriter(raw_pwrite_stream &OS);
} // namespace llvm

#endif // LLVM_MCSOFFOBJECTWRITER_H
