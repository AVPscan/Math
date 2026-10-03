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
  else { Mat.be = (Mat.r += Mat.i); Mat.ae = Mat.a + Mat.i;
    do *Mat.be-- = *Mat.ae--; while(Mat.j--); } Mat.x = *--Mat.r;
  Mat.N = (Mat.Nim && (Mat.x & 128)) ? 255:0; while(Mat.i-- && !*--Mat.r) { }
  Mat.i++; Mat.F = (Mat.i | Mat.x) ? (!Mat.i && Mat.Nim && Mat.x == 128) ? 2:0:1; return Mat.k; }
anu FCOLD(anu f, anu l, an r, an a) { Mat.y = FMOV(l, r, a); Mat.t = ((Mat.x = Mat.y)) ? 2:1;
  while((Mat.x >>= 1)) { Mat.t <<= 1; } Mat.r = r; Mat.e = Mat.r + Mat.y; Mat.x = --Mat.t - Mat.y;
  Mat.y = Mat.N; if (Mat.F) { Mat.y = *Mat.e; *Mat.e = 0; Mat.y = 0; }
  while(Mat.x--) { *++Mat.e = Mat.y; } *Mat.e = Mat.F ? Mat.y:*Mat.e;
  if (f) { FSWAP(Mat.t, Mat.r, Mat.r); } return Mat.t; }
anu FVI(anu f, an r, anu l, an c) { if (l--) { if (f) { FSWAP(l, r, c); return FMOV(l, r, r); }
    else return FMOV(l, r, c); } Mat.F = 2; Mat.N = 255; *r = 128; return 0; }

