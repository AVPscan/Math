/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include "math.h"

MATH_CACHE_INIT
void FInit(anu x, anu y, an r, anu c, an a) { while(x--) *r-- = 0;
  c = (c > y) ? y : c; while(c--) *++r = *a++; }
void FAddr(anu y, As* r, anu c, As* a) {
  c = (c > y) ? y : c; while(c--) *r++ = *a++; }
void FLD(an r, anu D) { Mat.lar = 0; Mat.N = (Mat.Nim && (D & 0x80)) ? 0xFF : 0;
  Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 2 : 0 : 1; *r = D; }
void FLVD(an r, anu Dl, anu Dh) { Mat.lar = 1; *r++ = Dl; Mat.N = (Mat.Nim && (Dh & 0x80)) ? 0xFF : 0;
  if ((Mat.F = (Dl || Dh) ? (!Dl && Mat.Nim && (Dh == 0x80)) ? 2 : 0 : 1)) { Mat.lar--; r--; } *r = Dh; }
void FMOV(anu l, an r, an a) { Mat.lar = l; Mat.e = r; Mat.F = 0;
  if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.F |= (*--Mat.r = *--Mat.a); }
  else { while(l--) Mat.F |= (*r++ = *a++); } *r = *a; Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0;
  if ((Mat.F = (Mat.F || *r) ? (!Mat.F && Mat.Nim && (*r == 0x80)) ? 2 : 0 : 1)) { *Mat.e = *r; Mat.lar = 0; }
  else { l = Mat.lar; while(Mat.lar && *r == Mat.N && !((*(r - 1) ^ Mat.N) & 0x80)) { Mat.lar--; r--; }
	if ((l - Mat.lar) && *r == 0x80) { l = Mat.lar; while(l && *--r == 0) { l--; } Mat.lar += !l; } } }
void FSWAP(anu l, an r, an a) { Mat.lar = l; Mat.b = r; Mat.r = r + l; Mat.a = a + l; Mat.fb = l & 1;
  Mat.da = *a++; Mat.F = (l) ? *Mat.a-- : 0; *r++ = Mat.F; *Mat.r-- = Mat.da; if ((l >>= 1)) {
	while(--l) { Mat.F |= (Mat.dr = *a++) | (Mat.db = *Mat.a--); *r++ = Mat.db; *Mat.r-- = Mat.dr; }
    if (!Mat.fb) Mat.F |= (*r = *a); } Mat.N = (Mat.Nim && (Mat.da & 0x80)) ? 0xFF : 0;
  Mat.F = (Mat.F || Mat.da) ? (!Mat.F && Mat.Nim && (Mat.da == 0x80)) ? 2 : 0 : 1; }
void FCOLD(anu l, an r, an a) { Mat.lar = ((Mat.dr = l)) ? 2 : 1; while((Mat.dr >>= 1)) Mat.lar <<= 1;
  Mat.fb = --Mat.lar - l; if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.F |= (*--Mat.r = *--Mat.a); }
  else { while(l--) Mat.F |= (*r++ = *a++); } *r = *a; Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0;
  if ((Mat.F = (Mat.F || *r) ? (!Mat.F && Mat.Nim && (*r == 0x80)) ? 2 : 0 : 1)) { Mat.dr = *r; *r = 0; }
  while(Mat.fb--) { *++r = Mat.N; } *r = Mat.F ? Mat.dr : *r; if (Mat.Be) Fswap(Mat.lar, r) }

void FADD(an r, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b; }
void FSUB(an r, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b; }
void FMUL(an r, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b; l = Mat.lar; Mat.C = (l > (Mat.lar += 1 + Mat.lbe)); }
void FDIV(an r, an e, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b; (void)e; }

void FADDc(an r, an a, anu l, an c) { if (!l) FMOV(Mat.lar, r, a); else FADD(r, a, --l, c); }
void FSUBc(an r, an a, anu l, an c) { if (!l) FMOV(Mat.lar, r, a); else FSUB(r, a, --l, c); }
void FMULc(an r, an a, anu l, an c) { if (!l) FMOV(Mat.lar, r, a); else FMUL(r, a, --l, c); }
void FDIVc(an r, an e, an a, anu l, an c) { if (!l) { FMOV(Mat.lar, r, a); *e = 0; Mat.lbe = 0; Mat.Ne = 0; Mat.Fe = 1; }
  else FDIV(r, e, a, --l, c); }
