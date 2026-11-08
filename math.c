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
void FAddr(anu y, As* r, anu c, As* a) { c = (c > y) ? y:c; while(c--) *r++ = *a++; }

void FSWAP(an r, anu l, an a) { Mat.i = l; Mat.r = r; Mat.a = a; Mat.be = Mat.r + Mat.i;
  Mat.ae = Mat.a + Mat.i; Mat.j = *Mat.a++; *Mat.r++ = Mat.i ? *Mat.ae--:Mat.j; *Mat.be-- = Mat.j;
  Mat.i >>= 1; while(Mat.i--) { Mat.j = *Mat.a++; *Mat.r++ = *Mat.ae--; *Mat.be-- = Mat.j; } }
anu FMOV(an r, anu l, an a) { Mat.i = l; Mat.r = r; Mat.a = a;
  if (Mat.V) { Mat.ae = Mat.a + Mat.i; Mat.z = (Mat.Nim && (*Mat.ae & 128)) ? 255:0; Mat.j = Mat.i;
    while((Mat.x = *Mat.ae--) == Mat.z && Mat.i && !((*Mat.ae ^ Mat.z) & 128)) Mat.i--;
    Mat.t = Mat.i; while(Mat.t-- && !*Mat.ae--); if (Mat.i == Mat.j) {
      if (!++Mat.t && (!Mat.x || Mat.x == 128)) { Mat.a += Mat.i; Mat.i = 0; } }
    else Mat.i += (!++Mat.t && Mat.x == 128); } Mat.j = Mat.i; Mat.t = Mat.i; if (r < a) {
    do *Mat.r++ = *Mat.a++; while(Mat.j--); Mat.x = *--Mat.r; } else {
    Mat.be = (Mat.r += Mat.i); Mat.ae = Mat.a + Mat.i;
    do *Mat.be-- = *Mat.ae--; while(Mat.j--); Mat.x = *Mat.r; }
  Mat.z = (Mat.Nim && (Mat.x & 128)) ? 255:0; while(Mat.i && !*--Mat.r) Mat.i--;
  Mat.u = (Mat.i | Mat.x) ? (Mat.Nim && !Mat.i && Mat.x == 128) ? 2:0:1; return Mat.t; }
anu FOLD(anu f, an r, anu l, an a) { Mat.y = FMOV(r, l, a); Mat.t = ((Mat.x = Mat.y)) ? 2:1;
  while((Mat.x >>= 1)) { Mat.t <<= 1; } Mat.r = r; Mat.ae = Mat.r + Mat.y; Mat.x = --Mat.t - Mat.y;
  Mat.y = Mat.z; if (Mat.u) { Mat.y = *Mat.ae; *Mat.ae = 0; } while(Mat.x--) *++Mat.ae = Mat.z;
  *Mat.ae = Mat.u ? Mat.y:*Mat.ae; if (f) { Fswap(Mat.t, Mat.r); } return Mat.t; }
anu FVAR(anu f, an r, anu l, an c) { if (l--) { if (f) { FSWAP(r, l, c); return Fmov(l, r); }
    else return FMOV(r, l, c); } return Fvle(r, 0); }

