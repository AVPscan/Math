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

void FLD(an r, anu D) { Mat.lar = 0;
  Mat.N = Mat.Nim ? (D & 0x80) ? 0xFF:0:0; Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 2:0:1; *r = D; }
void FLVD(an r, anu Dl, anu Dh) { Mat.lar = 1; *r++ = Dl; Mat.N = Mat.Nim ? (Dh & 0x80) ? 0xFF:0:0;
  if ((Mat.F = (Dl || Dh) ? (!Dl && Mat.Nim && (Dh == 0x80)) ? 2:0:1)) { Mat.lar--; r--; } *r = Dh;
  if (Mat.V && Mat.lar && Dh == Mat.N && !(Mat.Nim && ((Dl ^ Mat.N) & 0x80))) Mat.lar--; }
void FMOV(anu l, an r, an a) { Mat.lar = l; Mat.e = r; Mat.dr = 0;
  if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.dr |= (*--Mat.r = *--Mat.a); }
  else { while(l--) Mat.dr |= (*r++ = *a++); } *r = *a; Mat.N = Mat.Nim ? (*r & 0x80) ? 0xFF:0:0;
  if ((Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1)) { *Mat.e = *r; Mat.lar = 0; }
  else if (Mat.V) {
	l = Mat.lar; while(Mat.lar && *r == Mat.N && !(Mat.Nim && ((*(r - 1) ^ Mat.N) & 0x80))) { Mat.lar--; r--; }
	if (Mat.Nim && (l - Mat.lar) && *r == 0x80) { l = Mat.lar; while(l && *--r == 0) { l--; } Mat.lar += !l; } } }
void FCOLD(anu l, an r, an a) { Mat.e = r; Mat.lar = ((Mat.dr = l)) ? 2:1;
  while((Mat.dr >>= 1)) { Mat.lar <<= 1; } Mat.fb = --Mat.lar - l;
  if (r > a) { Mat.r = (r += l); Mat.a = (a += l); while(l--) Mat.dr |= (*--Mat.r = *--Mat.a); }
  else { while(l--) Mat.dr |= (*r++ = *a++); } *r = *a; Mat.N = Mat.Nim ? (*r & 0x80) ? 0xFF:0:0;
  if ((Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1)) { Mat.dr = *r; *r = 0; }
  while(Mat.fb--) { *++r = Mat.N; } *r = Mat.F ? Mat.dr : *r; if (Mat.Be) Fswap(Mat.lar, Mat.e) }

