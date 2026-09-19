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
void FSWAP(anu l, an r, an a) { Mat.a = a + l; Mat.r = r + l;
  Mat.x = *a++; *r++ = (l) ? *Mat.a--:Mat.x; *Mat.r-- = Mat.x; l >>= 1;
  while(l--) { Mat.x = *a++; *r++ = *Mat.a--; *Mat.r-- = Mat.x; } }

anu FLD(an r, anu D) { *r = D; Mat.N = Mat.Nim && (D & 0x80) ? 0xFF:0;
  Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 2:0:1; return 0; }
anu FLVD(an r, anu Dl, anu Dh) { *r++ = Dl; *r = Dh; Mat.N = (Mat.Nim && (Dh & 0x80)) ? 0xFF:0;
  if ((Mat.F = (Dl | Dh) ? (!Dl && Mat.Nim && (Dh == 0x80)) ? 2:0:1)) { *--r = Dh; Mat.x = 0; }
  else { if (Mat.Nim) Mat.x = !(Mat.N == Dh && !((Mat.N ^ Dl) & 0x80)); else Mat.x = Dh ? 1:0; }
  return Mat.x; }
anu FMOV(anu l, an r, an a) { Mat.z = 0; Mat.y = 0; Mat.C = 0; Mat.F = 0;
  Mat.fa = *(Mat.r = a + l); Mat.N = Mat.Nim ? (Mat.fa & 0x80) ? 0xFF:0:0;
  if (!Mat.fa || (Mat.Nim && Mat.fa == 0x80)) { Mat.x = l; Mat.a = a; while(l-- && !*Mat.a++) { }
    if ((Mat.F = ++l ? 0: Mat.fa ? 2:1)) { *r = Mat.fa; return 0; } l = Mat.x; }
  while(l && ((Mat.y = *Mat.r--) == Mat.N) && (Mat.Nim ? !((*Mat.r ^ Mat.N) & 0x80):1)) { l--; }
  Mat.x = l; if (Mat.Nim && Mat.y == 0x80) { while(l-- && !*Mat.r--) { }
    Mat.z = (Mat.C = (Mat.x == 255)) ? 0: ++l ? 0:1; l = Mat.x; }
  if (r < a) while(l--) *r++ = *a++; else { Mat.r = (r += l); Mat.a = (a += l);
    while(l--) *--Mat.r = *--Mat.a; } *r = *a; if (Mat.z) { *++r = Mat.N; Mat.x++; } return Mat.x; }
anu FCOLD(anu f, anu l, an r, an a) { l = FMOV(l, r, a); Mat.x = ((Mat.z = l)) ? 2:1;
  while((Mat.z >>= 1)) { Mat.x <<= 1; } Mat.r = r; r += l; Mat.z = --Mat.x - l; Mat.y = Mat.N;
  if (Mat.F) { l = *r; *r = 0; Mat.y = 0; } while(Mat.z--) { *++r = Mat.y; } *r = Mat.F ? l:*r;
  if (f) { FSWAP(Mat.x, Mat.r, Mat.r); } return Mat.x; }
anu FVI(anu f, an r, anu l, an c) { if (l--) { if (f) { FSWAP(l, r, c); return FMOV(l, r, r); }
    else return FMOV(l, r, c); } l++; Mat.F = 1; Mat.N = l; *r = l; return l; }

void FNEG(anu l, an r) { Mat.y = 1; do { Mat.y = !(*r = ~*r + Mat.y); r++; } while(l--); }
void FNEG2(anu l, an r, an a) { Mat.y = 1; do { Mat.y = !(*r++ = ~*a++ + Mat.y); } while(l--); }
void FADD(an r, an a, anu l, an b) { Mat.r = r; Mat.dr = 0; Mat.C = (Mat.C != 0);
  Mat.fa = *(Mat.a = a + Mat.l); Mat.na = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF:0;
  Mat.fb = *(Mat.b = b + l); Mat.nb = (Mat.Nim && (Mat.fb & 0x80)) ? 0xFF:0; Mat.N = l;
  if (Mat.Nim) { Mat.F = 0; if (Mat.fb == 0x80) { Mat.e = b; while(l-- && !*Mat.e++) { } Mat.F = !++l; }
    if (!Mat.F && Mat.fa == 0x80) { l = Mat.l; Mat.e = b; while(l-- && !*Mat.e++) { } Mat.F = !++l; }
    if (Mat.F) { *r = 0x80; Mat.l = 0; Mat.F = 2; Mat.N = 0xFF; return; } }
  while(Mat.l-- && *Mat.a-- == Mat.na && (Mat.Nim ? !((*Mat.a ^ Mat.na) & 0x80):1)) { } Mat.F = ++Mat.l;
  while(Mat.N-- && *Mat.b-- == Mat.nb && (Mat.Nim ? !((*Mat.b ^ Mat.nb) & 0x80):1)) { } Mat.N++;
  while(Mat.F && Mat.N && !(*a | *b)) { Mat.dr |= (*r++ = Mat.C); Mat.C = 0; a++; b++; --Mat.F; --Mat.N; }
  if (Mat.F > Mat.N) { Mat.F -= Mat.N; while(Mat.N--) { Mat.x = *a++; Mat.y = *b++;
      l = (*r++ = Mat.x + Mat.y + Mat.C); Mat.dr |= l; Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); }
    Mat.y = *b; while(Mat.F--) { Mat.x = *a++; l = (*r++ = Mat.x + Mat.y + Mat.C); Mat.dr |= l;
      Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); Mat.y = Mat.nb; } Mat.x = *a; }
  else { Mat.N -= Mat.F; while(Mat.F--) { Mat.x = *a++; Mat.y = *b++; l = (*r++ = Mat.x + Mat.y + Mat.C);
      Mat.dr |= l; Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); } Mat.x = *a;
    while(Mat.N--) { Mat.y = *b++; l = (*r++ = Mat.x + Mat.y + Mat.C); Mat.dr |= l;
      Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); Mat.x = Mat.na; } Mat.y = *b; }
  Mat.l = r - Mat.r; *r = Mat.x + Mat.y + Mat.C; Mat.C = (Mat.x > *r) || (Mat.C && Mat.x == *r);
  Mat.C = (Mat.Nim) ? ((!(Mat.na ^ Mat.nb) && ((Mat.na ^ *r) & 0x80)) || (!Mat.dr && *r == 0x80)):Mat.C;
  if (Mat.C && Mat.l != 0xFF) { Mat.l++; Mat.dr |= *r++; *r = Mat.Nim ? Mat.na:Mat.C; Mat.C--; }
  Mat.N = (Mat.Nim) ? (*r & 0x80) ? 0xFF:0:0; if ((Mat.F = !(Mat.dr | *r))) Mat.l = 0; }
