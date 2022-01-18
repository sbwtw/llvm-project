//
// Created by sbw on 1/16/22.
//

#include "llvm/MC/MCSOFFObjectWriter.h"
#include "llvm/MC/MCAssembler.h"
#include "llvm/MC/MCValue.h"

using namespace llvm;

class SOFFObjectWriter : public llvm::MCObjectWriter {
private:
  support::endian::Writer W;
  std::unique_ptr<MCSOFFObjectTargetWriter> TargetObjectWriter;

public:
  SOFFObjectWriter(std::unique_ptr<MCSOFFObjectTargetWriter> MOTW,
                   raw_pwrite_stream &OS);

  void executePostLayoutBinding(llvm::MCAssembler &Asm,
                                const llvm::MCAsmLayout &Layout) override;
  void recordRelocation(llvm::MCAssembler &Asm, const llvm::MCAsmLayout &Layout,
                        const llvm::MCFragment *Fragment,
                        const llvm::MCFixup &Fixup, llvm::MCValue Target,
                        uint64_t &FixedValue) override;
  uint64_t writeObject(llvm::MCAssembler &Asm,
                       const llvm::MCAsmLayout &Layout) override;
};

SOFFObjectWriter::SOFFObjectWriter(std::unique_ptr<MCSOFFObjectTargetWriter> MOTW, raw_pwrite_stream &OS)
    : W(OS, support::little), TargetObjectWriter(std::move(MOTW))
{

}

void SOFFObjectWriter::executePostLayoutBinding(MCAssembler &Asm,
                                                const MCAsmLayout &Layout)
{

}

void SOFFObjectWriter::recordRelocation(MCAssembler &Asm,
                                        const MCAsmLayout &Layout,
                                        const MCFragment *Fragment,
                                        const MCFixup &Fixup, MCValue Target,
                                        uint64_t &FixedValue)
{

}

uint64_t SOFFObjectWriter::writeObject(MCAssembler &Asm,
                                       const MCAsmLayout &Layout)
{
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
