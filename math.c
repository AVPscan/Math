/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include "sys.h"

Cache Mat = {0};

void FINIT (anu lb, anu n, anu o) { Mat.Nim = (n != 0); Mat.Over = (o != 0); Mat.lb = lb; Mat.lar = lb; Mat.clar = 0;
  Mat.C = 0; Mat.F = 0; Mat.N = 0; Mat.Fre = 0; Mat.Nre = 0; }

void FLD (anu *r, anu D) { *r = D; Mat.lar = 1; Mat.clar = 0; Mat.N = (Mat.Nim && (D & 0x80)) ? 0xFF : 0;
  Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 1 : 0 : 1; }

void FLVD (anu *r, anu Dl, anu Dh) { Mat.lar = 2; Mat.clar = 0; *r++ = Dl; Mat.N = (Mat.Nim && (Dh & 0x80)) ? 0xFF : 0;
  if ((Mat.F = (Dh || Dl) ? (Mat.Nim && (Dh == 0x80) && !Dl) ? 1 : 0 : 1)) { Mat.lar--; r--; } *r = Dh; }

void FRR (anu *r) { r--; Mat.tl = Mat.lar;
  while(Mat.tl--) { Mat.na = *++r & 1; *r >>= 1; if (Mat.C) { *r |= 0x80; } Mat.C = Mat.na; } if (Mat.clar) { --Mat.tl;
    while(Mat.tl--) { Mat.na = *++r & 1; *r >>= 1; if (Mat.C) { *r |= 0x80; } Mat.C = Mat.na; } } Mat.C = (Mat.C != 0); }

void FRL (anu *r) { r += Mat.lar + ((Mat.clar) ? 255 : 0); Mat.tl = Mat.lar;
  while(Mat.tl--) { Mat.na = *--r & 0x80; *r <<= 1; if (Mat.C) { *r |= 1; } Mat.C = Mat.na; } if (Mat.clar) { --Mat.tl;
    while(Mat.tl--) { Mat.na = *--r & 0x80; *r <<= 1; if (Mat.C) { *r |= 1; } Mat.C = Mat.na; } } Mat.C = (Mat.C != 0); }

void FMOV (anu l, anu *r, anu *a) { if (l) { Mat.r = r; Mat.lar = l; Mat.clar = 0; Mat.dr = 0;
    if (r < a) { while(--l) Mat.dr |= (*r++ = *a++); } else { r += l; a += l; while(--l) { Mat.dr |= (*--r = *--a); } r--; a--; } 
    Mat.N = (Mat.Nim && ((*r = *a) & 0x80)) ? 0xFF : 0; if ((Mat.F = (*r || Mat.dr) ? (Mat.Nim && (*r == 0x80) && !Mat.dr) ? 1 : 0 : 1)) {
      *Mat.r = *r; Mat.lar = 1; } } }

void FSWAP (anu l, anu *r, anu *a) { if (l) { Mat.r = r + l; Mat.a = a + l; Mat.fa = (l & 1); l >>= 1;
    while(l--) { Mat.da = *--Mat.a; Mat.dr = *a++; *r++ = Mat.da; *--Mat.r = Mat.dr; } if (Mat.fa) *r = *a; } }

void VIKARA (anu l, anu *r, anu *a) { Mat.C = 0; if ((Mat.tl = l)) { Mat.a = a; Mat.N = (Mat.Nim && (*a & 0x80)) ? 0xFF : 0;
    if ((Mat.F = (*a) ? (Mat.Nim && *a == 0x80) ? 1 : 0 : 1)) while(--Mat.tl && (Mat.F = (*++Mat.a) ? 0 : Mat.F));
    if (Mat.F) { Mat.N = (*r = *a) ? 0xFF : 0; Mat.clar = 0; Mat.lar = 1; return; }
    if (Mat.clar || (Mat.lar >= l)) { r += Mat.lar + ((Mat.clar) ? 255 : 0); a += l; Mat.tl = Mat.lar; Mat.tl -= l - (Mat.clar != 0);
      do *--r = *--a; while(--l); while(Mat.tl--) { *--r = Mat.N; } return; }
    l -= Mat.lar; do Mat.C = (*a++ == Mat.N) ? Mat.C : 1; while(--l); Mat.da = *a;
    if (Mat.Nim) { Mat.C = ((Mat.da ^ Mat.N) & 0x80) ? 1 : Mat.C; Mat.da &= 0x7F; Mat.da |= (Mat.N & 0x80);
      if (Mat.C) { Mat.C--; Mat.F++; Mat.N = 0xFF; *r = 0x80; Mat.lar = 1; return; } }
    *r++ = Mat.da; l = Mat.lar; while(--l) { *r++ = *++a; } return ; }
  Mat.F = 0; Mat.N = 0; Mat.clar = 0; if (Mat.lar) { Mat.F++; *r = 0; Mat.lar = 1;  } }

void FCold (anu BigEndian, anu lb, anu *r, anu *b) { if ((Mat.tl = lb)) { Mat.clar = 0; if (lb > 2) {
      Mat.tl = (lb - 1) >> 1; Mat.lar = 2; do Mat.lar <<= 1; while((Mat.tl >>= 1)); } Mat.tl = Mat.lar; VIKARA(lb, r, b); Mat.lar = lb;
    if (Mat.F) { lb = Mat.tl; Mat.dr = *(Mat.r = r); while(--lb) { *Mat.r++ = 0; } *Mat.r = Mat.dr; } if (BigEndian) FSWAP(Mat.tl, r, r); } }