void FADD(an r, an a, anu l, an b) { Mat.lb = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.N = Mat.lb;
  Mat.ae = Mat.a + Mat.l; Mat.be = Mat.b + Mat.N; Mat.na = ((Mat.x = *Mat.ae--) & 128) ? 255:0;
  Mat.nb = ((Mat.y = *Mat.be--) & 128) ? 255:0; Mat.F = Mat.l; if (Mat.Nim) { Mat.i = Mat.l;
    while(Mat.i && !*Mat.ae--) { Mat.i--; } Mat.j = Mat.lb; while(Mat.j && !*Mat.be--) { Mat.j--; }
    if ((!Mat.i && Mat.x == 128) | (!Mat.j && Mat.y == 128)) { Mat.F = 2; Mat.N = 255; Mat.C = 0;
      Mat.i = (Mat.l = Mat.V ? 0:Mat.l); while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } }
  Mat.ae = Mat.r; Mat.j = 0; if (!Mat.V && Mat.l < Mat.N) { Mat.be = Mat.b + Mat.N;
    while(*Mat.be-- == Mat.nb && Mat.N && !((*Mat.be ^ Mat.nb) & 128)) { Mat.N--; }
    if (Mat.l < Mat.N) { if (Mat.Nim) { Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.i = Mat.l;
      while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } Mat.j++; Mat.N = Mat.l; } }
  Mat.be = Mat.b; Mat.i = (Mat.F > Mat.N) ? Mat.N:Mat.F; Mat.F -= Mat.i; Mat.N -= Mat.i;
  Mat.C = (Mat.C != 0); do { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x + *Mat.be++ + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); } while(Mat.i--);
  if (Mat.N) do { Mat.x = *Mat.be++; Mat.y = (*Mat.ae++ = Mat.na + Mat.x + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x + Mat.nb + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.x = --Mat.ae - Mat.r; Mat.N = (Mat.y & 128) ? 255:0; 
  while(*Mat.ae-- == Mat.N && Mat.x && (Mat.Nim ? !((*Mat.ae ^ Mat.N) & 128):1)) { Mat.x--; }
  Mat.i = Mat.x; Mat.y = *(Mat.be = ++Mat.ae); while(Mat.i-- && !*--Mat.be) { }
  Mat.F = !(++Mat.i | Mat.y); if (Mat.Nim) {
    Mat.C = (Mat.na != Mat.N && !(Mat.na ^ Mat.nb)) || (!Mat.i && Mat.y == 128);
    if (Mat.C && Mat.x != 255 && (Mat.V || (!Mat.V && Mat.x < Mat.l))) { Mat.x++; Mat.C--;
      Mat.N = (!Mat.i && Mat.y == 128) ? Mat.na:~Mat.N; Mat.F = (!(Mat.i | Mat.y | Mat.N));
      *++Mat.ae = Mat.N; } if (Mat.C || Mat.j) { Mat.F = 2; Mat.N = 255; Mat.C = 0;
        Mat.i = (Mat.l = Mat.V ? 0:Mat.l); while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128;
        return; } }
  Mat.C |= Mat.j; if (!Mat.V && Mat.x < Mat.l) { Mat.i = Mat.l - Mat.x; Mat.ae++;
    do *++Mat.ae = Mat.N; while(--Mat.i); return; } Mat.l = Mat.x; }

void FSUB(an r, an a, anu l, an b) { Mat.lb = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.N = Mat.lb;
  Mat.ae = Mat.a + Mat.l; Mat.be = Mat.b + Mat.N; Mat.na = ((Mat.x = *Mat.ae--) & 128) ? 255:0;
  Mat.nb = ((Mat.y = *Mat.be--) & 128) ? 255:0; Mat.F = Mat.l; if (Mat.Nim) { Mat.i = Mat.l;
    while(Mat.i && !*Mat.ae--) { Mat.i--; } Mat.j = Mat.lb; while(Mat.j && !*Mat.be--) { Mat.j--; }
    if ((!Mat.i && Mat.x == 128) | (!Mat.j && Mat.y == 128)) { Mat.F = 2; Mat.N = 255; Mat.C = 0;
      Mat.i = (Mat.l = Mat.V ? 0:Mat.l); while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } }
  Mat.ae = Mat.r; Mat.j = 0; if (!Mat.V && Mat.l < Mat.N) { Mat.be = Mat.b + Mat.N;
    while(*Mat.be-- == Mat.nb && Mat.N && !((*Mat.be ^ Mat.nb) & 128)) { Mat.N--; }
    if (Mat.l < Mat.N) { if (Mat.Nim) { Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.i = Mat.l;
      while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } Mat.j++; Mat.N = Mat.l; } }
  Mat.be = Mat.b; Mat.i = (Mat.F > Mat.N) ? Mat.N:Mat.F; Mat.F -= Mat.i; Mat.N -= Mat.i;
  Mat.C = (Mat.C != 0); do { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x - *Mat.be++ - Mat.C);
    Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); } while(Mat.i--);
  if (Mat.N) do { Mat.y = (*Mat.ae++ = Mat.na - *Mat.be++ - Mat.C);
    Mat.C = (Mat.na < Mat.y) || (Mat.C && Mat.y == Mat.na); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x - Mat.nb - Mat.C);
    Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.x = --Mat.ae - Mat.r; Mat.N = (Mat.y & 128) ? 255:0; 
  while(*Mat.ae-- == Mat.N && Mat.x && (Mat.Nim ? !((*Mat.ae ^ Mat.N) & 128):1)) { Mat.x--; }
  Mat.i = Mat.x; Mat.y = *(Mat.be = ++Mat.ae); while(Mat.i-- && !*--Mat.be) { }
  Mat.F = !(++Mat.i | Mat.y); if (Mat.Nim) {
    Mat.C = ((Mat.na ^ Mat.nb) && (Mat.na ^ Mat.N)) || (!Mat.i && Mat.y == 128);
    if (Mat.C && Mat.x != 255 && (Mat.V || (!Mat.V && Mat.x < Mat.l))) { Mat.x++; Mat.C--;
      Mat.N = (!Mat.i && Mat.y == 128) ? Mat.na:~Mat.N; Mat.F = (!(Mat.i | Mat.y | Mat.N));
      *++Mat.ae = Mat.N; } if (Mat.C || Mat.j) { Mat.F = 2; Mat.N = 255; Mat.C = 0;
        Mat.i = (Mat.l = Mat.V ? 0:Mat.l); while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128;
        return; } }
  Mat.C |= Mat.j; if (!Mat.V && Mat.x < Mat.l) { Mat.i = Mat.l - Mat.x; Mat.ae++;
    do *++Mat.ae = Mat.N; while(--Mat.i); return; } Mat.l = Mat.x; }

