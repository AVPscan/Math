/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3).
 */

#include "math.h"

MCINIT
void FInit(anu x, anu y, an r, anu c, an a) { while(x--) *--r = 0;
  c = (c > y) ? y:c; while(c--) *r++ = *a++; }
void FAddr(anu y, As* r, anu c, As* a) { if ((c = (c > y) ? y:c)) { *r++ = *a;
  do *r++ = *a++; while(--c); } }

void FSWAP(an r, anu l, an a) { Mat.i = l; Mat.r = r; Mat.a = a; Mat.be = Mat.r + Mat.i;
  Mat.ae = Mat.a + Mat.i; Mat.j = *Mat.a++; *Mat.r++ = Mat.i ? *Mat.ae--:Mat.j; *Mat.be-- = Mat.j;
  Mat.i >>= 1; while(Mat.i--) { Mat.j = *Mat.a++; *Mat.r++ = *Mat.ae--; *Mat.be-- = Mat.j; } }
anu FMOV(an a, anu l, an b) { Mat.i = l; Mat.a = a; Mat.e = b; Mat.be = Mat.e;
  if (Mat.V) { Mat.ae = Mat.e + Mat.i; Mat.z = (Mat.Nim && (*Mat.ae & 128)) ? 255:0; Mat.j = Mat.i;
    while((Mat.x = *Mat.ae--) == Mat.z && Mat.i && !((*Mat.ae ^ Mat.z) & 128)) Mat.i--;
    Mat.q = Mat.i; while(Mat.q-- && !*Mat.ae--); if (Mat.i == Mat.j) {
      if (!++Mat.q && (!Mat.x || Mat.x == 128)) { Mat.e += Mat.i; Mat.i = 0; } }
    else Mat.i += (!++Mat.q && Mat.x == 128); } Mat.j = Mat.i; Mat.q = Mat.i; Mat.ae = Mat.a;
  if (a < b) { do *Mat.ae++ = *Mat.be++; while(Mat.j--); Mat.x = *--Mat.ae; } else {
    Mat.ae += Mat.i; Mat.be += Mat.i; do *Mat.ae-- = *Mat.be--; while(Mat.j--);
    Mat.x = *(Mat.ae = Mat.a + Mat.i); }
  Mat.z = (Mat.Nim && (Mat.x & 128)) ? 255:0; while(Mat.i && !*--Mat.ae) Mat.i--;
  Mat.u = (Mat.i | Mat.x) ? (Mat.Nim && !Mat.i && Mat.x == 128) ? 2:0:1; return Mat.q; }
anu FOLD(anu f, an a, anu l, an b) { Mat.y = FMOV(a, l, b); Mat.q = ((Mat.x = Mat.y)) ? 2:1;
  while((Mat.x >>= 1)) { Mat.q <<= 1; } Mat.a = a; Mat.ae = Mat.a + Mat.y; Mat.x = --Mat.q - Mat.y;
  Mat.y = Mat.z; if (Mat.u) { Mat.y = *Mat.ae; *Mat.ae = 0; } while(Mat.x--) *++Mat.ae = Mat.z;
  *Mat.ae = Mat.u ? Mat.y:*Mat.ae; if (f) { Fswap(Mat.q, Mat.a); } return Mat.q; }
anu FVAR(anu f, an a, anu l, an c) { if (l--) { if (f) { FSWAP(a, l, c); return Fmov(l, a); }
    else return FMOV(a, l, c); } return Fvle(a, 0); }

anu Fsin(anu s, anu x) { static anu w[] = {0,1,2,3,4,5,7,8,9,10,11,12,13,14,15,16,
  17,18,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44, 45,45,
  46,47,48,49,50,51,52, 53,53, 54,55,56,57,58,59,59,60,61,62,63 }; Mat.x = x; Mat.y = Mat.x&63;
  Mat.y = (Mat.x&64) ? *(w + Mat.y) | 64: *(w + Mat.y); Mat.y = (Mat.x&128) ? 127 - Mat.y:Mat.y;
  return (s) ? -Mat.y:Mat.y; }
void FSIN(an r, anu l, an b) { Mat.N = ((Mat.y = Fsin(*(b+l)&128,*b))&128) ? 255:0;
  Mat.F = !Mat.y; Mat.l = 0; *r = Mat.y; }