void FADD(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.ae = Mat.a + Mat.l; Mat.u = (((Mat.x = *Mat.ae--) & 128) && Mat.Nim) ? 255:0; Mat.F = Mat.l;
  Mat.be = Mat.b + Mat.N; Mat.z = (((Mat.y = *Mat.be--) & 128) && Mat.Nim) ? 255:0; if (Mat.Nim) {
    Mat.i = Mat.l; Mat.j = Mat.lb; while(Mat.i-- && !*Mat.ae--); while(Mat.j-- && !*Mat.be--);
    Mat.j = (!++Mat.j && Mat.y == 128); Mat.j += (!++Mat.i && Mat.x == 128); if (Mat.j) {
      Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.i = (Mat.l = Mat.V ? 0:Mat.l);
      while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } } Mat.ae = Mat.r; Mat.j = 0;
  if (!Mat.V && Mat.l < Mat.N) { Mat.be = Mat.b + Mat.N;
    while(*Mat.be-- == Mat.z && Mat.N && !((*Mat.be ^ Mat.z) & 128)) { Mat.N--; }
    if (Mat.l < Mat.N) { if (Mat.Nim) { Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.i = Mat.l;
      while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } Mat.j++; Mat.N = Mat.l; } }
  Mat.be = Mat.b; Mat.i = (Mat.F > Mat.N) ? Mat.N:Mat.F; Mat.F -= Mat.i; Mat.N -= Mat.i;
  Mat.C = (Mat.C != 0); do { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x + *Mat.be++ + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); } while(Mat.i--);
  if (Mat.N) do { Mat.x = *Mat.be++; Mat.y = (*Mat.ae++ = Mat.u + Mat.x + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x + Mat.z + Mat.C);
    Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.x = --Mat.ae - Mat.r; Mat.N = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(*Mat.ae-- == Mat.N && Mat.x && !((*Mat.ae ^ Mat.N) & 128)) { Mat.x--; } Mat.i = Mat.x;
  Mat.y = *(Mat.be = ++Mat.ae); while(Mat.i-- && !*--Mat.be) { } Mat.F = !(++Mat.i | Mat.y);
  if (Mat.Nim) { Mat.C = (Mat.u != Mat.N && !(Mat.u ^ Mat.z)) || (!Mat.i && Mat.y == 128);
    if (Mat.C && Mat.x != 255 && (Mat.V || (!Mat.V && Mat.x < Mat.l))) { Mat.x++; Mat.C--;
      Mat.N = (!Mat.i && Mat.y == 128) ? Mat.N:~Mat.N; Mat.F = (!(Mat.i | Mat.y | Mat.N));
      *++Mat.ae = Mat.N; } if (Mat.C || Mat.j) { Mat.F = 2; Mat.N = 255; Mat.C = 0;
      Mat.i = (Mat.l = Mat.V ? 0:Mat.l); while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128;
      return; } } Mat.C |= Mat.j; if (!Mat.V && Mat.x < Mat.l) { Mat.i = Mat.l - Mat.x;
    do *++Mat.ae = Mat.N; while(--Mat.i); return; } Mat.l = Mat.x; }

void FSUB(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
    Mat.ae = Mat.a + Mat.l; Mat.u = (((Mat.x = *Mat.ae--) & 128) && Mat.Nim) ? 255:0; Mat.F = Mat.l;
    Mat.be = Mat.b + Mat.N; Mat.z = (((Mat.y = *Mat.be--) & 128) && Mat.Nim) ? 255:0; if (Mat.Nim) {
      Mat.i = Mat.l; Mat.j = Mat.lb; while(Mat.i-- && !*Mat.ae--); while(Mat.j-- && !*Mat.be--);
      Mat.j = (!++Mat.j && Mat.y == 128); Mat.j += (!++Mat.i && Mat.x == 128); if (Mat.j) {
        Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.i = (Mat.l = Mat.V ? 0:Mat.l);
        while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } } Mat.ae = Mat.r; Mat.j = 0;
  if (!Mat.V && Mat.l < Mat.N) { Mat.be = Mat.b + Mat.N;
    while(*Mat.be-- == Mat.z && Mat.N && !((*Mat.be ^ Mat.z) & 128)) { Mat.N--; }
    if (Mat.l < Mat.N) { if (Mat.Nim) { Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.i = Mat.l;
      while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } Mat.j = 4; Mat.N = Mat.l; } }
  Mat.be = Mat.b; Mat.i = (Mat.F > Mat.N) ? Mat.N:Mat.F; Mat.F -= Mat.i; Mat.N -= Mat.i;
  Mat.C = (Mat.C != 0); do { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x - *Mat.be++ - Mat.C);
    Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); } while(Mat.i--);
  if (Mat.N) do { Mat.y = (*Mat.ae++ = Mat.u - *Mat.be++ - Mat.C);
    Mat.C = (Mat.u < Mat.y) || (Mat.C && Mat.y == Mat.u); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x - Mat.z - Mat.C);
    Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.x = --Mat.ae - Mat.r; Mat.N = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(*Mat.ae-- == Mat.N && Mat.x && !((*Mat.ae ^ Mat.N) & 128)) { Mat.x--; } Mat.i = Mat.x;
  Mat.y = *(Mat.be = ++Mat.ae); while(Mat.i-- && !*--Mat.be) { } Mat.F = !(++Mat.i | Mat.y);
  if (Mat.Nim) { Mat.C = ((Mat.u ^ Mat.z) && (Mat.u ^ Mat.N)) || (!Mat.i && Mat.y == 128);
    if (Mat.C && Mat.x != 255 && (Mat.V || (!Mat.V && Mat.x < Mat.l))) { Mat.x++; Mat.C--;
      Mat.N = (!Mat.i && Mat.y == 128) ? Mat.N:~Mat.N; Mat.F = (!(Mat.i | Mat.y | Mat.N));
      *++Mat.ae = Mat.N; } if (Mat.C || Mat.j) { Mat.F = 2; Mat.N = 255; Mat.C = 0;
      Mat.i = (Mat.l = Mat.V ? 0:Mat.l); while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128;
      return; } }  Mat.C |= (Mat.j == 4); if (!Mat.V && Mat.x < Mat.l) { Mat.i = Mat.l - Mat.x;
    do *++Mat.ae = Mat.N; while(--Mat.i); return; } Mat.l = Mat.x; }

