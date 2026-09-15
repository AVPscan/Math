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
#define m 128
anu la,lb;

void Num(anu s, an a) { anu t[m]; if (s > 8) { printf(" %d|? ", s + 1); return; }
  FMOV(s, (an)t, a); a = (an)t; printf("(%d|%d) ", s + 1, Mat.l + 1);
  Fcold(OutputBigEndian, Mat.l, a); if (Mat.F && Mat.N) { printf("inf "); return; }
  if (Mat.Nim) { if (Mat.l > 3) printf("%ld " , *(int64_t*)a); else if (Mat.l > 1) printf("%d ", *(int32_t*)a);
    else if (Mat.l) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
  else { if (Mat.l > 3) printf("%lu ", *(uint64_t*)a); else if (Mat.l > 1) printf("%u ", *(uint32_t*)a);
    else if (Mat.l) printf("%u ", *(uint16_t*)a); else printf("%u ", *(uint8_t*)a); } }
void Show(char s) { anu lr, i = 4; printf("\n"); while(i--) { Mat.Nim = ((3 - i) & 2) ? 1:0; Mat.V = ((3 - i) & 1) ? 1:0;
    Mat.C = 0; Flong(la, lb); if (s == '+') FAdd(lb, Mat.B); else if (s == '-') FSub(lb, Mat.B);
    else if (s == '*') FMul(lb, Mat.B); else if (s == '/') FDiv(lb, Mat.B); else FSubc(2);
    printf("%c%c%c%c ", Mat.Nim ? 'N':' ', Mat.V ? 'V':' ', Mat.C ? 'C':' ', Mat.F ? (Mat.N ? 'I':'Z'):(Mat.N ? '-':'+'));
    lr = Mat.l; Num(la, Mat.A); printf("%c ", s); if (s == '+' || s == '-' || s == '*' || s == '/') Num(lb, Mat.B);
    else { printf("X|x Const "); } printf("= "); Num(lr, Mat.R); if (s == '/') {
      printf("  %c ", Mat.Fe ? (Mat.Ne ? 'I':'Z') : (Mat.Ne ? '-':'+')); Num(Mat.le, Mat.E); } printf("\n"); } }

int main(void) { anu a[m],b[m],e[m],r[m+m]; Fini(1); Faddr((As)r, (As)e, (As)a, (As)b);
  printf("A "); Num(la = Const(InputBigEndian, Mat.A, 128,1), Mat.A);
  printf("B "); Num(lb = Const(InputBigEndian, Mat.B, 255), Mat.B);
  printf("Const (1|1) 2\n"); Show('+'); Show('-'); Show('M');//Show('*'); Show('/');
  return 0; }
