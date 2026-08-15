/* 
 * Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * 
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3).
 */

#include "sys.h"

Cache Mat = {0};

void FINIT (anu Nim, anu l) { Mat.Nim = (Nim != 0); Mat.L = l; Mat.Ll = l; Mat.Lh = 0;
  Mat.C = 0; Mat.F = 0; Mat.Z = 0; Mat.Fe = 0; Mat.Ze = 0; }

void FLD (anu *r, anu D) { *r = D; Mat.Ll = 1; Mat.Lh = 0; Mat.Z = (Mat.Nim && (D & 0x80)) ? 0xFF : 0;
  Mat.F = (D) ? (Mat.Nim && (D == 0x80)) ? 1 : 0 : 1; }

void FLVD (anu *r, anu Dl, anu Dh) { Mat.Ll = 2; Mat.Lh = 0; *r++ = Dl; Mat.Z = (Mat.Nim && (Dh & 0x80)) ? 0xFF : 0;
  if ((Mat.F = (Dh || Dl) ? (Mat.Nim && (Dh == 0x80) && !Dl) ? 1 : 0 : 1)) { Mat.Ll--; r--; } *r = Dh; }

void FRR (anu *r) { r--; Mat.Z = Mat.Ll;
  while(Mat.Z--) { Mat.za = *++r & 1; *r >>= 1; if (Mat.C) { *r |= 0x80; } Mat.C = Mat.za; } if (Mat.Lh) { --Mat.Z;
    while(Mat.Z--) { Mat.za = *++r & 1; *r >>= 1; if (Mat.C) { *r |= 0x80; } Mat.C = Mat.za; } }
  Mat.C = (Mat.C != 0); }

void FRL (anu *r) { r += Mat.Ll + ((Mat.Lh) ? 255 : 0); Mat.Z = Mat.Ll;
  while(Mat.Z--) { Mat.za = *--r & 0x80; *r <<= 1; if (Mat.C) { *r |= 1; } Mat.C = Mat.za; } if (Mat.Lh) { --Mat.Z;
    while(Mat.Z--) { Mat.za = *--r & 0x80; *r <<= 1; if (Mat.C) { *r |= 1; } Mat.C = Mat.za; } }
  Mat.C = (Mat.C != 0); }

void FMOV (anu l, anu *r, anu *a) { if (l) { Mat.r = r; Mat.Lh = 0; Mat.br = 0; Mat.Ll = l;
    if (r < a) { while(--l) Mat.br |= (*r++ = *a++); } else { r += l; a += l; while(--l) { Mat.br |= (*--r = *--a); } r--; a--; } 
    Mat.Z = (Mat.Nim && ((*r = *a) & 0x80)) ? 0xFF : 0; if ((Mat.F = (*r || Mat.br) ? (Mat.Nim && (*r == 0x80) && !Mat.br) ? 1 : 0 : 1)) {
      *Mat.r = *r; Mat.Ll = 1; } } }

void FSWAP (anu l, anu *r, anu *a) { if (l) { Mat.r = r + l; Mat.a = a + l; Mat.fa = (l & 1); l >>= 1;
    while(l--) { Mat.ba = *--Mat.a; Mat.bb = *a++; *r++ = Mat.ba; *--Mat.r = Mat.bb; } if (Mat.fa) *r = *a; } }

void VIKARA (anu l, anu *r, anu *a) { Mat.C = 0; if ((Mat.Lc = l)) { Mat.a = a; Mat.Z = (Mat.Nim) ? (*a & 0x80) ? 0xFF : 0 : 0;
    if ((Mat.F = (*a) ? (Mat.Nim && *a == 0x80) ? 1 : 0 : 1)) while(--Mat.Lc && (Mat.F = (*++Mat.a) ? 0 : Mat.F));
    if (Mat.F) { Mat.Z = (*r = *a) ? 0xFF : 0; Mat.Lh = 0; Mat.Ll = 1; return; }
    if (Mat.Lh || (Mat.Ll >= l)) { r += Mat.Ll + ((Mat.Lh) ? 255 : 0); a += l; Mat.Lc = Mat.Ll; Mat.Lc -= l - (Mat.Lh != 0);
      do *--r = *--a; while(--l); while(Mat.Lc--) { *--r = Mat.Z; } return; }
    l -= Mat.Ll; do Mat.C = (*a++ == Mat.Z) ? Mat.C : 1; while(--l); Mat.ba = *a;
    if (Mat.Nim) { Mat.C = ((Mat.ba ^ Mat.Z) & 0x80) ? 1 : Mat.C; Mat.ba &= 0x7F; Mat.ba |= (Mat.Z & 0x80);
      if (Mat.C) { Mat.C--; Mat.F++; Mat.Z = 0xFF; *r = 0x80; Mat.Ll = 1; return; } }
    *r++ = Mat.ba; l = Mat.Ll; while(--l) { *r++ = *++a; } return ; }
  Mat.F = 0; Mat.Z = 0; Mat.Lh = 0; if (Mat.Ll) { Mat.F++; *r = 0; Mat.Ll = 1;  } }

