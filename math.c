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
void FSWAP(anu l, an r, an a) { Mat.fa = !(l & 1); Mat.r = r + l; Mat.a = a + l;
  Mat.na = *a++; *r++ = (l) ? *Mat.a--:0; *Mat.r-- = Mat.na; if ((l >>= 1)) {
    while(--l) { Mat.na = *a++; *r++ = *Mat.a--; *Mat.r-- = Mat.na; } if (Mat.fa) *r = *a; } }

void FLD(an r, anu D) { Mat.l = 0;
  Mat.N = Mat.Nim ? (D & 0x80) ? 0xFF:0:0; Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 2:0:1; *r = D; }
void FLVD(an r, anu Dl, anu Dh) { Mat.l = 1; *r++ = Dl; Mat.N = Mat.Nim ? (Dh & 0x80) ? 0xFF:0:0;
  if ((Mat.F = (Dl || Dh) ? (!Dl && Mat.Nim && (Dh == 0x80)) ? 2:0:1)) {
    if (Mat.V) { Mat.l--; *--r = Dh; } return; } *r = Dh;
  if (Mat.V && Dh == Mat.N && !(Mat.Nim && ((Dl ^ Mat.N) & 0x80))) Mat.l--; }
void FMOV(anu l, an r, an a) { Mat.l = l; Mat.e = r; Mat.dr = 0;
  if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.dr |= (*--Mat.r = *--Mat.a); }
  else { while(l--) Mat.dr |= (*r++ = *a++); } *r = *a; Mat.N = Mat.Nim ? (*r & 0x80) ? 0xFF:0:0;
  if ((Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1)) {
    if (Mat.V) { *Mat.e = *r; Mat.l = 0; } return; }
  if (Mat.V) { l = Mat.l;
    while(Mat.l && *r == Mat.N && !(Mat.Nim && ((*(r - 1) ^ Mat.N) & 0x80))) { Mat.l--; r--; }
    if (Mat.Nim && (l - Mat.l) && *r == 0x80) { l = Mat.l; while(l && *--r == 0) l--;
      Mat.l += !l; } } }
void FCOLD(anu f, anu l, an r, an a) { Mat.e = r; Mat.l = ((Mat.dr = l)) ? 2:1;
  while((Mat.dr >>= 1)) { Mat.l <<= 1; } Mat.fb = --Mat.l - l;
  if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.dr |= (*--Mat.r = *--Mat.a); }
  else { while(l--) Mat.dr |= (*r++ = *a++); } *r = *a; Mat.na = (Mat.N = Mat.Nim ? (*r & 0x80) ? 0xFF:0:0);
  if ((Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1)) { Mat.dr = *r; *r = 0;
    Mat.na = 0; } while(Mat.fb--) { *++r = Mat.na; } *r = Mat.F ? Mat.dr:*r; if (f) Fswap(Mat.l, Mat.e); }
anu CONST(anu f, an r, anu l, an c) { Mat.nab = Mat.l;
  if (l--) { if (f) { FSWAP(l, r, c); FMOV(l, r, r); } else FMOV(l, r, c);
    l = Mat.l; Mat.l = Mat.nab; return l; } l++; *r = 0; Mat.F = 1; Mat.N = 0; return 0; }