void FMUL(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.be = Mat.b;
  Mat.F = Mat.l; Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.u = (Mat.Nim && (Mat.x & 128)) ? 255:0;
  Mat.lb = Mat.N; Mat.y = *(Mat.e = Mat.b + Mat.N); Mat.z = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(Mat.F-- && *Mat.ae-- == Mat.u && !((*Mat.ae ^ Mat.u) & 128));
  Mat.i = ++Mat.F; while(Mat.N-- && *Mat.e-- == Mat.z && !((*Mat.e ^ Mat.z) & 128));
  Mat.j = ++Mat.N; while(Mat.F-- && !*Mat.a) { Mat.a++; } Mat.F++;
  while(Mat.N-- && !*Mat.be) { Mat.be++; } Mat.N++; Mat.t = !(Mat.x | Mat.i) || !(Mat.y | Mat.j);
  if (!Mat.t && Mat.Nim) { Mat.t = (Mat.lb == Mat.j && !Mat.N && Mat.y == 128) ? 2:0;
    Mat.t = (Mat.l == Mat.i && !Mat.F && Mat.x == 128) ? 2:Mat.t; }
  Mat.x = Mat.i; Mat.k = Mat.i; Mat.k += Mat.j; Mat.i -= Mat.F; Mat.j -= Mat.N; Mat.k++;
  Mat.t = Mat.t ? Mat.t:(Mat.x > Mat.k) ? 2:0; Mat.y = 1; Mat.ae = (an)Mat.H; Mat.e = (an)Mat.L;
  if (Mat.F < Mat.N) { Mat.x = Mat.N; Mat.N = Mat.F; Mat.F = Mat.x;
    if (Mat.z) do Mat.y = !(*Mat.ae++ = ~*Mat.be++ + Mat.y) && Mat.y; while(Mat.x--);
    else { do *Mat.ae++ = *Mat.be++; while(Mat.x--); } Mat.y = 1; Mat.x = Mat.N;
    if (Mat.u) do Mat.y = !(*Mat.e++ = ~*Mat.a++ + Mat.y) && Mat.y; while(Mat.x--);
    else do *Mat.e++ = *Mat.a++; while(Mat.x--); } else { Mat.x = Mat.F;
    if (Mat.u) do Mat.y = !(*Mat.ae++ = ~*Mat.a++ + Mat.y) && Mat.y; while(Mat.x--);
    else { do *Mat.ae++ = *Mat.a++; while(Mat.x--); } Mat.y = 1; Mat.x = Mat.N;
    if (Mat.z) do Mat.y = !(*Mat.e++ = ~*Mat.be++ + Mat.y) && Mat.y; while(Mat.x--);
    else do *Mat.e++ = *Mat.be++; while(Mat.x--); } Mat.C = (Mat.C != 0); Mat.u ^= Mat.z;
  Mat.z = 0; *Mat.e = 0; Mat.N++; if (!Mat.t) { Mat.e = (Mat.ae = Mat.r) + Mat.i + Mat.j;
    *Mat.ae++ = Mat.C; Mat.C = 0; while(Mat.k--) *Mat.ae++ = 0;
    Mat.ae = (an)Mat.H; do { if ((Mat.i = *Mat.ae++)) { Mat.a = (an)Mat.S;
        Mat.be = (an)Mat.L; Mat.j = Mat.N; do *Mat.a++ = *Mat.be++; while(Mat.j--); do {
          Mat.be = (an)Mat.S; Mat.j = Mat.N; Mat.t = 0; if (!(Mat.i & 1)) do { Mat.k = *Mat.be;
            *Mat.be++ = (Mat.k << 1) | Mat.t; Mat.t = (Mat.k & 128) ? 1:0; } while(Mat.j--);
          else { Mat.a = Mat.e; Mat.z |= Mat.C; Mat.C = 0;
            do { Mat.k = *Mat.be; Mat.x = *Mat.a; Mat.y = (*Mat.a++ = Mat.x + Mat.k + Mat.C);
              Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.x == Mat.y);
              *Mat.be++ = (Mat.k << 1) | Mat.t; Mat.t = (Mat.k & 128) ? 1:0; } while(Mat.j--); }
          Mat.z |= Mat.t; } while(Mat.i >>= 1); } Mat.e++; } while(Mat.F--); Mat.F++;
    Mat.t = Mat.z | Mat.C; Mat.l = Mat.e - Mat.r;
    if ((Mat.N = Mat.u)) { Mat.j = Mat.l; Mat.ae = Mat.r; Mat.z = 1;
      do { Mat.z = !(*Mat.ae = ~*Mat.ae + Mat.z) && Mat.z; Mat.ae++; } while(Mat.j--); }
    while(*Mat.e-- == Mat.N  && Mat.l && (Mat.Nim ? !((*Mat.e ^ Mat.N) & 128):1)) { Mat.l--; }
    if (*++Mat.e != 128) { return; } Mat.be = Mat.e; Mat.j = Mat.l; while(Mat.j-- && !*--Mat.e);
    if (++Mat.j) { return; } if (Mat.l != 255) { if (Mat.Nim) { Mat.l++; *++Mat.be = Mat.N; }
      return; } Mat.t = 2; }
  Mat.F = (Mat.C = (!Mat.Nim && Mat.t == 2)) ? 1:Mat.t; Mat.N = 0; Mat.N -= (Mat.F == 2);
  Mat.l = Mat.V ? 0:Mat.l; Mat.i = Mat.l; while(Mat.i--) *Mat.r++ = 0; *Mat.r = Mat.N & 128; }

