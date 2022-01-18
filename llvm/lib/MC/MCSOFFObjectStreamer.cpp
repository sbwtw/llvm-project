//
// Created by sbw on 1/16/22.
//

#include "llvm/MC/MCSOFFObjectStreamer.h"
#include "llvm/MC/MCObjectWriter.h"
#include "llvm/MC/MCSection.h"
#include "llvm/MC/MCAsmBackend.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/Support/Format.h"

using namespace llvm;

MCSOFFObjectStreamer::MCSOFFObjectStreamer(MCContext &Context,
                               std::unique_ptr<MCAsmBackend> TAB,
                               std::unique_ptr<MCObjectWriter> OW,
                               std::unique_ptr<MCCodeEmitter> Emitter)
    : MCObjectStreamer(Context, std::move(TAB), std::move(OW), std::move(Emitter))
{

}

bool MCSOFFObjectStreamer::emitSymbolAttribute(MCSymbol *Symbol,
                                         MCSymbolAttr Attribute)
{
  return false;
}

void MCSOFFObjectStreamer::emitCommonSymbol(MCSymbol *Symbol, uint64_t Size,
                                      unsigned int ByteAlignment)
{
  llvm::outs() << "MCSOFFObjectStreamer::emitCommonSymbol" << Symbol->getName() << "\n";
}

void MCSOFFObjectStreamer::emitZerofill(MCSection *Section, MCSymbol *Symbol,
                                  uint64_t Size, unsigned int ByteAlignment,
                                  SMLoc Loc)
{
  llvm::outs() << "MCSOFFObjectStreamer::emitZerofill" << Section->getName() << ", " << Symbol->getName() << "\n";
}

void MCSOFFObjectStreamer::emitInstToData(const MCInst &Inst,
                                    const MCSubtargetInfo &STI)
{
    MCDataFragment *DF = getOrCreateDataFragment();

    SmallVector<MCFixup, 4> Fixups;
    SmallString<256> Code;
    raw_svector_ostream VecOS(Code);
    getAssembler().getEmitter().encodeInstruction(Inst, VecOS, Fixups, STI);

    // Add the fixups and data.
    for (auto F : Fixups) {
      F.setOffset(F.getOffset() + DF->getContents().size());
      DF->getFixups().push_back(F);
    }
    DF->setHasInstructions(STI);
    DF->getContents().append(Code.begin(), Code.end());

//    MCAssembler &Assembler = getAssembler();
//    SmallVector<MCFixup, 4> Fixups;
//    SmallString<256> Code;
//    raw_svector_ostream VecOS(Code);
//    Assembler.getEmitter().encodeInstruction(Inst, VecOS, Fixups, STI);
//
//    for (auto C : Code)
//    {
//      llvm::outs() << format_hex((unsigned char)C, 4) << ' ';
//    }
//
//    if (!Fixups.empty())
//    {
//      for (auto F : Fixups)
//        llvm::outs() << '(' << F.getTargetKind() << ", " << F.getOffset() << ") ";
//    }
//
//    llvm::outs() << '\n';

//    llvm::outs() << "MCSOFFObjectStreamer::emitInstruction" << "\n";
//    Inst.dump();
}

namespace llvm {
MCStreamer *createSOFFObjectStreamer(MCContext &Ctx,
                               std::unique_ptr<MCAsmBackend> &&TAB,
                               std::unique_ptr<MCObjectWriter> &&OW,
                               std::unique_ptr<MCCodeEmitter> &&CE)
{
  return new MCSOFFObjectStreamer(Ctx, std::move(TAB), std::move(OW), std::move(CE));
}
} // namespace llvm
