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

#if Lon == 1
 typedef uint8_t buf; typedef int8_t zbuf;
 typedef uint16_t Dbuf; typedef int16_t zDbuf;
 anu a_data[] = {251}, b_data[] = {6};
#elif Lon == 2
 typedef uint16_t buf; typedef int16_t zbuf;
 typedef uint32_t Dbuf; typedef int32_t zDbuf;
 anu a_data[] = {2,1}, b_data[] = {4,0};
#elif Lon == 4
 typedef uint32_t buf; typedef int32_t zbuf;
 typedef uint64_t Dbuf; typedef int64_t zDbuf;
 anu a_data[] = {128,5,0,0}, b_data[] = {127,0,0,0};
#endif
buf o1, o2; zbuf o3, o4;
an a = a_data, b = b_data;

void Show(anu i, const char *str, void *r, void *e) {
  printf(" %s%s", (Mat.C) ? "C" : " ", (Mat.F) ? (Mat.N) ? "I " : "Z " : (Mat.N) ? "- " : "+ ");
  Mat.C = 0; i = (i != 2) ? 1 : 2; if (!BE) { FSWAP(Mat.lb * i, (an)r, (an)r); FSWAP(Mat.lb, (an)e, (an)e); }
#if Lon == 4
  if (Mat.Nim) { printf("%d %s %d = ", o3, str, o4); if (i > 1) printf("%ld", *(zDbuf*)r); else printf("%d", *(zbuf*)r); }
  else { printf("%d %s %d = ", o1, str, o2); if (i > 1) printf("%ld", *(Dbuf*)r); else printf("%d", *(buf*)r); }
#else
  if (Mat.Nim) { printf("%d %s %d = ", o3, str, o4); if (i > 1) printf("%d", *(zDbuf*)r); else printf("%d", *(zbuf*)r); }
  else { printf("%d %s %d = ", o1, str, o2); if (i > 1) printf("%d", *(Dbuf*)r); else printf("%d", *(buf*)r); }
#endif
  if (str[0] == '*') { printf(" long %d", ((Mat.cl << 8) | Mat.l)); }
  else if (str[0] == '/') { if (Mat.Nim) printf(" tile %d", *(zbuf*)e); else printf(" tile %d", *(buf*)e);
    printf(" %s", (Mat.Fre) ? (Mat.Nre) ? " I" : " Z" : (Mat.Nre) ? " -" : " +"); } printf("\n"); }

int main(void) {
  FINI(Lon); printf("Long = %d\n", Mat.lb); buf r, e; Dbuf rm; zbuf zr, ze; zDbuf zm; Mat.A = a; Mat.B = b;
  FSWAP(Mat.lb, (an)&o1, Mat.A); FSWAP(Mat.lb, (an)&o2, Mat.B); FSWAP(Mat.lb, (an)&o3, (an)&a);
  FSWAP(Mat.lb, (an)&o4, (an)&b); if (BE) { FSWAP(Mat.lb, (an)&o1, (an)&o1); FSWAP(Mat.lb, (an)&o2, (an)&o2);
    FSWAP(Mat.lb, (an)&o3, (an)&o3); FSWAP(Mat.lb, (an)&o4, (an)&o4); }
  FADD(Mat.lb, (an)&r, Mat.A, Mat.B); Show(1, "+", &r, &e); FSUB(Mat.lb, (an)&r, Mat.A, Mat.B); Show(1, "-", &r, &e);
  FMUL(Mat.lb, (an)&rm, Mat.A, Mat.B); Show(2, "*", &rm, &e); Mat.cl = 0; Mat.l = Mat.lb; FDIV(Mat.lb, (an)&r, Mat.A, Mat.B, (an)&e);
  Show(1, "/", &r, &e); Mat.Nim = 1; FADD(Mat.lb, (an)&zr, Mat.A, Mat.B); Show(1, "+", &zr, &ze); FSUB(Mat.lb, (an)&zr, Mat.A, Mat.B);
  Show(1, "-", &zr, &ze); FMUL(Mat.lb, (an)&zm, Mat.A, Mat.B); Show(2, "*", &zm, &ze); Mat.cl = 0; Mat.l = Mat.lb;
  FDIV(Mat.lb, (an)&zr, Mat.A, Mat.B, (an)&ze); Show(1, "/", &zr, &ze); return 0; }