void FDIV(an r, an e, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b;
  Mat.F = Mat.l; Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.u = (Mat.Nim && (Mat.x & 128)) ? 255:0;
  Mat.lb = Mat.N; Mat.y = *(Mat.e = Mat.b + Mat.N); Mat.z = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(Mat.F-- && *Mat.ae-- == Mat.u && !((*Mat.ae ^ Mat.u) & 128));
  Mat.i = ++Mat.F; while(Mat.N-- && *Mat.e-- == Mat.z && !((*Mat.e ^ Mat.z) & 128));
  Mat.j = ++Mat.N; while(Mat.F-- && !*Mat.a) { Mat.a++; } Mat.F++;
  while(Mat.N-- && !*Mat.be) { Mat.be++; } Mat.N++; Mat.t = !(Mat.x | Mat.i) || !(Mat.y | Mat.j);
  if (!Mat.t && Mat.Nim) { Mat.t = (Mat.lb == Mat.j && !Mat.N && Mat.y == 128) ? 2:0;
    Mat.t = (Mat.l == Mat.i && !Mat.F && Mat.x == 128) ? 2:Mat.t; }
  (void)e; }

void FTST(an a, anu l, an b) { Mat.i = Mat.l; Mat.j = l; Mat.a = a; Mat.b = b;
  Mat.x = ((*(Mat.ae = Mat.a + Mat.i) & 128) && Mat.Nim) ? 255:0; Mat.lb = Mat.j;
  Mat.TN = ((*(Mat.be = Mat.b + Mat.j) & 128) && Mat.Nim) ? 255:0; Mat.TF = 0;
  while(*Mat.ae-- == Mat.x && Mat.i && !((*Mat.ae ^ Mat.x) & 128)) { Mat.i--; } Mat.ae++;
  while(*Mat.be-- == Mat.TN && Mat.j && !((*Mat.be ^ Mat.TN) & 128)) { Mat.j--; } Mat.be++;
  if (Mat.Nim) if ((Mat.l == Mat.i && *Mat.ae == 128) || (Mat.lb == Mat.j && *Mat.be == 128)) {
      Mat.k = Mat.i; while(Mat.k-- && !*Mat.a) { Mat.a++; } Mat.t = Mat.j; Mat.r = Mat.b;
      while(Mat.t-- && !*Mat.r) { Mat.r++; } Mat.t++; if (!++Mat.k && *Mat.a == 128) {
          if (!Mat.t && *Mat.r == 128) { Mat.TF++; Mat.TN = 0; } return; }
      if (!Mat.t && *Mat.r == 128) { Mat.TN = ~Mat.x; return; } }
  if (!(Mat.x ^ Mat.TN) && Mat.i == Mat.j) { while((*Mat.ae-- == *Mat.be--) && Mat.i--) { }
    if (!++Mat.i) { Mat.TF++; Mat.TN = 0; } else { Mat.TN = !(*++Mat.be < *++Mat.ae); } return; }
  if (Mat.x ^ Mat.TN) { Mat.TN = ~Mat.TN; return; } Mat.TN = Mat.x ? (Mat.j < Mat.i):(Mat.i < Mat.j); }

