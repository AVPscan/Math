/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */
 
#include <stdio.h>
#include "sys.h"

anu a[] = {251,1,0,2}, la = 0, b[] = {128,0,1,0}, lb = 0, cl = 0, Nim = 0, Be = 1, V = 0, l, c[8], d[8], r[16], e[8];

void Num( anu s, an a) {
  if (Mat.Nim) { if (s > 8) printf("XxX"); else if (s > 3) printf("%ld", *(int64_t*)a);
    else if (s > 1) printf("%d", *(int32_t*)a); else if (s) printf("%d", *(int16_t*)a); else printf("%d", *(int8_t*)a); }
  else { if (s > 8) printf("XxX"); else if (s > 3) printf("%ld", *(uint64_t*)a); else if (s > 1) printf("%d", *(uint32_t*)a);
    else if (s) printf("%d", *(uint16_t*)a); else printf("%d", *(uint8_t*)a); } }
void Show(const char *s) { anu i = (s[0] == '*');
  printf(" %s%s", (Mat.C) ? "C" : " ", (Mat.F) ? (Mat.N) ? "I " : "Z " : (Mat.N) ? "- " : "+ "); Mat.C = 0;
  if (Mat.Be) { Fswap(((Mat.lb + 1) * (1 + i)) - 1, (an)r, (an)r); Fswap(Mat.lb, (an)e, (an)e); }
  Num(la, (an)c); printf(" %s ", s); Num(Mat.lb, (an)d); printf(" = ");
  if (s[0] == '+' || s[0] == '-') {
    Num(Mat.l, (an)r); printf("\n"); }
  else if (s[0] == '*') {
    Num(Mat.l, (an)r); printf(" long %d\n", ((Mat.cl << 8) | Mat.l)); }
  else { Num(Mat.l, (an)r); printf(" tile "); Num(Mat.lb, (an)e);
    printf(" %s", (Mat.Fre) ? (Mat.Nre) ? " I\n" : " Z\n" : (Mat.Nre) ? " -\n" : " +\n"); } 
  Flong(la, lb - 1, cl); }
void Test(anu type) { Mat.Nim = type; FADD(lb, r, Mat.A, Mat.B); Show("+"); FSUB(lb, r, Mat.A, Mat.B); Show("-");
  FMUL(lb, r, Mat.A, Mat.B); Show("*"); FDIV(lb, r, Mat.A, Mat.B, e); Show("/"); }

int main(void) {
  Fini(Nim, V, Be, la, lb, cl); Mat.A = (an)a; Mat.B = (an)b; Fmov(Mat.l, (an)c, Mat.A); Fmov(Mat.lb, (an)d, Mat.B);
  if (Mat.Be) { Fswap(Mat.l, (an)c, (an)c); Fswap(Mat.lb, (an)d, (an)d); }
  printf("long b = %d V = %d\n", (lb = Mat.lb + 1), Mat.V); Test(Nim); Test(~Nim);
  Fini(Nim, ~V, Be); Flong(la, lb - 1, cl);
  printf("long b = %d V = %d\n", lb, Mat.V); Test(Nim); Test(~Nim); return 0; }
