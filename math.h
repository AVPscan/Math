/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3).
 */

#ifndef MATH_H
#define MATH_H
#include <stdint.h>
// Begin 05.07.2026 in Russia
//  As (As   अः    основа, бытие, существовать) Nim (Nimitta निमित्त {знаковое} представление)
// anu (anu  अणु   атом)                          V (Vṛddhi  वृद्धि  {изменение} разрядности)
//  an (anka अङ्क  цифра, число)             Vikara (Vikāra  विकार  {модификация} чисел)
// [{0..0}0x00] Не бытие - состояние {нет пары} находится в любом представлении чисел
// [{0..0}0x80] Бесконечность - состояние {нет пары} находится только в знаковом представлении
// Mat.Nim        [00/XX] Без знаковое/Знаковое представление
// Mat.V          [00/XX] Возможность изменить разрядность результата при необходимости
// Mar.Be         [00/XX] Сначала записан младший иначе старший байт числа только для FCOLD
// Mat.{R,A,B,E} Адреса, Mat.Nim, Mat.V и Mat.Be не подлежат изменению внутри функций
// Mat.C          [00/XX] Нет переполнения/Переполнение
// Mat.{F, Fe}    [00/XX] {0}число/состояние{{1}не бытиё,{2}бесконечность} {результат,остаток}
// Mat.{N, Ne}    [00/FF] для чисел без знаковое или положительное{00} иначе {FF}отрицательное
// Mat.lar        [0.255] длина операнда a, длина результата r
// Mat.lbe        [0.255] длина операнда b, длина остатка при делении re
typedef uintptr_t As;                           // Разрядность процессора - основа
typedef uint8_t anu;                            // Байт - атом
typedef anu* an;                                // Начальный адрес расположения - число
typedef struct { anu l, m[254], h, e; } MatBuf;	// 256 атомов + 1 сдвиг {умножение/деление}
typedef struct { MatBuf Li, Hi; anu Nim, V, Be, lar, lbe, C, F, N, Fe, Ne, fa, na, fb, nb,
  dr, de, da, db; an r, e, a, b, R, E, A, B; } Cache;
extern Cache Mat;

void _FInit(anu x, anu y, an r, anu c, an a);               // Инициализация библиотеки
void _FAddr (anu y, As* r, anu c, As* a);
void FLD(an r, anu D);                                      // Создание числа из атома
#define Fld(D) FLD(Mat.R, D)
void FLVD(an r, anu Dl, anu Dh);                            // Создание числа из двух атомов
#define Flvd(Dl, Dh) FLVD(Mat.R, Dl, Dh)
void FMOV(an r, an a, anu l);                               // Копирование числа
#define Fmov(l) FMOV(Mat.R, Mat.A, l)
void FSWAP(an r, an a, anu l);                              // Зеркалирование атомов внутри относительно центра числа
#define Fswap(l) FSWAP(Mat.R, Mat.A, l)
void FVIKARA(an r, an a, anu l);                            // Модификация длины числа
#define Fvikara(l) FVIKARA(Mat.R, Mat.A, l)
void FCOLD(an r, an a, anu l);                              // Приведение к старым форматам l = 1, 2, 4, 8, 16, 32, 64, 128, 256 байт 
#define Fcold(l) FCOLD(Mat.R, Mat.A, l)
void FADD(an r, an a, anu l, an b);                         // Сложение r = a + b
#define Fadd(l, b) FADD(Mat.R, Mat.A, l, b)
void FSUB(an r, an a, anu l, an b);                         // Вычитание r = a - b
#define Fsub(l, b) FSUB(Mat.R, Mat.A, l, b)
void FMUL(an r, an a, anu l, an b);                         // Умножение r = a * b
#define Fmul(l, b) FMUL(Mat.R, Mat.A, l, b)
void FDIV(an r, an e, an a, anu l, an b);                   // Деление r = a / b, e = a mod b
#define Fdiv(l, b) FDIV(Mat.R, Mat.E, Mat.A, l, b)
#define _anu(...) (anu)((sizeof((anu[]){0, ##__VA_ARGS__}) / sizeof(anu)) - 1), (anu[]){0, ##__VA_ARGS__} + 1
#define _adr(...) (sizeof((As[]){0, ##__VA_ARGS__}) / sizeof(As)) - 1, (As[]){0, ##__VA_ARGS__} + 1
#define Fini(...) _FInit(10,5,&Mat.Ne,_anu(__VA_ARGS__))    // Nim=V=Be=lb=la=cl=C=F=Fe=Ne=0, {Nim{,V{,Be{,lb{,la}}}}} (Mat.Nim = Nim; Mat.V = V; ..)
#define Flong(...) _FInit(0,2,&Mat.Be,_anu(__VA_ARGS__))    // {lb{,la}} (Mat.lbe = lb; Mat.lar = la;)
#define Faddr(...) _FAddr(4,(As*)&Mat.R,_adr(__VA_ARGS__))  // {r{,e{,a{,b}}}} (Mat.R = r; Mat.E = e; Mat.A = a; Mat.B = b;)
#endif
