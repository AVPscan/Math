/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include "math.h"

Cache Mat = {0};
void _FInit(anu x, anu y, an r, anu c, an a) { while(x--) { *r-- = 0; } c = (c > y) ? y : c; while(c--) *++r = *a++; }
void _FAddr(anu y, As* r, anu c, As* a) { c = (c > y) ? y : c; while(c--) *r++ = *a++; }

void FVIKARA(anu l, an r, an a) { Mat.F = 0; Mat.fa = l;
  if (Mat.lar < (Mat.fb = Mat.lar - l)) { Mat.fb = l - Mat.lar; Mat.N = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF : 0;
    if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.F |= (*--Mat.r = *--Mat.a); }
    else { while(l--) Mat.F |= (*r++ = *a++); } Mat.F = (*a || Mat.F) ? (!Mat.F && Mat.Nim && (*a == 0x80)) ? 2 : 0 : 1;
    Mat.C = (Mat.Nim) ? ((Mat.N ^ *a) & 0x80) : 0; *r = (!Mat.F && Mat.C) ? (*a ^ 0x80) : *a; while(Mat.fb-- && !(Mat.C |= (*++a ^ Mat.N))); }
  else { Mat.C = 0; l = Mat.lar;
    if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.F |= (*--Mat.r = *--Mat.a); }
    else { while(l--) Mat.F |= (*r++ = *a++); } *r = *a; Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0;
    if ((Mat.F = (*r || Mat.F) ? (!Mat.F && Mat.Nim && (*r == 0x80)) ? 2 : 0 : 1)) { Mat.dr = *r; *r = 0; }
    while(Mat.fb--) { *++r = Mat.N; } if (Mat.F) { *r = Mat.dr; } }
  Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0; Mat.C = (Mat.C != 0); Mat.lar = Mat.fa; }

void FLD(an r, anu D) { Mat.lar = 0; Mat.N = (Mat.Nim && (D & 0x80)) ? 0xFF : 0;
  Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 2 : 0 : 1; *r = D; }
void FLVD(an r, anu Dl, anu Dh) { Mat.lar = 1; *r++ = Dl; Mat.N = (Mat.Nim && (Dh & 0x80)) ? 0xFF : 0;
  Mat.F = (Dh || Dl) ? (!Dl && Mat.Nim && (Dh == 0x80)) ? 2 : 0 : 1; if (Mat.V) { if (Mat.F) { Mat.lar--; r--; }
    else if ((Dh == Mat.N && (!Mat.N && (Dl != 0x80))) || (Mat.Nim && !((Dl ^ Mat.N) & 0x80))) { Mat.lar--; return; } } *r = Dh; }

void FMOV(anu l, an r, an a) { Mat.lar = l; Mat.b = r; Mat.F = 0;
  if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.F |= (*--Mat.r = *--Mat.a); }
  else { while(l--) Mat.F |= (*r++ = *a++); } *r = *a; Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0;
  if ((Mat.F = (*r || Mat.F) ? (!Mat.F && (*r == 0x80)) ? 2 : 0 : 1)) { *Mat.b = *r; Mat.lar = 0; return; }
  if (Mat.V) {  } }

void FSWAP(anu l, an r, an a) { Mat.lar = l; Mat.b = r; Mat.r = r + l; Mat.a = a + l; Mat.fb = l & 1; Mat.da = *a++;
  Mat.F = (l) ? *Mat.a-- : 0; *r++ = Mat.F; *Mat.r-- = Mat.da; if ((l >>= 1)) {
	while(--l) { Mat.F |= (Mat.dr = *a++) | (Mat.db = *Mat.a--); *r++ = Mat.db; *Mat.r-- = Mat.dr; }
    if (!Mat.fb) Mat.F |= (*r = *a); } Mat.N = (Mat.Nim && (Mat.da & 0x80)) ? 0xFF : 0;
  if ((Mat.F = (Mat.da || Mat.F) ? (!Mat.F && Mat.Nim && (Mat.da == 0x80)) ? 2 : 0 : 1)) { *Mat.b = Mat.da; Mat.lar = 0; return; }
  }

void FCOLD(anu l, an r, an a) { Mat.lbe = 1; if ((Mat.nb = l)) { do Mat.lbe <<= 1; while((Mat.nb >>= 1)); } Mat.nb = Mat.lar; Mat.lar = --Mat.lbe;
  FVIKARA(l, r, a); if (Mat.Be) { Fswap(Mat.lbe, r) } Mat.lar = Mat.nb; }

void FADD(an r, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b; }
void FSUB(an r, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b; }
void FMUL(an r, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b; l = Mat.lar; Mat.C = (l > (Mat.lar += 1 + Mat.lbe)); }
void FDIV(an r, an e, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b; (void)e; }

void FADDc(an r, an a, anu l, an c) { if (!l) FMOV(Mat.lar, r, a); else FADD(r, a, --l, c); }
void FSUBc(an r, an a, anu l, an c) { if (!l) FMOV(Mat.lar, r, a); else FSUB(r, a, --l, c); }
void FMULc(an r, an a, anu l, an c) { if (!l) FMOV(Mat.lar, r, a); else FMUL(r, a, --l, c); }
void FDIVc(an r, an e, an a, anu l, an c) {
  if (!l) { FMOV(Mat.lar, r, a); *e = 0; Mat.lbe = 0; Mat.Ne = 0; Mat.Fe = 1; } else FDIV(r, e, a, --l, c); }
