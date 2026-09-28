/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */
 
#include "math.h"
MATH_CACHE_INIT

void FInit(anu x, anu y, an r, anu c, an a) { while(x--) *--r = 0;
  c = (c > y) ? y:c; while(c--) *r++ = *a++; }
void FAddr(anu y, As* r, anu c, As* a) {
  c = (c > y) ? y:c; while(c--) *r++ = *a++; }

void FSWAP(anu l, an r, an a) { Mat.i = l; Mat.r = r; Mat.a = a; Mat.be = Mat.r + Mat.i;
  Mat.ae = Mat.a + Mat.i; Mat.t = *Mat.a++; *Mat.r++ = Mat.i ? *Mat.ae--:Mat.t; *Mat.be-- = Mat.t;
  Mat.i >>= 1; while(Mat.i--) { Mat.t = *Mat.a++; *Mat.r++ = *Mat.ae--; *Mat.be-- = Mat.t; } }
anu FMOV(anu l, an r, an a) { Mat.i = l; Mat.r = r; Mat.a = a;
  Mat.F = 0; Mat.j = Mat.i; Mat.k = Mat.i; if (r < a) do *Mat.r++ = *Mat.a++; while(Mat.j--);
  else { Mat.be = (Mat.r += Mat.i); Mat.ae = Mat.a + Mat.i; do *Mat.be-- = *Mat.ae--; while(Mat.j--); }
  Mat.x = *--Mat.r; Mat.N = (Mat.Nim && (Mat.x & 128)) ? 255:0; while(Mat.i-- && !*--Mat.r) { }
  Mat.i++; Mat.F = (Mat.i | Mat.x) ? (!Mat.i && Mat.Nim && Mat.x == 128) ? 2:0:1; return Mat.k; }
anu FCOLD(anu f, anu l, an r, an a) { Mat.y = FMOV(l, r, a); Mat.t = ((Mat.x = Mat.y)) ? 2:1;
  while((Mat.x >>= 1)) { Mat.t <<= 1; } Mat.r = r; Mat.e = Mat.r + Mat.y; Mat.x = --Mat.t - Mat.y;
  Mat.y = Mat.N; if (Mat.F) { Mat.y = *Mat.e; *Mat.e = 0; Mat.y = 0; } while(Mat.x--) { *++Mat.e = Mat.y; }
  *Mat.e = Mat.F ? Mat.y:*Mat.e; if (f) { FSWAP(Mat.t, Mat.r, Mat.r); } return Mat.t; }
anu FVI(anu f, an r, anu l, an c) { if (l--) { if (f) { FSWAP(l, r, c); return FMOV(l, r, r); }
    else return FMOV(l, r, c); } Mat.F = 1; Mat.N = 0; *r = 0; return 0; }

