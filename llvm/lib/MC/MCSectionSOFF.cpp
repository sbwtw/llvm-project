//
// Created by sbw on 1/16/22.
//

#include "llvm/MC/MCSectionSOFF.h"

using namespace llvm;

MCSectionSOFF::MCSectionSOFF(StringRef Name, SectionKind K, MCSymbol *Begin)
    : MCSection(SV_SOFF, Name, K, Begin)
{
}

void MCSectionSOFF::PrintSwitchToSection(
    const MCAsmInfo &MAI, const Triple &T, raw_ostream &OS,
    const MCExpr *Subsection) const
{
}

bool MCSectionSOFF::UseCodeAlign() const { return false; }

bool MCSectionSOFF::isVirtualSection() const { return false; }
