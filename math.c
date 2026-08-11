/* 
 * Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * 
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3).
 */

#include "sys.h"
MATH_VARS_INIT;

void FSWAP (anu l, anu *r, anu *a) { if (l) { Mat.r = r + l; Mat.a = a + l; Mat.fa = (l & 1); l >>= 1;
  while(l--) { Mat.ba = *--Mat.a; Mat.bb = *a++; *r++ = Mat.ba; *--Mat.r = Mat.bb; } if (Mat.fa) { *r = *a; } } }

void FMOV (anu l, anu *r, anu *a) { while(l--) *r++ = *a++; }

void FLDA (anu l, anu *r, anu D) { Mat.Carry = 0; if (l) { Mat.Rnim = (Mat.Nim) ? (D & 0x80) ? 0xFF : 0 : 0;
  Mat.Riz = (D) ? (Mat.Nim && D == 0x80) ? 1 : 0 : 1; while(--l) { *r++ = Mat.Rnim; } *r = D; } }

void FLDVA (anu l, anu *r, anu Dh, anu Dl) { Mat.Carry = 0; if (l) { if (--l) { Mat.Rnim = (Mat.Nim) ? (Dh & 0x80) ? 0xFF : 0 : 0;
  Mat.Riz = (!Dl) ? (Mat.Nim && Dh == 0x80) ? 1 : (!Dh) : 0; while(--l) { *r++ = Mat.Rnim; } *r++ = Dh; *r = Dl; return; } *r = Dl;
  Mat.Rnim = (Mat.Nim) ? (Dl & 0x80) ? 0xFF : 0 : 0; Mat.Riz = (Dl) ? (Mat.Nim && Dl == 0x80) ? 1 : 0 : 1; Mat.Carry = (Dh != Mat.Rnim); } }

void FRR (anu l, anu *r) { r--; while(l--) { Mat.za = *++r & 1; *r >>= 1; if (Mat.Carry) { *r |= 0x80; } Mat.Carry = Mat.za; }
  Mat.Carry = (Mat.Carry != 0); }

void FRL (anu l, anu *r) { r += l; while(l--) { Mat.za = *--r & 0x80; *r <<= 1; if (Mat.Carry) { *r |= 1; } Mat.Carry = Mat.za; }
  Mat.Carry = (Mat.Carry != 0); }

void VIKARA (anu lr, anu la, anu *r, anu *a) { Mat.Carry = 0; if ((Mat.loop = la)) { Mat.Rnim = (Mat.Nim) ? (*a & 0x80) ? 0xFF : 0 : 0;
    Mat.a = a; if ((Mat.Riz = (*a) ? (Mat.Nim && *a == 0x80) ? 1 : 0 : 1)) while(--Mat.loop && (Mat.Riz = (*++Mat.a) ? 0 : Mat.Riz));
    if (Mat.Riz) { if (lr) { *r++ = *a; while(--lr) *r++ = 0; } } if (!lr) return;
    if (lr >= la) { r += lr; a += la; lr -= la; do *--r = *--a; while(--la); while(lr--) { *--r = Mat.Rnim; } return; }
    la -= lr; do Mat.Carry = (*a++ == Mat.Rnim) ? Mat.Carry : 1; while(--la); Mat.ba = *a;
    if (Mat.Nim) { Mat.Carry = ((Mat.ba ^ Mat.Rnim) & 0x80) ? 1 : Mat.Carry; Mat.ba &= 0x7F; Mat.ba |= (Mat.Rnim & 0x80);
      if (Mat.Carry) { Mat.Carry--; Mat.Riz++; Mat.Rnim = 0xFF; *r++ = 0x80; while(--lr) { *r++ = 0; } return; } } *r++ = Mat.ba;
    while(--lr) { *r++ = *++a; } return ; } Mat.Rnim = 0; Mat.Riz = 0; if (lr) { Mat.Riz++; do *r++ = 0; while(--lr); } }

