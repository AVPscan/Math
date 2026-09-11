/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3).
 */

#ifndef MATH_H
#define MATH_H
#include <stdint.h>
// Begin 05.07.2026 in Russia                  As (As      अः   основа, бытие, существовать)
// anu (anu     अणु   атом)                     an (anka    अङ्क цифра, число)
// Nim (Nimitta निमित्त {знаковое} представление)  V  (Vṛddhi  वृद्धि  {изменение} разрядности)
// [{0..0}0x00] Не бытие - состояние {нет пары} находится в любом представлении чисел
// [{0..0}0x80] Бесконечность - состояние {нет пары} находится только в знаковом представлении
// Mar.Be       [00/XX] {нет/да} сначала записан старший иначе младший байт числа, для FCOLD
// Mat.Nim      [00/XX] {без знаковое/знаковое} представление чисел
// Mat.V        [00/XX] {нет/да} возможность увеличить разрядность результата {плюс атом}
// Mat.R{E{A{B}}} Mat.Be, Mat.Nim и Mat.V не подлежат изменению внутри функций
// Mat.C        [00/XX] {нет переполнения/переполнение}
// Mat.F{Fe}    [00/XX] {0}число/состояние{{1}не бытиё,{2}бесконечность} результата{остатка}
// Mat.N{Ne}    [00/FF] для чисел без знаковое или положительное{00} иначе {FF}отрицательное
// Mat.lar      [0.255] длина операнда a, длина результата r
// Mat.lbe      [0.255] длина операнда b, длина остатка при делении re
typedef uintptr_t As;                           // Разрядность процессора - основа
typedef uint8_t anu;                            // Байт - атом
typedef anu* an;                                // Начальный адрес расположения - число
typedef struct { anu l, m[254], h, e; } MatBuf;	// 256 атомов + 1 сдвиг {умножение/деление}
typedef struct { MatBuf Li, Hi; anu Be, Nim, V, // Структура реализации библиотеки
  lar, lbe, C, F, N, Fe, Ne, fa, na, fb, nb, dr, de, da, db; an r, e, a, b, R, E, A, B; } Math;
void FInit(anu x, anu y, an r, anu c, an a);    // Инициализация библиотеки
void FAddr(anu y, As* r, anu c, As* a);         //
void FLD(an r, anu D);                          // Создание числа из атома
void FLVD(an r, anu Dl, anu Dh);                // Создание числа из двух атомов и автонормализация
void FMOV(anu l, an r, an a);                   // Копирование числа и автонормализация
void FSWAP(anu l, an r, an a);                  // Зеркалирование атомов относительно центра числа
void FCOLD(anu l, an r, an a);                  // Приведение к формату l = 1,2,4,8,16,32,64,128,256
void FADD(an r, an a, anu l, an b);             // Сложение r = a + b
void FADDc(an r, an a, anu l, an c);            // r = a + Const {x = x + 256 -> Faddc(x, 0, 1)}
void FSUB(an r, an a, anu l, an b);             // Вычитание r = a - b
void FSUBc(an r, an a, anu l, an c);            // r = a - Const
void FMUL(an r, an a, anu l, an b);             // Умножение r = a * b
void FMULc(an r, an a, anu l, an c);            // r = a * Const
void FDIV(an r, an e, an a, anu l, an b);       // Деление r = a / b, e = a mod b - Евклид {+}
void FDIVc(an r, an e, an a, anu l, an c);      // r = a / Const, e = a mod Const

extern Math Mat;
#define MATH_CACHE_INIT Math Mat = {0};
#define Anu(...) (anu)(sizeof((anu[]){0, ##__VA_ARGS__}) - 1), (anu[]){0, ##__VA_ARGS__} + 1
#define Adr(...) (anu)((sizeof((As[]){0, ##__VA_ARGS__})/sizeof(As)) - 1), (As[]){0, ##__VA_ARGS__} + 1
#define Faddr(...) FAddr(4, (As*)&Mat.R, Adr(__VA_ARGS__)); // {r{,e{,a{,b}}}} (Mat.R = r; ..)
#define Fini(...) FInit(10, 5, &Mat.Ne, Anu(__VA_ARGS__));  // Be=Nim=V=..Ne=0 {Be{,Nim{,V{,la{,lb}}}}}
#define Flong(...) FInit(0, 2, &Mat.V, Anu(__VA_ARGS__));   // {la{,lb}} (Mat.lar = la; Mat.lbe = lb;)
#define Fld(D) FLD(Mat.R, D);
#define Flvd(Dl, Dh) FLVD(Mat.R, Dl, Dh);
#define Fmov(l, x) FMOV(l, x, x);
#define Fswap(l, x) FSWAP(l, x, x);
#define Fcold(l, x) FCOLD(l, x, x);
#define FAdd(r) FADD(r, Mat.A, Mat.lbe, Mat.B);  
#define FAddc(r, ...) FADDc(r, Mat.A, Anu(__VA_ARGS__));
#define Fadd(r, l, b) FADD(r, r, l, b);
#define Faddc(r, ...) FADDc(r, r, Anu(__VA_ARGS__));
#define FSub(r) FSUB(r, Mat.A, Mat.lbe, Mat.B);
#define FSubc(r, ...) FSUBc(r, Mat.A, Anu(__VA_ARGS__));
#define Fsub(r, l, b) FSUB(r, r, l, b);
#define Fsubc(r, ...) FSUBc(r, r, Anu(__VA_ARGS__));
#define FMul(r) FMUL(r, Mat.A, Mat.lbe, Mat.B);
#define FMulc(r, ...) FMULc(r, Mat.A, Anu(__VA_ARGS__));
#define Fmul(r, l, b) FMUL(r, r, l, b);
#define Fmulc(r, ...) FMULc(r, r, Anu(__VA_ARGS__));
#define FDiv(r, e) FDIV(r, e, Mat.A, Mat.lbe, Mat.B);
#define FDivc(r, e, ...) FDIVc(r, e, Mat.A, Anu(__VA_ARGS__));
#define Fdiv(r, e, l, b) FDIV(r, e, r, l, b);
#define Fdivc(r, e, ...) FDIVc(r, e, r, Anu(__VA_ARGS__));
#endif
