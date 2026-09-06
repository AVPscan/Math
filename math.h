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
typedef struct { MatBuf Li, Hi; anu Nim, V, Be, // Структура реализации библиотеки
  lar, lbe, C, F, N, Fe, Ne, fa, na, fb, nb, dr, de, da, db; an r, e, a, b, R, E, A, B; } Cache;
extern Cache Mat;
void _FInit(anu x, anu y, an r, anu c, an a);   // Инициализация библиотеки
void _FAddr (anu y, As* r, anu c, As* a);
void FLD(an r, anu D);                          // Создание числа из атома
#define Fld(D) FLD(Mat.R, D);
void FLVD(an r, anu Dl, anu Dh);                // Создание числа из двух атомов
#define Flvd(Dl, Dh) FLVD(Mat.R, Dl, Dh);
void FMOV(anu l, an r, an a);                   // Копирование числа
#define Fmov(l, x) FMOV(l, x, x);
void FSWAP(anu l, an r, an a);                  // Зеркалирование атомов относительно центра числа
#define Fswap(l, x) FSWAP(l, x, x);
void FVIKARA(anu l, an r, an a);                // Модификация длины числа
#define Fvikara(l) FVIKARA(l, Mat.R, Mat.A);
void FCOLD(anu l, an r, an a);                  // Приведение к формату l = 1,2,4,8,16,32,64,128,256 атомов
#define Fcold(l) FCOLD(l, Mat.R, Mat.A);
void _FADD(an r, an a, anu l, an b);            // Сложение r = a + b
#define FADD(r) _FADD(r, Mat.A, Mat.lbe, Mat.B);
void _FSUB(an r, an a, anu l, an b);            // Вычитание r = a - b
#define FSUB(r) _FSUB(r, Mat.A, Mat.lbe, Mat.B);
void _FMUL(an r, an a, anu l, an b);            // Умножение r = a * b
#define FMUL(r) _FMUL(r, Mat.A, Mat.lbe, Mat.B);
void _FDIV(an r, an e, an a, anu l, an b);      // Деление r = a / b, e = a mod b - Евклид {положительный}
#define FDIV(r, e) _FDIV(r, e, Mat.A, Mat.lbe, Mat.B);
#define _num(x) (anu)((sizeof(x)/sizeof(anu)) - 1), (an)&x
#define FAdd(r, a, x) _FADD(r, a, _num(x));     // Работа с константой {малые буквы в названии функции}
#define FSub(r, a, x) _FSUB(r, a, _num(x));
#define FMul(r, a, x) _FMUL(r, a, _num(x));
#define FDiv(r, e, a, x) _FDIV(r, e, a, _num(x));
#define Fadd(x) _FADD(Mat.R, Mat.A, _num(x));   // Все буквы малые - используются адреса по умолчанию
#define Fsub(x) _FSUB(Mat.R, Mat.A, _num(x));
#define Fmul(x) _FMUL(Mat.R, Mat.A, _num(x));
#define Fdiv(x) _FDIV(Mat.R, Mat.E, Mat.A, _num(x));
#define _anu(...) (anu)((sizeof((anu[]){0, ##__VA_ARGS__})/sizeof(anu)) - 1), (anu[]){0, ##__VA_ARGS__} + 1
#define _adr(...) (sizeof((As[]){0, ##__VA_ARGS__})/sizeof(As)) - 1, (As[]){0, ##__VA_ARGS__} + 1
#define Faddr(...) _FAddr(4,(As*)&Mat.R,_adr(__VA_ARGS__));// {r{,e{,a{,b}}}} (Mat.R = r; ..)
#define Fini(...) _FInit(10,5,&Mat.Ne,_anu(__VA_ARGS__));  // Nim=V=Be=..Ne=0 {Nim{,V{,Be{,la{,lb}}}}}
#define Flong(...) _FInit(0,2,&Mat.Be,_anu(__VA_ARGS__));  // {la{,lb}} (Mat.lar = la; Mat.lbe = lb;)
#endif
