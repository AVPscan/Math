/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include <stdio.h>
#include "math.h"

#define T 7
anu la = T, a[] = {0,0,0,0,0,0,0,0}, lb = T, b[] = {0,128,128,0,0,0,0,0,0};

void Num(anu s, an a) { anu t[8]; printf("(%d) ", s + 1); if (s > 7) { printf("XxX "); return; }
  Mat.L = s; FMOV((an)t, a, s); s = Mat.L; a = (an)t; FCOLD(a, a, s); s = Mat.l;
  if (Mat.Nim) { if (s > 3) printf("%ld " , *(int64_t*)a); else if (s > 1) printf("%d ", *(int32_t*)a);
    else if (s) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
  else { if (s > 3) printf("%lu ", *(uint64_t*)a); else if (s > 1) printf("%u ", *(uint32_t*)a);
    else if (s) printf("%u ", *(uint16_t*)a); else printf("%u ", *(uint8_t*)a); } }
void Show(char s) { anu i = 4; printf("\nA%cB\n", s); while(i--) { Mat.Nim = ((3 - i) & 2) ? 1 : 0; Mat.V = ((3 - i) & 1) ? 1 : 0;
	FMOV(Mat.B, Mat.B, lb); lb = Mat.L; FMOV(Mat.A, Mat.A, la); la = Mat.L; if (s == '+') Fadd(Mat.l, Mat.B);
	else if (s == '-') Fsub(Mat.l, Mat.B); else if (s == '*') Fmul(Mat.l, Mat.B); else if (s == '/') Fdiv(Mat.l, Mat.B);
    printf("%c%c%c%c ", Mat.C ? 'C' : ' ', Mat.F ? Mat.N ? 'I' : 'Z' : Mat.N ? '-' : '+', Mat.V ? 'v' : ' ', Mat.Nim ? 'n' : ' ');
    Num(Mat.L, Mat.R); if (!Mat.V) { Num(la, Mat.A); Num(Mat.l, Mat.B); }
    if (s == '/') { printf("%c tile ", (Mat.Fe) ? (Mat.Ne) ? 'I' : 'Z' : (Mat.Ne) ? '-' : '+'); Num(Mat.l, Mat.E); }
    printf("\n"); Mat.C = 0; Flong(lb, la); } }
 
int main(void) { anu r[16], e[8]; Fini(0, 0, 0, lb, la); Faddr((As)r, (As)e, (As)a, (As)b); // Nim,V,Be
  Show('+'); Show('-'); Show('*'); Show('/'); return 0; }