void FADD (anu l, anu *r, anu *a, anu *b) {
  if ((Mat.tl = l)) { Mat.F = 0; Mat.N = 0; Mat.C = (Mat.C != 0); Mat.N = !((*a ^ *b) & 0x80); Mat.dr = 0;
    if (Mat.Nim) { Mat.fa = (*a == 0x80); Mat.fb = (*b == 0x80); if (Mat.fa || Mat.fb) { Mat.a = a; Mat.b = b;
      while(--Mat.tl && (Mat.fa || Mat.fb)) { Mat.fa = (Mat.fa) ? (*++Mat.a == 0) : Mat.fa; Mat.fb = (Mat.fb) ? (*++Mat.b == 0) : Mat.fb; }
      if (!Mat.tl && (Mat.fa || Mat.fb)) { Mat.F++; Mat.N--; *r++ = 0x80; while(--l) { *r++ = 0; } return; } Mat.tl = l; } }
  r += l; a += l; b += l; while(--l) { Mat.da = *--a; Mat.dr |= (*--r = Mat.da + *--b + Mat.C); Mat.C = (*r < Mat.da); }
  Mat.da = *--a; *--r = Mat.da + *--b + Mat.C; Mat.C = (*r < Mat.da); Mat.db = *r; if (Mat.Nim) {
    if ((!Mat.dr && *r == 0x80) || (((Mat.db ^ *a) & 0x80) && Mat.N)) { Mat.F++; Mat.N--; *r++ = 0x80; while(--Mat.tl) *r++ = 0; }
    else { Mat.N = (*r & 0x80) ? 0xFF : 0; } Mat.C = 0; } if (!Mat.dr && !Mat.db) { Mat.F++; Mat.N = 0; } } }

void FSUB (anu l, anu *r, anu *a, anu *b) {
  if ((Mat.tl = l)) { Mat.F = 0; Mat.N = 0; Mat.C = (Mat.C != 0); Mat.N = !((*a ^ ~*b) & 0x80); Mat.dr = 0;
    if (Mat.Nim) { Mat.fa = (*a == 0x80); Mat.fb = (*b == 0x80); if (Mat.fa || Mat.fb) { Mat.a = a; Mat.b = b;
      while(--Mat.tl && (Mat.fa || Mat.fb)) { Mat.fa = (Mat.fa) ? (*++Mat.a == 0) : Mat.fa; Mat.fb = (Mat.fb) ? (*++Mat.b == 0) : Mat.fb; }
      if (!Mat.tl && (Mat.fa || Mat.fb)) { Mat.F++; Mat.N--; *r++ = 0x80; while(--l) { *r++ = 0; } return; } Mat.tl = l; } }
  r += l; a += l; b += l; while(--l) { Mat.da = *--a; Mat.dr |= (*--r = Mat.da - *--b - Mat.C); Mat.C = (*r > Mat.da); }
  Mat.da = *--a; *--r = Mat.da - *--b - Mat.C; Mat.C = (*r > Mat.da); Mat.db = *r; if (Mat.Nim) {
    if ((!Mat.dr && *r == 0x80) || (((Mat.db ^ *a) & 0x80) && Mat.N)) { Mat.F++; Mat.N--; *r++ = 0x80; while(--Mat.tl) *r++ = 0; }
    else { Mat.N = (*r & 0x80) ? 0xFF : 0; } Mat.C = 0; } if (!Mat.dr && !Mat.db) { Mat.F++; Mat.N = 0; } } }

void FMUL (anu l, anu *r, anu *a, anu *b) {
  if (l) { Mat.F = 0; Mat.na = (Mat.Nim && *a & 0x80) ? 0xFF : 0; Mat.nb = (Mat.Nim && *b & 0x80) ? 0xFF : 0;
    Mat.N = Mat.na ^ Mat.nb; Mat.a = &Mat.Ho.l; Mat.b = &Mat.Lo.l; Mat.lar = l; Mat.clar = ((Mat.lar += l) < l);
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

void FDIV (anu l, anu *r, anu *a, anu *b, anu *e) {
  if ((Mat.tl = l)) { Mat.F = 0; Mat.na = (Mat.Nim && (*a & 0x80)) ? 0xFF : 0; Mat.nb = (Mat.Nim && (*b & 0x80)) ? 0xFF : 0;
    Mat.N = Mat.na ^ Mat.nb; Mat.b = &Mat.Lo.l; Mat.da = 1; Mat.db = 1; Mat.fa = 0; Mat.fb = 0; r += l; a += l; b += l; e += l;
    do { Mat.fa = (*--a) ? (Mat.fa) ? Mat.fa : l : Mat.fa; Mat.fb = (*--b) ? (Mat.fb) ? Mat.fb : l : Mat.fb;
      Mat.db = (Mat.fb) ? (Mat.nb) ? !(*Mat.b++ = ~*b + Mat.db) : (*Mat.b++ = *b) : Mat.db;
      Mat.da = (Mat.na) ? !(*--e = ~*a + Mat.da) : (*--e = *a); *--r = 0; } while(--l); if (Mat.fa < 2 || Mat.fb < 2) {
      if (!Mat.fa || !Mat.fb || (Mat.Nim && *b == 0x80)) { Mat.F++; Mat.N = 0; return; }
      if (Mat.Nim && (*a == 0x80)) { *r = 0x80; Mat.F++; Mat.N = 0xFF; return; } }
    } }
