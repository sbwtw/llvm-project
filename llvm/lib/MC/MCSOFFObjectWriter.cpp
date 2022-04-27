//
// Created by sbw on 1/16/22.
//

#include "llvm/MC/MCSOFFObjectWriter.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCValue.h"
#include "llvm/MC/MCSection.h"
#include "llvm/MC/MCFragment.h"

using namespace llvm;

class SOFFObjectWriter : public MCObjectWriter {
private:
  support::endian::Writer W;
  std::unique_ptr<MCSOFFObjectTargetWriter> TargetObjectWriter;

public:
  SOFFObjectWriter(std::unique_ptr<MCSOFFObjectTargetWriter> MOTW,
                   raw_pwrite_stream &OS);

  void executePostLayoutBinding(MCAssembler &Asm,
                                const MCAsmLayout &Layout) override;
  void recordRelocation(MCAssembler &Asm, const MCAsmLayout &Layout,
                        const MCFragment *Fragment,
                        const MCFixup &Fixup, MCValue Target,
                        uint64_t &FixedValue) override;
  uint64_t writeObject(MCAssembler &Asm,
                       const MCAsmLayout &Layout) override;
};

SOFFObjectWriter::SOFFObjectWriter(std::unique_ptr<MCSOFFObjectTargetWriter> MOTW, raw_pwrite_stream &OS)
    : W(OS, support::little), TargetObjectWriter(std::move(MOTW))
{

}

void SOFFObjectWriter::executePostLayoutBinding(MCAssembler &Asm,
                                                const MCAsmLayout &Layout)
{
  llvm::outs() << "SOFFObjectWriter::executePostLayoutBinding\n";
}

void SOFFObjectWriter::recordRelocation(MCAssembler &Asm,
                                        const MCAsmLayout &Layout,
                                        const MCFragment *Fragment,
                                        const MCFixup &Fixup, MCValue Target,
                                        uint64_t &FixedValue)
{
  uint64_t FragOffset = Layout.getFragmentOffset(Fragment);
  uint64_t FixupOffset = FragOffset + Fixup.getOffset();

  llvm::outs() << "SOFFObjectWriter::recordRelocation"
               << " Total Offset = " << FixupOffset
               << " Frag Offset = " << FragOffset
               << " Offset = " << Fixup.getOffset()
               << " Kind = " << Fixup.getKind()
               << " Loc = " << Fixup.getLoc().getPointer() << '\n';
}

uint64_t SOFFObjectWriter::writeObject(MCAssembler &Asm,
                                       const MCAsmLayout &Layout)
{
  llvm::outs() << "SOFFObjectWriter::writeObject\n";

  for (MCSection &Sec : Asm)
  {
    if (!Sec.hasInstructions())
      continue;

    llvm::outs() << "WriteObject Section " << Sec.getName() << '\n';
    for (auto &F : Sec)
    {
//      if (!F.hasInstructions())
//      {
//        llvm::outs() << "Segment " << int(F.getKind()) << " does not have instructions" << '\n';
//        continue;
//      }

      if (auto *Align = dyn_cast<MCAlignFragment>(&F)) {
        llvm::outs() << "Alignment: " << Align->getAlignment() << '\n';
        llvm::outs() << "Value: " << Align->getValue() << '\n';
        llvm::outs() << "ValueSize: " << Align->getValueSize() << '\n';
        llvm::outs() << "hasEmitNops: " << Align->hasEmitNops() << '\n';
      }

      llvm::outs() << "WriteObject Fragment" << '\n';
      if (const auto *DF = dyn_cast<MCDataFragment>(&F)) {
        int Cnt = 0;
        for (auto C : DF->getContents())
        {
          llvm::outs() << format_hex((unsigned char)C, 4) << ' ';
          W.OS.write(C);

          if (Cnt++ % 5 == 4)
            llvm::outs() << '\n';
        }

        llvm::outs() << '\n';
      }
    }
  }

  llvm::outs() << "Write Finished!!!" << '\n';

  return 0;
}

MCSOFFObjectTargetWriter::MCSOFFObjectTargetWriter()
  : MCObjectTargetWriter()
{

}

namespace llvm {

std::unique_ptr<MCObjectWriter>
createSOFFObjectWriter(std::unique_ptr<MCSOFFObjectTargetWriter> MOTW,
                       raw_pwrite_stream &OS) {
  return std::make_unique<SOFFObjectWriter>(std::move(MOTW), OS);
}

} // namespace llvm
