//
// Created by sbw on 1/16/22.
//

#ifndef LLVM_MCSOFFSTREAMER_H
#define LLVM_MCSOFFSTREAMER_H

#include "llvm/MC/MCStreamer.h"

namespace llvm {
class MCSOFFStreamer : public MCStreamer
{
public:
  MCSOFFStreamer(MCContext &Ctx);
  bool emitSymbolAttribute(MCSymbol *Symbol,
                                 MCSymbolAttr Attribute) override;
  void emitCommonSymbol(MCSymbol *Symbol, uint64_t Size,
                                unsigned ByteAlignment) override;
  void emitZerofill(MCSection *Section, MCSymbol *Symbol = nullptr,
                        uint64_t Size = 0, unsigned ByteAlignment = 0,
                        SMLoc Loc = SMLoc()) override;
};
} // namespace llvm

#endif // LLVM_MCSOFFSTREAMER_H
