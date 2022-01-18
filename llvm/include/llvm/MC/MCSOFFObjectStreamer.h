//
// Created by sbw on 1/16/22.
//

#ifndef LLVM_MCSOFFOBJECTSTREAMER_H
#define LLVM_MCSOFFOBJECTSTREAMER_H

#include "llvm/MC/MCObjectStreamer.h"

namespace llvm {
class MCSOFFObjectStreamer : public MCObjectStreamer
{
public:
  MCSOFFObjectStreamer(MCContext &Context, std::unique_ptr<MCAsmBackend> TAB,
      std::unique_ptr<MCObjectWriter> OW,  std::unique_ptr<MCCodeEmitter> Emitter);
  bool emitSymbolAttribute(MCSymbol *Symbol,
                                 MCSymbolAttr Attribute) override;
  void emitCommonSymbol(MCSymbol *Symbol, uint64_t Size,
                                unsigned ByteAlignment) override;
  void emitZerofill(MCSection *Section, MCSymbol *Symbol = nullptr,
                        uint64_t Size = 0, unsigned ByteAlignment = 0,
                        SMLoc Loc = SMLoc()) override;
  void emitInstToData(const MCInst &Inst, const MCSubtargetInfo&) override;
};
} // namespace llvm

#endif // LLVM_MCSOFFOBJECTSTREAMER_H