void FCold (anu BigEndian, anu *r, anu *a) { if ((Mat.Lc = Mat.Ll)) { Mat.Lh = 0;
    if ((Mat.za = Mat.Ll) > 2) { Mat.Lc = (Mat.za - 1) >> 1; Mat.Ll = 2; do Mat.Ll <<= 1; while((Mat.Lc >>= 1)); }
    Mat.Lc = Mat.Ll; VIKARA(Mat.za, r, a); Mat.Ll = Mat.za; if (Mat.F) { Mat.za = Mat.Lc; Mat.br = *(Mat.r = r);
      while(--Mat.za) { *Mat.r++ = 0; } *Mat.r = Mat.br; } if (BigEndian) FSWAP(Mat.Lc, r, r); } }

void FADD (anu l, anu *r, anu *a, anu *b) {
  if ((Mat.Lc = l)) { Mat.F = 0; Mat.Z = 0; Mat.C = (Mat.C != 0); Mat.Z = !((*a ^ *b) & 0x80); Mat.br = 0;
    if (Mat.Nim) { Mat.fa = (*a == 0x80); Mat.fb = (*b == 0x80); if (Mat.fa || Mat.fb) { Mat.a = a; Mat.b = b;
      while(--Mat.Lc && (Mat.fa || Mat.fb)) { Mat.fa = (Mat.fa) ? (*++Mat.a == 0) : Mat.fa; Mat.fb = (Mat.fb) ? (*++Mat.b == 0) : Mat.fb; }
      if (!Mat.Lc && (Mat.fa || Mat.fb)) { Mat.F++; Mat.Z--; *r++ = 0x80; while(--l) { *r++ = 0; } return; } Mat.Lc = l; } }
  r += l; a += l; b += l; while(--l) { Mat.ba = *--a; Mat.br |= (*--r = Mat.ba + *--b + Mat.C); Mat.C = (*r < Mat.ba); }
  Mat.ba = *--a; *--r = Mat.ba + *--b + Mat.C; Mat.C = (*r < Mat.ba); Mat.bb = *r; if (Mat.Nim) {
    if ((!Mat.br && *r == 0x80) || (((Mat.bb ^ *a) & 0x80) && Mat.Z)) { Mat.F++; Mat.Z--; *r++ = 0x80; while(--Mat.Lc) *r++ = 0; }
    else { Mat.Z = (*r & 0x80) ? 0xFF : 0; } Mat.C = 0; } if (!Mat.br && !Mat.bb) { Mat.F++; Mat.Z = 0; } } }

void FSUB (anu l, anu *r, anu *a, anu *b) {
  if ((Mat.Lc = l)) { Mat.F = 0; Mat.Z = 0; Mat.C = (Mat.C != 0); Mat.Z = !((*a ^ ~*b) & 0x80); Mat.br = 0;
    if (Mat.Nim) { Mat.fa = (*a == 0x80); Mat.fb = (*b == 0x80); if (Mat.fa || Mat.fb) { Mat.a = a; Mat.b = b;
      while(--Mat.Lc && (Mat.fa || Mat.fb)) { Mat.fa = (Mat.fa) ? (*++Mat.a == 0) : Mat.fa; Mat.fb = (Mat.fb) ? (*++Mat.b == 0) : Mat.fb; }
      if (!Mat.Lc && (Mat.fa || Mat.fb)) { Mat.F++; Mat.Z--; *r++ = 0x80; while(--l) { *r++ = 0; } return; } Mat.Lc = l; } }
  r += l; a += l; b += l; while(--l) { Mat.ba = *--a; Mat.br |= (*--r = Mat.ba - *--b - Mat.C); Mat.C = (*r > Mat.ba); }
  Mat.ba = *--a; *--r = Mat.ba - *--b - Mat.C; Mat.C = (*r > Mat.ba); Mat.bb = *r; if (Mat.Nim) {
    if ((!Mat.br && *r == 0x80) || (((Mat.bb ^ *a) & 0x80) && Mat.Z)) { Mat.F++; Mat.Z--; *r++ = 0x80; while(--Mat.Lc) *r++ = 0; }
    else { Mat.Z = (*r & 0x80) ? 0xFF : 0; } Mat.C = 0; } if (!Mat.br && !Mat.bb) { Mat.F++; Mat.Z = 0; } } }