void FADD (anu l, anu *r, anu *a, anu *b) { if ((Mat.loop = l)) { Mat.Riz = 0; Mat.Rnim = 0; Mat.Carry = (Mat.Carry != 0);
  Mat.zr = !((*a ^ *b) & 0x80); Mat.br = 0; if (Mat.Nim) { Mat.fa = (*a == 0x80); Mat.fb = (*b == 0x80);
    if (Mat.fa || Mat.fb) { Mat.a = a; Mat.b = b; 
      while(--Mat.loop && (Mat.fa || Mat.fb)) { Mat.fa = (Mat.fa) ? (*++Mat.a == 0) : Mat.fa; Mat.fb = (Mat.fb) ? (*++Mat.b == 0) : Mat.fb; }
      if (!Mat.loop && (Mat.fa || Mat.fb)) { Mat.Riz++; Mat.Rnim--; *r++ = 0x80; while(--l) { *r++ = 0; } return; } Mat.loop = l; } } 
  r += l; a += l; b += l; while(--l) { Mat.ba = *--a; Mat.br |= (*--r = Mat.ba + *--b + Mat.Carry); Mat.Carry = (*r < Mat.ba); }
  Mat.ba = *--a; *--r = Mat.ba + *--b + Mat.Carry; Mat.Carry = (*r < Mat.ba); Mat.bb = *r; if (Mat.Nim) {
    if ((!Mat.br && *r == 0x80) || (((Mat.bb ^ *a) & 0x80) && Mat.zr)) { Mat.Riz++; Mat.Rnim--; *r++ = 0x80; while(--Mat.loop) *r++ = 0; }
    else { Mat.Rnim = (*r & 0x80) ? 0xFF : 0; } Mat.Carry = 0; } if (!Mat.br && !Mat.bb) { Mat.Riz++; Mat.Rnim = 0; } } }

void FSUB (anu l, anu *r, anu *a, anu *b) { if ((Mat.loop = l)) { Mat.Riz = 0; Mat.Rnim = 0; Mat.Carry = (Mat.Carry != 0);
  Mat.zr = !((*a ^ ~*b) & 0x80); Mat.br = 0; if (Mat.Nim) { Mat.fa = (*a == 0x80); Mat.fb = (*b == 0x80);
    if (Mat.fa || Mat.fb) { Mat.a = a; Mat.b = b; 
      while(--Mat.loop && (Mat.fa || Mat.fb)) { Mat.fa = (Mat.fa) ? (*++Mat.a == 0) : Mat.fa; Mat.fb = (Mat.fb) ? (*++Mat.b == 0) : Mat.fb; }
      if (!Mat.loop && (Mat.fa || Mat.fb)) { Mat.Riz++; Mat.Rnim--; *r++ = 0x80; while(--l) { *r++ = 0; } return; } Mat.loop = l; } } 
  r += l; a += l; b += l; while(--l) { Mat.ba = *--a; Mat.br |= (*--r = Mat.ba - *--b - Mat.Carry); Mat.Carry = (*r > Mat.ba); }
  Mat.ba = *--a; *--r = Mat.ba - *--b - Mat.Carry; Mat.Carry = (*r > Mat.ba); Mat.bb = *r; if (Mat.Nim) {
    if ((!Mat.br && *r == 0x80) || (((Mat.bb ^ *a) & 0x80) && Mat.zr)) { Mat.Riz++; Mat.Rnim--; *r++ = 0x80; while(--Mat.loop) *r++ = 0; }
    else { Mat.Rnim = (*r & 0x80) ? 0xFF : 0; } Mat.Carry = 0; } if (!Mat.br && !Mat.bb) { Mat.Riz++; Mat.Rnim = 0; } } }

