//
// Created by sbw on 1/16/22.
//

#ifndef LLVM_MCSYMBOLSOFF_H
#define LLVM_MCSYMBOLSOFF_H

#include "llvm/MC/MCSymbol.h"

namespace llvm {

class MCSymbolSOFF : public MCSymbol {
public:
  MCSymbolSOFF(const StringMapEntry<bool> *Name, bool IsTemporary)
      : MCSymbol(SymbolKindGOFF, Name, IsTemporary) {}
  static bool classof(const MCSymbol *S) { return S->isSOFF(); }
};
} // end namespace llvm

#endif // LLVM_MCSYMBOLSOFF_H
