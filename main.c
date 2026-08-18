/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */
 
#include <stdio.h>
#include "sys.h"

#define BE  0
#define Lon 1

anu a[] = {251,1,0,0}, b[] = {6,0,0,0}, c[4] = {0}, d[4] = {0}, r[8] = {0}, e[4] = {0};

void Show(const char *s) { anu i;
  printf(" %s%s", (Mat.C) ? "C" : " ", (Mat.F) ? (Mat.N) ? "I " : "Z " : (Mat.N) ? "- " : "+ ");
  Mat.C = 0; i = (s[0] == '*') ? 2 : 1; if (!BE) { FSWAP(Mat.lb * i, r, r); FSWAP(Mat.lb, e, e); } if (Lon == 4) {
    if (Mat.Nim) { printf("%d %s %d = ", *(int32_t*)c, s, *(int32_t*)d); if (i > 1) printf("%ld", *(int64_t*)r); else printf("%d", *(int32_t*)r); }
    else { printf("%d %s %d = ", *(uint32_t*)c, s, *(uint32_t*)d); if (i > 1) printf("%ld", *(uint64_t*)r); else printf("%d", *(uint32_t*)r); } }
  else if (Lon == 2) {
    if (Mat.Nim) { printf("%d %s %d = ", *(int16_t*)c, s, *(int16_t*)d); if (i > 1) printf("%d", *(int32_t*)r); else printf("%d", *(int16_t*)r); }
    else { printf("%d %s %d = ", *(uint16_t*)c, s, *(uint16_t*)d); if (i > 1) printf("%d", *(uint32_t*)r); else printf("%d", *(uint16_t*)r); } }
  else if (Lon == 1) {
    if (Mat.Nim) { printf("%d %s %d = ", *(int8_t*)c, s, *(int8_t*)d); if (i > 1) printf("%d", *(int16_t*)r); else printf("%d", *(int8_t*)r); }
    else { printf("%d %s %d = ", *(uint8_t*)c, s, *(uint8_t*)d); if (i > 1) printf("%d", *(uint16_t*)r); else printf("%d", *(uint8_t*)r); } }
  if (s[0] == '*') { printf(" long %d", ((Mat.cl << 8) | Mat.l)); }
  else if (s[0] == '/') {
    if (Lon == 4) { if (Mat.Nim) printf(" tile %d", *(int32_t*)e); else printf(" tile %d", *(uint32_t*)e); }
    else if (Lon == 2) { if (Mat.Nim) printf(" tile %d", *(int16_t*)e); else printf(" tile %d", *(uint16_t*)e); }
    else if (Lon == 1) { if (Mat.Nim) printf(" tile %d", *(int8_t*)e); else printf(" tile %d", *(uint8_t*)e); }
    printf(" %s", (Mat.Fre) ? (Mat.Nre) ? " I" : " Z" : (Mat.Nre) ? " -" : " +"); } printf("\n"); }

int main(void) {
  FINI(Lon); printf("Long = %d\n", Mat.lb); Mat.A = (an)a; Mat.B = (an)b; FSWAP(Mat.lb, (an)c, Mat.A);
  FSWAP(Mat.lb, (an)d, Mat.B); if (BE) { FSWAP(Mat.lb, (an)c, (an)c); FSWAP(Mat.lb, (an)d, (an)d); }
  FADD(Mat.lb, r, Mat.A, Mat.B); Show("+"); FSUB(Mat.lb, r, Mat.A, Mat.B); Show("-"); FMUL(Mat.lb, r, Mat.A, Mat.B);
  Show("*"); Mat.cl = 0; Mat.l = Mat.lb; FDIV(Mat.lb, r, Mat.A, Mat.B, e); Show("/"); Mat.Nim = 1;
  FADD(Mat.lb, r, Mat.A, Mat.B); Show("+"); FSUB(Mat.lb, r, Mat.A, Mat.B); Show("-"); FMUL(Mat.lb, r, Mat.A, Mat.B);
  Show("*"); Mat.cl = 0; Mat.l = Mat.lb; FDIV(Mat.lb, r, Mat.A, Mat.B, e); Show("/"); return 0; }