void FCADD(an r, an a, anu l, an c) { if (l--) return FADD(r, a, l, c); return FADD(r, a, Mat.lb, Mat.b); }
void FCSUB(an r, an a, anu l, an c) { if (l--) return FSUB(r, a, l, c); return FSUB(r, a, Mat.lb, Mat.b); }
void FCMUL(an r, an a, anu l, an c) { if (l--) return FMUL(r, a, l, c); return FMUL(r, a, Mat.lb, Mat.b); }
void FCDIV(an r, an e, an a, anu l, an c) { if (l--) return FDIV(r, e, a, l, c);
  return FDIV(r, e, a, Mat.lb, Mat.b); }

void FCTST(an a, anu l, an c) { if (l--) return FTST(a, l, c); return FTST(a, Mat.lb, Mat.b); }
anu FCGE(an a, anu l, an c) { if (l--) { Mat.e = c; do { Mat.y = (Mat.l > l) ? l:Mat.l;
      FTST(a, Mat.y, Mat.e); Mat.e += 1 + Mat.y; l -= Mat.y; Mat.z = !Mat.TN; if (!l--) break;
      Mat.y = (Mat.l > l) ? l:Mat.l; FTST(a, Mat.y, Mat.e); Mat.e += 1 + Mat.y; l -= Mat.y;
      Mat.z = Mat.z && (Mat.TN | Mat.TF); if (!l--) break; } while(!Mat.z); return Mat.z; }
  FTST(a, Mat.lb, Mat.b); return !Mat.TN; }
anu FCEQ(an a, anu l, an c) { if (l--) { Mat.e = c; do { Mat.y = (Mat.l > l) ? l:Mat.l;
      FTST(a, Mat.y, Mat.e); Mat.e += 1 + Mat.y; l -= Mat.y; if (!l--) break; } while(!Mat.TF);
    return Mat.TF; } FTST(a, Mat.lb, Mat.b); return Mat.TF; }
