/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include <stdio.h>
#include "math.h"

#define T 1
anu la = T, a[] = {0,0,0,0,0,0,0,0}, lb = T, b[] = {0,128,128,0,0,0,0,0,0};

void Num(anu s, an a) {
  anu t[8]; printf("(%d) ", s + 1); if (s > 7) { printf("XxX "); return; } FCOLD(s, (an)t, a); s = Mat.lbe; a = (an)t;
  if (Mat.Nim) { if (s > 3) printf("%ld " , *(int64_t*)a); else if (s > 1) printf("%d ", *(int32_t*)a);
    else if (s) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
  else { if (s > 3) printf("%lu ", *(uint64_t*)a); else if (s > 1) printf("%u ", *(uint32_t*)a);
    else if (s) printf("%u ", *(uint16_t*)a); else printf("%u ", *(uint8_t*)a); } }

void Show(char s) {
  anu i = 4; printf("\nA%cB\n", s); while(i--) { Mat.Nim = ((3 - i) & 2) ? 1 : 0; Mat.V = ((3 - i) & 1) ? 1 : 0;
	if (s == '+') FAdd(Mat.R) else if (s == '-') FSub(Mat.R) else if (s == '*') FMul(Mat.R) else if (s == '/') FDiv(Mat.R, Mat.E)
    printf("%c%c%c%c ", Mat.C ? 'C' : ' ', Mat.F ? Mat.N ? 'I' : 'Z' : Mat.N ? '-' : '+', Mat.V ? 'v' : ' ', Mat.Nim ? 'n' : ' ');
    Num(Mat.lar, Mat.R); if (!Mat.V) { Num(la, Mat.A); Num(lb, Mat.B); }
    if (s == '/') { printf("%c tile ", (Mat.Fe) ? (Mat.Ne) ? 'I' : 'Z' : (Mat.Ne) ? '-' : '+'); Num(Mat.lbe, Mat.E); Flong(la, lb) }
    else { Flong(la) } printf("\n"); Mat.C = 0; } }

int main(void) { printf("%d %d", la + 1, lb + 1);
  anu r[16], e[8]; Fini() Faddr((As)r, (As)e, (As)a, (As)b) Fmov(lb, Mat.B) lb = Mat.lar;
  Fmov(la, Mat.A) la = Mat.lar; Show('+'); Show('-'); Show('*'); Show('/'); return 0; }
