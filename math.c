/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include "sys.h"

Cache Mat = {0};

void _MatInit (anu x, anu y, an r, anu c, an a) { do { *r-- = 0; } while(--x); if (c) { c = (c > y) ? y : c; do *++r = *a++; while(--c); } }

void Fld (an r, anu D) { Mat.l = 1; Mat.cl = 0; *r = D;
  Mat.N = (Mat.Nim && (D & 0x80)) ? 0xFF : 0; Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 1 : 0 : 1; }
void Flvd (an r, anu Dl, anu Dh) { Mat.l = 2; Mat.cl = 0; *r++ = Dl; Mat.N = (Mat.Nim && (Dh & 0x80)) ? 0xFF : 0;
  if ((Mat.F = (Dh || Dl) ? (Mat.Nim && (Dh == 0x80) && !Dl) ? 1 : 0 : 1)) { Mat.l--; r--; } *r = Dh; }
void Fmov (anu lb, an r, an b) { Mat.l = lb; Mat.cl = 0; Mat.a = r; Mat.dr = 0;
  if (r <= b) while(lb--) Mat.dr |= (*r++ = *b++);
  else { Mat.r = (r += lb); Mat.b = (b += lb); while(lb--) Mat.dr |= (*--Mat.r = *--Mat.b); }
  Mat.N = (((*r = *b) & 0x80) && Mat.Nim) ? 0xFF : 0;
  if ((Mat.F = (*r || Mat.dr) ? (Mat.Nim && (*r == 0x80) && !Mat.dr) ? 1 : 0 : 1)) { *Mat.a = *r; Mat.l = 1; } }
void Fswap (anu lb, an r, an b) { Mat.r = r + lb; Mat.b = b + lb; Mat.fb = !(lb & 1); Mat.N = *b++; Mat.F = (lb++) ? *Mat.b : 0;
  *r++ = Mat.F; *Mat.r-- = Mat.N; if ((lb = (lb) ? (lb >> 1) : 0x80)) {
    while(--lb) { Mat.F |= (Mat.db = *--Mat.b); Mat.F |= (Mat.dr = *b++); *r++ = Mat.db; *Mat.r-- = Mat.dr; }
    if (Mat.fb) Mat.F |= (*r = *b); }
  Mat.F = (Mat.N || Mat.F) ? (Mat.Nim && (Mat.N == 0x80) && !Mat.F) ? 1 : 0 : 1; Mat.N = (Mat.Nim && (Mat.N & 0x80)) ? 0xFF : 0; }
void Fvikara (anu lb, an r, an b) { Mat.C = 0; Mat.cl = (Mat.cl != 0); (void)*r; (void)*b;
  if ((Mat.fa = Mat.cl - (Mat.l < (Mat.fb = Mat.l - lb))) == 0xFF) { Mat.fb = lb - Mat.l; }
  else {
    
    } }
void FCold (anu lb, an r, an b) { Mat.cl = 0; Mat.lre = 1; if ((Mat.l = lb)) do Mat.lre <<= 1; while((Mat.l >>= 1));
  Mat.l = --Mat.lre; Fvikara(lb, r, b); Mat.l = lb; if (Mat.Be) Fswap(Mat.lre, r, r); }