void FSUB(an r, an a, anu l, an b) { Mat.r = r; Mat.dr = 0; Mat.C = (Mat.C != 0);
  Mat.fa = *(Mat.a = a + Mat.l); Mat.na = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF:0;
  Mat.fb = *(Mat.b = b + l); Mat.nb = (Mat.Nim && (Mat.fb & 0x80)) ? 0xFF:0; Mat.N = l;
  if (Mat.Nim) { Mat.F = 0; if (Mat.fb == 0x80) { Mat.e = b; while(l-- && !*Mat.e++) { } Mat.F = !++l; }
    if (!Mat.F && Mat.fa == 0x80) { l = Mat.l; Mat.e = b; while(l-- && !*Mat.e++) { } Mat.F = !++l; }
    if (Mat.F) { *r = 0x80; Mat.l = 0; Mat.F = 2; Mat.N = 0xFF; return; } } l = Mat.C ? 0xFF:0;
  while(Mat.l-- && *Mat.a-- == Mat.na && (Mat.Nim ? !((*Mat.a ^ Mat.na) & 0x80):1)) { } Mat.F = ++Mat.l;
  while(Mat.N-- && *Mat.b-- == Mat.nb && (Mat.Nim ? !((*Mat.b ^ Mat.nb) & 0x80):1)) { } Mat.N++;
  while(Mat.F && Mat.N && !(*a | *b)) { Mat.dr |= (*r++ = l); a++; b++; --Mat.F; --Mat.N; }
  if (Mat.F > Mat.N) { Mat.F -= Mat.N; while(Mat.N--) { Mat.x = *a++; Mat.y = *b++;
      l = (*r++ = Mat.x - Mat.y - Mat.C); Mat.dr |= l; Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); }
    Mat.y = *b; while(Mat.F--) { Mat.x = *a++; l = (*r++ = Mat.x - Mat.y - Mat.C); Mat.dr |= l;
      Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); Mat.y = Mat.nb; } Mat.x = *a; }
  else { Mat.N -= Mat.F; while(Mat.F--) { Mat.x = *a++; Mat.y = *b++; l = (*r++ = Mat.x - Mat.y - Mat.C);
      Mat.dr |= l; Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); } Mat.x = *a;
    while(Mat.N--) { Mat.y = *b++; l = (*r++ = Mat.x - Mat.y - Mat.C); Mat.dr |= l;
      Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); Mat.x = Mat.na; } Mat.y = *b; }
  Mat.l = r - Mat.r; *r = Mat.x - Mat.y - Mat.C; Mat.C = (Mat.x < *r) || (Mat.C && Mat.x == *r);
  if (!Mat.Nim) { Mat.N = 0; if (Mat.C) { Mat.dr = 1; Mat.N++; Mat.C--; } }
  else { Mat.N = (*r & 0x80) ? 0xFF:0;
    Mat.C = (((Mat.na ^ Mat.nb) && (Mat.na ^ Mat.N)) || (!Mat.dr && *r == 0x80)); 
    if (Mat.C && Mat.l != 0xFF) { Mat.l++; Mat.dr |= *r++; *r = Mat.na; Mat.N = Mat.na; Mat.C--; } }
  if ((Mat.F = !(Mat.dr | *r))) Mat.l = 0; }
