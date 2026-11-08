/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3).
 */

#include <stdio.h>
#include "math.h"

#define Obe    0    // вывод на экран {0} little endian, иначе big endian
#define NoSign 0    // беззнаковое представление
#define Sign   1    // знаковое представление
#define MatV   0    // возможность увеличения разрядности
#define m      128  // максимальное число атомов в числах

anu la,lb;
void Num(anu s, an a) { anu ns,t[m]; if (s > 8) printf(" %d|? ", s + 1);
  else { printf("(%d|%d) ", s + 1, (ns = FOLD(Obe, (an)t, s, a)) + 1); a = (an)t;
    if (Mat.na == 2) printf("inf "); else {
      if (Mat.Nim) { if (ns > 3) printf("%ld " , *(int64_t*)a); else if (ns > 1) printf("%d ", *(int32_t*)a);
        else if (ns) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
      else { if (ns > 3) printf("%lu ", *(uint64_t*)a); else if (ns > 1) printf("%u ", *(uint32_t*)a);
        else if (ns) printf("%u ", *(uint16_t*)a); else printf("%u ", *(uint8_t*)a); } } } }
void Show(char s) { Flong(Mat.lb,la); Mat.C = 0; if (s == '+') FAdd(Mat.R, Mat.A); else if (s == '-') FSub(Mat.R, Mat.A);
  else if (s == '*') FMul(Mat.R, Mat.A); else if (s == '/') FDiv(Mat.R, Mat.A, Mat.E); else if (s == '?') Ftst(Mat.A);
  else { Ftst(Mat.A, 127); } if (s == '?' || s == 'c') printf(" %c ", Mat.CF ? 'Z':Mat.CN ? '-':'+');
  else { printf("%c%c ", Mat.C ? 'C':' ', Mat.F ? Mat.N ? 'I':'Z':Mat.N ? '-':'+'); } Num(la, Mat.A);
  if (s == '?' || s == 'c') printf("%c ", Mat.CF ? '=':Mat.CN ? '<':'>'); else {
    if (s == 'c') printf("? "); else printf("%c ", s); } Num(Mat.lb, Mat.b); if (s < '?') { printf("= "); Num(Mat.l, Mat.R); }
  if (s == '/') { printf("  %c ", Mat.Fe ? (Mat.Ne ? 'I':'Z') : (Mat.Ne ? '-':'+')); Num(Mat.le, Mat.E); } printf("\n"); }
void Test(void) { Faddr((As)Mat.B); Flong(lb,la); anu t,i = 2; printf("%c%c A B\n", Mat.Nim ? 'N':' ', Mat.V ? 'V':' '); Show('+');
  Show('-'); Show('?'); Show('*'); /*Show('/');*/ printf("   A Const\n"); Show('c'); while(i--) { t = *Mat.b; *Mat.b = ++t; Show('?'); }
  Num(la, Mat.A); printf("%c FEq(A, 2,0,-2,-1,-10,-1)\n", FEq(Mat.A, 2,0,-2,-1,-10,-1) ? 'T':'F');
  Num(la, Mat.A); printf("%c FGe(A, -10,-1,-1,-1,0,1)\n", FGe(Mat.A, -10,-1,-1,-1,0,1) ? 'T':'F');}

int main(void) { anu a[m],b[m],e[m],r[m+m]; Faddr((As)b, (As)a, (As)r, (As)e); Fini(NoSign,MatV); la = Fvbe(Mat.A, -1,-10);
  lb = Fvle(Mat.B, -100,255,255,255,255); Test(); Fset(Sign,MatV); la = Fmov(la, Mat.A); lb = Fmov(lb, Mat.B); Test(); return 0; }
