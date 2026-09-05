/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include "math.h"

Cache Mat = {0};
void _FInit (anu x, anu y, an r, anu c, an a) { while(x--) { *r-- = 0; } if (c) { c = (c > y) ? y : c; do *++r = *a++; while(--c); } }

void FVIKARA (an r, an a, anu l, anu cl) { Mat.cL = (cl != 0); Mat.F = 0;
  if ((Mat.fa = Mat.cL - (Mat.L < (Mat.fb = Mat.L - l))) == 0xFF) { Mat.fb = l - Mat.L;
    Mat.cL = Mat.L; Mat.fa = *(a + l); Mat.N = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF : 0;
    if (r > a) { Mat.r = (r += Mat.L); Mat.a = (a += Mat.L); while(Mat.cL--) Mat.F |= (*--Mat.r = *--Mat.a); }
    else { while(Mat.cL--) Mat.F |= (*r++ = *a++); } Mat.F = (*a || Mat.F) ? (!Mat.F && Mat.Nim && (*a == 0x80)) ? 1 : 0 : 1;
    Mat.C = (Mat.Nim) ? ((Mat.N ^ *a) & 0x80) : 0; *r = (!Mat.F && Mat.C) ? (*a ^ 0x80) : *a; while(Mat.fb-- && !(Mat.C |= (*++a ^ Mat.N))); }
  else { Mat.C = 0;
    if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.F |= (*--Mat.r = *--Mat.a); }
    else { while(l--) Mat.F |= (*r++ = *a++); } *r = *a; Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0;
    if ((Mat.F = (*r || Mat.F) ? (!Mat.F && Mat.Nim && (*r == 0x80)) ? 1 : 0 : 1)) { Mat.dr = *r; *r = 0; }
    while(Mat.fb--) { *++r = Mat.N; } if (Mat.fa) { Mat.fb++; while(--Mat.fb) *++r = Mat.N; } if (Mat.F) { *r = Mat.dr; } }
  Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0; Mat.C = (Mat.C != 0); Mat.cL = 0; }

void FLD (an r, anu D) { Mat.L = 0; Mat.cL = 0; Mat.N = (Mat.Nim && (D & 0x80)) ? 0xFF : 0;
  Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 1 : 0 : 1; *r = D; }
void FLVD (an r, anu Dl, anu Dh) { Mat.L = 1; Mat.cL = 0; *r++ = Dl; Mat.N = (Mat.Nim && (Dh & 0x80)) ? 0xFF : 0;
  Mat.F = (Dh || Dl) ? (!Dl && Mat.Nim && (Dh == 0x80)) ? 1 : 0 : 1; if (Mat.V) { if (Mat.F) { Mat.L--; r--; }
    else if ((Dh == Mat.N && (!Mat.N && (Dl != 0x80))) || (Mat.Nim && !((Dl ^ Mat.N) & 0x80))) { Mat.L--; return; } } *r = Dh; }

void FMOV (an r, an b, anu l, anu cl) { Mat.fa = l; Mat.L = l; Mat.cL = cl; Mat.a = r; Mat.F = 0;
  if (r > b) { Mat.r = (r += Mat.fa); Mat.b = (b += Mat.fa); while(Mat.fa--) Mat.F |= (*--Mat.r = *--Mat.b); }
  else { while(Mat.fa--) Mat.F |= (*r++ = *b++); } *r = *b; Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF : 0;
  if ((Mat.F = (*r || Mat.F) ? (!Mat.F && (*r == 0x80)) ? 1 : 0 : 1)) { if (Mat.V) { *Mat.a = *r; Mat.L = 0; } return; }
  if (Mat.V) {  } }

void FSWAP (an r, an b, anu l, anu cl) { Mat.fa = l; Mat.L = l; Mat.cL = cl; Mat.r = r + l; Mat.b = b + l; Mat.fb = l & 1; Mat.N = *b++;
  Mat.F = (Mat.fa++) ? *Mat.b-- : 0; *r++ = Mat.F; *Mat.r-- = Mat.N; if ((Mat.fa = (Mat.fa) ? (Mat.fa >> 1) : 0x80)) {
	while(--Mat.fa) { Mat.F |= (Mat.dr = *b++) | (Mat.db = *Mat.b--); *r++ = Mat.db; *Mat.r-- = Mat.dr; }
    if (!Mat.fb) Mat.F |= (*r = *b); } Mat.F = (Mat.N || Mat.F) ? (!Mat.F && Mat.Nim && (Mat.N == 0x80)) ? 1 : 0 : 1;
  Mat.N = (Mat.Nim && (Mat.N & 0x80)) ? 0xFF : 0; }

void FCOLD (an r, an b, anu l, anu cl) { Mat.l = 1; if ((Mat.nb = l)) { do Mat.l <<= 1; while((Mat.nb >>= 1)); } Mat.nb = Mat.L; --Mat.l;
  Mat.na = Mat.cL; FVIKARA(r, b, l, cl); if (Mat.Be) { FSWAP(r, r, Mat.l, cl); } Mat.L = Mat.nb; Mat.cL = Mat.na; }

void FADD (an r, an a, anu l, an b) { Mat.l = l; (void)r; (void)a; (void)b; }
void FSUB (an r, an a, anu l, an b) { Mat.l = l; (void)r; (void)a; (void)b; }
void FMUL (an r, an a, anu l, an b) { Mat.l = l; (void)r; (void)a; (void)b; }
void FDIV (an r, an e, an a, anu l, an b) { Mat.l = l; (void)r; (void)a; (void)b; (void)e; }
