/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */
 
#include <stdio.h>
#include "math.h"

#define T 2
anu a[] = {255,0,0,0,0,0,0,0}, b[] = {255,254,0,0,0,0,0,0}, c[16], r[16], e[8];
anu cl = 0, la = T, lb = T, Nim = 0, Be = 0, V = 0;

void Num(anu s, an a) { printf("(%d) ", s + 1); if (s > 7) { printf("XxX "); return; }
  if (Mat.Be) Fmov(s, (an)c, a); else { Fswap(s, (an)c, a); } a = (an)c; FCold(s, a, a); s = Mat.lre;
  if (Mat.Nim) { if (s > 3) printf("%ld " , *(int64_t*)a); else if (s > 1) printf("%d ", *(int32_t*)a);
    else if (s) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
  else { if (s > 3) printf("%ld ", *(uint64_t*)a); else if (s > 1) printf("%d ", *(uint32_t*)a);
    else if (s) printf("%d ", *(uint16_t*)a); else printf("%d ", *(uint8_t*)a); } }

void Si(void) { Fswap(la, Mat.A, Mat.A); Fswap(Mat.lb, Mat.B, Mat.B); }
void Se(void) { Fswap(la, Mat.A, Mat.A); Fswap(Mat.lb, Mat.B, Mat.B); Fswap(Mat.l, Mat.R, Mat.R); }

void Show(char s) { anu i = 4; printf("\nA%cB\n", s); while(i--) {
    Mat.Nim = ((3 - i) & 2) ? 1 : 0; Mat.V = ((3 - i) & 1) ? 1 : 0;
    if (s == 'a') { Si(); Fadd(Mat.lb, Mat.R, Mat.A, Mat.B); Se(); }
    else if (s == '+') { FADD(Mat.lb + 1, Mat.R, Mat.A, Mat.B); }
    else if (s == '-') { FSUB(Mat.lb + 1, Mat.R, Mat.A, Mat.B); }
    else if (s == '*') { FMUL(Mat.lb + 1, Mat.R, Mat.A, Mat.B); }
    else if (s == '/') { FDIV(Mat.lb + 1, Mat.R, Mat.A, Mat.B, Mat.RE); }
    printf("%c%c%c", (Mat.C) ? 'C' : ' ', (Mat.F) ? (Mat.N) ? 'I' : 'Z' : (Mat.N) ? '-' : '+', Mat.V ? 'v' : ' ');
    printf("%c ", Mat.Nim ? 'n' : ' '); Num(Mat.l, Mat.R); if (!Mat.V) { Num(la, Mat.A); Num(Mat.lb, Mat.B); }
    if (s == '/') { printf("%c tile ", (Mat.Fre) ? (Mat.Nre) ? 'I' : 'Z' : (Mat.Nre) ? '-' : '+'); Num(Mat.lb, Mat.RE); } 
    printf("\n"); Mat.C = 0; Flong(cl, la); } }

int main(void) { Fini(Nim, V, Be, cl, la, lb); Mat.A = (an)a; Mat.B = (an)b; Mat.R = (an)r; Mat.RE = (an)e;
  Show('a'); Show('+'); Show('-'); Show('*'); Show('/'); return 0; }