void FCOS(an r, anu l, an b) { Mat.N = ((Mat.y = Fcos(*(b+l)&128,*b))&128) ? 255:0;
  Mat.F = !Mat.y; Mat.l = 0; *r = Mat.y; }

void FTST(an a, anu l, an b) { Mat.i = Mat.l; Mat.lb = l; Mat.a = a; Mat.b = b; Mat.TF = 0;
  Mat.u = ((*(Mat.ae = Mat.a + Mat.i) & 128) && Mat.Nim) ? 255:0; Mat.j = Mat.lb;
  Mat.TN = (Mat.z = ((*(Mat.be = Mat.b + Mat.j) & 128) && Mat.Nim) ? 255:0) != 0;
  while(*Mat.ae-- == Mat.u && Mat.i && !((*Mat.ae ^ Mat.u) & 128)) { Mat.i--; } Mat.ae++;
  while(*Mat.be-- == Mat.z && Mat.j && !((*Mat.be ^ Mat.z) & 128)) { Mat.j--; } Mat.be++;
  if (Mat.Nim) if ((Mat.i == Mat.l && *Mat.ae == 128) || (Mat.j == Mat.lb && *Mat.be == 128)) {
      Mat.k = Mat.i; while(Mat.k-- && !*Mat.a++) { } Mat.k++; Mat.a = Mat.b;
      Mat.x = Mat.j; while(Mat.x-- && !*Mat.a++) { } if (!Mat.k++ && *Mat.ae == 128) {
        if (!++Mat.x && *Mat.be == 128) { Mat.TF++; Mat.TN = 0; Mat.k = 3; } return; }
      if (!++Mat.x && *Mat.be == 128) { Mat.TN = !Mat.u; Mat.k = 2; return; } } Mat.k = 0;
  if (!(Mat.u ^ Mat.z) && Mat.i == Mat.j) { while((*Mat.ae-- == *Mat.be--) && Mat.i--) { }
    if (!++Mat.i) { Mat.TF++; Mat.TN = 0; } else { Mat.TN = *++Mat.be >= *++Mat.ae; }
    Mat.i = Mat.j; return; }
  if (Mat.u ^ Mat.z) Mat.TN = !Mat.z; else Mat.TN = Mat.u ? (Mat.j < Mat.i):(Mat.i < Mat.j); }

