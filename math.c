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
  Mat.da = *a++; *r++ = (l) ? *Mat.a--:Mat.da; *Mat.r-- = Mat.da; l >>= 1;
  while(l--) { Mat.da = *a++; *r++ = *Mat.a--; *Mat.r-- = Mat.da; } }

void FLD(an r, anu D) { Mat.N = Mat.Nim ? (D & 0x80) ? 0xFF:0:0;
  Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 2:0:1; *r = D; }
void FLVD(an r, anu Dl, anu Dh) { *r++ = Dl; Mat.N = Mat.Nim ? (Dh & 0x80) ? 0xFF:0:0;
  Mat.F = (Dl || Dh) ? (!Dl && Mat.Nim && (Dh == 0x80)) ? 2:0:1; *r = Dh; }
void FMOV(anu l, an r, an a) { Mat.r = r; Mat.dr = 0;
  if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.dr |= (*--Mat.r = *--Mat.a); }
  else { while(l--) Mat.dr |= (*r++ = *a++); } *r = *a; Mat.N = Mat.Nim ? (*r & 0x80) ? 0xFF:0:0;
  Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1; }
anu FCOLD(anu f, anu l, an r, an a) { Mat.r = r; Mat.x = ((Mat.dr = l)) ? 2:1;
  while((Mat.dr >>= 1)) { Mat.x <<= 1; } Mat.fb = --Mat.x - l; 
  if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.dr |= (*--Mat.r = *--Mat.a); }
  else { while(l--) Mat.dr |= (*r++ = *a++); } *r = *a; Mat.y = (Mat.N = (Mat.Nim && (*r & 0x80)) ? 0xFF:0);
  if ((Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1)) { Mat.dr = *r; *r = 0;
    Mat.y = 0; } while(Mat.fb--) { *++r = Mat.y; } *r = Mat.F ? Mat.dr:*r; if (f) Fswap(Mat.l, Mat.r);
  return Mat.x; }
anu CONST(anu f, an r, anu l, an c) { if (!l--) { l++; Mat.F = 1; Mat.N = l; Mat.l = l; *r = l; }
  else { if (f) { FSWAP(l, r, c); } else FMOV(l, r, c); } return l; }

