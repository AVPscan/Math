/* 
 * Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * 
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
 sanu a = {0}, b = {128};
#elif Lon == 2
 typedef uint16_t buf; typedef int16_t zbuf;
 typedef uint32_t Dbuf; typedef int32_t zDbuf;
 vanu a = {129,{1}}, b = {2,{0}};
#elif Lon == 4
 typedef uint32_t buf; typedef int32_t zbuf;
 typedef uint64_t Dbuf; typedef int64_t zDbuf;
 an a = {128,{5,0,0}}, b = {127,{0,0,0}};
#endif
buf o1, o2; zbuf o3, o4;

void Show(anu i, const char *str, void *r, void *e) {
  printf(" %s%s", (Mat.Carry) ? "C" : " ", (Mat.Riz) ? (Mat.Rnim) ? "I " : "Z " : (Mat.Rnim) ? "- " : "+ ");
  Mat.Carry = 0; i = (i != 2) ? 1 : 2; if (!BE) { FSWAP(Mat.L * i, (anu*)r, (anu*)r); FSWAP(Mat.L, (anu*)e, (anu*)e); }
#if Lon == 4
  if (Mat.Nim) { printf("%d %s %d = ", o3, str, o4); if (i > 1) printf("%ld", *(zDbuf*)r); else printf("%d", *(zbuf*)r); }
  else { printf("%d %s %d = ", o1, str, o2); if (i > 1) printf("%ld", *(Dbuf*)r); else printf("%d", *(buf*)r); }
#else
  if (Mat.Nim) { printf("%d %s %d = ", o3, str, o4); if (i > 1) printf("%d", *(zDbuf*)r); else printf("%d", *(zbuf*)r); }
  else { printf("%d %s %d = ", o1, str, o2); if (i > 1) printf("%d", *(Dbuf*)r); else printf("%d", *(buf*)r); }
#endif
  if (str[0] == '*') { printf(" long %d", ((Mat.Lh << 8) | Mat.Ll)); }
  else if (str[0] == '/') { if (Mat.Nim) printf(" tile %d", *(zbuf*)e); else printf(" tile %d", *(buf*)e); 
    printf(" %s", (Mat.Eiz) ? (Mat.Enim) ? " I" : " Z" : (Mat.Enim) ? " -" : " +"); } printf("\n"); }

int main(void) { buf r, e; Dbuf rm; zbuf zr, ze; zDbuf zm; Mat.L = Lon; Mat.A = (anu*)&a.h; Mat.B = (anu*)&b.h;
  FSWAP(Mat.L, (anu*)&o1, Mat.A); FSWAP(Mat.L, (anu*)&o2, Mat.B); FSWAP(Mat.L, (anu*)&o3, (anu*)&a.h); FSWAP(Mat.L, (anu*)&o4, (anu*)&b.h);
  if (BE) { FSWAP(Mat.L, (anu*)&o1, (anu*)&o1); FSWAP(Mat.L, (anu*)&o2, (anu*)&o2); FSWAP(Mat.L, (anu*)&o3, (anu*)&o3); 
    FSWAP(Mat.L, (anu*)&o4, (anu*)&o4); } printf("Long = %d\n", Lon); Mat.Nim = 0; FADD(Mat.L, (anu*)&r, Mat.A, Mat.B); Show(1, "+", &r, &e);
  FSUB(Mat.L, (anu*)&r, Mat.A, Mat.B); Show(1, "-", &r, &e); FMUL(Mat.L, (anu*)&rm, Mat.A, Mat.B); Show(2, "*", &rm, &e); 
  FDIV(Mat.L, (anu*)&r, Mat.A, Mat.B, (anu*)&e); Show(1, "/", &r, &e); Mat.Nim = 1;
  FADD(Mat.L, (anu*)&zr, Mat.A, Mat.B); Show(1, "+", &zr, &ze); FSUB(Mat.L, (anu*)&zr, Mat.A, Mat.B); Show(1, "-", &zr, &ze);
  FMUL(Mat.L, (anu*)&zm, Mat.A, Mat.B); Show(2, "*", &zm, &ze); FDIV(Mat.L, (anu*)&zr, Mat.A, Mat.B, (anu*)&ze); Show(1, "/", &zr, &ze); return 0; }