void FADD(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.ae = Mat.a + Mat.l; Mat.u = (((Mat.x = *Mat.ae--) & 128) && Mat.Nim) ? 255:0; Mat.F = Mat.l;
  Mat.be = Mat.b + Mat.N; Mat.z = (((Mat.y = *Mat.be--) & 128) && Mat.Nim) ? 255:0; Mat.j = 0;
  if (Mat.Nim && (!(Mat.x^128)|!(Mat.y^128))) { if ((Mat.i = Mat.l)) while(!*Mat.ae-- && --Mat.i) { }
    if ((Mat.j = Mat.lb)) while(!*Mat.be-- && --Mat.j);
    Mat.j = !(Mat.i|(Mat.x^128))|!(Mat.j|(Mat.y^128)); }
  if (!Mat.V && Mat.l < Mat.N) { Mat.be = Mat.b + Mat.N;
    while(*Mat.be-- == Mat.z && Mat.N && !((*Mat.be ^ Mat.z) & 128)) { Mat.N--; }
    if (Mat.l < Mat.N) { Mat.N = Mat.l; Mat.j++; } } Mat.ae = Mat.r; Mat.be = Mat.b;
  Mat.i = (Mat.F > Mat.N) ? Mat.N:Mat.F; Mat.F -= Mat.i; Mat.N -= Mat.i; Mat.C = (Mat.C != 0);
  do { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x + *Mat.be++ + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); } while(Mat.i--);
  if (Mat.N) do { Mat.x = *Mat.be++; Mat.y = (*Mat.ae++ = Mat.u + Mat.x + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x + Mat.z + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.x = --Mat.ae - Mat.r; Mat.N = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(*Mat.ae-- == Mat.N && Mat.x && !((*Mat.ae ^ Mat.N) & 128)) { Mat.x--; } Mat.i = Mat.x;
  Mat.y = *(Mat.be = ++Mat.ae); while(Mat.i-- && !*--Mat.be) { } Mat.F = !(++Mat.i | Mat.y);
  if (Mat.Nim) { Mat.C = (Mat.u != Mat.N && !(Mat.u ^ Mat.z)) || !(Mat.i|(Mat.y^128));
    if (Mat.C && Mat.x != 255 && (Mat.V || Mat.x < Mat.l)) { Mat.x++; Mat.C--;
      Mat.N = !(Mat.i|(Mat.y^128)) ? Mat.N:~Mat.N; Mat.F = (!(Mat.i | Mat.y | Mat.N));
      *++Mat.ae = Mat.N; } if (Mat.C || Mat.j) { Mat.i = (Mat.l = Mat.V ? 0:Mat.l); Mat.F = 2;
      Mat.N = 255; Mat.C = 0; while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } }
  Mat.C |= Mat.j; if (!Mat.V && Mat.x < Mat.l) { Mat.i = Mat.l - Mat.x;
    do *++Mat.ae = Mat.N; while(--Mat.i); return; } Mat.l = Mat.x; }

void FSUB(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.ae = Mat.a + Mat.l; Mat.u = (((Mat.x = *Mat.ae--) & 128) && Mat.Nim) ? 255:0; Mat.F = Mat.l;
  Mat.be = Mat.b + Mat.N; Mat.z = (((Mat.y = *Mat.be--) & 128) && Mat.Nim) ? 255:0; Mat.j = 0;
  if (Mat.Nim && (!(Mat.x^128)|!(Mat.y^128))) { if ((Mat.i = Mat.l)) while(!*Mat.ae-- && --Mat.i) { }
    if ((Mat.j = Mat.lb)) while(!*Mat.be-- && --Mat.j);
    Mat.j = !(Mat.i|(Mat.x^128))|!(Mat.j|(Mat.y^128)); }
  if (!Mat.V && Mat.l < Mat.N) { Mat.be = Mat.b + Mat.N;
    while(*Mat.be-- == Mat.z && Mat.N && !((*Mat.be ^ Mat.z) & 128)) { Mat.N--; }
    if (Mat.l < Mat.N) { Mat.N = Mat.l; Mat.j++; } } Mat.ae = Mat.r; Mat.be = Mat.b;
  Mat.i = (Mat.F > Mat.N) ? Mat.N:Mat.F; Mat.F -= Mat.i; Mat.N -= Mat.i; Mat.C = (Mat.C != 0);
  do { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x - *Mat.be++ - Mat.C);
    Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); } while(Mat.i--);
  if (Mat.N) do { Mat.y = (*Mat.ae++ = Mat.u - *Mat.be++ - Mat.C);
    Mat.C = (Mat.u < Mat.y) || (Mat.C && Mat.y == Mat.u); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x - Mat.z - Mat.C);
    Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.x = --Mat.ae - Mat.r; Mat.N = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(*Mat.ae-- == Mat.N && Mat.x && !((*Mat.ae ^ Mat.N) & 128)) { Mat.x--; } Mat.i = Mat.x;
  Mat.y = *(Mat.be = ++Mat.ae); while(Mat.i-- && !*--Mat.be) { } Mat.F = !(++Mat.i | Mat.y);
  if (Mat.Nim) { Mat.C = ((Mat.u ^ Mat.z) && (Mat.u ^ Mat.N)) || !(Mat.i|(Mat.y^128));
    if (Mat.C && Mat.x != 255 && (Mat.V || Mat.x < Mat.l)) { Mat.x++; Mat.C--;
      Mat.N = !(Mat.i|(Mat.y^128)) ? Mat.N:~Mat.N; Mat.F = (!(Mat.i | Mat.y | Mat.N));
      *++Mat.ae = Mat.N; } if (Mat.C || Mat.j) { Mat.i = (Mat.l = Mat.V ? 0:Mat.l); Mat.F = 2;
      Mat.N = 255; Mat.C = 0; while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } }
  Mat.C |= Mat.j; if (!Mat.V && Mat.x < Mat.l) { Mat.i = Mat.l - Mat.x;
    do *++Mat.ae = Mat.N; while(--Mat.i); return; } Mat.l = Mat.x; }

