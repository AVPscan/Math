/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */
 
#include <stdio.h>
#include "sys.h"

#define T 0
anu a[] = {255,0,0,0,0,0,0,0}, b[] = {255,254,0,0,0,0,0,0}, c[16], r[16], e[8];
anu cl = 0, la = T, lb = T, Nim = 0, Be = 0, V = 0;

void Num(anu s, an a) {
  if (s > 7) { printf("XxX"); return; }
  Fswap(s, (an)c, a); a = (an)c; FCold(s, a, a); s = Mat.lre;
  if (Mat.Nim) { if (s > 3) printf("%ld" , *(int64_t*)a); else if (s > 1) printf("%d ", *(int32_t*)a);
    else if (s) printf("%d ", *(int16_t*)a); else printf("%d ", *(int8_t*)a); }
  else { if (s > 3) printf("%ld ", *(uint64_t*)a); else if (s > 1) printf("%d ", *(uint32_t*)a);
    else if (s) printf("%d ", *(uint16_t*)a); else printf("%d ", *(uint8_t*)a); } }

void Show(const char *s) {
  printf("\n%s%s", (Mat.C) ? "C" : " ", (Mat.F) ? (Mat.N) ? "I " : "Z " : (Mat.N) ? "- " : "+ ");
  printf("%s%s ", Mat.Nim ? "n" : " ", Mat.V ? "v " : "  "); printf("(%d %d %s %d) = ", la + 1, lb, s, Mat.l + 1); Num(Mat.l, Mat.R);
  if (s[0] == '/') { printf("(%d) %s tile ", lb, (Mat.Fre) ? (Mat.Nre) ? "I" : "Z" : (Mat.Nre) ? "-" : "+"); Num(Mat.lb, Mat.RE); } 
  Mat.C = 0; Flong(cl, la); }

void Test(anu type) {
  Mat.Nim = type; Fadd(Mat.lb, Mat.R, Mat.A, Mat.B); Show("add"); FADD(lb, Mat.R, Mat.A, Mat.B); Show("+"); 
  FSUB(lb, Mat.R, Mat.A, Mat.B); Show("-"); FMUL(lb, Mat.R, Mat.A, Mat.B); Show("*");
  FDIV(lb, Mat.R, Mat.A, Mat.B, Mat.RE); Show("/"); }

int main(void) {
  Fini(Nim, V, Be, cl, la, lb); lb = Mat.lb + 1; Mat.A = (an)a; Mat.B = (an)b; Mat.R = (an)r; Mat.RE = (an)e;
  printf("A (%d) ", Mat.l + 1); Num(Mat.l, Mat.A); Mat.Nim++; Num(Mat.l, Mat.A); Mat.Nim--;
  printf("\nB (%d) ", Mat.lb + 1); Num(Mat.lb, Mat.B); Mat.Nim++; Num(Mat.lb, Mat.B); Mat.Nim--;
  Test(Nim); Test(~Nim); Fini(Nim, ~V, Be); Flong(cl, la, lb - 1); Test(Nim); Test(~Nim); return 0; }
