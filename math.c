/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3).
 */

#include "math.h"
MATH_CACHE_INIT

void FAddr(anu y, As* r, anu c, As* a) { c = (c > y) ? y:c; while(c--) *r++ = *a++; }
void FInit(anu x, anu y, an r, anu c, an a) { while(x--) *--r = 0; c = (c > y) ? y:c;
  while(c--) *r++ = *a++; }

void FSWAP(anu l, an r, an a) { Mat.i = l; Mat.r = r; Mat.a = a; Mat.be = Mat.r + Mat.i;
  Mat.ae = Mat.a + Mat.i; Mat.j = *Mat.a++; *Mat.r++ = Mat.i ? *Mat.ae--:Mat.j; *Mat.be-- = Mat.j;
  Mat.i >>= 1; while(Mat.i--) { Mat.j = *Mat.a++; *Mat.r++ = *Mat.ae--; *Mat.be-- = Mat.j; } }
anu FMOV(anu l, an r, an a) { Mat.i = l; Mat.r = r; Mat.a = a; if (Mat.V) {
    Mat.ae = Mat.a + Mat.i; Mat.nb = (*Mat.ae & 128) ? 255:0; Mat.j = Mat.i;
    while((Mat.x = *Mat.ae--) == Mat.nb && Mat.i && !((*Mat.ae ^ Mat.nb) & 128)) Mat.i--;
    Mat.t = Mat.i; while(Mat.t-- && !*Mat.ae--) { } if (Mat.i == Mat.j) {
      if (!++Mat.t && (!Mat.x || Mat.x == 128)) { Mat.a += Mat.i; Mat.i = 0; } }
    else Mat.i += (!++Mat.t && Mat.x == 128); }
  Mat.j = Mat.i; Mat.t = Mat.i; if (r < a) do *Mat.r++ = *Mat.a++; while(Mat.j--);
  else { Mat.be = (Mat.r += Mat.i); Mat.ae = Mat.a + Mat.i;
    do *Mat.be-- = *Mat.ae--; while(Mat.j--); }
  Mat.x = *--Mat.r; Mat.nb = (Mat.Nim && (Mat.x & 128)) ? 255:0; while(Mat.i && !*--Mat.r) Mat.i--;
  Mat.na = (Mat.i | Mat.x) ? (Mat.Nim && !Mat.i && Mat.x == 128) ? 2:0:1; return Mat.t; }
anu FCOLD(anu f, anu l, an r, an a) { Mat.y = FMOV(l, r, a); Mat.t = ((Mat.x = Mat.y)) ? 2:1;
  while((Mat.x >>= 1)) { Mat.t <<= 1; } Mat.r = r; Mat.ae = Mat.r + Mat.y; Mat.x = --Mat.t - Mat.y;
  Mat.y = Mat.nb; if (Mat.na) { Mat.y = *Mat.ae; *Mat.ae = 0; } while(Mat.x--) *++Mat.ae = Mat.nb;
  *Mat.ae = Mat.na ? Mat.y:*Mat.ae; if (f) { Fswap(Mat.t, Mat.r); } return Mat.t; }
anu FIV(anu f, an r, anu l, an c) { if (l--) { if (f) { FSWAP(l, r, c); return Fmov(l, r); }
    else return FMOV(l, r, c); } return Fv(r, 0); }