void FADD(an r, an a, anu l, an b) { Mat.e = r; Mat.C = (Mat.C != 0); Mat.dr = 0; Mat.da = 0; Mat.db = 0;
  Mat.a = a + Mat.l; Mat.na = Mat.Nim ? (*Mat.a & 0x80) ? 0xFF:0:0; Mat.F = Mat.l; Mat.N = l;
  Mat.b = b + l; Mat.nb = Mat.Nim ? (*Mat.b & 0x80) ? 0xFF:0:0; Mat.le = l; l = (Mat.F >= l) ? l:Mat.F;
  while(l-- && !(*a || *b)) { a++; b++; Mat.dr |= (*r++ = Mat.C); Mat.C = 0; Mat.F--; Mat.N--; } l = Mat.N;
  while(Mat.N && *Mat.b == Mat.nb && !(Mat.Nim && (*(Mat.b - 1) ^ Mat.nb) & 0x80)) { Mat.N--; Mat.b--; }
  if (Mat.Nim && l != Mat.N && *Mat.b == 0x80) { l = Mat.N; while(l && !*--Mat.b) { l--; } Mat.N += !l; }
  l = (Mat.F >= Mat.N) ? Mat.N:Mat.F; Mat.F -= l; Mat.N -= l;
  while(l--) { Mat.da |= (Mat.fa = *a); Mat.db |= (Mat.fb = *b); Mat.dr |= (*r = *a++ + *b++ + Mat.C);
    Mat.C = (Mat.fa > *r++) || (Mat.C && Mat.fb == 255); } l = 1;
  if (Mat.F) { Mat.fb = *b; if (!Mat.db && (Mat.Nim && (Mat.fb == 0x80))) l--;
    while(Mat.F--) { Mat.da |= (Mat.fa = *a++); Mat.dr |= (*r = Mat.fa + Mat.fb + Mat.C);
      Mat.C = (Mat.fa > *r++) || (Mat.C && Mat.fb == 255); Mat.fb = Mat.nb; } Mat.fa = *a;
    if (!Mat.da && (Mat.Nim && (Mat.fa == 0x80))) l = 0; }
  else { Mat.fa = *a; if (!Mat.da && (Mat.Nim && (Mat.fa == 0x80))) l--;
    if (Mat.V) { while(Mat.N--) { Mat.db |= (Mat.fb = *b++); Mat.dr |= (*r = Mat.fa + Mat.fb + Mat.C);
        Mat.C = (Mat.fa > *r++) || (Mat.C && Mat.fb == 255); Mat.fa = Mat.na; } Mat.N++;
      Mat.l = Mat.le; } Mat.fb = *b; if (!Mat.db && (Mat.Nim && (Mat.fb == 0x80))) l = 0; }
  if (l) { *r = Mat.fa + Mat.fb + Mat.C; Mat.C = (Mat.fa > *r) || (Mat.C && Mat.fb == 255);
    if (Mat.Nim) Mat.C = ((Mat.na ^ *r) & 0x80) || (!Mat.dr && *r == 0x80);
    if (Mat.V && Mat.C && Mat.l != 0xFF) { Mat.dr |= *r++; Mat.l++; *r = Mat.Nim ? Mat.na:Mat.C;
      Mat.C = 0; } Mat.C = Mat.C ? 1:(Mat.N != 0); Mat.N = Mat.Nim ? (*r & 0x80) ? 0xFF:0:0;
    if ((Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1)) {
      if (Mat.F == 1) { Mat.l = Mat.V ? 0:Mat.l; return; } }
    else if (!(Mat.Nim && Mat.na == Mat.nb && Mat.N != Mat.na)) return; }
  if (Mat.V) Mat.l = 0; else { l = Mat.l; while(l--) *Mat.e++ = 0; } *Mat.e = 0x80; Mat.F = 2;
  Mat.N = 0xFF; Mat.C = 1; }