void FADD (anu l, an r, an a, an b) {
  if ((Mat.lre = l)) { Mat.F = 0; Mat.N = 0; Mat.C = (Mat.C != 0); Mat.N = !((*a ^ *b) & 0x80); Mat.dr = 0;
    if (Mat.Nim) { Mat.fa = (*a == 0x80); Mat.fb = (*b == 0x80); if (Mat.fa || Mat.fb) { Mat.a = a; Mat.b = b;
      while(--Mat.lre && (Mat.fa || Mat.fb)) { Mat.fa = (Mat.fa) ? (*++Mat.a == 0) : Mat.fa; Mat.fb = (Mat.fb) ? (*++Mat.b == 0) : Mat.fb; }
      if (!Mat.lre && (Mat.fa || Mat.fb)) { Mat.F++; Mat.N--; *r++ = 0x80; while(--l) { *r++ = 0; } return; } Mat.lre = l; } }
  r += l; a += l; b += l; while(--l) { Mat.da = *--a; Mat.dr |= (*--r = Mat.da + *--b + Mat.C); Mat.C = (*r < Mat.da); }
  Mat.da = *--a; *--r = Mat.da + *--b + Mat.C; Mat.C = (*r < Mat.da); Mat.db = *r; if (Mat.Nim) {
    if ((!Mat.dr && *r == 0x80) || (((Mat.db ^ *a) & 0x80) && Mat.N)) { Mat.F++; Mat.N--; *r++ = 0x80; while(--Mat.lre) *r++ = 0; }
    else { Mat.N = (*r & 0x80) ? 0xFF : 0; } Mat.C = 0; } if (!Mat.dr && !Mat.db) { Mat.F++; Mat.N = 0; } } }

void FSUB (anu l, an r, an a, an b) {
  if ((Mat.lre = l)) { Mat.F = 0; Mat.N = 0; Mat.C = (Mat.C != 0); Mat.N = !((*a ^ ~*b) & 0x80); Mat.dr = 0;
    if (Mat.Nim) { Mat.fa = (*a == 0x80); Mat.fb = (*b == 0x80); if (Mat.fa || Mat.fb) { Mat.a = a; Mat.b = b;
      while(--Mat.lre && (Mat.fa || Mat.fb)) { Mat.fa = (Mat.fa) ? (*++Mat.a == 0) : Mat.fa; Mat.fb = (Mat.fb) ? (*++Mat.b == 0) : Mat.fb; }
      if (!Mat.lre && (Mat.fa || Mat.fb)) { Mat.F++; Mat.N--; *r++ = 0x80; while(--l) { *r++ = 0; } return; } Mat.lre = l; } }
  r += l; a += l; b += l; while(--l) { Mat.da = *--a; Mat.dr |= (*--r = Mat.da - *--b - Mat.C); Mat.C = (*r > Mat.da); }
  Mat.da = *--a; *--r = Mat.da - *--b - Mat.C; Mat.C = (*r > Mat.da); Mat.db = *r; if (Mat.Nim) {
    if ((!Mat.dr && *r == 0x80) || (((Mat.db ^ *a) & 0x80) && Mat.N)) { Mat.F++; Mat.N--; *r++ = 0x80; while(--Mat.lre) *r++ = 0; }
    else { Mat.N = (*r & 0x80) ? 0xFF : 0; } Mat.C = 0; } if (!Mat.dr && !Mat.db) { Mat.F++; Mat.N = 0; } } }

