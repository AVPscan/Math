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

#define Lon 2

#if Lon == 1
 typedef uint8_t buf;
 typedef int8_t zbuf;
 typedef uint16_t Dbuf;
 typedef int16_t zDbuf;
#elif Lon == 2
 typedef uint16_t buf;
 typedef int16_t zbuf;
 typedef uint32_t Dbuf;
 typedef int32_t zDbuf;
#elif Lon == 4
 typedef uint32_t buf;
 typedef int32_t zbuf;
 typedef uint64_t Dbuf;
 typedef int64_t zDbuf;
#endif

int main(void) {
    buf a = 5, b = 3; Dbuf r = 0;
    Mat.Long = Lon; Mat.Nim = 0;
    printf("A %d B %d\n", a, b); FBSWAP(Mat.Long, (anu*)&a, (anu*)&a); FBSWAP(Mat.Long, (anu*)&b, (anu*)&b);
    FADD(Mat.Long, (anu*)&r, (anu*)&a, (anu*)&b); FBSWAP(Mat.Long, (anu*)&r, (anu*)&r); printf("A + B = %d\n", r);
    FSUB(Mat.Long, (anu*)&r, (anu*)&a, (anu*)&b); FBSWAP(Mat.Long, (anu*)&r, (anu*)&r); printf("A - B = %d\n", r);
    FMUL(Mat.Long, (anu*)&r, (anu*)&a, (anu*)&b); FBSWAP(Mat.Long * 2, (anu*)&r, (anu*)&r); printf("A * B = %d\n", r); 
    zbuf c = -5, d = 3; zDbuf t = 0; Mat.Nim = 1;
    printf("C %d D %d\n", c, d); FBSWAP(Mat.Long, (anu*)&c, (anu*)&c); FBSWAP(Mat.Long, (anu*)&d, (anu*)&d);
    FADD(Mat.Long, (anu*)&t, (anu*)&c, (anu*)&d); FBSWAP(Mat.Long, (anu*)&t, (anu*)&t); printf("C + D = %d\n", t);
    FSUB(Mat.Long, (anu*)&t, (anu*)&c, (anu*)&d); FBSWAP(Mat.Long, (anu*)&t, (anu*)&t); printf("C - D = %d\n", t);
    FMUL(Mat.Long, (anu*)&t, (anu*)&c, (anu*)&d); FBSWAP(Mat.Long * 2, (anu*)&t, (anu*)&t); printf("C * D = %d\n", t); 
    return 0; }