void FMUL (anu l, anu *r, anu *a, anu *b) { if (l) { Mat.fa = 0; Mat.fb = 0; Mat.ba = 1; Mat.bb = 1; Mat.Riz = 0;
    Mat.za = (Mat.Nim && *a & 0x80) ? 0xFF : 0; Mat.zb = (Mat.Nim && *b & 0x80) ? 0xFF : 0; Mat.Rnim = Mat.za ^ Mat.zb;
    Mat.r = r; r += l; Mat.e = r + l; a += l; b += l; Mat.a = &Mat.Ho.h; Mat.b = &Mat.Lo.h; Mat.Ll = l; Mat.Lh = ((Mat.Ll += l) < l);
    do { Mat.fa = (*--a) ? (Mat.fa) ? Mat.fa : l : Mat.fa; Mat.fb = (*--b) ? (Mat.fb) ? Mat.fb : l : Mat.fb;
      Mat.ba = (Mat.fa) ? (Mat.za) ? !(*Mat.a++ = ~*a + Mat.ba) : (*Mat.a++ = *a) : Mat.ba;
      Mat.bb = (Mat.fb) ? (Mat.zb) ? !(*Mat.b++ = ~*b + Mat.bb) : (*Mat.b++ = *b) : Mat.bb; *--r = 0; *--Mat.e = 0; } while(--l);
    Mat.ba = Mat.a - &Mat.Ho.h; Mat.bb = Mat.b - &Mat.Lo.h; Mat.e = Mat.r + Mat.fa + Mat.fb; if (Mat.ba < 2 || Mat.bb < 2) {
      if (!Mat.ba || !Mat.bb) { Mat.Rnim = 0; Mat.Riz++; return; }
      if (Mat.Nim && (*(Mat.a - 1) == 0x80 || *(Mat.b - 1) == 0x80)) { Mat.Riz++; *r = 0x80; Mat.Rnim = 0xFF; return; } } Mat.ba = 0; Mat.bb = 0;
    do { Mat.fa -= ((Mat.ba = (Mat.ba) ? Mat.ba : (*--Mat.a))) ? 0 : 1; Mat.fb -= ((Mat.bb = (Mat.bb) ? Mat.bb : (*--Mat.b))) ? 0 : 1; }
    while(!(Mat.ba && Mat.bb)); Mat.ba = *Mat.a; Mat.bb = *Mat.b; Mat.a = &Mat.Ho.h; Mat.b = &Mat.Lo.h;
    if (Mat.fb > Mat.fa || (Mat.fb == Mat.fa && Mat.bb > Mat.ba)) { Mat.a = Mat.b; Mat.b = &Mat.Ho.h; l = Mat.fa;
      Mat.fa = Mat.fb; Mat.fb = l; } *(Mat.b + Mat.fb++) = 0; r = Mat.e;
    do { if ((Mat.ba = *Mat.a++)) { a = &Mat.Sr.h; b = Mat.b; l = Mat.fb; do *a++ = *b++; while(--l);
        do { Mat.zb = 0; b = &Mat.Sr.h; l = Mat.fb; if (!(Mat.ba & 1)) do { Mat.br = (*b << 1) + Mat.zb;
            Mat.zb = ((*b & 0x80) == 0x80); *b++ = Mat.br; } while(--l);
          else { a = r; Mat.za = 0; do { Mat.br = *--a; *a += *b + Mat.za; Mat.za = (*a < Mat.br);
            Mat.br = (*b << 1) + Mat.zb; Mat.zb = ((*b & 0x80) == 0x80); *b++ = Mat.br; } while(--l); } 
          } while(Mat.ba >>= 1); } --r; } while(--Mat.fa);
    if (Mat.Rnim) { Mat.br = 1; do { Mat.ba = *--Mat.e; Mat.br = !(*Mat.e = ~Mat.ba + Mat.br); } while(Mat.e > Mat.r); }
    Mat.Rnim = (Mat.Nim) ? Mat.Rnim : 0; } }

void FDIV (anu l, anu *r, anu *a, anu *b, anu *e) { if ((Mat.loop = l)) { Mat.fa = 0; Mat.fb = 0;
    Mat.Riz = 0; Mat.za = (Mat.Nim && (*a & 0x80)) ? 0xFF : 0; Mat.zb = (Mat.Nim && (*b & 0x80)) ? 0xFF : 0;
    Mat.Rnim = Mat.za ^ Mat.zb; r += l; a += l; b += l; e += l; Mat.b = &Mat.Lo.h; Mat.ba = 1; Mat.bb = 1;
    do { Mat.fa = (*--a) ? (Mat.fa) ? Mat.fa : l : Mat.fa; Mat.fb = (*--b) ? (Mat.fb) ? Mat.fb : l : Mat.fb;
      Mat.bb = (Mat.fb) ? (Mat.zb) ? !(*Mat.b++ = ~*b + Mat.bb) : (*Mat.b++ = *b) : Mat.bb;
      Mat.ba = (Mat.za) ? !(*--e = ~*a + Mat.ba) : (*--e = *a); *--r = 0; } while(--l);
    if (Mat.fa < 2 || Mat.fb < 2) { if (!Mat.fa || !Mat.fb || (Mat.Nim && *b == 0x80)) { Mat.Riz++; Mat.Rnim = 0; return; }
      if (Mat.Nim && (*a == 0x80)) { *r = 0x80; Mat.Riz++; Mat.Rnim = 0xFF; return; } } 
    } }
