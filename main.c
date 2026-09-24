/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */

#include <stdio.h>
#include "math.h"

#define Obe 0
#define m 128
anu la,lb;

void Num(anu s, an a) { anu ns, t[m]; if (s > 8) { printf(" %d|? ", s + 1); return; }
  printf("(%d|%d) ", s + 1, (ns = FCOLD(Obe, s, (an)t, a)) + 1); a = (an)t; if (Mat.F == 2) { printf("inf "); return; }
  if (Mat.Nim) { if (ns > 3) printf("%ld " , *(int64_t*)a); else if (ns > 1) printf("%d ", *(int32_t*)a);
    else if (ns) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
  else { if (ns > 3) printf("%lu ", *(uint64_t*)a); else if (ns > 1) printf("%u ", *(uint32_t*)a);
    else if (ns) printf("%u ", *(uint16_t*)a); else printf("%u ", *(uint8_t*)a); } }
void Show(char s) { Flong(la,lb); Mat.C = 0;
  if (s == '+') FAdd(); else if (s == '-') FSub(); else if (s == '*') FMul(); else if (s == '/') FDiv();
  else { FMulc(127); } printf("%c%c ", Mat.C ? 'C':' ', Mat.F ? (Mat.N ? 'I':'Z') : (Mat.N ? '-':'+'));
  Num(la, Mat.A); if (s == 'c') printf("* "); else { printf("%c ", s); } Num(Mat.lb, Mat.b); printf("= "); Num(Mat.l, Mat.R);
  if (s == '/') { printf("  %c ", Mat.Fe ? (Mat.Ne ? 'I':'Z') : (Mat.Ne ? '-':'+')); Num(Mat.le, Mat.E); } printf("\n"); }
void Const(void) { anu l, i = 2; printf("Const\n"); Show('c'); Mat.D = Mat.B;
  Mat.B = Mat.b; l = lb; lb = Mat.lb; while(i--) { (*Mat.B)++; Show('*'); } Mat.B = Mat.D; lb = l; }
void Test(void) { printf("%c A B\n", Mat.Nim ? 'N':' '); Show('+'); Show('-'); Show('*'); /*Show('/');*/Const(); }

int main(void) { anu a[m], b[m], e[m], r[m+m]; Faddr((As)r, (As)e, (As)a, (As)b);
  Fini(); la = Fbvi(Mat.A, 255,0); lb = Fvi(Mat.B, 255); Test();
  Fset(1); la = Fmov(la, Mat.A); lb = Fmov(lb, Mat.B); Test(); return 0; }
