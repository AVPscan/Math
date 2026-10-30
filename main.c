/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3).
 */

#include <stdio.h>
#include "math.h"

#define Obe 0   // input little endian 0, else big endian
#define m 128

anu la,lb;
void Num(anu s, an a) { anu ns, t[m]; if (s > 8) printf(" %d|? ", s + 1);
  else { printf("(%d|%d) ", s + 1, (ns = FCOLD(Obe, s, (an)t, a)) + 1); a = (an)t;
    if (Mat.na == 2) printf("inf "); else {
      if (Mat.Nim) { if (ns > 3) printf("%ld " , *(int64_t*)a); else if (ns > 1) printf("%d ", *(int32_t*)a);
        else if (ns) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
      else { if (ns > 3) printf("%lu ", *(uint64_t*)a); else if (ns > 1) printf("%u ", *(uint32_t*)a);
        else if (ns) printf("%u ", *(uint16_t*)a); else printf("%u ", *(uint8_t*)a); } } } }
void Show(char s) { Flong(la,lb); Mat.C = 0; if (s == '+') FAdd(Mat.R, Mat.A); else if (s == '-') FSub(Mat.R, Mat.A);
  else if (s == '*') FMul(Mat.R, Mat.A); else if (s == '/') FDiv(Mat.R, Mat.A, Mat.E); else if (s == '?') Fcmp(Mat.A);
  else { Fcmp(Mat.A, 127); } printf("%c%c ", Mat.C ? 'C':' ', Mat.F ? Mat.N ? 'I':'Z':Mat.N ? '-':'+'); Num(la, Mat.A);
  if (s == '?' || s == 'c') printf("%c ", Mat.N ? '<':Mat.F ? '=':'>');
  else { if (s == 'c') printf("? "); else printf("%c ", s); } Num(Mat.lb, Mat.b); if (s < '?') { printf("= "); Num(Mat.l, Mat.R);
    if (s == '/') { printf("  %c ", Mat.Fe ? (Mat.Ne ? 'I':'Z') : (Mat.Ne ? '-':'+')); Num(Mat.le, Mat.E); } } printf("\n"); }
void Const(void) { an sb; anu l, i = 2; printf("   A Const\n"); Show('c'); sb = Mat.B; Mat.B = Mat.b; l = lb; lb = Mat.lb;
  while(i--) { if (!++(*Mat.B) && lb) { (*(Mat.B + 1))++; } Show('?'); } Mat.B = sb; lb = l; }
void Test(void) { printf("%c%c A B\n", Mat.Nim ? 'N':' ', Mat.V ? 'V':' '); Show('+'); Show('-'); Show('?');
  Show('*'); /*Show('/');*/ Const(); }
void Cmp(void) { Num(la, Mat.A); Mat.C = 0; printf("%s Feq(A, 2,0,-2,-1,0,4)\n", Feq(Mat.A, 2,0,-2,-1,0,4) ? "True":"False");
  Num(la, Mat.A); printf("%s Fge(A, -5,-1,0,0,3,0)\n", Fge(Mat.A, -5,-1,0,0,3,0) ? "True":"False"); }
int main(void) { anu v = 0,a[m],b[m],e[m],r[m+m]; Faddr((As)r, (As)e, (As)a, (As)b); Fini(0,v); la = Fbv(Mat.A, -1,-2);
  lb = Fv(Mat.B, -100,255,255,255,255); Test(); Fset(1,v); la = Fmov(la, Mat.A); lb = Fmov(lb, Mat.B); Test(); Cmp(); return 0; }
