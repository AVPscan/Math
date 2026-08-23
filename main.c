/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */
 
#include <stdio.h>
#include "sys.h"

anu a[] = {251,5,0,0,0,0,0,0}, b[] = {6,0,0,0,0,0,0,0};
anu cl = 0, la = 1, lb = 1, Nim = 0, Be = 0, V = 0, c[8], r[16], e[8];

void Num(anu s, an a) {
  if (s > 7) { printf("XxX"); return; } printf("(%d) ", s + 1); FCold(s, (an)c, a); a = (an)c; s = Mat.lre;
  if (Mat.Be == 0) Fswap(s, a, a);      // Так как задаю операнды в Be формате и библиотека пока на нём
  if (Mat.Nim) { if (s > 3) printf("%ld", *(int64_t*)a); else if (s > 1) printf("%d", *(int32_t*)a);
    else if (s) printf("%d", *(int16_t*)a); else printf("%d", *(int8_t*)a); }
  else { if (s > 3) printf("%ld", *(uint64_t*)a); else if (s > 1) printf("%d", *(uint32_t*)a);
    else if (s) printf("%d", *(uint16_t*)a); else printf("%d", *(uint8_t*)a); } }
void Show(const char *s) {
  printf(" %s%s", (Mat.C) ? "C" : " ", (Mat.F) ? (Mat.N) ? "I " : "Z " : (Mat.N) ? "- " : "+ ");
  Num(la, Mat.A); printf(" %s ", s); Num(Mat.lb, Mat.B); printf(" = "); Num(Mat.l, Mat.R);
  if (s[0] == '/') { printf(" "); Num(Mat.lb, Mat.RE);
    printf(" %s", (Mat.Fre) ? (Mat.Nre) ? " I" : " Z" : (Mat.Nre) ? " -" : " +"); } 
  printf("\n"); Mat.C = 0; Flong(cl, la); }
void Test(anu type) { Mat.Nim = type;
  FADD(lb, Mat.R, Mat.A, Mat.B); Show("+");
  FSUB(lb, Mat.R, Mat.A, Mat.B); Show("-");
  FMUL(lb, Mat.R, Mat.A, Mat.B); Show("*");
  FDIV(lb, Mat.R, Mat.A, Mat.B, Mat.RE); Show("/"); }

int main(void) {
  Fini(Nim, V, Be, cl, la, lb); lb = Mat.lb + 1; Mat.A = (an)a; Mat.B = (an)b; Mat.R = (an)r; Mat.RE = (an)e;
  printf("long b = %d V = %d\n", lb, Mat.V); Test(Nim); Test(~Nim);
  Fini(Nim, ~V, Be); Flong(cl, la, lb - 1);
  printf("long b = %d V = %d\n", lb, Mat.V); Test(Nim); Test(~Nim); return 0; }
