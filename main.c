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

int main(void) {
    uint32_t a = 5;
    uint32_t b = 3;
    uint64_t r = 0;
    Mat.Nim = 0; Mat.Long = 4;
    
    printf("A %d B %d\n", a, b); FBSWAP(Mat.Long, (anu*)&a, (anu*)&a); FBSWAP(Mat.Long, (anu*)&b, (anu*)&b);
    FADD(Mat.Long, (anu*)&r, (anu*)&a, (anu*)&b); FBSWAP(Mat.Long, (anu*)&r, (anu*)&r); printf("A + B = %d\n", r);
    FSUB(Mat.Long, (anu*)&r, (anu*)&a, (anu*)&b); FBSWAP(Mat.Long, (anu*)&r, (anu*)&r); printf("A - B = %d\n", r);
    FMUL(Mat.Long, (anu*)&r, (anu*)&a, (anu*)&b); FBSWAP(Mat.Long * 2, (anu*)&r, (anu*)&r); printf("A * B = %d\n", r); 
    
    return 0; }
