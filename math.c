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
  Mat.z = *a++; *r++ = (l) ? *Mat.a--:Mat.z; *Mat.r-- = Mat.z; l >>= 1;
  while(l--) { Mat.z = *a++; *r++ = *Mat.a--; *Mat.r-- = Mat.z; } }
void FNEG(anu l, an r) { Mat.z = 1; do { Mat.z = !(*r = ~*r + Mat.z); r++; } while(l--); }
void FNEG2(anu l, an r, an a) { Mat.z = 1; do { Mat.z = !(*r++ = ~*a++ + Mat.z); } while(l--); }

anu FLD(an r, anu D) { *r = D; Mat.N = (Mat.Nim && (D & 128)) ? 255:0;
  Mat.F = (D) ? (Mat.Nim && (D == 128)) ? 2:0:1; return 0; }
anu FLVD(an r, anu Dl, anu Dh) { *r++ = Dl; *r = Dh; Mat.N = (Mat.Nim && (Dh & 128)) ? 255:0;
  if ((Mat.F = (Dl | Dh) ? (!Dl && Mat.Nim && (Dh == 128)) ? 2:0:1)) { *--r = Dh; return 0; }
  return (((Dl == 128) ? 1: (Mat.Nim) ? (((Dl^Mat.N)&128)|(Dh != Mat.N)):(Dh ? 1:0)) != 0); }
anu FMOV(anu l, an r, an a) { Mat.F = 0; Mat.C = 0;
  Mat.y = *(Mat.r = a + l); Mat.N = (Mat.Nim && (Mat.y & 128)) ? 255:0; Mat.z = l;
  if (!Mat.y || (Mat.Nim && Mat.y == 128)) { Mat.a = a; while(!*Mat.a++ && l) { l--; }
    if ((Mat.F = l ? 0: Mat.y ? 2:1)) { *r = Mat.y; return 0; } l = Mat.z; }
  while(((Mat.y = *Mat.r--) == Mat.N) && (Mat.Nim ? !((*Mat.r ^ Mat.N) & 128):1) && l) { l--; }
  Mat.z = l; if (Mat.y != 128) Mat.y = 0; else { while(!*Mat.r-- && l) { l--; }
    Mat.y = (Mat.C = (Mat.z == 255)) ? 0:l ? 0:1;
    if ((Mat.F = (Mat.C && !l) << 1)) { *r = 128; return 0; } l = Mat.z; }
  if (r < a) do *r++ = *a++; while(l--); else { Mat.r = (r += l + 1); Mat.a = (a += l + 1);
    do *--Mat.r = *--Mat.a; while(l--); } if (Mat.y) { *r = Mat.N; Mat.z++; } return Mat.z; }
anu FCOLD(anu f, anu l, an r, an a) { l = FMOV(l, r, a); Mat.z = ((Mat.x = l)) ? 2:1;
  while((Mat.x >>= 1)) { Mat.z <<= 1; } Mat.r = r; r += l; Mat.x = --Mat.z - l; Mat.y = Mat.N;
  if (Mat.F) { l = *r; *r = 0; Mat.y = 0; } while(Mat.x--) { *++r = Mat.y; } *r = Mat.F ? l:*r;
  if (f) { FSWAP(Mat.z, Mat.r, Mat.r); } return Mat.z; }
anu FVI(anu f, an r, anu l, an c) { if (l--) { if (f) { FSWAP(l, r, c); return FMOV(l, r, r); }
    else return FMOV(l, r, c); } Mat.F = 1; Mat.N = 0; *r = 0; return 0; }