void FMUL(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b;
  Mat.F = Mat.l; Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0;
  Mat.lb = Mat.N; Mat.y = *(Mat.e = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(*Mat.ae-- == Mat.na && Mat.F && (Mat.Nim ? !((*Mat.ae ^ Mat.na) & 128):1)) { Mat.F--; }
  while(*Mat.e-- == Mat.nb && Mat.N && (Mat.Nim ? !((*Mat.b ^ Mat.nb) & 128):1)) { Mat.N--; }
  Mat.e = (an)Mat.H; Mat.ae = (an)Mat.L; Mat.be = Mat.b; Mat.i = Mat.F; Mat.j = Mat.N;
  while(!*Mat.a && Mat.F) { Mat.a++; Mat.F--; } while(!*Mat.be && Mat.N) { Mat.be++; Mat.N--; }
  if (!(Mat.t = (!(Mat.x | Mat.i) || !(Mat.y | Mat.j))) && Mat.Nim) {
    Mat.t = (Mat.lb == Mat.j && !Mat.N && Mat.y == 128) ? 2:0;
    Mat.t = (Mat.l == Mat.i && !Mat.F && Mat.x == 128) ? 2:Mat.t; }
  Mat.k = Mat.i; Mat.k += Mat.j; Mat.k++; Mat.t = (Mat.i > Mat.k) ? 2:Mat.t; if (!Mat.t) {
    Mat.i -= Mat.F; Mat.j -= Mat.N; if (Mat.F > Mat.N) { Mat.y = Mat.F; if (Mat.na) { Mat.x = 1;
        do Mat.x = !(*Mat.e++ = ~*Mat.a++ + Mat.x) && Mat.x; while(Mat.y--); }
      else { do *Mat.e++ = *Mat.a++; while(Mat.y--); } Mat.y = Mat.N; if (Mat.nb) { Mat.x = 1;
        do Mat.x = !(*Mat.ae++ = ~*Mat.be++ + Mat.x) && Mat.x; while(Mat.y--); }
      else do *Mat.ae++ = *Mat.be++; while(Mat.y--); }
    else { Mat.y = Mat.N; Mat.N = Mat.F; Mat.F = Mat.y; if (Mat.nb) { Mat.x = 1;
        do Mat.x = !(*Mat.e++ = ~*Mat.be++ + Mat.x) && Mat.x; while(Mat.y--); }
      else { do *Mat.e++ = *Mat.be++; while(Mat.y--); } Mat.y = Mat.N; if (Mat.na) { Mat.x = 1;
        do Mat.x = !(*Mat.ae++ = ~*Mat.a++ + Mat.x) && Mat.x; while(Mat.y--); }
      else do *Mat.ae++ = *Mat.a++; while(Mat.y--); } *Mat.ae = 0; Mat.N++;
    Mat.na ^= Mat.nb; Mat.nb = 0; Mat.e = (Mat.ae = Mat.r) + Mat.i + Mat.j;
    *Mat.ae++ = (Mat.C != 0); do *Mat.ae++ = 0; while(Mat.k--); Mat.ae = (an)Mat.H;
    do { if ((Mat.i = *Mat.ae++)) { Mat.a = (an)Mat.S; Mat.be = (an)Mat.L;
           Mat.j = Mat.N; do *Mat.a++ = *Mat.be++; while(Mat.j--);
           do { Mat.t = 0; Mat.be = (an)Mat.S; Mat.j = Mat.N;
             if (!(Mat.i & 1)) { do { Mat.k = *Mat.be; *Mat.be++ = (Mat.k << 1) | Mat.t;
                 Mat.t = (Mat.k & 128) ? 1:0; } while(Mat.j--); }
             else { Mat.a = Mat.e; Mat.C = 0; do { Mat.k = *Mat.be;
                 Mat.x = *Mat.a; Mat.y = (*Mat.a++ = Mat.x + Mat.k + Mat.C);
                 Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.x == Mat.y);
                 *Mat.be++ = (Mat.k << 1) | Mat.t; Mat.t = (Mat.k & 128) ? 1:0; }
               while(Mat.j--); } Mat.nb |= Mat.t; } while(Mat.i >>= 1); } Mat.e++;
       } while(Mat.F--); Mat.l = Mat.e - Mat.r; Mat.F++;
    if ((Mat.N = Mat.na)) { Mat.j = Mat.l; Mat.ae = Mat.r; Mat.t = 1;
      do { Mat.t = !(*Mat.ae = ~*Mat.ae + Mat.t) && Mat.t; Mat.ae++; } while(Mat.j--); }
    while(*Mat.e-- == Mat.N  && Mat.l && (Mat.Nim ? !((*Mat.e ^ Mat.N) & 128):1)) { Mat.l--; }
    if (*++Mat.e != 128) { return; } Mat.be = Mat.e; Mat.j = Mat.l;
    while(Mat.j && !*--Mat.e) { Mat.j--; } if (Mat.j) { return; }
    if (Mat.l != 255) { Mat.l++; *++Mat.be = Mat.N; return; } Mat.t = 2; }
  Mat.F = !Mat.Nim ? 1:Mat.t; Mat.N = (Mat.F == 1) ? 0:255; Mat.l = Mat.V ? 0:Mat.l;
  Mat.i = Mat.l; while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = Mat.N ? 128:0; }

