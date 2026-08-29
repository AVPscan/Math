/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3).
 */
 
#ifndef MATH_H
#define MATH_H
#include <stdint.h>

//Begin 05.07.2026 in Russia
//  As (As   основа, бытие, существовать) अः       n (Nimitta знак{овое}) निमित्त
// anu (anu  атом) अणु                                                             v (Vṛddhi  увеличение {разрядности}) वृद्धि
//  an (anka цифра, число) अङ्क                          Vikara (Vikāra  модификация, изменение состояния) विकार
// Не бытие как состояние определяется в любом представлении.
// Бесконечность как состояние определяется только в знаковом представлении.
//Mat.Nim         {00/XX} Без знаковое/Знаковое представление
//Mat.V           {00/XX} Возможность увеличения разрядности результата по мере необходимости
//Mat.C           {00/XX} Нет переполнения/Переполнение
//Mat.{F, Fre}    {00/01} Число/Состояние {Результата/Остатка}
//Mat.{Z, Zre}    {00/FF} Если число то {+/-} иначе состояние {Не бытие 0x00/0x80 Бесконечность}
//Mat.{l, cl}     длина операнда a, на выходе длина результата r {l = Mat.l + ((Mat.cl) ? 256 : 0);}
//Mat.lb          длина операнда b {не полдежит изменению внутри функций}
//Mat.lre         FDIV длина остатка re, FCold длина результата r
//Mat.{R,A,B,RE}  для удобства {не подлежат изменению внутри функций}
typedef uintptr_t  As;
typedef uint8_t anu;
typedef anu* an;                                // Начальный адрес расположения числа
typedef struct { anu l, m[254], h, e; } MatBuf;	// На байт больше для организации сдвига
typedef struct { MatBuf Ho, Sr, Lo; anu Nim, V, Be, cl, l, lb, lre, C, F, N, Fre, Nre,
  fc, fa, fb, na, nb, dr, da, db, de; an r, a, b, re, R, A, B, RE; } Cache;
extern Cache Mat;

#define _anu(...) (anu)((sizeof((anu[]){0, ##__VA_ARGS__}) / sizeof(anu)) - 1), (anu[]){0, ##__VA_ARGS__} + 1
void _FInit (anu x, anu y, an r, anu c, an a);
#define Fini(...) _FInit(12,6,&Mat.Nre,_anu(__VA_ARGS__))
#define Flong(...) _FInit(0,3,&Mat.Be,_anu(__VA_ARGS__))

void Fvikara (anu l, an r, an a);
void Fld (an r, anu D);
void Flvd (an r, anu Dl, anu Dh);
void Fmov (anu lb, an r, an b);
void Fswap (anu lb, an r, an b);
void FCold (anu lb, an r, an b);
void Fadd (anu lb, an r, an a, an b);
void FADD (anu lb, an r, an a, an b);
void FSUB (anu lb, an r, an a, an b);
void FMUL (anu lb, an r, an a, an b);
void FDIV (anu lb, an r, an a, an b, an re);
#endif
