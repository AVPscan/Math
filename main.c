/* 
 * Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * 
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3).
 */

#include <stdio.h>
#include "sys.h"

#define BE  0
#define Lon 1

#if Lon == 1
 typedef uint8_t buf;
 typedef int8_t zbuf;
 typedef uint16_t Dbuf;
 typedef int16_t zDbuf;
 sanu a = {250}, b = {3};
#elif Lon == 2
 typedef uint16_t buf;
 typedef int16_t zbuf;
 typedef uint32_t Dbuf;
 typedef int32_t zDbuf;
 vanu a = {0,{5}}, b = {0,{2}};
#elif Lon == 4
 typedef uint32_t buf;
 typedef int32_t zbuf;
 typedef uint64_t Dbuf;
 typedef int64_t zDbuf;
 an a = {0,{0,0,5}}, b = {0,{0,0,2}};
#endif
buf o1, o2;
zbuf o3, o4;
  
void Show(anu i, const char *str, anu *r, anu *e) { printf(" %s%s", (Mat.Carry) ? "C" : " ", (Mat.Riz) ? (Mat.Rnim) ? "I " : "Z " : (Mat.Rnim) ? "- " : "+ ");
  Mat.Carry = 0; i = (i != 2) ? 1 : 2; if (!BE) { FSWAP(Mat.L * i, (anu*)r, (anu*)r); FSWAP(Mat.L, (anu*)e, (anu*)e); }
  if (Mat.Nim) { printf("%d %s %d = ", o3, str, o4); } else { printf("%d %s %d = ", o1, str, o2); } }

int main(void) {
  buf r, e; Dbuf rm; zbuf zr, ze; zDbuf zm; Mat.L = Lon; Mat.Nim = 0; FSWAP(Mat.L, (anu*)&o1, (anu*)&a.h);
  FSWAP(Mat.L, (anu*)&o2, (anu*)&b.h); FSWAP(Mat.L, (anu*)&o3, (anu*)&a.h); FSWAP(Mat.L, (anu*)&o4, (anu*)&b.h);
  if (BE) { FSWAP(Mat.L, (anu*)&o1, (anu*)&o1); FSWAP(Mat.L, (anu*)&o2, (anu*)&o2); FSWAP(Mat.L, (anu*)&o3, (anu*)&o3);
    FSWAP(Mat.L, (anu*)&o4, (anu*)&o4); } Mat.Nim = 0;
  FADD(Mat.L, (anu*)&r, (anu*)&a.h, (anu*)&b.h); Show(1, "+", (anu*)&r, (anu*)&e); printf("%d\n", r);
  FSUB(Mat.L, (anu*)&r, (anu*)&a.h, (anu*)&b.h); Show(1, "-", (anu*)&r, (anu*)&e); printf("%d\n", r);
  FMUL(Mat.L, (anu*)&rm, (anu*)&a.h, (anu*)&b.h); Show(2, "*", (anu*)&rm, (anu*)&e); printf("%d\n", rm); Mat.Nim = 1;
  FADD(Mat.L, (anu*)&zr, (anu*)&a.h, (anu*)&b.h); Show(1, "+", (anu*)&zr, (anu*)&ze); printf("%d\n", zr);
  FSUB(Mat.L, (anu*)&zr, (anu*)&a.h, (anu*)&b.h); Show(1, "-", (anu*)&zr, (anu*)&ze); printf("%d\n", zr);
  FMUL(Mat.L, (anu*)&zm, (anu*)&a.h, (anu*)&b.h); Show(2, "*", (anu*)&zm, (anu*)&ze); printf("%d\n", zm);
  return 0; }
