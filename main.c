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
anu la = 2, a[] = {0,0,127,3,4,5,6,7}, l = 8;
anu lb = 7, b[] = {255,255,255,255,255,255,255,129};

void Num(anu s, an a) { anu t[l]; if (s >= l) { printf("(%d) XxX ", s + 1); return; }
  FMOV(s, (an)t, a); a = (an)t; printf("(%d) ", Mat.lar + 1); Fcold(Mat.lar, a)
  if (Mat.Nim) { if (Mat.lar > 3) printf("%ld " , *(int64_t*)a); else if (Mat.lar > 1) printf("%d ", *(int32_t*)a);
    else if (Mat.lar) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
  else { if (Mat.lar > 3) printf("%lu ", *(uint64_t*)a); else if (Mat.lar > 1) printf("%u ", *(uint32_t*)a);
    else if (Mat.lar) printf("%u ", *(uint16_t*)a); else printf("%u ", *(uint8_t*)a); } }
void Show(char s) { anu i = 4; printf("\nA%cB\n", s);
  while(i--) { Mat.Nim = ((3 - i) & 2) ? 1 : 0; Mat.V = ((3 - i) & 1) ? 1 : 0;
	if (s == '+') FAdd(Mat.R) else if (s == '-') FSub(Mat.R) else if (s == '*') FMul(Mat.R) else if (s == '/') FDiv(Mat.R, Mat.E)
    printf("%c%c%c%c ", Mat.Nim ? 'N':' ', Mat.V ? 'V':' ', Mat.C ? 'C':' ', Mat.F ? (Mat.N ? 'I':'Z'):(Mat.N ? '-':'+'));
    Num(Mat.lar, Mat.R); Num(la, Mat.A); Num(lb, Mat.B); if (s == '/') {
	  printf("tile %c ", Mat.Fe ? (Mat.Ne ? 'I':'Z') : (Mat.Ne ? '-':'+')); Num(Mat.lbe, Mat.E); Flong(la, lb) }
    else { Flong(la) } printf("\n"); Mat.C = 0; } }

int main(void) { anu r[l + l], e[l]; Fini(OutputBigEndian) Faddr((As)r, (As)e, (As)a, (As)b)
  if (InputBigEndian) { Fswap(lb, Mat.B) Fswap(la, Mat.A) } printf("%d %d", la + 1, lb + 1);
  Show('+'); Show('-'); Show('*'); Show('/'); return 0; }
