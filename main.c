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
#define Lon 2

#if Lon == 1
 typedef uint8_t buf;
 typedef int8_t zbuf;
 typedef uint16_t Dbuf;
 typedef int16_t zDbuf;
 sanu o1 = {5}, o2 = {6};
 sanu o3 = {250}, o4 = {5};
#elif Lon == 2
 typedef uint16_t buf;
 typedef int16_t zbuf;
 typedef uint32_t Dbuf;
 typedef int32_t zDbuf;
 vanu o1 = {0,{5}}, o2 = {0,{2}};
 vanu o3 = {255,{250}}, o4 = {0,{2}};
#elif Lon == 4
 typedef uint32_t buf;
 typedef int32_t zbuf;
 typedef uint64_t Dbuf;
 typedef int64_t zDbuf;
 an o1 = {0,{0,0,5}}, o2 = {0,{0,0,2}};
 an o3 = {255,{255,255,250}}, o4 = {0,{0,0,2}};
#endif

void Show(void) { printf("%s%s", (Mat.Riz) ? (Mat.Rnim) ? " I" : " Z" : (Mat.Rnim) ? " -" : " +", (Mat.Carry) ? "C  " : "   "); }

int main(void) {
    buf a = 0, b = 0, ra = 0, rs = 0; Dbuf rm = 0; zbuf c = 0, d = 0, za = 0, zs = 0; zDbuf zm = 0; Mat.Long = Lon; FBSWAP(Mat.Long, (anu*)&a, (anu*)&o1.h);
    FBSWAP(Mat.Long, (anu*)&b, (anu*)&o2.h); FBSWAP(Mat.Long, (anu*)&c, (anu*)&o3.h); FBSWAP(Mat.Long, (anu*)&d, (anu*)&o4.h); Mat.Nim = 0;
    if (BE) { FBSWAP(Mat.Long, (anu*)&a, (anu*)&a); FBSWAP(Mat.Long, (anu*)&b, (anu*)&b); FBSWAP(Mat.Long, (anu*)&c, (anu*)&c); FBSWAP(Mat.Long, (anu*)&d, (anu*)&d); }
    FADD(Mat.Long, (anu*)&ra, (anu*)&o1.h, (anu*)&o2.h); if (!BE) { FBSWAP(Mat.Long, (anu*)&ra, (anu*)&ra); } Show(); printf("%d + %d = %d\n", a, b, ra);
    FSUB(Mat.Long, (anu*)&rs, (anu*)&o1.h, (anu*)&o2.h); if (!BE) { FBSWAP(Mat.Long, (anu*)&rs, (anu*)&rs); } Show(); printf("%d - %d = %d\n", a, b, rs);
    FMUL(Mat.Long, (anu*)&rm, (anu*)&o1.h, (anu*)&o2.h); if (!BE) { FBSWAP(Mat.Long * 2, (anu*)&rm, (anu*)&rm); } Show(); printf("%d * %d = %d\n", a, b, rm); Mat.Carry = 0;
    Mat.Nim = 1; FADD(Mat.Long, (anu*)&za, (anu*)&o3.h, (anu*)&o4.h); if (!BE) { FBSWAP(Mat.Long, (anu*)&za, (anu*)&za); } Show(); printf("%d + %d = %d\n", c, d, za);
    FSUB(Mat.Long, (anu*)&zs, (anu*)&o3.h, (anu*)&o4.h); if (!BE) { FBSWAP(Mat.Long, (anu*)&zs, (anu*)&zs); } Show(); printf("%d - %d = %d\n", c, d, zs);
    FMUL(Mat.Long, (anu*)&zm, (anu*)&o3.h, (anu*)&o4.h); if (!BE) { FBSWAP(Mat.Long * 2, (anu*)&zm, (anu*)&zm); } Show(); printf("%d * %d = %d\n", c, d, zm);
    return 0; }
