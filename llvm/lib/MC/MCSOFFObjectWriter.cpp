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
  llvm::outs() << "SOFFObjectWriter::recordRelocation" << " " << Fixup.getOffset() << '\n';
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
      if (!F.hasInstructions())
        continue;

      llvm::outs() << "WriteObject Fragment " << '\n';
      if (const auto *DF = dyn_cast<MCDataFragment>(&F)) {
        for (auto C : DF->getContents())
        {
          llvm::outs() << format_hex((unsigned char)C, 4) << ' ';
        }
        llvm::outs() << '\n';
      }
    }
  }

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