void FADD(an r, an a, anu l, an b) { Mat.r = r; Mat.C = (Mat.C != 0); Mat.da = 0; Mat.db = 0; Mat.dr = 0;
  Mat.fa = *(Mat.a = a + Mat.l); Mat.na = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF:0; Mat.F = Mat.l;
  Mat.fb = *(Mat.b = b + l); Mat.nb = (Mat.Nim && (Mat.fb & 0x80)) ? 0xFF:0; Mat.N = l; Mat.le = l;
  while(Mat.F-- && (*Mat.a-- == Mat.na) && !(Mat.Nim | ((*Mat.a ^ Mat.na) & 0x80))) { } Mat.F++;
  while(Mat.N-- && (*Mat.b-- == Mat.nb) && !(Mat.Nim | ((*Mat.b ^ Mat.nb) & 0x80))) { } Mat.N++;
  while(Mat.F && Mat.N && !(*a | *b)) { Mat.dr |= (*r++ = Mat.C); Mat.C = 0; a++; b++; --Mat.F; --Mat.N; }
  if (Mat.F > Mat.N) { Mat.F -= Mat.N; while(Mat.N--) { Mat.da |= (Mat.x = *a++); Mat.db |= (Mat.y = *b++);
      Mat.dr |= (l = (*r++ = Mat.x + Mat.y + Mat.C)); Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); }
    Mat.y = *b; while(Mat.F--) { Mat.da |= (Mat.x = *a++); Mat.dr |= (l = (*r++ = Mat.x + Mat.y + Mat.C));
      Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); Mat.y = Mat.nb; } Mat.F++; Mat.x = *a; }
  else { Mat.N -= Mat.F; while(Mat.F--) { Mat.da |= (Mat.x = *a++); Mat.db |= (Mat.y = *b++);
      Mat.dr |= (l = (*r++ = Mat.x + Mat.y + Mat.C)); Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); }
    Mat.F = r - Mat.r; Mat.F = Mat.l - Mat.F; Mat.F = (Mat.F > Mat.N) ? Mat.N:Mat.F; Mat.N -= Mat.F;
    Mat.x = *a; while(Mat.F--) { Mat.db |= (Mat.y = *b++); Mat.dr |= (l = (*r++ = Mat.x + Mat.y + Mat.C));
      Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l); Mat.x = Mat.na; } Mat.y = *b; if (Mat.V) {
      Mat.F = (Mat.N != 0); while(Mat.N--) { Mat.db |= (Mat.y = *b++);
      Mat.dr |= (l = (*r++ = Mat.x + Mat.y + Mat.C)); Mat.C = (Mat.x > l) || (Mat.C && Mat.x == l);
      Mat.x = Mat.na; } Mat.y = *b; } } *r = Mat.x + Mat.y + Mat.C;
  Mat.C = (Mat.x > *r) || (Mat.C && Mat.x == *r); if (!Mat.V) { l = r - Mat.r;
    if ((l = Mat.l - l)) { Mat.N = (Mat.Nim) ? (*r & 0x80) ? 0xFF:0:0; Mat.Ne = Mat.N ^ Mat.C; Mat.C = 0;
      while(l--) { Mat.db |= (*r++ = Mat.Ne); Mat.Ne = Mat.N; } r--; } } Mat.C = Mat.C | Mat.F;
  if (Mat.da || !(Mat.Nim && (Mat.fa == 0x80))) { if (Mat.db || !(Mat.Nim && (Mat.fb == 0x80))) {
      Mat.C = Mat.Nim ? ((!(Mat.na ^ Mat.nb) && ((Mat.na ^ *r) & 0x80)) || (!Mat.dr && *r == 0x80)):Mat.C;
      if (Mat.V && Mat.C && Mat.l != 0xFF) { Mat.dr |= *r++; Mat.l++; *r = Mat.Nim ? Mat.na:Mat.C;
      Mat.C = 0; } Mat.N = (Mat.Nim) ? (*r & 0x80) ? 0xFF:0:0;
      if ((Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1)) {
        if (Mat.F == 1) { Mat.l = Mat.V ? 0:Mat.l; return; } }
      if (!Mat.F && !(Mat.Nim && Mat.na == Mat.nb && Mat.N != Mat.na)) return; } }
  if (Mat.V) Mat.l = 0; else { l = Mat.l; while(l--) *Mat.r++ = 0; } *Mat.r = 0x80; Mat.F = 2;
  Mat.N = 0xFF; Mat.C = 1; }