void FMUL(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.be = Mat.b;
  Mat.F = Mat.l; Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.u = (Mat.Nim && (Mat.x & 128)) ? 255:0;
  Mat.lb = Mat.N; Mat.y = *(Mat.e = Mat.b + Mat.N); Mat.z = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(Mat.F-- && *Mat.ae-- == Mat.u && !((*Mat.ae ^ Mat.u) & 128));
  Mat.i = ++Mat.F; while(Mat.N-- && *Mat.e-- == Mat.z && !((*Mat.e ^ Mat.z) & 128));
  Mat.j = ++Mat.N; while(Mat.F-- && !*Mat.a) { Mat.a++; } Mat.F++;
  while(Mat.N-- && !*Mat.be) { Mat.be++; } Mat.N++; Mat.q = !(Mat.x | Mat.i) || !(Mat.y | Mat.j);
  if (!Mat.q && Mat.Nim) { Mat.q = (Mat.lb == Mat.j && !Mat.N && Mat.y == 128) ? 2:0;
    Mat.q = (Mat.l == Mat.i && !Mat.F && Mat.x == 128) ? 2:Mat.q; }
  Mat.x = Mat.i; Mat.k = Mat.i; Mat.k += Mat.j; Mat.i -= Mat.F; Mat.j -= Mat.N; Mat.k++;
  Mat.q = Mat.q ? Mat.q:(Mat.x > Mat.k) ? 2:0; Mat.y = 1; Mat.ae = (an)Mat.H; Mat.e = (an)Mat.L;
  if (Mat.F < Mat.N) { Mat.x = Mat.N; Mat.N = Mat.F; Mat.F = Mat.x;
    if (Mat.z) do Mat.y = !(*Mat.ae++ = ~*Mat.be++ + Mat.y) && Mat.y; while(Mat.x--);
    else { do *Mat.ae++ = *Mat.be++; while(Mat.x--); } Mat.y = 1; Mat.x = Mat.N;
    if (Mat.u) do Mat.y = !(*Mat.e++ = ~*Mat.a++ + Mat.y) && Mat.y; while(Mat.x--);
    else do *Mat.e++ = *Mat.a++; while(Mat.x--); } else { Mat.x = Mat.F;
    if (Mat.u) do Mat.y = !(*Mat.ae++ = ~*Mat.a++ + Mat.y) && Mat.y; while(Mat.x--);
    else { do *Mat.ae++ = *Mat.a++; while(Mat.x--); } Mat.y = 1; Mat.x = Mat.N;
    if (Mat.z) do Mat.y = !(*Mat.e++ = ~*Mat.be++ + Mat.y) && Mat.y; while(Mat.x--);
    else do *Mat.e++ = *Mat.be++; while(Mat.x--); } Mat.C = (Mat.C != 0); Mat.u ^= Mat.z;
  Mat.z = 0; *Mat.e = 0; Mat.N++; if (!Mat.q) { Mat.e = (Mat.ae = Mat.r) + Mat.i + Mat.j;
    *Mat.ae++ = Mat.C; Mat.C = 0; while(Mat.k--) *Mat.ae++ = 0;
    Mat.ae = (an)Mat.H; do { if ((Mat.i = *Mat.ae++)) { Mat.a = (an)Mat.S;
        Mat.be = (an)Mat.L; Mat.j = Mat.N; do *Mat.a++ = *Mat.be++; while(Mat.j--); do {
          Mat.be = (an)Mat.S; Mat.j = Mat.N; Mat.q = 0; if (!(Mat.i & 1)) do { Mat.k = *Mat.be;
            *Mat.be++ = (Mat.k << 1) | Mat.q; Mat.q = (Mat.k & 128) ? 1:0; } while(Mat.j--);
          else { Mat.a = Mat.e; Mat.z |= Mat.C; Mat.C = 0;
            do { Mat.k = *Mat.be; Mat.x = *Mat.a; Mat.y = (*Mat.a++ = Mat.x + Mat.k + Mat.C);
              Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.x == Mat.y);
              *Mat.be++ = (Mat.k << 1) | Mat.q; Mat.q = (Mat.k & 128) ? 1:0; } while(Mat.j--); }
          Mat.z |= Mat.q; } while(Mat.i >>= 1); } Mat.e++; } while(Mat.F--); Mat.F++;
    Mat.q = Mat.z | Mat.C; Mat.l = Mat.e - Mat.r;
    if ((Mat.N = Mat.u)) { Mat.j = Mat.l; Mat.ae = Mat.r; Mat.z = 1;
      do { Mat.z = !(*Mat.ae = ~*Mat.ae + Mat.z) && Mat.z; Mat.ae++; } while(Mat.j--); }
    while(*Mat.e-- == Mat.N  && Mat.l && (Mat.Nim ? !((*Mat.e ^ Mat.N) & 128):1)) { Mat.l--; }
    if (*++Mat.e != 128) { return; } Mat.be = Mat.e; Mat.j = Mat.l; while(Mat.j-- && !*--Mat.e);
    if (++Mat.j) { return; } if (Mat.l != 255) { if (Mat.Nim) { Mat.l++; *++Mat.be = Mat.N; }
      return; } Mat.q = 2; }
  Mat.F = (Mat.C = (!Mat.Nim && Mat.q == 2)) ? 1:Mat.q; Mat.N = 0; Mat.N -= (Mat.F == 2);
  Mat.l = Mat.V ? 0:Mat.l; Mat.i = Mat.l; while(Mat.i--) *Mat.r++ = 0; *Mat.r = Mat.N & 128; }