void FADD(an r, an a, anu l, an b) { Mat.e = r; Mat.C = (Mat.C != 0); Mat.dr = 0; Mat.da = 0; Mat.db = 0;
  Mat.de = Mat.lar; Mat.a = a + Mat.lar; Mat.na = Mat.Nim ? (*Mat.a & 0x80) ? 0xFF:0:0;
  Mat.lbe = l; Mat.b = b + Mat.lbe; Mat.nb = Mat.Nim ? (*Mat.b & 0x80) ? 0xFF:0:0; if (Mat.V) {
    while(Mat.lar-- && *Mat.a-- == Mat.na && !(Mat.Nim && ((*Mat.a ^ Mat.na) & 0x80)));
    while(Mat.lbe-- && *Mat.b-- == Mat.nb && !(Mat.Nim && ((*Mat.b ^ Mat.nb) & 0x80)));
    Mat.lar++; Mat.lbe++; if (Mat.Nim) {
	  if ((Mat.de - Mat.lar) && *Mat.a == 0x80) { l = Mat.lar; while(l-- && *Mat.a-- == 0) { } Mat.lar += !++l; }
	  if ((l - Mat.lbe) && *Mat.b == 0x80) { l = Mat.lbe; while(l-- && *Mat.b-- == 0) { } Mat.lbe += !++l; } }
    l = Mat.lbe;
    if (Mat.lar < l) { Mat.a = b; b = a; a = Mat.a; l = Mat.lar; Mat.lar = Mat.lbe; } Mat.N = Mat.lar - l;
    while(l--) { Mat.da |= (Mat.fa = *a); Mat.db |= (Mat.fb = *b); Mat.dr |= (*r = *a++ + *b++ + Mat.C);
	  Mat.C = (Mat.fa > *r++) || (Mat.C && Mat.fb == 255); } Mat.fb = *b;
    if (Mat.db || !(Mat.Nim && (*b == 0x80))) {
      while(Mat.N--) { Mat.da |= (Mat.fa = *a); Mat.dr |= (*r = *a++ + Mat.fb + Mat.C);
	    Mat.C = (Mat.fa > *r++) || (Mat.C && Mat.fb == 255); Mat.fb = Mat.nb; }
      if (Mat.da || !(Mat.Nim && (*a == 0x80))) { l = *a + Mat.fb + Mat.C;
		Mat.C = (*a > l) || (Mat.C && Mat.fb == 255); *r = l;
        Mat.C = ((Mat.Nim ? (((Mat.na & 0x80) ^ (l & 0x80)) || (l == 0x80 && !Mat.dr)) : Mat.C) != 0);
        if (Mat.C && Mat.na == Mat.nb && Mat.lar != 0xFF) { Mat.dr |= *r++; *r = Mat.Nim ? Mat.na : Mat.C;
	      Mat.lar++; Mat.C--; } Mat.N = Mat.Nim ? (*r & 0x80) ? 0xFF:0:0;
        if ((Mat.F = (Mat.dr || *r) ? (Mat.Nim && !Mat.dr && (*r == 0x80)) ? 2:0:1)) {
		  Mat.lar = 0; Mat.C = (*Mat.e = *r) ? 1:Mat.C; return; }
        if (!(Mat.Nim && Mat.na == Mat.nb && Mat.N != Mat.na)) return; } }
	Mat.lar = 0; *Mat.e = 0xFF; Mat.F = 2; Mat.N = 0xFF; Mat.C = 1; return; }
  Mat.de = Mat.lar;
  if (Mat.lar < l) { Mat.a = b; b = a; a = Mat.a; l = Mat.lar; Mat.lar = Mat.lbe; } Mat.N = Mat.lar - l;
  while(l--) { Mat.da |= (Mat.fa = *a); Mat.db |= (Mat.fb = *b); Mat.dr |= (*r = *a++ + *b++ + Mat.C);
	Mat.C = (Mat.fa > *r++) || (Mat.C && Mat.fb == 255); } Mat.fb = *b;
  if (Mat.db || !(Mat.Nim && (*b == 0x80))) {
    while(Mat.N--) { Mat.da |= (Mat.fa = *a); Mat.dr |= (*r = *a++ + Mat.fb + Mat.C);
	  Mat.C = (Mat.fa > *r++) || (Mat.C && Mat.fb == 255); Mat.fb = Mat.nb; }
    if (Mat.da || !(Mat.Nim && (*a == 0x80))) { l = *a + Mat.fb + Mat.C;
	  Mat.C = (*a > l) || (Mat.C && Mat.fb == 255); *r = l; Mat.N = Mat.Nim ? (l & 0x80) ? 0xFF:0:0;
	  Mat.C = ((Mat.Nim ? (((Mat.na & 0x80) ^ (l & 0x80)) || (l == 0x80 && !Mat.dr)) : Mat.C) != 0);
      if ((Mat.F = (Mat.dr || l) ? (Mat.Nim && !Mat.dr && (l == 0x80)) ? 2:0:1)) {
		Mat.C = (l) ? 1:Mat.C; return; }
	  if (!(Mat.Nim && Mat.na == Mat.nb && Mat.N != Mat.na)) return; } }
  Mat.lar = Mat.de; while(Mat.de--) { *Mat.e++ = 0; } *Mat.e = 0xFF; Mat.F = 2; Mat.N = 0xFF; Mat.C = 1; }

void FSUB(an r, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b; }
void FMUL(an r, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b;
  l = Mat.lar; Mat.C = (l > (Mat.lar += 1 + Mat.lbe)); }
void FDIV(an r, an e, an a, anu l, an b) { Mat.lbe = l; (void)r; (void)a; (void)b; (void)e; }

void FADDc(an r, an a, anu l, an c) {
  if (!l) FMOV(Mat.lar, r, a); else FADD(r, a, --l, c); }
void FSUBc(an r, an a, anu l, an c) {
  if (!l) FMOV(Mat.lar, r, a); else FSUB(r, a, --l, c); }
void FMULc(an r, an a, anu l, an c) {
  if (!l) FMOV(Mat.lar, r, a); else FMUL(r, a, --l, c); }
void FDIVc(an r, an e, an a, anu l, an c) {
  if (!l) { FMOV(Mat.lar, r, a); *e = 0; Mat.lbe = 0; Mat.Ne = 0; Mat.Fe = 1; } else FDIV(r, e, a, --l, c); }
