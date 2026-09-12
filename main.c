/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include <stdio.h>
#include "math.h"

#define InputBigEndian 1
#define OutputBigEndian 0
anu la = 1, a[] = {128,1,2,3,4,5,6,7}, l = 8;
anu lb = 1, b[] = {129,255,255,255,255,255,255,255};

void Num(anu f, anu s, an a) { anu t[l]; if (s >= l) { printf(" %d|? ", s + 1); return; }
  FMOV(s, (an)t, a); a = (an)t; printf(" %d|%d  ", s + 1, Mat.lar + 1); Fcold(Mat.lar, a) if (f == 2) { printf("inf "); return; }
  if (Mat.Nim) { if (Mat.lar > 3) printf("%ld " , *(int64_t*)a); else if (Mat.lar > 1) printf("%d ", *(int32_t*)a);
    else if (Mat.lar) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
  else { if (Mat.lar > 3) printf("%lu ", *(uint64_t*)a); else if (Mat.lar > 1) printf("%u ", *(uint32_t*)a);
    else if (Mat.lar) printf("%u ", *(uint16_t*)a); else printf("%u ", *(uint8_t*)a); } }
void Show(char s) { anu i = 4; printf("\nA%cB\n", s);
  while(i--) { Mat.Nim = ((3 - i) & 2) ? 1 : 0; Mat.V = ((3 - i) & 1) ? 1 : 0; Mat.C = 0; Flong(la, lb) 
	if (s == '+') FAdd(Mat.R) else if (s == '-') FSub(Mat.R) else if (s == '*') FMul(Mat.R)
	else if (s == '/') FDiv(Mat.R, Mat.E) else if (s == 'x') FAddc(Mat.R,255,255)
    printf("%c%c%c%c ", Mat.Nim ? 'N':' ', Mat.V ? 'V':' ', Mat.C ? 'C':' ', Mat.F ? (Mat.N ? 'I':'Z'):(Mat.N ? '-':'+'));
    Num(Mat.F, Mat.lar, Mat.R); Num(0, la, Mat.A); if (s != 'x') Num(0, lb, Mat.B);
    else { printf(" X|x  Const"); } if (s == '/') {
	  printf("  %c ", Mat.Fe ? (Mat.Ne ? 'I':'Z') : (Mat.Ne ? '-':'+')); Num(Mat.Fe, Mat.lbe, Mat.E); } printf("\n"); } }
int main(void) { anu r[l + l], e[l]; Fini(OutputBigEndian) Faddr((As)r, (As)e, (As)a, (As)b)
  if (InputBigEndian) { Fswap(lb, Mat.B) Fswap(la, Mat.A) } printf("%d|%d", la + 1, lb + 1);
  Show('+'); Show('x');/*Show('-'); Show('*'); Show('/');*/return 0; }