void FADD(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0; Mat.F = Mat.l;
  Mat.y = *(Mat.be = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(*Mat.ae-- == Mat.na && Mat.F && (Mat.Nim ? !((*Mat.ae ^ Mat.na) & 128):1)) { Mat.F--; }
  while(*Mat.be-- == Mat.nb && Mat.N && (Mat.Nim ? !((*Mat.be ^ Mat.nb) & 128):1)) { Mat.N--; }
  Mat.C = (Mat.C != 0); if (Mat.Nim) { Mat.i = Mat.F; Mat.j = Mat.N;
    if ((Mat.x == 128 && Mat.F == Mat.l) || (Mat.y == 128 && Mat.N == Mat.lb)) {
      while(Mat.i && !*Mat.ae--) { Mat.i--; } while(Mat.j && !*Mat.be--) { Mat.j--; }
      if (!(Mat.i && Mat.j)) { Mat.F = 2; Mat.N = 255; Mat.l = Mat.V ? 0:Mat.l; Mat.i = Mat.l;
        while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; Mat.C = 0; return; } } } Mat.t = 0;
  if (!Mat.V && Mat.N > Mat.l) { Mat.N = Mat.l; Mat.t++; } Mat.j = (Mat.F > Mat.N) ? Mat.N:Mat.F;
  Mat.i = Mat.j++; Mat.F -= Mat.i; Mat.N -= Mat.i; Mat.ae = Mat.r; Mat.be = Mat.b;
  do { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x + *Mat.be++ + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); } while(--Mat.j);
  if (Mat.N) do { Mat.x = *Mat.be++; Mat.y = (*Mat.ae++ = Mat.na + Mat.x + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x + Mat.nb + Mat.C);
      Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.x = --Mat.ae - Mat.r; Mat.be = Mat.ae; Mat.i = Mat.x; while(Mat.i-- && !*--Mat.be) { }
  Mat.F = !(++Mat.i | Mat.y); Mat.N = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  Mat.i = (!Mat.i && Mat.y == 128); if (Mat.Nim) { 
    Mat.C = (Mat.na != Mat.N && !(Mat.na ^ Mat.nb)) || Mat.i;
    if (Mat.C && Mat.x != 255 && (Mat.V || (!Mat.V && Mat.x < Mat.l))) { Mat.F = 0; Mat.x++;
      Mat.C--; Mat.N = Mat.i ? Mat.N:~Mat.N; *++Mat.ae = Mat.N; }
    if ((Mat.t | Mat.C)) { Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.l = Mat.V ? 0:Mat.l;
      Mat.i = Mat.l; while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } }
  if (!Mat.V && Mat.l > Mat.x) { Mat.i = Mat.l - Mat.x; do *++Mat.ae = Mat.N; while(--Mat.i);
    Mat.x = Mat.l; } Mat.C |= Mat.t; Mat.l = Mat.x; }
void FSUB(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0; Mat.F = Mat.l;
  Mat.y = *(Mat.be = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(*Mat.ae-- == Mat.na && Mat.F && (Mat.Nim ? !((*Mat.ae ^ Mat.na) & 128):1)) { Mat.F--; }
  while(*Mat.be-- == Mat.nb && Mat.N && (Mat.Nim ? !((*Mat.be ^ Mat.nb) & 128):1)) { Mat.N--; }
  Mat.C = (Mat.C != 0); if (Mat.Nim) { Mat.i = Mat.F; Mat.j = Mat.N;
    if ((Mat.x == 128 && Mat.F == Mat.l) || (Mat.y == 128 && Mat.N == Mat.lb)) {
      while(Mat.i && !*Mat.ae--) { Mat.i--; } while(Mat.j && !*Mat.be--) { Mat.j--; }
      if (!(Mat.i && Mat.j)) { Mat.F = 2; Mat.N = 255; Mat.l = Mat.V ? 0:Mat.l; Mat.i = Mat.l;
        while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; Mat.C = 0; return; } } } Mat.t = 0;
  if (!Mat.V && Mat.N > Mat.l) { Mat.N = Mat.l; Mat.t++; } Mat.j = (Mat.F > Mat.N) ? Mat.N:Mat.F;
  Mat.i = Mat.j++; Mat.F -= Mat.i; Mat.N -= Mat.i; Mat.ae = Mat.r; Mat.be = Mat.b;
  do { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x - *Mat.be++ - Mat.C);
    Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); } while(--Mat.j);
  if (Mat.N) do { Mat.y = (*Mat.ae++ = Mat.na - *Mat.be++ - Mat.C);
    Mat.C = (Mat.na < Mat.y) || (Mat.C && Mat.y == Mat.na); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x - Mat.nb - Mat.C);
      Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.x = --Mat.ae - Mat.r; Mat.be = Mat.ae; Mat.i = Mat.x; while(Mat.i-- && !*--Mat.be) { }
  Mat.F = !(++Mat.i | Mat.y); Mat.N = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  Mat.i = (!Mat.i && Mat.y == 128); if (Mat.Nim) {
    Mat.C = ((Mat.na ^ Mat.nb) && (Mat.na ^ Mat.N)) || Mat.i;
    if (Mat.C && Mat.x != 255 && (Mat.V || (!Mat.V && Mat.x < Mat.l))) { Mat.F = 0; Mat.x++;
      Mat.C--; Mat.N = Mat.i ? Mat.N:~Mat.N; *++Mat.ae = Mat.N; }
    if ((Mat.t | Mat.C)) { Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.l = Mat.V ? 0:Mat.l;
      Mat.i = Mat.l; while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } }
  if (!Mat.V && Mat.l > Mat.x) { Mat.i = Mat.l - Mat.x; do *++Mat.ae = Mat.N; while(--Mat.i);
    Mat.x = Mat.l; } Mat.N = Mat.Nim ? Mat.N:Mat.C; Mat.C |= Mat.t; Mat.l = Mat.x; }