void FADD(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.ae = Mat.a + Mat.l; Mat.na = (((Mat.x = *Mat.ae--) & 128) && Mat.Nim) ? 255:0; Mat.F = Mat.l;
  Mat.be = Mat.b + Mat.N; Mat.nb = (((Mat.y = *Mat.be--) & 128) && Mat.Nim) ? 255:0; if (Mat.Nim) {
    Mat.i = Mat.l; while(Mat.i-- && !*Mat.ae--) { } Mat.j = Mat.lb; while(Mat.j-- && !*Mat.be--) { }
    Mat.j = (!++Mat.j && Mat.y == 128); Mat.j += (!++Mat.i && Mat.x == 128); if (Mat.j) {
      Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.i = (Mat.l = Mat.V ? 0:Mat.l);
      while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } } Mat.ae = Mat.r; Mat.j = 0;
  if (!Mat.V && Mat.l < Mat.N) { Mat.be = Mat.b + Mat.N;
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
  Mat.x = --Mat.ae - Mat.r; Mat.N = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(*Mat.ae-- == Mat.N && Mat.x && !((*Mat.ae ^ Mat.N) & 128)) { Mat.x--; } Mat.i = Mat.x;
  Mat.y = *(Mat.be = ++Mat.ae); while(Mat.i-- && !*--Mat.be) { } Mat.F = !(++Mat.i | Mat.y);
  if (Mat.Nim) { Mat.C = (Mat.na != Mat.N && !(Mat.na ^ Mat.nb)) || (!Mat.i && Mat.y == 128);
    if (Mat.C && Mat.x != 255 && (Mat.V || (!Mat.V && Mat.x < Mat.l))) { Mat.x++; Mat.C--;
      Mat.N = (!Mat.i && Mat.y == 128) ? Mat.N:~Mat.N; Mat.F = (!(Mat.i | Mat.y | Mat.N));
      *++Mat.ae = Mat.N; } if (Mat.C || Mat.j) { Mat.F = 2; Mat.N = 255; Mat.C = 0;
      Mat.i = (Mat.l = Mat.V ? 0:Mat.l); while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128;
      return; } } Mat.C |= Mat.j; if (!Mat.V && Mat.x < Mat.l) { Mat.i = Mat.l - Mat.x;
    do *++Mat.ae = Mat.N; while(--Mat.i); return; } Mat.l = Mat.x; }
void FCADD(an r, an a, anu l, an c) { if (l--) return FADD(r, a, l, c);
  return FADD(r, a, Mat.lb, Mat.B); }

void FSUB(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.lb = Mat.N;
  Mat.ae = Mat.a + Mat.l; Mat.na = (((Mat.x = *Mat.ae--) & 128) && Mat.Nim) ? 255:0; Mat.F = Mat.l;
  Mat.be = Mat.b + Mat.N; Mat.nb = (((Mat.y = *Mat.be--) & 128) && Mat.Nim) ? 255:0; if (Mat.Nim) {
    Mat.i = Mat.l; while(Mat.i-- && !*Mat.ae--) { } Mat.j = Mat.lb; while(Mat.j-- && !*Mat.be--) { }
    Mat.j = (!++Mat.j && Mat.y == 128); Mat.j += Mat.j + (!++Mat.i && Mat.x == 128); if (Mat.j) {
      Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.i = (Mat.l = Mat.V ? 0:Mat.l);
      while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } } Mat.ae = Mat.r; Mat.j = 0;
  if (!Mat.V && Mat.l < Mat.N) { Mat.be = Mat.b + Mat.N;
    while(*Mat.be-- == Mat.nb && Mat.N && !((*Mat.be ^ Mat.nb) & 128)) { Mat.N--; }
    if (Mat.l < Mat.N) { if (Mat.Nim) { Mat.F = 2; Mat.N = 255; Mat.C = 0; Mat.i = Mat.l;
      while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128; return; } Mat.j = 4; Mat.N = Mat.l; } }
  Mat.be = Mat.b; Mat.i = (Mat.F > Mat.N) ? Mat.N:Mat.F; Mat.F -= Mat.i; Mat.N -= Mat.i;
  Mat.C = (Mat.C != 0); do { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x - *Mat.be++ - Mat.C);
    Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); } while(Mat.i--);
  if (Mat.N) do { Mat.y = (*Mat.ae++ = Mat.na - *Mat.be++ - Mat.C);
    Mat.C = (Mat.na < Mat.y) || (Mat.C && Mat.y == Mat.na); } while(--Mat.N);
  else while(Mat.F--) { Mat.x = *Mat.a++; Mat.y = (*Mat.ae++ = Mat.x - Mat.nb - Mat.C);
    Mat.C = (Mat.x < Mat.y) || (Mat.C && Mat.y == Mat.x); }
  Mat.x = --Mat.ae - Mat.r; Mat.N = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(*Mat.ae-- == Mat.N && Mat.x && !((*Mat.ae ^ Mat.N) & 128)) { Mat.x--; } Mat.i = Mat.x;
  Mat.y = *(Mat.be = ++Mat.ae); while(Mat.i-- && !*--Mat.be) { } Mat.F = !(++Mat.i | Mat.y);
  if (Mat.Nim) { Mat.C = ((Mat.na ^ Mat.nb) && (Mat.na ^ Mat.N)) || (!Mat.i && Mat.y == 128);
    if (Mat.C && Mat.x != 255 && (Mat.V || (!Mat.V && Mat.x < Mat.l))) { Mat.x++; Mat.C--;
      Mat.N = (!Mat.i && Mat.y == 128) ? Mat.N:~Mat.N; Mat.F = (!(Mat.i | Mat.y | Mat.N));
      *++Mat.ae = Mat.N; } if (Mat.C || Mat.j) { Mat.F = 2; Mat.N = 255; Mat.C = 0;
      Mat.i = (Mat.l = Mat.V ? 0:Mat.l); while(Mat.i--) { *Mat.r++ = 0; } *Mat.r = 128;
      return; } }  Mat.C |= (Mat.j == 4); if (!Mat.V && Mat.x < Mat.l) { Mat.i = Mat.l - Mat.x;
    do *++Mat.ae = Mat.N; while(--Mat.i); return; } Mat.l = Mat.x; }