void FDIV(an r, an e, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b;
  Mat.F = Mat.l; Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0;
  Mat.lb = Mat.N; Mat.y = *(Mat.e = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(*Mat.ae-- == Mat.na && Mat.F && (Mat.Nim ? !((*Mat.ae ^ Mat.na) & 128):1)) { Mat.F--; }
  while(*Mat.e-- == Mat.nb && Mat.N && (Mat.Nim ? !((*Mat.b ^ Mat.nb) & 128):1)) { Mat.N--; }
  Mat.e = (an)Mat.H; Mat.ae = (an)Mat.L; Mat.be = Mat.b; Mat.i = Mat.F; Mat.j = Mat.N;
  while(!*Mat.a && Mat.F) { Mat.a++; Mat.F--; } while(!*Mat.be && Mat.N) { Mat.be++; Mat.N--; }
  if (!(Mat.t = (!(Mat.x | Mat.i) || !(Mat.y | Mat.j))) && Mat.Nim) {
    Mat.t = (Mat.lb == Mat.j && !Mat.N && Mat.y == 128) ? 2:0;
    Mat.t = (Mat.l == Mat.i && !Mat.F && Mat.x == 128) ? 2:Mat.t; }
  (void)e; }

void FADDc(an r, an a, anu l, an c) { if (l--) { FADD(r, a, l, c); return; } Mat.l = FMOV(Mat.l, r, a); }
void FSUBc(an r, an a, anu l, an c) { if (l--) { FSUB(r, a, l, c); return; } Mat.l = FMOV(Mat.l, r, a); }
void FMULc(an r, an a, anu l, an c) { if (l--) { FMUL(r, a, l, c); return; } Mat.F = 1; Mat.N = 0; *r = 0;
  Mat.l = 0; }
void FDIVc(an r, an e, an a, anu l, an c) { if (l--) { FDIV(r, e, a, l, c); return; }
  Mat.le = FMOV(Mat.l, e, a); Mat.Fe = Mat.F; Mat.Ne = Mat.N; Mat.F = 1; Mat.N = 0; *r = 0; Mat.l = 0; }
