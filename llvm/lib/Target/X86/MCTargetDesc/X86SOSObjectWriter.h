//
// Created by sbw on 1/16/22.
//

#ifndef LLVM_X86SOSOBJECTWRITER_H
#define LLVM_X86SOSOBJECTWRITER_H

#include "llvm/MC/MCObjectWriter.h"
namespace {

class X86SOSObjectWriter : public llvm::MCObjectTargetWriter {
public:
  X86SOSObjectWriter();
  virtual ~X86SOSObjectWriter() = default;

  llvm::Triple::ObjectFormatType getFormat() const override;
};

} // namespace

#endif // LLVM_X86SOSOBJECTWRITER_H
