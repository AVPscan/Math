/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */
 
#include <stdio.h>
#include "sys.h"

anu cl = 0, l = 1, a[] = {251,1,0,0}, lb, b[] = {6,0,0,0}, c[8], d[8], r[16], e[8];

void Num( anu s, an a) {
  if (Mat.Nim) { if (s > 8) printf("XxX"); else if (s > 3) printf("%ld", *(int64_t*)a);
    else if (s > 1) printf("%d", *(int32_t*)a); else if (s) printf("%d", *(int16_t*)a);
    else printf("%d", *(int8_t*)a); }
  else { if (s > 8) printf("XxX"); else if (s > 3) printf("%ld", *(uint64_t*)a);
    else if (s > 1) printf("%d", *(uint32_t*)a); else if (s) printf("%d", *(uint16_t*)a);
    else printf("%d", *(uint8_t*)a); } }
void Show(const char *s) { anu i = (s[0] == '*');
  printf(" %s%s", (Mat.C) ? "C" : " ", (Mat.F) ? (Mat.N) ? "I " : "Z " : (Mat.N) ? "- " : "+ "); Mat.C = 0;
  if (Mat.Be) { FSWAP(((Mat.lb + 1) * (1 + i)) - 1, (an)r, (an)r); FSWAP(Mat.lb, (an)e, (an)e); }
  Num(Mat.l, (an)c); printf(" %s ", s); Num(Mat.lb, (an)d); printf(" = ");
  if (s[0] == '+' || s[0] == '-') {
    Num(Mat.l, (an)r); printf("\n"); }
  else if (s[0] == '*') {
    Num(Mat.l, (an)r); printf(" long %d\n", ((Mat.cl << 8) | Mat.l)); }
  else { Num(Mat.l, (an)r); printf(" tile "); Num(Mat.lb, (an)e);
    printf(" %s", (Mat.Fre) ? (Mat.Nre) ? " I\n" : " Z\n" : (Mat.Nre) ? " -\n" : " +\n"); } }
void Test(anu type) { Mat.Nim = type; FADD(lb, r, Mat.A, Mat.B); Show("+"); Mat.cl = cl; Mat.l = l;
  FSUB(lb, r, Mat.A, Mat.B); Show("-"); Mat.cl = cl; Mat.l = l; FMUL(lb, r, Mat.A, Mat.B); Show("*");
  Mat.cl = cl; Mat.l = l; FDIV(lb, r, Mat.A, Mat.B, e); Show("/"); }

int main(void) {
  FINI(0,0,1); Mat.A = (an)a; Mat.B = (an)b; FMOV(Mat.lb, (an)c, Mat.A); FMOV(Mat.lb, (an)d, Mat.B);
  if (Mat.Be) { FSWAP(Mat.lb, (an)c, (an)c); FSWAP(Mat.lb, (an)d, (an)d); }
  printf("long b %d\n", (lb = Mat.lb + 1)); Test(0); Test(1); return 0; }