void FSUB(an r, an a, anu l, an b) { Mat.r = r; Mat.C = (Mat.C != 0); Mat.da = 0; Mat.db = 0; Mat.dr = 0;
  Mat.fa = *(Mat.a = a + Mat.l); Mat.na = (Mat.Nim && (Mat.fa & 0x80)) ? 0xFF:0; Mat.F = Mat.l;
  Mat.fb = *(Mat.b = b + l); Mat.nb = (Mat.Nim && (Mat.fb & 0x80)) ? 0xFF:0; Mat.N = l; Mat.le = l;
  while(Mat.F-- && (*Mat.a-- == Mat.na) && !(Mat.Nim | ((*Mat.a ^ Mat.na) & 0x80)));
  while(Mat.N-- && (*Mat.b-- == Mat.nb) && !(Mat.Nim | ((*Mat.b ^ Mat.nb) & 0x80)));
  Mat.F++; Mat.N++; l = Mat.C ? 0xFF:0; while(Mat.F && Mat.N && !(*a | *b)) { Mat.dr |= (*r++ = l);
    a++; b++; --Mat.F; --Mat.N; }
  if (Mat.F > Mat.N) { Mat.F -= Mat.N; while(Mat.N--) { Mat.da |= (Mat.x = *a++); Mat.db |= (Mat.y = *b++);
      Mat.dr |= (l = (*r++ = Mat.x - Mat.y - Mat.C)); Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); }
    Mat.y = *b; while(Mat.F--) { Mat.da |= (Mat.x = *a++); Mat.dr |= (l = (*r++ = Mat.x - Mat.y - Mat.C));
      Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); Mat.y = Mat.nb; } Mat.F++; Mat.x = *a; }
  else { Mat.N -= Mat.F; while(Mat.F--) { Mat.da |= (Mat.x = *a++); Mat.db |= (Mat.y = *b++);
      Mat.dr |= (l = (*r++ = Mat.x - Mat.y - Mat.C)); Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); }
    Mat.F = r - Mat.r; Mat.F = Mat.l - Mat.F; Mat.F = (Mat.F > Mat.N) ? Mat.N:Mat.F; Mat.N -= Mat.F;
    Mat.x = *a; while(Mat.F--) { Mat.db |= (Mat.y = *b++); Mat.dr |= (l = (*r++ = Mat.x - Mat.y - Mat.C));
      Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l); Mat.x = Mat.na; } Mat.y = *b; if (Mat.V) {
      Mat.F = (Mat.N != 0); while(Mat.N--) { Mat.db |= (Mat.y = *b++);
      Mat.dr |= (l = (*r++ = Mat.x - Mat.y - Mat.C)); Mat.C = (Mat.x < l) || (Mat.C && Mat.x == l);
      Mat.x = Mat.na; } Mat.y = *b; } } *r = Mat.x - Mat.y - Mat.C;
  Mat.C = (Mat.x < *r) || (Mat.C && Mat.x == *r); if (!Mat.V) { l = r - Mat.r;
    if ((l = Mat.l - l)) { Mat.N = (Mat.Nim) ? (*r & 0x80) ? 0xFF:0:0; Mat.Ne = Mat.N ^ Mat.C; Mat.C = 0;
      while(l--) { Mat.db |= (*r++ = Mat.Ne); Mat.Ne = Mat.N; } r--; } } Mat.C = Mat.C | Mat.F;
  if (Mat.da || !(Mat.Nim && (Mat.fa == 0x80))) { if (Mat.db || !(Mat.Nim && (Mat.fb == 0x80))) {
      Mat.C = Mat.Nim ? (((Mat.na ^ Mat.nb) && ((Mat.na ^ *r) & 0x80)) || (!Mat.dr && *r == 0x80)):Mat.C;
      if (Mat.V && Mat.C && Mat.l != 0xFF) { Mat.dr |= *r++; Mat.l++; *r = Mat.Nim ? Mat.na:Mat.C;
        Mat.C = 0; } Mat.N = (Mat.Nim) ? (*r & 0x80) ? 0xFF:0:0;
      if ((Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1)) {
        if (Mat.F == 1) { Mat.l = Mat.V ? 0:Mat.l; return; } }
      if (!Mat.F && !(Mat.Nim && Mat.na != Mat.nb && Mat.N != Mat.na)) return; } }
  if (Mat.V) Mat.l = 0; else { l = Mat.l; while(l--) *Mat.r++ = 0; } *Mat.r = 0x80; Mat.F = 2;
  Mat.N = 0xFF; Mat.C = 1; }

void FMUL(an r, an a, anu l, an b) { Mat.r = r; Mat.C = (Mat.C != 0); Mat.da = 0; Mat.db = 0; Mat.dr = 0;
  Mat.fa = *(Mat.a = a + Mat.l); Mat.na = Mat.Nim ? (Mat.fa & 0x80) ? 0xFF:0:0; Mat.F = Mat.l;
  Mat.fb = *(Mat.b = b + l); Mat.nb = Mat.Nim ? (Mat.fb & 0x80) ? 0xFF:0:0; Mat.N = l; Mat.le = l;
  while(Mat.F && *Mat.a == Mat.na && !(Mat.Nim && (*(Mat.a - 1) ^ Mat.na) & 0x80)) { --Mat.a; --Mat.F; }
  while(Mat.N && *Mat.b == Mat.nb && !(Mat.Nim && (*(Mat.b - 1) ^ Mat.nb) & 0x80)) { --Mat.b; --Mat.N; }
  while(Mat.F && Mat.N && !(*a | *b)) { Mat.dr |= (*r++ = Mat.C); Mat.C = 0; a++; b++; --Mat.F; --Mat.N; }
  
  }

void FDIV(an r, an e, an a, anu l, an b) { (void)l; (void)r; (void)a; (void)b; (void)e; }

void FADDc(an r, an a, anu l, an c) {
  if (!l) FMOV(Mat.l, r, a); else FADD(r, a, --l, c); }
void FSUBc(an r, an a, anu l, an c) {
  if (!l) FMOV(Mat.l, r, a); else FSUB(r, a, --l, c); }
void FMULc(an r, an a, anu l, an c) {
  if (!l) FMOV(Mat.l, r, a); else FMUL(r, a, --l, c); }
void FDIVc(an r, an e, an a, anu l, an c) {
  if (!l) { FMOV(Mat.l, r, a); *e = 0; Mat.le = 0; Mat.Ne = 0; Mat.Fe = 1; }
  else FDIV(r, e, a, --l, c); }