void FSUB(an r, an a, anu l, an b) { Mat.e = r; Mat.C = (Mat.C != 0); Mat.dr = 0; Mat.da = 0; Mat.db = 0;
  Mat.a = a + Mat.l; Mat.na = Mat.Nim ? (*Mat.a & 0x80) ? 0xFF:0:0; Mat.F = Mat.l; Mat.N = l;
  Mat.b = b + l; Mat.nb = Mat.Nim ? (*Mat.b & 0x80) ? 0xFF:0:0; Mat.le = l; l = (Mat.F >= l) ? l:Mat.F;
  while(l-- && !(*a || *b)) { a++; b++; Mat.dr |= (*r++ = Mat.C ? 0xFF:0); Mat.F--; Mat.N--; } l = Mat.N;
  while(Mat.N && *Mat.b == Mat.nb && !(Mat.Nim && (*(Mat.b - 1) ^ Mat.nb) & 0x80)) { Mat.N--; Mat.b--; }
  if (Mat.Nim && l != Mat.N && *Mat.b == 0x80) { l = Mat.N; while(l && !*--Mat.b) { l--; } Mat.N += !l; }
  l = (Mat.F >= Mat.N) ? Mat.N:Mat.F; Mat.F -= l; Mat.N -= l;
  while(l--) { Mat.da |= (Mat.fa = *a); Mat.db |= (Mat.fb = *b); Mat.dr |= (*r = *a++ - *b++ - Mat.C);
    Mat.C = (Mat.fa < *r++) || (Mat.C && Mat.fb == 255); } l = 1;
  if (Mat.F) { Mat.fb = *b; if (!Mat.db && (Mat.Nim && (Mat.fb == 0x80))) l--;
    while(Mat.F--) { Mat.da |= (Mat.fa = *a++); Mat.dr |= (*r = Mat.fa - Mat.fb - Mat.C);
      Mat.C = (Mat.fa < *r++) || (Mat.C && Mat.fb == 255); Mat.fb = Mat.nb; } Mat.fa = *a;
    if (!Mat.da && (Mat.Nim && (Mat.fa == 0x80))) l = 0; }
  else { Mat.fa = *a; if (!Mat.da && (Mat.Nim && (Mat.fa == 0x80))) l--;
    if (Mat.V) { while(Mat.N--) { Mat.db |= (Mat.fb = *b++); Mat.dr |= (*r = Mat.fa - Mat.fb - Mat.C);
        Mat.C = (Mat.fa < *r++) || (Mat.C && Mat.fb == 255); Mat.fa = Mat.na; } Mat.N++;
      Mat.l = Mat.le; } Mat.fb = *b; if (!Mat.db && (Mat.Nim && (Mat.fb == 0x80))) l = 0; }
  if (l) { *r = Mat.fa - Mat.fb - Mat.C; Mat.C = (Mat.fa < *r) || (Mat.C && Mat.fb == 255);
    if (Mat.Nim) Mat.C = (((Mat.na ^ Mat.nb) & 0x80) && ((Mat.na ^ *r) & 0x80)) || (!Mat.dr && *r == 0x80);
    if (Mat.V && Mat.C && Mat.l != 0xFF) { Mat.dr |= *r++; Mat.l++; *r = Mat.Nim ? Mat.na:Mat.C;
      Mat.C = 0; } Mat.C = Mat.C ? 1:(Mat.N != 0); Mat.N = Mat.Nim ? (*r & 0x80) ? 0xFF:0:0;
    if ((Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1)) {
      if (Mat.F == 1) { Mat.l = Mat.V ? 0:Mat.l; return; } }
    else if (!(Mat.Nim && Mat.na != Mat.nb && Mat.N != Mat.na)) return; }
  if (Mat.V) Mat.l = 0; else { l = Mat.l; while(l--) *Mat.e++ = 0; } *Mat.e = 0x80; Mat.F = 2;
  Mat.N = 0xFF; Mat.C = 1; }

void FMUL(an r, an a, anu l, an b) { Mat.le = l; (void)r; (void)a; (void)b;
  l = Mat.l; Mat.C = (l > (Mat.l += 1 + Mat.le)); }

void FDIV(an r, an e, an a, anu l, an b) { Mat.le = l; (void)r; (void)a; (void)b; (void)e; }

void FADDc(an r, an a, anu l, an c) {
  if (!l) FMOV(Mat.l, r, a); else FADD(r, a, --l, c); }
void FSUBc(an r, an a, anu l, an c) {
  if (!l) FMOV(Mat.l, r, a); else FSUB(r, a, --l, c); }
void FMULc(an r, an a, anu l, an c) {
  if (!l) FMOV(Mat.l, r, a); else FMUL(r, a, --l, c); }
void FDIVc(an r, an e, an a, anu l, an c) {
  if (!l) { FMOV(Mat.l, r, a); *e = 0; Mat.le = 0; Mat.Ne = 0; Mat.Fe = 1; }
  else FDIV(r, e, a, --l, c); }