void FMUL (anu l, an r, an a, an b) {
  if (l) { Mat.F = 0; Mat.na = (Mat.Nim && *a & 0x80) ? 0xFF : 0; Mat.nb = (Mat.Nim && *b & 0x80) ? 0xFF : 0;
    Mat.N = Mat.na ^ Mat.nb; Mat.a = &Mat.Ho.l; Mat.b = &Mat.Lo.l; Mat.l = l; Mat.cl = ((Mat.l += l) < l);
    Mat.fa = 0; Mat.fb = 0; Mat.da = 1; Mat.db = 1; Mat.r = r; r += l; Mat.re = r + l; a += l; b += l;
    do { Mat.fa = (*--a) ? (Mat.fa) ? Mat.fa : l : Mat.fa; Mat.fb = (*--b) ? (Mat.fb) ? Mat.fb : l : Mat.fb;
      Mat.da = (Mat.fa) ? (Mat.na) ? !(*Mat.a++ = ~*a + Mat.da) : (*Mat.a++ = *a) : Mat.da;
      Mat.db = (Mat.fb) ? (Mat.nb) ? !(*Mat.b++ = ~*b + Mat.db) : (*Mat.b++ = *b) : Mat.db; *--r = 0; *--Mat.re = 0; } while(--l);
    Mat.da = Mat.a - &Mat.Ho.l; Mat.db = Mat.b - &Mat.Lo.l; Mat.re = Mat.r + Mat.fa + Mat.fb; if (Mat.da < 2 || Mat.db < 2) {
      if (!Mat.da || !Mat.db) { Mat.N = 0; Mat.F++; return; }
      if (Mat.Nim && (*(Mat.a - 1) == 0x80 || *(Mat.b - 1) == 0x80)) { Mat.F++; *r = 0x80; Mat.N = 0xFF; return; } } Mat.da = 0; Mat.db = 0;
    do { Mat.fa -= ((Mat.da = (Mat.da) ? Mat.da : (*--Mat.a))) ? 0 : 1; Mat.fb -= ((Mat.db = (Mat.db) ? Mat.db : (*--Mat.b))) ? 0 : 1; }
    while(!(Mat.da && Mat.db)); Mat.da = *Mat.a; Mat.db = *Mat.b; Mat.a = &Mat.Ho.l; Mat.b = &Mat.Lo.l;
    if (Mat.fb > Mat.fa || (Mat.fb == Mat.fa && Mat.db > Mat.da)) { Mat.a = Mat.b; Mat.b = &Mat.Ho.l; l = Mat.fa;
      Mat.fa = Mat.fb; Mat.fb = l; } *(Mat.b + Mat.fb++) = 0; r = Mat.re;
    do { if ((Mat.da = *Mat.a++)) { a = &Mat.Sr.l; b = Mat.b; l = Mat.fb; do *a++ = *b++; while(--l);
        do { Mat.nb = 0; b = &Mat.Sr.l; l = Mat.fb; if (!(Mat.da & 1)) do { Mat.dr = (*b << 1) + Mat.nb;
            Mat.nb = ((*b & 0x80) == 0x80); *b++ = Mat.dr; } while(--l);
          else { a = r; Mat.na = 0; do { Mat.dr = *--a; *a += *b + Mat.na; Mat.na = (*a < Mat.dr);
            Mat.dr = (*b << 1) + Mat.nb; Mat.nb = ((*b & 0x80) == 0x80); *b++ = Mat.dr; } while(--l); }
          } while(Mat.da >>= 1); } --r; } while(--Mat.fa);
    if (Mat.N) { Mat.dr = 1; do { Mat.da = *--Mat.re; Mat.dr = !(*Mat.re = ~Mat.da + Mat.dr); } while(Mat.re > Mat.r); }
    Mat.N = (Mat.Nim) ? Mat.N : 0; } }

void FDIV (anu l, an r, an a, an b, an e) {
  if ((Mat.lre = l)) { Mat.F = 0; Mat.na = (Mat.Nim && (*a & 0x80)) ? 0xFF : 0; Mat.nb = (Mat.Nim && (*b & 0x80)) ? 0xFF : 0;
    Mat.N = Mat.na ^ Mat.nb; Mat.b = &Mat.Lo.l; Mat.da = 1; Mat.db = 1; Mat.fa = 0; Mat.fb = 0; r += l; a += l; b += l; e += l;
    do { Mat.fa = (*--a) ? (Mat.fa) ? Mat.fa : l : Mat.fa; Mat.fb = (*--b) ? (Mat.fb) ? Mat.fb : l : Mat.fb;
      Mat.db = (Mat.fb) ? (Mat.nb) ? !(*Mat.b++ = ~*b + Mat.db) : (*Mat.b++ = *b) : Mat.db;
      Mat.da = (Mat.na) ? !(*--e = ~*a + Mat.da) : (*--e = *a); *--r = 0; } while(--l); if (Mat.fa < 2 || Mat.fb < 2) {
      if (!Mat.fa || !Mat.fb || (Mat.Nim && *b == 0x80)) { Mat.F++; Mat.N = 0; return; }
      if (Mat.Nim && (*a == 0x80)) { *r = 0x80; Mat.F++; Mat.N = 0xFF; return; } }
    } }
