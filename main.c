/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете 
 * распространять ее и/или изменять согласно условиям Стандартной общественной 
 * лицензии GNU (GPLv3). 
 */
 
#include <stdio.h>
#include "sys.h"

anu BE = 0, lb = 1, cl = 0, l = 1, a[] = {251,1,0,0}, b[] = {6,0,0,0}, c[4], d[4], r[8], e[4];

void Show(const char *s) { anu i = (s[0] == '*');
  printf(" %s%s", (Mat.C) ? "C" : " ", (Mat.F) ? (Mat.N) ? "I " : "Z " : (Mat.N) ? "- " : "+ "); Mat.C = 0;
  if (!BE) { FSWAP(Mat.lb * (1 + i), r, r); FSWAP(Mat.lb, e, e); }
  if (lb == 4) {
    if (Mat.Nim) { printf("%d %s %d = ", *(int32_t*)c, s, *(int32_t*)d); if (i) printf("%ld", *(int64_t*)r); else printf("%d", *(int32_t*)r); }
    else { printf("%d %s %d = ", *(uint32_t*)c, s, *(uint32_t*)d); if (i) printf("%ld", *(uint64_t*)r); else printf("%d", *(uint32_t*)r); } }
  else if (lb == 2) {
    if (Mat.Nim) { printf("%d %s %d = ", *(int16_t*)c, s, *(int16_t*)d); if (i) printf("%d", *(int32_t*)r); else printf("%d", *(int16_t*)r); }
    else { printf("%d %s %d = ", *(uint16_t*)c, s, *(uint16_t*)d); if (i) printf("%d", *(uint32_t*)r); else printf("%d", *(uint16_t*)r); } }
  else if (lb == 1) {
    if (Mat.Nim) { printf("%d %s %d = ", *(int8_t*)c, s, *(int8_t*)d); if (i) printf("%d", *(int16_t*)r); else printf("%d", *(int8_t*)r); }
    else { printf("%d %s %d = ", *(uint8_t*)c, s, *(uint8_t*)d); if (i) printf("%d", *(uint16_t*)r); else printf("%d", *(uint8_t*)r); } }
  if (s[0] == '*') {
    printf(" long %d", ((Mat.cl << 8) | Mat.l)); }
  else if (s[0] == '/') {
    if (lb == 4) { if (Mat.Nim) printf(" tile %d", *(int32_t*)e); else printf(" tile %d", *(uint32_t*)e); }
    else if (lb == 2) { if (Mat.Nim) printf(" tile %d", *(int16_t*)e); else printf(" tile %d", *(uint16_t*)e); }
    else if (lb == 1) { if (Mat.Nim) printf(" tile %d", *(int8_t*)e); else printf(" tile %d", *(uint8_t*)e); }
    printf(" %s", (Mat.Fre) ? (Mat.Nre) ? " I" : " Z" : (Mat.Nre) ? " -" : " +"); }
  printf("\n"); }

int main(void) { FINI(lb); printf("long b %d\n", Mat.lb); Mat.A = (an)a; Mat.B = (an)b;
  FSWAP(Mat.lb, (an)c, Mat.A); FSWAP(Mat.lb, (an)d, Mat.B); if (BE) { FSWAP(Mat.lb, (an)c, (an)c); FSWAP(Mat.lb, (an)d, (an)d); }
  Mat.cl = cl; Mat.l = l; FADD(Mat.lb, r, Mat.A, Mat.B); Show("+");
  Mat.cl = cl; Mat.l = l; FSUB(Mat.lb, r, Mat.A, Mat.B); Show("-");
  Mat.cl = cl; Mat.l = l; FMUL(Mat.lb, r, Mat.A, Mat.B); Show("*");
  Mat.cl = cl; Mat.l = l; FDIV(Mat.lb, r, Mat.A, Mat.B, e); Show("/"); Mat.Nim = 1;
  Mat.cl = cl; Mat.l = l; FADD(Mat.lb, r, Mat.A, Mat.B); Show("+");
  Mat.cl = cl; Mat.l = l; FSUB(Mat.lb, r, Mat.A, Mat.B); Show("-");
  Mat.cl = cl; Mat.l = l; FMUL(Mat.lb, r, Mat.A, Mat.B); Show("*");
  Mat.cl = cl; Mat.l = l; FDIV(Mat.lb, r, Mat.A, Mat.B, e); Show("/");
  return 0; }