void FMUL(an r, an a, anu l, an b) { Mat.r = r; Mat.dr = 0; Mat.C = (Mat.C != 0);
  Mat.fa = *(Mat.a = a + Mat.l); Mat.na = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF:0; Mat.N = l;
  Mat.fb = *(Mat.b = b + l); Mat.nb = (Mat.Nim && (Mat.fb & 0x80)) ? 0xFF:0; Mat.F = Mat.l;
  while(Mat.F && !*a) { a++; Mat.F--; } while(Mat.N && !*b) { b++; Mat.N--; }
  if (!Mat.F || !Mat.N) { if (!Mat.fa || !Mat.fb || (Mat.Nim && (Mat.fa == 0x80 || Mat.fb == 0x80))) {
      Mat.F = (Mat.N = (*r = (Mat.fa && Mat.fb) ? 0x80:0) ? 0xFF:0) ? 2:1; Mat.l = 0; Mat.C = 0; return; } }
  Mat.F = Mat.l - Mat.F; Mat.N = l - Mat.N; Mat.x = Mat.F + Mat.N;
  while(Mat.l && *Mat.a-- == Mat.na && (Mat.Nim ? !((*Mat.a ^ Mat.na) & 0x80):1)) { Mat.l--; }
  while(l && *Mat.b-- == Mat.nb && (Mat.Nim ? !((*Mat.b ^ Mat.nb) & 0x80):1)) { l--; }
  Mat.F = Mat.l - Mat.F; Mat.N = l - Mat.N; Mat.l += l; Mat.l++;
  if (l > Mat.l) { Mat.F = 2; Mat.N = 0xFF; *r = 0x80; Mat.l = 0; Mat.C = 1; return; }
  Mat.a = &Mat.Hi.l; Mat.b = &Mat.Lo.l; if (Mat.F > Mat.N) { l = Mat.F; if (Mat.na) { Mat.y = 1;
      do Mat.y = !(*Mat.a++ = ~*a++ + Mat.y); while(l--); } else { do *Mat.a++ = *a++; while(l--); }
    l = Mat.N; if (Mat.nb) { Mat.y = 1; do Mat.y = !(*Mat.b++ = ~*b++ + Mat.y); while(l--); }
    else { do *Mat.b++ = *b++; while(l--); } } else { l = Mat.F; Mat.F = Mat.N; Mat.N = l; if (Mat.nb) {
    Mat.y = 1; do Mat.y = !(*Mat.a++ = ~*b++ + Mat.y); while(l--); } else { do *Mat.a++ = *b++; while(l--); }
    l = Mat.F; if (Mat.na) { Mat.y = 1; do Mat.y = !(*Mat.b++ = ~*a++ + Mat.y); while(l--); }
    else { do *Mat.b++ = *a++; while(l--); } } *Mat.b = 0; Mat.N++; l = Mat.l;
  *r++ = Mat.C; do *r++ = 0; while(l--); r = Mat.r + Mat.x; Mat.a = &Mat.Hi.l;
  do { if ((Mat.da = *Mat.a++)) { a = &Mat.Sr.l; b = &Mat.Lo.l; l = Mat.N; do *a++ = *b++; while(--l);
         do { Mat.x = 0; b = &Mat.Sr.l; l = Mat.N; if (!(Mat.da & 1)) do { Mat.db = *b;
             *b++ = (Mat.db << 1) | Mat.x; Mat.x = (Mat.db & 0x80) ? 1:0; } while(--l);
           else { a = r; Mat.C = 0; do { Mat.db = *b; Mat.y = *a; Mat.z = (*a++ = (Mat.y + Mat.db + Mat.C));
               Mat.C = (Mat.y > Mat.z) || (Mat.C && Mat.y == Mat.z); *b++ = (Mat.db << 1) | Mat.x;
               Mat.x = (Mat.db & 0x80) ? 1:0; } while(--l); } } while(Mat.da >>= 1); }
       r++; } while(Mat.F--);
  Mat.F++; if ((Mat.N = (Mat.Nim && (Mat.na ^ Mat.nb)) ? 0xFF:0)) { l = Mat.l; Mat.y = 1;
    do { Mat.y = !(*Mat.r = ~*Mat.r + Mat.y); Mat.r++; } while(l--); } }

void FDIV(an r, an e, an a, anu l, an b) { (void)l; (void)r; (void)a; (void)b; (void)e; }

void FADDc(an r, an a, anu l, an c) { if (l--) { FADD(r, a, l, c); return; } FMOV(Mat.l, r, a); }
void FSUBc(an r, an a, anu l, an c) { if (l--) { FSUB(r, a, l, c); return; } FMOV(Mat.l, r, a); }
void FMULc(an r, an a, anu l, an c) { if (l--) { FMUL(r, a, l, c); return; } *r = 0; Mat.N = 0; Mat.F = 1;
  Mat.l = 0; }
void FDIVc(an r, an e, an a, anu l, an c) { if (l--) { FDIV(r, e, a, l, c); return; }
  Mat.le = 0; *r = Mat.Nim ? 0xFF:0; Mat.N = *r; Mat.F = Mat.Nim ? 2:1; *e = 0; Mat.Ne = 0; Mat.Fe = 1;
  Mat.l = 0; }