void FMUL(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0; Mat.F = Mat.l;
  Mat.y = *(Mat.be = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0; Mat.C = (Mat.C != 0);
  while(Mat.F && *Mat.ae-- == Mat.na && (Mat.Nim ? !((*Mat.ae ^ Mat.na) & 128):1)) { Mat.F--; }  
  while(Mat.N && *Mat.be-- == Mat.nb && (Mat.Nim ? !((*Mat.be ^ Mat.nb) & 128):1)) { Mat.N--; }
  if (!(Mat.x | Mat.F) || !(Mat.y | Mat.N)) { Mat.F = 1; Mat.N = 0; *r = 0; Mat.l = 0; Mat.C = 0; return; }
  Mat.be = Mat.b; Mat.i = Mat.F; Mat.j = Mat.N; Mat.k = Mat.F; Mat.k += Mat.N; Mat.k++; Mat.t = 0;
  while(!*Mat.a && Mat.F) { Mat.a++; Mat.F--; } while(!*Mat.be && Mat.N) { Mat.be++; Mat.N--; }
  if (Mat.Nim) { if (!Mat.N && Mat.y == 128 && Mat.lb == Mat.j) Mat.t++;
    if (Mat.t || (!Mat.F && Mat.x == 128 && Mat.l == Mat.i)) Mat.t++; } if (Mat.t || (Mat.i > Mat.k)) {
    Mat.F = 2; Mat.N = 255; *r = 128; Mat.l = 0; Mat.C = !Mat.t; return; }
  Mat.l = Mat.k; Mat.i -= Mat.F; Mat.j -= Mat.N; Mat.i += Mat.j; Mat.e = (an)Mat.H; Mat.ae = (an)Mat.L;
  if (Mat.F > Mat.N) { Mat.j = Mat.F; if (Mat.na) { Mat.t = 1;
      do Mat.t = !(*Mat.e++ = ~*Mat.a++ + Mat.t); while(Mat.j--); }
    else do *Mat.e++ = *Mat.a++; while(Mat.j--);
    Mat.j = Mat.N; if (Mat.nb) { Mat.t = 1; do Mat.t = !(*Mat.ae++ = ~*Mat.be++ + Mat.t); while(Mat.j--); }
    else do *Mat.ae++ = *Mat.be++; while(Mat.j--); } else { Mat.j = Mat.N; Mat.N = Mat.F; Mat.F = Mat.j;
    if (Mat.nb) { Mat.t = 1; do Mat.t = !(*Mat.e++ = ~*Mat.be++ + Mat.t); while(Mat.j--); }
    else do *Mat.e++ = *Mat.be++; while(Mat.j--);
    Mat.j = Mat.N; if (Mat.na) { Mat.t = 1; do Mat.t = !(*Mat.ae++ = ~*Mat.a++ + Mat.t); while(Mat.j--); }
    else do *Mat.ae++ = *Mat.a++; while(Mat.j--); } *Mat.ae = 0; Mat.N++; Mat.e = Mat.r; Mat.e += Mat.i;
  Mat.ae = Mat.r; *Mat.ae++ = Mat.C; Mat.j = Mat.l; do *Mat.ae++ = 0; while(Mat.j--); Mat.ae = (an)Mat.H;
  do { if ((Mat.i = *Mat.ae++)) {
         Mat.a = (an)Mat.S; Mat.be = (an)Mat.L; Mat.j = Mat.N; do *Mat.a++ = *Mat.be++; while(Mat.j--);
         do { Mat.t = 0; Mat.be = (an)Mat.S; Mat.j = Mat.N;
           if (!(Mat.i & 1)) { do { Mat.k = *Mat.be; *Mat.be++ = (Mat.k << 1) | Mat.t;
               Mat.t = (Mat.k & 128) ? 1:0; } while(Mat.j--); } else { Mat.a = Mat.e; Mat.C = 0;
               do { Mat.k = *Mat.be; Mat.x = *Mat.a; Mat.y = (*Mat.a++ = (Mat.x + Mat.k + Mat.C));
                 Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.x == Mat.y);
             *Mat.be++ = (Mat.k << 1) | Mat.t; Mat.t = (Mat.k & 128) ? 1:0; } while(Mat.j--); }
         } while(Mat.i >>= 1); } Mat.e++; } while(Mat.F--); Mat.F++; Mat.N = Mat.na ^ Mat.nb;
  if (Mat.N) { Mat.j = Mat.l; Mat.e = Mat.r; Mat.t = 1;
    do { Mat.t = !(*Mat.e = ~*Mat.e + Mat.t); Mat.e++; } while(Mat.j--); } Mat.e = Mat.r + Mat.l;
  while(*Mat.e-- == Mat.N  && Mat.l && (Mat.Nim ? !((*Mat.e ^ Mat.N) & 128):1)) { Mat.l--; }
  if (*++Mat.e != 128) { return; } Mat.be = Mat.e; Mat.j = Mat.l; while(Mat.j && !*--Mat.e) { Mat.j--; }
  if (Mat.j) { return; } if (Mat.l != 255) { Mat.l++; *++Mat.be = Mat.N; return; }
  Mat.F = 2; Mat.N = 255; Mat.l = 0; *Mat.r = 128; }

void FDIV(an r, an e, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0; Mat.F = Mat.l;
  Mat.y = *(Mat.be = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0; Mat.C = (Mat.C != 0);
  while(Mat.F && *Mat.ae-- == Mat.na && (Mat.Nim ? !((*Mat.ae ^ Mat.na) & 128):1)) { Mat.F--; }  
  while(Mat.N && *Mat.be-- == Mat.nb && (Mat.Nim ? !((*Mat.be ^ Mat.nb) & 128):1)) { Mat.N--; }
  (void)e; }

void FADDc(an r, an a, anu l, an c) { if (l--) { FADD(r, a, l, c); return; } Mat.l = FMOV(Mat.l, r, a); }
void FSUBc(an r, an a, anu l, an c) { if (l--) { FSUB(r, a, l, c); return; } Mat.l = FMOV(Mat.l, r, a); }
void FMULc(an r, an a, anu l, an c) { if (l--) { FMUL(r, a, l, c); return; } Mat.F = 1; Mat.N = 0; *r = 0;
  Mat.l = 0; }
void FDIVc(an r, an e, an a, anu l, an c) { if (l--) { FDIV(r, e, a, l, c); return; }
  Mat.le = FMOV(Mat.l, e, a); Mat.Fe = Mat.F; Mat.Ne = Mat.N; Mat.F = 1; Mat.N = 0; *r = 0; Mat.l = 0; }