void FADD(an r, an a, anu l, an b) { Mat.r = r; Mat.u = 0; Mat.C = (Mat.C != 0); Mat.b = b;
  Mat.fa = *(Mat.a = a + Mat.l); Mat.na = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF:0; Mat.lb = l;
  Mat.fb = *(Mat.d = b + l); Mat.nb = (Mat.Nim && (Mat.fb & 0x80)) ? 0xFF:0; Mat.N = l;
  if (Mat.Nim) { Mat.F = 0; if (Mat.fb == 0x80) { Mat.e = b; while(l-- && !*Mat.e++) { } Mat.F = !++l; }
    if (!Mat.F && Mat.fa == 0x80) { l = Mat.l; Mat.e = b; while(l-- && !*Mat.e++) { } Mat.F = !++l; }
    if (Mat.F) { *r = 0x80; Mat.l = 0; Mat.F = 2; Mat.N = 0xFF; return; } }
  while(Mat.l-- && *Mat.a-- == Mat.na && (Mat.Nim ? !((*Mat.a ^ Mat.na) & 0x80):1)) { } Mat.F = ++Mat.l;
  while(Mat.N-- && *Mat.d-- == Mat.nb && (Mat.Nim ? !((*Mat.d ^ Mat.nb) & 0x80):1)) { } Mat.N++;
  while(Mat.F && Mat.N && !(*a | *b)) { Mat.u |= (*r++ = Mat.C); Mat.C = 0; a++; b++; --Mat.F; --Mat.N; }
  if (Mat.F > Mat.N) { Mat.F -= Mat.N; while(Mat.N--) { Mat.x = *a++; Mat.y = *b++;
      l = (*r++ = Mat.x + Mat.y + Mat.C); Mat.u |= l; Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); }
    Mat.y = *b; while(Mat.F--) { Mat.x = *a++; l = (*r++ = Mat.x + Mat.y + Mat.C); Mat.u |= l;
      Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); Mat.y = Mat.nb; } Mat.x = *a; }
  else { Mat.N -= Mat.F; while(Mat.F--) { Mat.x = *a++; Mat.y = *b++; l = (*r++ = Mat.x + Mat.y + Mat.C);
      Mat.u |= l; Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); } Mat.x = *a;
    while(Mat.N--) { Mat.y = *b++; l = (*r++ = Mat.x + Mat.y + Mat.C); Mat.u |= l;
      Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); Mat.x = Mat.na; } Mat.y = *b; }
  Mat.l = r - Mat.r; *r = Mat.x + Mat.y + Mat.C; Mat.C = (Mat.x > *r) || (Mat.C && Mat.x == *r);
  Mat.C = (Mat.Nim) ? ((!(Mat.na ^ Mat.nb) && ((Mat.na ^ *r) & 0x80)) || (!Mat.u && *r == 0x80)):Mat.C;
  if (Mat.C && Mat.l != 0xFF) { Mat.l++; Mat.u |= *r++; *r = Mat.Nim ? Mat.na:Mat.C; Mat.C--; }
  Mat.N = (Mat.Nim) ? (*r & 0x80) ? 0xFF:0:0; if ((Mat.F = !(Mat.u | *r))) Mat.l = 0; }

