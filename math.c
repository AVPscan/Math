/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include "math.h"

MATH_CACHE_INIT
void FInit(anu x, anu y, an r, anu c, an a) { while(x--) *--r = 0;
  c = (c > y) ? y : c; while(c--) *r++ = *a++; }
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
  if (!Mat.y || (Mat.Nim && Mat.y == 128)) { Mat.a = a; while(l && !*Mat.a++) { l--; }
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

void FADD(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.x = *(Mat.e = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0; Mat.F = Mat.l;
  Mat.y = *(Mat.d = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0; Mat.C = (Mat.C != 0);
  while(*Mat.e-- == Mat.na && Mat.F && (Mat.Nim ? !((*Mat.e ^ Mat.na) & 128):1)) { Mat.F--; }  
  while(*Mat.d-- == Mat.nb && Mat.N && (Mat.Nim ? !((*Mat.d ^ Mat.nb) & 128):1)) { Mat.N--; }
  if (Mat.Nim) { if ((Mat.x == 128 && Mat.F == Mat.l) || (Mat.y == 128 && Mat.N == Mat.lb)) {
      Mat.u = Mat.F; Mat.v = Mat.N; while(Mat.u-- && !*Mat.e--) { } while(Mat.v-- && !*Mat.d--) { } 
      Mat.u++; Mat.v++; if (!(Mat.u && Mat.v)) { Mat.F = 2; Mat.N = 255; *Mat.r = 128; Mat.l = 0;
        return; } } } Mat.l = (Mat.F > Mat.N) ? Mat.F:Mat.N; Mat.v = (Mat.F > Mat.N) ? Mat.N:Mat.F;
  Mat.u = Mat.v++; Mat.F -= Mat.u; Mat.N -= Mat.u; Mat.d = Mat.b;
  do { Mat.x = *Mat.a++; Mat.y = (*Mat.r++ = Mat.x + *Mat.d++ + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); } while(--Mat.v);
  if (Mat.N) do { Mat.x = *Mat.d++; Mat.y = (*Mat.r++ = Mat.na + Mat.x + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.r++ = Mat.x + Mat.nb + Mat.C);
      Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.a = --Mat.r; Mat.v = Mat.l; while(Mat.v-- && !*--Mat.a) { } Mat.v++;
  Mat.N = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  if (Mat.Nim) Mat.C = ((!(Mat.na ^ Mat.nb) && (Mat.na ^ Mat.N)) || (!Mat.v && Mat.y == 128));
  if (Mat.C && Mat.l != 255) { Mat.l++; Mat.v |= Mat.y; *++Mat.r = Mat.Nim ? Mat.N:Mat.C; Mat.C--; }
  Mat.N = (Mat.Nim && (*Mat.r & 128)) ? 255:0; if ((Mat.F = !(Mat.v | *Mat.r))) Mat.l = 0; }
void FSUB(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.x = *(Mat.e = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0; Mat.F = Mat.l;
  Mat.y = *(Mat.d = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0; Mat.C = (Mat.C != 0);
  while(*Mat.e-- == Mat.na && Mat.F && (Mat.Nim ? !((*Mat.e ^ Mat.na) & 128):1)) { Mat.F--; }  
  while(*Mat.d-- == Mat.nb && Mat.N && (Mat.Nim ? !((*Mat.d ^ Mat.nb) & 128):1)) { Mat.N--; }
  if (Mat.Nim) { if ((Mat.x == 128 && Mat.F == Mat.l) || (Mat.y == 128 && Mat.N == Mat.lb)) {
      Mat.u = Mat.F; Mat.v = Mat.N; while(Mat.u-- && !*Mat.e--) { } while(Mat.v-- && !*Mat.d--) { } 
      Mat.u++; Mat.v++; if (!(Mat.u && Mat.v)) { Mat.F = 2; Mat.N = 255; *Mat.r = 128; Mat.l = 0;
        return; } } } Mat.l = (Mat.F > Mat.N) ? Mat.F:Mat.N; Mat.v = (Mat.F > Mat.N) ? Mat.N:Mat.F;
  Mat.u = Mat.v++; Mat.F -= Mat.u; Mat.N -= Mat.u; Mat.d = Mat.b;
  do { Mat.x = *Mat.a++; Mat.y = (*Mat.r++ = Mat.x - *Mat.d++ - Mat.C);
    Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); } while(--Mat.v);
  if (Mat.N) do { Mat.y = (*Mat.r++ = Mat.na - *Mat.d++ - Mat.C);
    Mat.C = (Mat.na < Mat.y) || (Mat.C && Mat.y == Mat.na); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.r++ = Mat.x - Mat.nb - Mat.C);
      Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.a = --Mat.r; Mat.v = Mat.l; while(Mat.v-- && !*--Mat.a) { } Mat.v++;
  if (!Mat.Nim) { Mat.N = 0; if (Mat.C) { Mat.v = 1; Mat.N++; Mat.C--; } }
  else { Mat.N = (Mat.y & 128) ? 255:0;
    Mat.C = (((Mat.na ^ Mat.nb) && (Mat.na ^ Mat.N)) || (!Mat.v && *r == 128)); 
    if (Mat.C && Mat.l != 255) { Mat.l++; Mat.v |= Mat.y; Mat.N = ~Mat.N; *++Mat.r = Mat.N; Mat.C--; } }
  if ((Mat.F = !(Mat.v | *Mat.r))) Mat.l = 0; }
void FMUL(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.x = *(Mat.e = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0; Mat.F = Mat.l;
  Mat.y = *(Mat.d = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0; Mat.C = (Mat.C != 0);
  while(Mat.F && *Mat.e-- == Mat.na && (Mat.Nim ? !((*Mat.e ^ Mat.na) & 128):1)) { Mat.F--; }  
  while(Mat.N && *Mat.d-- == Mat.nb && (Mat.Nim ? !((*Mat.d ^ Mat.nb) & 128):1)) { Mat.N--; }
  if (!(Mat.x | Mat.F) || !(Mat.y | Mat.N)) { Mat.F = 1; Mat.N = 0; *r = 0; Mat.l = 0; Mat.C = 0; return; }
  Mat.d = Mat.b; Mat.u = Mat.F; Mat.v = Mat.N; Mat.w = Mat.F; Mat.w += Mat.N; Mat.w++; Mat.z = 0;
  while(!*Mat.a && Mat.F) { Mat.a++; Mat.F--; } while(!*Mat.d && Mat.N) { Mat.d++; Mat.N--; }
  if (Mat.Nim) { if (!Mat.N && Mat.y == 128 && Mat.lb == Mat.v) Mat.z++;
    if (Mat.z || (!Mat.F && Mat.x == 128 && Mat.l == Mat.u)) Mat.z++; } if (Mat.z || (Mat.u > Mat.w)) {
    Mat.F = 2; Mat.N = 255; *r = 128; Mat.l = 0; Mat.C = !Mat.z; return; }
  Mat.l = Mat.w; Mat.u -= Mat.F; Mat.v -= Mat.N; Mat.u += Mat.v; Mat.g = &Mat.Hi.l; Mat.e = &Mat.Lo.l;
  if (Mat.F > Mat.N) { Mat.v = Mat.F; if (Mat.na) {
      Mat.z = 1; do Mat.z = !(*Mat.g++ = ~*Mat.a++ + Mat.z); while(Mat.v--); }
    else do *Mat.g++ = *Mat.a++; while(Mat.v--);
    Mat.v = Mat.N; if (Mat.nb) { Mat.z = 1; do Mat.z = !(*Mat.e++ = ~*Mat.d++ + Mat.z); while(Mat.v--); }
    else do *Mat.e++ = *Mat.d++; while(Mat.v--); } else { Mat.v = Mat.N; Mat.N = Mat.F; Mat.F = Mat.v;
    if (Mat.nb) { Mat.z = 1; do Mat.z = !(*Mat.g++ = ~*Mat.d++ + Mat.z); while(Mat.v--); }
    else do *Mat.g++ = *Mat.d++; while(Mat.v--);
    Mat.v = Mat.N; if (Mat.na) { Mat.z = 1; do Mat.z = !(*Mat.e++ = ~*Mat.a++ + Mat.z); while(Mat.v--); }
    else do *Mat.e++ = *Mat.a++; while(Mat.v--); } *Mat.e = 0; Mat.N++; Mat.g = Mat.r; Mat.g += Mat.u;
  Mat.e = Mat.r; *Mat.e++ = Mat.C; Mat.v = Mat.l; do *Mat.e++ = 0; while(Mat.v--); Mat.e = &Mat.Hi.l;
  do { if ((Mat.u = *Mat.e++)) {
         Mat.a = &Mat.Sr.l; Mat.d = &Mat.Lo.l; Mat.v = Mat.N; do *Mat.a++ = *Mat.d++; while(Mat.v--);
         do { Mat.z = 0; Mat.d = &Mat.Sr.l; Mat.v = Mat.N;
           if (!(Mat.u & 1)) { do { Mat.w = *Mat.d; *Mat.d++ = (Mat.w << 1) | Mat.z;
               Mat.z = (Mat.w & 128) ? 1:0; } while(Mat.v--); } else { Mat.a = Mat.g; Mat.C = 0;
               do { Mat.w = *Mat.d; Mat.x = *Mat.a; Mat.y = (*Mat.a++ = (Mat.x + Mat.w + Mat.C));
                 Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.x == Mat.y);
             *Mat.d++ = (Mat.w << 1) | Mat.z; Mat.z = (Mat.w & 128) ? 1:0; } while(Mat.v--); }
         } while(Mat.u >>= 1); } Mat.g++; } while(Mat.F--);
  Mat.F++; Mat.N = Mat.na ^ Mat.nb; if (Mat.N) { Mat.v = Mat.l; Mat.g = Mat.r; Mat.z = 1;
    do { Mat.z = !(*Mat.g = ~*Mat.g + Mat.z); Mat.g++; } while(Mat.v--); } Mat.g = Mat.r + Mat.l;
  while(*Mat.g-- == Mat.N  && Mat.l && (Mat.Nim ? !((*Mat.g ^ Mat.N) & 128):1)) { Mat.l--; }
  if (*++Mat.g != 128) { return; } Mat.d = Mat.g; Mat.v = Mat.l; while(Mat.v && !*--Mat.g) { Mat.v--; }
  if (Mat.v) { return; } if (Mat.l != 255) { Mat.l++; *++Mat.d = Mat.N; return; }
  Mat.F = 2; Mat.N = 255; Mat.l = 0; *Mat.r = 128; }

void FDIV(an r, an e, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.x = *(Mat.e = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0; Mat.F = Mat.l;
  Mat.y = *(Mat.d = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0; Mat.C = (Mat.C != 0);
  while(Mat.F && *Mat.e-- == Mat.na && (Mat.Nim ? !((*Mat.e ^ Mat.na) & 128):1)) { Mat.F--; }  
  while(Mat.N && *Mat.d-- == Mat.nb && (Mat.Nim ? !((*Mat.d ^ Mat.nb) & 128):1)) { Mat.N--; }
  (void)e; }

void FADDc(an r, an a, anu l, an c) { if (l--) { FADD(r, a, l, c); return; } Mat.l = FMOV(Mat.l, r, a); }
void FSUBc(an r, an a, anu l, an c) { if (l--) { FSUB(r, a, l, c); return; } Mat.l = FMOV(Mat.l, r, a); }
void FMULc(an r, an a, anu l, an c) { if (l--) { FMUL(r, a, l, c); return; } Mat.F = 1; Mat.N = 0; *r = 0;
  Mat.l = 0; }
void FDIVc(an r, an e, an a, anu l, an c) { if (l--) { FDIV(r, e, a, l, c); return; }
  Mat.le = FMOV(Mat.l, e, a); Mat.Fe = Mat.F; Mat.Ne = Mat.N; Mat.F = 1; Mat.N = 0; *r = 0; Mat.l = 0; }