void FDIV(an r, an e, an a, anu l, an b) { Mat.r = r; Mat.e = e; FTST(a, l, b); Mat.le = Mat.lb;
  if (Mat.k) { return; }
  if (Mat.TF) { Mat.F = 0; Mat.N = 0; Mat.Fe = 1; Mat.Ne = 0; *Mat.r = 1; *Mat.e = 0;
    if (Mat.V) { Mat.l = 0; Mat.le = 0; return; } Mat.j = Mat.le; while(Mat.j--) { *++Mat.e = 0; }
    Mat.i = Mat.l; while(Mat.i--) { *++Mat.r = 0; } return; }
  if (Mat.TN) { if (Mat.u || Mat.z) {
      return; }
    Mat.F = 1; Mat.N = 0; *Mat.r = Mat.N; Mat.le = FMOV(Mat.e, Mat.l, a);
    Mat.Fe = Mat.u; Mat.Ne = Mat.z; if (Mat.V) { Mat.l = 0; return; }
    Mat.i = Mat.l; while(Mat.i--) { *++Mat.r = 0; } return; }
  }

  void FCTST(an a, anu l, an c) { if (l--) return FTST(a, l, c); return FTST(a, Mat.lb, Mat.b); }
  anu FCGE(an a, anu l, an c) { if (l--) { Mat.r = c; do { Mat.y = (Mat.l > l) ? l:Mat.l;
        FTST(a, Mat.y, Mat.r); Mat.r += 1 + Mat.y; l -= Mat.y; Mat.q = !Mat.TN; if (!l--) break;
        Mat.y = (Mat.l > l) ? l:Mat.l; FTST(a, Mat.y, Mat.r); Mat.r += 1 + Mat.y; l -= Mat.y;
        Mat.q = Mat.q && (Mat.TN | Mat.TF); } while(l-- && !Mat.q); return Mat.q; }
    FTST(a, Mat.lb, Mat.b); return !Mat.TN; }
  anu FCLT(an a, anu l, an c) { if (l--) { Mat.r = c; Mat.q = 1; do { Mat.y = (Mat.l > l) ? l:Mat.l;
        FTST(a, Mat.y, Mat.r); Mat.r += 1 + Mat.y; l -= Mat.y; Mat.q = Mat.q && Mat.TN; if (!l--) break;
        Mat.y = (Mat.l > l) ? l:Mat.l; FTST(a, Mat.y, Mat.r); Mat.r += 1 + Mat.y; l -= Mat.y;
        Mat.q = Mat.q || !(Mat.TN | Mat.TF); } while(l--); return Mat.q; }
    FTST(a, Mat.lb, Mat.b); return Mat.TN; }
  void FCEQ(an a, anu l, an c) { if (l--) { Mat.r = c; Mat.q = l;
      do { Mat.y = (Mat.l > Mat.q) ? Mat.q:Mat.l; FTST(a, Mat.y, Mat.r); Mat.r += 1 + Mat.y;
        Mat.q -= Mat.y; } while(Mat.q-- && !Mat.TF); return; } FTST(a, Mat.lb, Mat.b); }

void FCADD(an r, an a, anu l, an c) { if (l--) return FADD(r, a, l, c); return FADD(r, a, Mat.lb, Mat.b); }
void FCSUB(an r, an a, anu l, an c) { if (l--) return FSUB(r, a, l, c); return FSUB(r, a, Mat.lb, Mat.b); }
void FCMUL(an r, an a, anu l, an c) { if (l--) return FMUL(r, a, l, c); return FMUL(r, a, Mat.lb, Mat.b); }
void FCDIV(an r, an e, an a, anu l, an c) { if (l--) return FDIV(r, e, a, l, c); return FDIV(r, e, a, Mat.lb, Mat.b); }
