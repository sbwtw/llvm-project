//
// Created by sbw on 1/16/22.
//

#include "X86SOSObjectWriter.h"
#include "X86MCTargetDesc.h"

using namespace llvm;

X86SOSObjectWriter::X86SOSObjectWriter()
    : MCObjectTargetWriter()
{

}

Triple::ObjectFormatType X86SOSObjectWriter::getFormat() const {
  return Triple::SOFF;
}

std::unique_ptr<MCObjectTargetWriter> llvm::createX86SOSObjectWriter() {
  return std::make_unique<X86SOSObjectWriter>();
}