void FSUB(an r, an a, anu l, an b) { Mat.r = r; Mat.u = 0; Mat.C = (Mat.C != 0); Mat.b = b;
  Mat.fa = *(Mat.a = a + Mat.l); Mat.na = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF:0; Mat.lb = l;
  Mat.fb = *(Mat.d = b + l); Mat.nb = (Mat.Nim && (Mat.fb & 0x80)) ? 0xFF:0; Mat.N = l;
  if (Mat.Nim) { Mat.F = 0; if (Mat.fb == 0x80) { Mat.e = b; while(l-- && !*Mat.e++) { } Mat.F = !++l; }
    if (!Mat.F && Mat.fa == 0x80) { l = Mat.l; Mat.e = b; while(l-- && !*Mat.e++) { } Mat.F = !++l; }
    if (Mat.F) { *r = 0x80; Mat.l = 0; Mat.F = 2; Mat.N = 0xFF; return; } } l = Mat.C ? 0xFF:0;
  while(Mat.l-- && *Mat.a-- == Mat.na && (Mat.Nim ? !((*Mat.a ^ Mat.na) & 0x80):1)) { } Mat.F = ++Mat.l;
  while(Mat.N-- && *Mat.d-- == Mat.nb && (Mat.Nim ? !((*Mat.d ^ Mat.nb) & 0x80):1)) { } Mat.N++;
  while(Mat.F && Mat.N && !(*a | *b)) { Mat.u |= (*r++ = l); a++; b++; --Mat.F; --Mat.N; }
  if (Mat.F > Mat.N) { Mat.F -= Mat.N; while(Mat.N--) { Mat.x = *a++; Mat.y = *b++;
      l = (*r++ = Mat.x - Mat.y - Mat.C); Mat.u |= l; Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); }
    Mat.y = *b; while(Mat.F--) { Mat.x = *a++; l = (*r++ = Mat.x - Mat.y - Mat.C); Mat.u |= l;
      Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); Mat.y = Mat.nb; } Mat.x = *a; }
  else { Mat.N -= Mat.F; while(Mat.F--) { Mat.x = *a++; Mat.y = *b++; l = (*r++ = Mat.x - Mat.y - Mat.C);
      Mat.u |= l; Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); } Mat.x = *a;
    while(Mat.N--) { Mat.y = *b++; l = (*r++ = Mat.x - Mat.y - Mat.C); Mat.u |= l;
      Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); Mat.x = Mat.na; } Mat.y = *b; }
  Mat.l = r - Mat.r; *r = Mat.x - Mat.y - Mat.C; Mat.C = (Mat.x < *r) || (Mat.C && Mat.x == *r);
  if (!Mat.Nim) { Mat.N = 0; if (Mat.C) { Mat.u = 1; Mat.N++; Mat.C--; } }
  else { Mat.N = (*r & 0x80) ? 0xFF:0;
    Mat.C = (((Mat.na ^ Mat.nb) && (Mat.na ^ Mat.N)) || (!Mat.u && *r == 0x80)); 
    if (Mat.C && Mat.l != 0xFF) { Mat.l++; Mat.u |= *r++; *r = Mat.na; Mat.N = Mat.na; Mat.C--; } }
  if ((Mat.F = !(Mat.u | *r))) Mat.l = 0; }

