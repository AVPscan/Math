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
  printf("(%d|%d) ", s + 1, (ns = FCOLD(Obe, s, (an)t, a)) + 1); a = (an)t;
  if (Mat.F && Mat.N) { printf("inf "); return; }
  if (Mat.Nim) { if (ns > 3) printf("%ld " , *(int64_t*)a); else if (ns > 1) printf("%d ", *(int32_t*)a);
    else if (ns) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
  else { if (ns > 3) printf("%lu ", *(uint64_t*)a); else if (ns > 1) printf("%u ", *(uint32_t*)a);
    else if (ns) printf("%u ", *(uint16_t*)a); else printf("%u ", *(uint8_t*)a); } }
void Show(char s) { anu i = 2; printf("\n"); while(i--) { Mat.Nim = 1 - i;
    Mat.C = 0; Flong(la); if (s == '+') FAdd(lb, Mat.B); else if (s == '-') FSub(lb, Mat.B);
    else if (s == '*') FMul(lb, Mat.B); else if (s == '/') FDiv(lb, Mat.B); else FSubc(55);
    printf("%c%c%c%c ", Mat.Nim ? 'N':' ', Mat.C ? 'C':' ', Mat.F ? (Mat.F == 2) ? 'I':'Z':' ',(Mat.N ? '-':'+'));
    Num(la, Mat.A); printf("%c ", s); if (s == '+' || s == '-' || s == '*' || s == '/') Num(lb, Mat.B);
    else { printf("X|x Const "); } printf("= "); Num(Mat.l, Mat.R); if (s == '/') {
      printf("  %c ", Mat.Fe ? (Mat.Ne ? 'I':'Z') : (Mat.Ne ? '-':'+')); Num(Mat.le, Mat.E); } printf("\n"); } }

int main(void) { anu a[m],b[m],e[m],r[m+m]; Faddr((As)r, (As)e, (As)a, (As)b);
  Fini(); la = Fbvi(Mat.A, 255,255,129); lb = Fbvi(Mat.B, 128); printf("  A "); Num(la, Mat.A); printf("B ");
  Num(lb, Mat.B); Fini(1); printf("\nN A "); Num(la, Mat.A); printf("B "); Num(lb, Mat.B); printf("Const (1|1) 55\n");
  Show('+'); Show('-'); Show('M');/*Show('*'); Show('/');*/return 0; }