void FCSUB(an r, an a, anu l, an c) { if (l--) return FSUB(r, a, l, c);
  return FSUB(r, a, Mat.lb, Mat.B); }

void FMUL(an r, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b; Mat.be = Mat.b;
  Mat.F = Mat.l; Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0;
  Mat.lb = Mat.N; Mat.y = *(Mat.e = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(Mat.F-- && *Mat.ae == Mat.na && !((*--Mat.ae ^ Mat.na) & 128)) { } Mat.i = ++Mat.F;
  while(Mat.N-- && *Mat.e == Mat.nb && !((*--Mat.e ^ Mat.nb) & 128)) { } Mat.j = ++Mat.N;
  while(Mat.F-- && !*Mat.a) { Mat.a++; } Mat.F++; while(Mat.N-- && !*Mat.be) Mat.be++;
  Mat.N++; Mat.t = !(Mat.x | Mat.i) || !(Mat.y | Mat.j); if (!Mat.t && Mat.Nim) {
    Mat.t = (Mat.lb == Mat.j && !Mat.N && Mat.y == 128) ? 2:0;
    Mat.t = (Mat.l == Mat.i && !Mat.F && Mat.x == 128) ? 2:Mat.t; }
  Mat.x = Mat.i; Mat.k = Mat.i; Mat.k += Mat.j; Mat.i -= Mat.F; Mat.j -= Mat.N; Mat.k++;
  Mat.t = Mat.t ? Mat.t:(Mat.x > Mat.k) ? 2:0; Mat.y = 1; Mat.ae = (an)Mat.H; Mat.e = (an)Mat.L;
  if (Mat.F < Mat.N) { Mat.x = Mat.N; Mat.N = Mat.F; Mat.F = Mat.x;
    if (Mat.nb) do Mat.y = !(*Mat.ae++ = ~*Mat.be++ + Mat.y) && Mat.y; while(Mat.x--);
    else { do *Mat.ae++ = *Mat.be++; while(Mat.x--); } Mat.y = 1; Mat.x = Mat.N;
    if (Mat.na) do Mat.y = !(*Mat.e++ = ~*Mat.a++ + Mat.y) && Mat.y; while(Mat.x--);
    else do *Mat.e++ = *Mat.a++; while(Mat.x--); } else { Mat.x = Mat.F;
    if (Mat.na) do Mat.y = !(*Mat.ae++ = ~*Mat.a++ + Mat.y) && Mat.y; while(Mat.x--);
    else { do *Mat.ae++ = *Mat.a++; while(Mat.x--); } Mat.y = 1; Mat.x = Mat.N;
    if (Mat.nb) do Mat.y = !(*Mat.e++ = ~*Mat.be++ + Mat.y) && Mat.y; while(Mat.x--);
    else do *Mat.e++ = *Mat.be++; while(Mat.x--); } Mat.C = (Mat.C != 0); Mat.na ^= Mat.nb;
  Mat.nb = 0; *Mat.e = 0; Mat.N++; if (!Mat.t) { Mat.e = (Mat.ae = Mat.r) + Mat.i + Mat.j;
    *Mat.ae++ = Mat.C; Mat.C = 0; while(Mat.k--) *Mat.ae++ = 0;
    Mat.ae = (an)Mat.H; do { if ((Mat.i = *Mat.ae++)) { Mat.a = (an)Mat.S;
        Mat.be = (an)Mat.L; Mat.j = Mat.N; do *Mat.a++ = *Mat.be++; while(Mat.j--); do {
          Mat.be = (an)Mat.S; Mat.j = Mat.N; Mat.t = 0; if (!(Mat.i & 1)) do { Mat.k = *Mat.be;
            *Mat.be++ = (Mat.k << 1) | Mat.t; Mat.t = (Mat.k & 128) ? 1:0; } while(Mat.j--);
          else { Mat.a = Mat.e; Mat.nb |= Mat.C; Mat.C = 0;
            do { Mat.k = *Mat.be; Mat.x = *Mat.a; Mat.y = (*Mat.a++ = Mat.x + Mat.k + Mat.C);
              Mat.C = (Mat.x > Mat.y) || (Mat.C && Mat.x == Mat.y);
              *Mat.be++ = (Mat.k << 1) | Mat.t; Mat.t = (Mat.k & 128) ? 1:0; } while(Mat.j--); }
          Mat.nb |= Mat.t; } while(Mat.i >>= 1); } Mat.e++; } while(Mat.F--); Mat.F++;
    Mat.t = Mat.nb | Mat.C; Mat.l = Mat.e - Mat.r;
    if ((Mat.N = Mat.na)) { Mat.j = Mat.l; Mat.ae = Mat.r; Mat.nb = 1;
      do { Mat.nb = !(*Mat.ae = ~*Mat.ae + Mat.nb) && Mat.nb; Mat.ae++; } while(Mat.j--); }
    while(*Mat.e-- == Mat.N  && Mat.l && (Mat.Nim ? !((*Mat.e ^ Mat.N) & 128):1)) { Mat.l--; }
    if (*++Mat.e != 128) { return; } Mat.be = Mat.e; Mat.j = Mat.l; while(Mat.j-- && !*--Mat.e);
    if (++Mat.j) { return; } if (Mat.l != 255) { if (Mat.Nim) { Mat.l++; *++Mat.be = Mat.N; }
      return; } Mat.t = 2; }
  Mat.F = (Mat.C = (!Mat.Nim && Mat.t == 2)) ? 1:Mat.t; Mat.N = 0; Mat.N -= (Mat.F == 2);
  Mat.l = Mat.V ? 0:Mat.l; Mat.i = Mat.l; while(Mat.i--) *Mat.r++ = 0; *Mat.r = Mat.N & 128; }
void FCMUL(an r, an a, anu l, an c) { if (l--) return FMUL(r, a, l, c);
  return FMUL(r, a, Mat.lb, Mat.B); }

void FDIV(an r, an e, an a, anu l, an b) { Mat.N = l; Mat.r = r; Mat.a = a; Mat.b = b;
  Mat.F = Mat.l; Mat.x = *(Mat.ae = Mat.a + Mat.l); Mat.na = (Mat.Nim && (Mat.x & 128)) ? 255:0;
  Mat.lb = Mat.N; Mat.y = *(Mat.e = Mat.b + Mat.N); Mat.nb = (Mat.Nim && (Mat.y & 128)) ? 255:0;
  while(Mat.F-- && *Mat.ae == Mat.na && !((*--Mat.ae ^ Mat.na) & 128)) { } Mat.i = ++Mat.F;
  while(Mat.N-- && *Mat.e == Mat.nb && !((*--Mat.e ^ Mat.nb) & 128)) { } Mat.j = ++Mat.N;
  while(Mat.F-- && !*Mat.a) { Mat.a++; } Mat.be = Mat.b; while(Mat.N-- && !*Mat.be) Mat.be++;
  Mat.N++; Mat.F++; Mat.t = !(Mat.x | Mat.i) || !(Mat.y | Mat.j); if (!Mat.t && Mat.Nim) {
    Mat.t = (Mat.lb == Mat.j && !Mat.N && Mat.y == 128) ? 2:0;
    Mat.t = (Mat.l == Mat.i && !Mat.F && Mat.x == 128) ? 2:Mat.t; }
  (void)e; }
void FCDIV(an r, an e, an a, anu l, an c) { if (l--) return FDIV(r, e, a, l, c);
  return FDIV(r, e, a, Mat.lb, Mat.B); }

void FCMP(an a, anu l, an b) { Mat.k = Mat.C; Mat.C = 0; Mat.t = Mat.l; FSUB((an)Mat.S, a, l, b);
  Mat.N -= Mat.C; Mat.l = Mat.t; Mat.C = Mat.k; if (Mat.F == 2) {
    Mat.N = (Mat.F = (Mat.j == 3)) ? 0:(Mat.j == 1) ? Mat.nb:(Mat.j == 2) ? ~Mat.na:~Mat.nb; } }
void FCCMP(an a, anu l, an c) { if (l--) return FCMP(a, l, c); return FCMP(a, Mat.lb, Mat.B); }

anu FEQ(an a, anu l, an c) { if (l--) { Mat.z = Mat.V; Mat.V = 0; Mat.e = c; Mat.u = 0;
    while(!Mat.u && l >= Mat.l) { FCMP(a, Mat.l, Mat.e); Mat.u = Mat.F && !Mat.N;
      Mat.e += 1 + Mat.l; if ((l -= 1 + Mat.l) == 255) break; } Mat.V = Mat.z; return Mat.u; }
  FCMP(a, Mat.lb, Mat.B); return Mat.F; }

anu FGE(an a, anu l, an c) { if (l--) { Mat.z = Mat.V; Mat.V = 0; Mat.e = c; Mat.u = 0;
    while(!Mat.u && l >= Mat.l) { FCMP(a, Mat.l, Mat.e); Mat.u = !Mat.N;
      Mat.e += 1 + Mat.l; if ((l -= 1 + Mat.l) == 255) { break; } if (l < Mat.l) { break; }
      FCMP(a, Mat.l, Mat.e); Mat.u = Mat.u && (Mat.N | Mat.F); Mat.e += 1 + Mat.l;
      if ((l -= 1 + Mat.l) == 255) break; } Mat.V = Mat.z; return Mat.u; }
  FCMP(a, Mat.lb, Mat.B); return !Mat.N; }
