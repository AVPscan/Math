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
  Mat.Carry = 0; i = (i != 2) ? 1 : 2; if (!BE) { FBSWAP(Mat.Long * i, (anu*)r, (anu*)r); FBSWAP(Mat.Long * i, (anu*)e, (anu*)e); }
  if (Mat.Nim) { printf("%d %s %d = ", o3, str, o4); } else { printf("%d %s %d = ", o1, str, o2); } }

int main(void) {
  buf r, e; Dbuf rm, de; zbuf rz, ze; zDbuf zm, zde; Mat.Long = Lon; Mat.Nim = 0; FBSWAP(Mat.Long, (anu*)&o1, (anu*)&a.h);
  FBSWAP(Mat.Long, (anu*)&o2, (anu*)&b.h); Mat.Nim = 1; FBSWAP(Mat.Long, (anu*)&o3, (anu*)&a.h); FBSWAP(Mat.Long, (anu*)&o4, (anu*)&b.h);
  if (BE) { FBSWAP(Mat.Long, (anu*)&o1, (anu*)&o1); FBSWAP(Mat.Long, (anu*)&o2, (anu*)&o2); FBSWAP(Mat.Long, (anu*)&o3, (anu*)&o3);
    FBSWAP(Mat.Long, (anu*)&o4, (anu*)&o4); } Mat.Nim = 0;
  FADD(Mat.Long, (anu*)&r, (anu*)&a.h, (anu*)&b.h); Show(1, "+", (anu*)&r, (anu*)&e); printf("%d\n", r);
  FSUB(Mat.Long, (anu*)&r, (anu*)&a.h, (anu*)&b.h); Show(1, "-", (anu*)&r, (anu*)&e); printf("%d\n", r);
  FMUL(Mat.Long, (anu*)&rm, (anu*)&a.h, (anu*)&b.h); Show(2, "*", (anu*)&rm, (anu*)&de); printf("%d\n", rm); Mat.Nim = 1;
  FADD(Mat.Long, (anu*)&rz, (anu*)&a.h, (anu*)&b.h); Show(1, "+", (anu*)&rz, (anu*)&ze); printf("%d\n", rz);
  FSUB(Mat.Long, (anu*)&rz, (anu*)&a.h, (anu*)&b.h); Show(1, "-", (anu*)&rz, (anu*)&ze); printf("%d\n", rz);
  FMUL(Mat.Long, (anu*)&zm, (anu*)&a.h, (anu*)&b.h); Show(2, "*", (anu*)&zm, (anu*)&zde); printf("%d\n", zm);
  return 0; }
