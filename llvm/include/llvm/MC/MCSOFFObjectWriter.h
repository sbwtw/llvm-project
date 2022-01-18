//
// Created by sbw on 1/16/22.
//

#ifndef LLVM_MCSOFFOBJECTWRITER_H
#define LLVM_MCSOFFOBJECTWRITER_H

#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCAsmLayout.h"
#include "llvm/Support/Endian.h"
#include "llvm/Support/EndianStream.h"

namespace llvm {

class MCSOFFObjectTargetWriter : public MCObjectTargetWriter {
public:
  MCSOFFObjectTargetWriter();

  static bool classof(const MCObjectTargetWriter *W) {
    return W->getFormat() == Triple::SOFF;
  }
};

std::unique_ptr<MCObjectWriter>
createSOFFObjectWriter(std::unique_ptr<MCSOFFObjectTargetWriter> MOTW,
                       raw_pwrite_stream &OS);
} // namespace llvm

#endif // LLVM_MCSOFFOBJECTWRITER_H