void FMUL(an r, an a, anu l, an b) { Mat.r = r; Mat.C = (Mat.C != 0); Mat.b = b; Mat.lb = l;
  Mat.x = *(Mat.a = a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0; Mat.N = l;
  Mat.y = *(Mat.d = b + l); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0; Mat.F = Mat.l;
  while(!*a && Mat.F) { a++; Mat.F--; } while(!*b && Mat.N) { b++; Mat.N--; }
  if (!Mat.F || !Mat.N) { if (!Mat.x || !Mat.y || (Mat.Nim && (Mat.x == 128 || Mat.y == 128))) {
      Mat.F = (Mat.N = (*r = (Mat.x && Mat.y) ? 128:0) ? 255:0) ? 2:1; Mat.l = 0; Mat.C = 0; return; } }
  Mat.l -= Mat.F; l -= Mat.N;
  while(*Mat.a-- == Mat.na && (Mat.Nim ? !((*Mat.a ^ Mat.na) & 128):1) && Mat.F) { Mat.F--; }
  while(*Mat.d-- == Mat.nb && (Mat.Nim ? !((*Mat.d ^ Mat.nb) & 128):1) && Mat.N) { Mat.N--; }
  Mat.x = Mat.l + l; Mat.l = Mat.x + Mat.F + Mat.N; Mat.l++;
  if (Mat.x > Mat.l) { Mat.F = 2; Mat.N = 255; *r = 128; Mat.l = 0; Mat.C = 1; return; }
  Mat.a = &Mat.Hi.l; Mat.d = &Mat.Lo.l; if (Mat.F > Mat.N) {
    l = Mat.F; if (Mat.na) { Mat.z = 1; do Mat.z = !(*Mat.a++ = ~*a++ + Mat.z); while(l--); }
    else { do *Mat.a++ = *a++; while(l--); }
    l = Mat.N; if (Mat.nb) { Mat.z = 1; do Mat.z = !(*Mat.d++ = ~*b++ + Mat.z); while(l--); }
    else { do *Mat.d++ = *b++; while(l--); } }
  else { l = Mat.F; Mat.F = Mat.N;
    Mat.N = l; if (Mat.nb) { Mat.z = 1; do Mat.z = !(*Mat.a++ = ~*b++ + Mat.z); while(l--); }
    else { do *Mat.a++ = *b++; while(l--); }
    l = Mat.F; if (Mat.na) { Mat.z = 1; do Mat.z = !(*Mat.d++ = ~*a++ + Mat.z); while(l--); }
    else { do *Mat.d++ = *a++; while(l--); } } *Mat.d = 0; Mat.N++; *r++ = Mat.C; l = Mat.l;
  do *r++ = 0; while(l--); r = Mat.r + Mat.x; Mat.a = &Mat.Hi.l;
  do { if ((Mat.u = *Mat.a++)) { a = &Mat.Sr.l; b = &Mat.Lo.l; l = Mat.N; do *a++ = *b++; while(l--);
         do { Mat.z = 0; b = &Mat.Sr.l; l = Mat.N; if (!(Mat.u & 1)) {
             do { Mat.w = *b; *b++ = (Mat.w << 1) | Mat.z; Mat.z = (Mat.w & 128) ? 1:0; } while(l--); }
           else { a = r; Mat.C = 0; do { Mat.w = *b; Mat.x = *a; Mat.y = (*a++ = (Mat.x + Mat.w + Mat.C));
             Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.x == Mat.y); *b++ = (Mat.w << 1) | Mat.z;
             Mat.z = (Mat.w & 128) ? 1:0; } while(l--); } } while(Mat.u >>= 1); } r++; } while(Mat.F--);
  Mat.F++; Mat.N = Mat.na ^ Mat.nb; if (Mat.N) { l = Mat.l; r = Mat.r; Mat.z = 1;
    do { Mat.z = !(*r = ~*r + Mat.z); r++; } while(l--); } }

void FDIV(an r, an e, an a, anu l, an b) { Mat.r = r; Mat.C = (Mat.C != 0); Mat.b = b; Mat.lb = l;
  Mat.fa = *(Mat.a = a + Mat.l); Mat.na = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF:0; Mat.N = l;
  Mat.fb = *(Mat.d = b + l); Mat.nb = (Mat.Nim && (Mat.fb & 0x80)) ? 0xFF:0; Mat.F = Mat.l;
  while(Mat.F && !*a) { a++; Mat.F--; } while(Mat.N && !*b) { b++; Mat.N--; }
  if (!Mat.F || !Mat.N) { if (!Mat.fa || !Mat.fb || (Mat.Nim && (Mat.fa == 0x80 || Mat.fb == 0x80))) {
    return; } }
  (void)e; }

void FADDc(an r, an a, anu l, an c) { if (l--) { FADD(r, a, l, c); return; } Mat.l = FMOV(Mat.l, r, a); }
void FSUBc(an r, an a, anu l, an c) { if (l--) { FSUB(r, a, l, c); return; } Mat.l = FMOV(Mat.l, r, a); }
void FMULc(an r, an a, anu l, an c) { if (l--) { FMUL(r, a, l, c); return; } Mat.F = 1; Mat.N = 0; *r = 0;
  Mat.l = 0; }
void FDIVc(an r, an e, an a, anu l, an c) { if (l--) { FDIV(r, e, a, l, c); return; }
  Mat.le = FMOV(Mat.l, e, a); Mat.Fe = Mat.F; Mat.Ne = Mat.N; Mat.F = 1; Mat.N = 0; *r = 0; Mat.l = 0; }
