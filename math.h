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
//  As (As   अः    основа, бытие, существовать) Nim (Nimitta निमित्त {знаковое} представление)
// anu (anu  अणु   атом)                          V (Vṛddhi  वृद्धि  {изменение} разрядности)
//  an (anka अङ्क  цифра, число)             Vikara (Vikāra  विकार  {модификация} чисел)
// [{0..0}0x00] Не бытие - состояние {нет пары} находится в любом представлении чисел
// [{0..0}0x80] Бесконечность - состояние {нет пары} находится только в знаковом представлении
//Mat.Nim         [00/XX] Без знаковое/Знаковое представление
//Mat.V           [00/XX] Возможность изменить разрядность результата при необходимости
//Mar.Be          [00/XX] Сначала записан младший иначе старший байт числа только для FCOLD
//Mat.{R,A,B,E} Адреса, Mat.Nim, Mat.V и Mat.Be не подлежат изменению внутри функций
//Mat.C           [00/XX] Нет переполнения/Переполнение
//Mat.{F, Fe}     [00/XX] {0}число/состояние{{1}не бытиё,{2}бесконечность} {результат,остаток}
//Mat.{N, Ne}     [00/FF] для чисел без знаковое или положительное{00} иначе {FF}отрицательное
//Mat.l           [0.255] длина операнда b, длина остатка при делении re
//Mat.{L, cL}     [0.511] длина операнда a, длина результата r {l = Mat.L+((Mat.cL) ? 256:0)}
typedef uintptr_t As;                           // Разрядность процессора
typedef uint8_t anu;                            // Байт - атом для чисел
typedef anu* an;                                // Начальный адрес расположения числа
typedef struct { anu l, m[254], h, e; } MatBuf;	// 256 атомов + 1 сдвиг {умножение/деление}
typedef struct { MatBuf Ho, Sr, Lo; anu Nim, V, Be, l, L, cL, C, F, N, Fe, Ne, fa, na, fb, nb,
  dr, de, da, db; an r, e, a, b, R, E, A, B; } Cache;
extern Cache Mat;

#define _anu(...) (anu)((sizeof((anu[]){0, ##__VA_ARGS__}) / sizeof(anu)) - 1), (anu[]){0, ##__VA_ARGS__} + 1
#define _adr(...) (sizeof((As[]){0, ##__VA_ARGS__}) / sizeof(As)) - 1, (As[]){0, ##__VA_ARGS__} + 1
void _FInit(anu x, anu y, an r, anu c, an a);   // Инициализация библиотеки
void _FAddr (anu y, As* r, anu c, As* a);
#define Fini(...) _FInit(11,6,&Mat.Ne,_anu(__VA_ARGS__))
#define Flong(...) _FInit(0,3,&Mat.Be,_anu(__VA_ARGS__))
#define Faddr(...) _FAddr(4,(As*)&Mat.R,_adr(__VA_ARGS__))
void FLD(an r, anu D);                          // Создание числа из атома
#define Fld(D) FLD(Mat.R, D)
void FLVD(an r, anu Dl, anu Dh);                // Создание числа из двух атомов
#define Flvd(Dl, Dh) FLVD(Mat.R, Dl, Dh)
void FMOV(an r, an a, anu l, anu cl);           // Копирование числа
#define Fmov(l, cl) FMOV(Mat.R, Mat.A, l, cl)
void FSWAP(an r, an a, anu l, anu cl);          // Зеркалирование относительно центра числа атомов внутри
#define Fswap(l, cl) FSWAP(Mat.R, Mat.A, l, cl)
void FVIKARA(an r, an a, anu l, anu cl);        // Модификация изменение длин чисел
#define Fvikara(l, cl) FVIKARA(Mat.R, Mat.A, l, cl)
void FCOLD(an r, an a, anu l, anu cl);          // Приведение к старым форматам
#define Fcold(l, cl) FCOLD(Mat.R, Mat.A, l, cl)
void FADD(an r, an a, anu l, an b);             // Сложение
#define Fadd(l, b) FADD(Mat.R, Mat.A, l, b)
void FSUB(an r, an a, anu l, an b);             // Вычитание
#define Fsub(l, b) FSUB(Mat.R, Mat.A, l, b)
void FMUL(an r, an a, anu l, an b);             // Умножение
#define Fmul(l, b) FMUL(Mat.R, Mat.A, l, b)
void FDIV(an r, an e, an a, anu l, an b);       // Деление
#define Fdiv(l, b) FDIV(Mat.R, Mat.E, Mat.A, l, b)
#endif