void FMUL (anu l, anu *r, anu *a, anu *b) {
  if (l) { Mat.F = 0; Mat.za = (Mat.Nim && *a & 0x80) ? 0xFF : 0; Mat.zb = (Mat.Nim && *b & 0x80) ? 0xFF : 0;
    Mat.Z = Mat.za ^ Mat.zb; Mat.a = &Mat.Ho.l; Mat.b = &Mat.Lo.l; Mat.Ll = l; Mat.Lh = ((Mat.Ll += l) < l);
    Mat.fa = 0; Mat.fb = 0; Mat.ba = 1; Mat.bb = 1; Mat.r = r; r += l; Mat.e = r + l; a += l; b += l;
    do { Mat.fa = (*--a) ? (Mat.fa) ? Mat.fa : l : Mat.fa; Mat.fb = (*--b) ? (Mat.fb) ? Mat.fb : l : Mat.fb;
      Mat.ba = (Mat.fa) ? (Mat.za) ? !(*Mat.a++ = ~*a + Mat.ba) : (*Mat.a++ = *a) : Mat.ba;
      Mat.bb = (Mat.fb) ? (Mat.zb) ? !(*Mat.b++ = ~*b + Mat.bb) : (*Mat.b++ = *b) : Mat.bb; *--r = 0; *--Mat.e = 0; } while(--l);
    Mat.ba = Mat.a - &Mat.Ho.l; Mat.bb = Mat.b - &Mat.Lo.l; Mat.e = Mat.r + Mat.fa + Mat.fb; if (Mat.ba < 2 || Mat.bb < 2) {
      if (!Mat.ba || !Mat.bb) { Mat.Z = 0; Mat.F++; return; }
      if (Mat.Nim && (*(Mat.a - 1) == 0x80 || *(Mat.b - 1) == 0x80)) { Mat.F++; *r = 0x80; Mat.Z = 0xFF; return; } } Mat.ba = 0; Mat.bb = 0;
    do { Mat.fa -= ((Mat.ba = (Mat.ba) ? Mat.ba : (*--Mat.a))) ? 0 : 1; Mat.fb -= ((Mat.bb = (Mat.bb) ? Mat.bb : (*--Mat.b))) ? 0 : 1; }
    while(!(Mat.ba && Mat.bb)); Mat.ba = *Mat.a; Mat.bb = *Mat.b; Mat.a = &Mat.Ho.l; Mat.b = &Mat.Lo.l;
    if (Mat.fb > Mat.fa || (Mat.fb == Mat.fa && Mat.bb > Mat.ba)) { Mat.a = Mat.b; Mat.b = &Mat.Ho.l; l = Mat.fa;
      Mat.fa = Mat.fb; Mat.fb = l; } *(Mat.b + Mat.fb++) = 0; r = Mat.e;
    do { if ((Mat.ba = *Mat.a++)) { a = &Mat.Sr.l; b = Mat.b; l = Mat.fb; do *a++ = *b++; while(--l);
        do { Mat.zb = 0; b = &Mat.Sr.l; l = Mat.fb; if (!(Mat.ba & 1)) do { Mat.br = (*b << 1) + Mat.zb;
            Mat.zb = ((*b & 0x80) == 0x80); *b++ = Mat.br; } while(--l);
          else { a = r; Mat.za = 0; do { Mat.br = *--a; *a += *b + Mat.za; Mat.za = (*a < Mat.br);
            Mat.br = (*b << 1) + Mat.zb; Mat.zb = ((*b & 0x80) == 0x80); *b++ = Mat.br; } while(--l); }
          } while(Mat.ba >>= 1); } --r; } while(--Mat.fa);
    if (Mat.Z) { Mat.br = 1; do { Mat.ba = *--Mat.e; Mat.br = !(*Mat.e = ~Mat.ba + Mat.br); } while(Mat.e > Mat.r); }
    Mat.Z = (Mat.Nim) ? Mat.Z : 0; } }

void FDIV (anu l, anu *r, anu *a, anu *b, anu *e) {
  if ((Mat.Lc = l)) { Mat.F = 0; Mat.za = (Mat.Nim && (*a & 0x80)) ? 0xFF : 0; Mat.zb = (Mat.Nim && (*b & 0x80)) ? 0xFF : 0;
    Mat.Z = Mat.za ^ Mat.zb; Mat.b = &Mat.Lo.l; Mat.ba = 1; Mat.bb = 1; Mat.fa = 0; Mat.fb = 0; r += l; a += l; b += l; e += l;
    do { Mat.fa = (*--a) ? (Mat.fa) ? Mat.fa : l : Mat.fa; Mat.fb = (*--b) ? (Mat.fb) ? Mat.fb : l : Mat.fb;
      Mat.bb = (Mat.fb) ? (Mat.zb) ? !(*Mat.b++ = ~*b + Mat.bb) : (*Mat.b++ = *b) : Mat.bb;
      Mat.ba = (Mat.za) ? !(*--e = ~*a + Mat.ba) : (*--e = *a); *--r = 0; } while(--l); if (Mat.fa < 2 || Mat.fb < 2) {
      if (!Mat.fa || !Mat.fb || (Mat.Nim && *b == 0x80)) { Mat.F++; Mat.Z = 0; return; }
      if (Mat.Nim && (*a == 0x80)) { *r = 0x80; Mat.F++; Mat.Z = 0xFF; return; } }
    } }
