/*
 * Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * 
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3).
 */
 
#ifndef SYS_H
#define SYS_H
#include <stdint.h>

//Begin 05.07.2026 in Russia
//  As      (санскр. As      — основа, бытие, существовать) अः
// anu      (санскр. anu     — атом) अणु 
// an       (санскр. anka    — цифра) अङ्क 
// n        (санскр. Nimitta — знак{овое}) निमित्त 
// v        (санскр. Vṛddhi  — увеличение {разрядности вдвое}) वृद्धि
// Vikara   (санскр. Vikāra  — модификация, изменение состояния) विकार

//{Состояние} Возникает только в знаковом представлении чисел
//Mat.Nim   {Без знаковое/Знаковое}
//Mat.Carry {Нет переполнения/Переполнение} Результата
//Mat.Riz   {Число/Состояние} Результата
//Mat.Eiz   {Число/Состояние} Остатка
//Mat.Rnim  {00/FF}{Не бытие/Бесконечность} Результата
//Mat.Enim  {00/FF}{Не бытие/Бесконечность} Остатка
//Mat.Long  Для удобства при использовании {переменная константа}
//Mat.VLong Для удобства при использовании h,l {переменная константа}

typedef uintptr_t  As;
typedef uint8_t anu;                                // 1   anu [0..FF]
//typedef uint8_t nanu;                             // 1  n    [0,-7F..-1,80,+1..+7F]
typedef struct { anu h; } sanu;                     // 1       возможность работать с anu как со структурой
typedef struct { anu h, l[1]; } vanu;               // 2  v    [0..FFFF]
//typedef struct { anu h, l[1]; } vnanu             // 2 vn    [0,+1..+7FFF,8000,-7FFF..-1]
//typedef struct { anu h, l[2]; };                  // 3       [0..FFFFFF]    [17..24] бит диапазон теперь доступен
//typedef struct { anu h, l[2]; };                  // 3       [0,+1..+7FFFFF,800000,-7FFFFF..-1]
typedef struct { anu h, l[3]; } an;                 // 4   an  [0..FFFFFFFF]
//typedef struct { anu h, l[3]; } nan;              // 4  n    [0,+1..+7FFFFFFF,80000000,-7FFFFFFF..-1]
//typedef struct { anu h, l[4..6]; };               // 5-7
//typedef struct { anu h, l[4..6]; };               // 5-7n                   [33..56] бит диапазон теперь доступен
typedef struct { anu h, l[7]; } van;                // 8  v    [0..FFFFFFFFFFFFFFFF]
//typedef struct { anu h, l[7]; } vnan;             // 8 vn    [0,+1..+7FFFFFFFFFFFFFFF,8000000000000000,-7FFFFFFFFFFFFFFF..-1]
//typedef struct { anu h, l[0..254]; };             // 1-255
//typedef struct { anu h, l[0..254]; };             // 1-255n                 [8..2040] бит диапазон теперь доступен
typedef struct { anu h, l[255]; } MatBuf;           // 256....................[8..2048] для умножения {сдвиговый регистр}
typedef struct { MatBuf Ho, Sr, Lo; anu Nim, Carry, Riz, Rnim, Eiz, Enim, Long, VLongh, VLongl, Loop, Fa, Fb, Zr, Za, Zb, Br, Ba, Bb,
  *r, *a, *b, *e; } var_;
extern var_ Mat;
#define MATH_VARS_INIT \
var_ Mat = {.Nim = 0, .Long = 2, .VLongh = 0, .VLongl = 4};

void FBSWAP (anu l, anu *r, anu *a);
void FMOVB (anu l, anu *r, anu h);
void FVMOVB (anu s, anu *r, anu h, anu l);
void FRR (anu l, anu *r);
void FRL (anu l, anu *r);
void VIKARA (anu lr, anu la, anu *r, anu *a);
void FADD (anu l, anu *r, anu *a, anu *b);
void FSUB (anu l, anu *r, anu *a, anu *b);
void FMUL (anu l, anu *r, anu *a, anu *b);
void FDIV (anu l, anu *r, anu *a, anu *b, anu *e);
void FVDIV (anu l, anu *r, anu *a, anu *b, anu *e);

#endif /* SYS_H */
