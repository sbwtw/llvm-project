//
// Created by sbw on 1/16/22.
//

#include "llvm/MC/MCSOFFStreamer.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSection.h"

using namespace llvm;

MCSOFFStreamer::MCSOFFStreamer(MCContext &Ctx)
  : MCStreamer(Ctx)
{

}

bool MCSOFFStreamer::emitSymbolAttribute(MCSymbol *Symbol,
                                         MCSymbolAttr Attribute)
{
  return false;
}

void MCSOFFStreamer::emitCommonSymbol(MCSymbol *Symbol, uint64_t Size,
                                      unsigned int ByteAlignment)
{
  llvm::outs() << "MCSOFFStreamer::emitCommonSymbol" << Symbol->getName() << "\n";
}

void MCSOFFStreamer::emitZerofill(MCSection *Section, MCSymbol *Symbol,
                                  uint64_t Size, unsigned int ByteAlignment,
                                  SMLoc Loc)
{
  llvm::outs() << "MCSOFFStreamer::emitZerofill" << Section->getName() << ", " << Symbol->getName() << "\n";
}

namespace llvm {
MCStreamer *createSOFFStreamer(MCContext &Ctx,
                               std::unique_ptr<MCAsmBackend> &&TAB,
                               std::unique_ptr<MCObjectWriter> &&OW,
                               std::unique_ptr<MCCodeEmitter> &&CE)
{
  return new MCSOFFStreamer(Ctx);
}
} // namespace llvm
