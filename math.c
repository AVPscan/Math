/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include "math.h"

Cache Mat = {0};
void _FInit (anu x, anu y, an r, anu c, an a) { while(x--) { *r-- = 0; } c = (c > y) ? y : c; while(c--) *++r = *a++; }
void _FAddr (anu y, As* r, anu c, As* a) { c = (c > y) ? y : c; while(c--) *r++ = *a++; }

void FVIKARA (an r, an a, anu l) { Mat.F = 0; Mat.fa = l;
  if (Mat.L < (Mat.fb = Mat.L - l)) { Mat.fb = l - Mat.L; Mat.N = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF : 0;
    if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.F |= (*--Mat.r = *--Mat.a); }
    else { while(l--) Mat.F |= (*r++ = *a++); } Mat.F = (*a || Mat.F) ? (!Mat.F && Mat.Nim && (*a == 0x80)) ? 2 : 0 : 1;
    Mat.C = (Mat.Nim) ? ((Mat.N ^ *a) & 0x80) : 0; *r = (!Mat.F && Mat.C) ? (*a ^ 0x80) : *a; while(Mat.fb-- && !(Mat.C |= (*++a ^ Mat.N))); }
  else { Mat.C = 0; l = Mat.L;
    if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.F |= (*--Mat.r = *--Mat.a); }
    else { while(l--) Mat.F |= (*r++ = *a++); } *r = *a; Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0;
    if ((Mat.F = (*r || Mat.F) ? (!Mat.F && Mat.Nim && (*r == 0x80)) ? 2 : 0 : 1)) { Mat.dr = *r; *r = 0; }
    while(Mat.fb--) { *++r = Mat.N; } if (Mat.F) { *r = Mat.dr; } }
  Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0; Mat.C = (Mat.C != 0); Mat.L = Mat.fa; }

void FLD (an r, anu D) { Mat.L = 0; Mat.N = (Mat.Nim && (D & 0x80)) ? 0xFF : 0;
  Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 2 : 0 : 1; *r = D; }
void FLVD (an r, anu Dl, anu Dh) { Mat.L = 1; *r++ = Dl; Mat.N = (Mat.Nim && (Dh & 0x80)) ? 0xFF : 0;
  Mat.F = (Dh || Dl) ? (!Dl && Mat.Nim && (Dh == 0x80)) ? 2 : 0 : 1; if (Mat.V) { if (Mat.F) { Mat.L--; r--; }
    else if ((Dh == Mat.N && (!Mat.N && (Dl != 0x80))) || (Mat.Nim && !((Dl ^ Mat.N) & 0x80))) { Mat.L--; return; } } *r = Dh; }

void FMOV (an r, an b, anu l) { Mat.L = l; Mat.a = r; Mat.F = 0;
  if (r > b) { Mat.r = (r += l); Mat.b = (b += l); while(l--) Mat.F |= (*--Mat.r = *--Mat.b); }
  else { while(l--) Mat.F |= (*r++ = *b++); } *r = *b; Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0;
  if ((Mat.F = (*r || Mat.F) ? (!Mat.F && (*r == 0x80)) ? 2 : 0 : 1)) { if (Mat.V) { *Mat.a = *r; Mat.L = 0; } return; }
  if (Mat.V) {  } }

void FSWAP (an r, an b, anu l) { Mat.L = l; Mat.r = r + l; Mat.b = b + l; Mat.fb = l & 1; Mat.N = *b++;
  Mat.F = (l) ? *Mat.b-- : 0; *r++ = Mat.F; *Mat.r-- = Mat.N; if ((l >>= 1)) {
	while(--l) { Mat.F |= (Mat.dr = *b++) | (Mat.db = *Mat.b--); *r++ = Mat.db; *Mat.r-- = Mat.dr; }
    if (!Mat.fb) Mat.F |= (*r = *b); } Mat.F = (Mat.N || Mat.F) ? (!Mat.F && Mat.Nim && (Mat.N == 0x80)) ? 2 : 0 : 1;
  Mat.N = (Mat.Nim && (Mat.N & 0x80)) ? 0xFF : 0; }

void FCOLD (an r, an a, anu l) { Mat.l = 1; if ((Mat.nb = l)) { do Mat.l <<= 1; while((Mat.nb >>= 1)); } Mat.nb = Mat.L; Mat.L = --Mat.l;
  FVIKARA(r, a, l); if (Mat.Be) { FSWAP(r, r, Mat.l); } Mat.L = Mat.nb; }

void FADD (an r, an a, anu l, an b) { Mat.l = l; (void)r; (void)a; (void)b; }
void FSUB (an r, an a, anu l, an b) { Mat.l = l; (void)r; (void)a; (void)b; }
void FMUL (an r, an a, anu l, an b) { Mat.l = l; (void)r; (void)a; (void)b; }
void FDIV (an r, an e, an a, anu l, an b) { Mat.l = l; (void)r; (void)a; (void)b; (void)e; }
