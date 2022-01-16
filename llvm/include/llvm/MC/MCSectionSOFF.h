//
// Created by sbw on 1/16/22.
//

#ifndef LLVM_MCSECTIONSOFF_H
#define LLVM_MCSECTIONSOFF_H

#include "llvm/MC/MCSection.h"

namespace llvm {
class MCSectionSOFF final : public MCSection
{
public:
  MCSectionSOFF(StringRef Name, SectionKind K, MCSymbol *Begin);
  void PrintSwitchToSection(const MCAsmInfo &MAI, const Triple &T,
                                    raw_ostream &OS,
                                    const MCExpr *Subsection) const override;
  bool UseCodeAlign() const override;
  bool isVirtualSection() const override;
};
} // namespace llvm


#endif // LLVM_MCSECTIONSOFF_H
