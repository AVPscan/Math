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
// Mat.Nim      [00/XX] {без знаковое/знаковое} представление чисел
// Mat.V        [00/XX] {нет/да} возможность увеличить разрядность результата {плюс атом}
// Mat.R{E{A{B}}} Mat.Nim и Mat.V не подлежат изменению внутри функций
// Mat.C        [00/XX] {нет переполнения/переполнение}
// Mat.F{Fe}    [00/XX] {0}число/состояние{{1}не бытиё,{2}бесконечность} результата{остатка}
// Mat.N{Ne}    [00/FF] для чисел без знаковое или положительное{00} иначе {FF}отрицательное
// Mat.l        [0.255] длина операнда a, длина результата r
// Mat.le       [0.255] длина остатка e
typedef uintptr_t As;                           // основа, разрядность процессора
typedef uint8_t anu;                            // атом, минимальная единица
typedef anu* an;                                // число, начальный адрес расположения
typedef struct { anu l, m[254], h, e; } MatBuf;	// 256 атомов + 1 атом {умножение/деление}
typedef struct { MatBuf Li, Hi; anu Nim, V, l,  //  представление, возможность изменения длин,
  le, C, F, N, Fe, Ne, fa, na, fb, nb, nab, dr, //  длины, перенос, флаг состояний/знак {r,e,a,b}
  de, da, db; an r, e, a, b, R, E, A, B; } Math;// Структура реализации библиотеки
void FInit(anu x, anu y, an r, anu c, an a);    // Nim=V=la=..Ne=0 {Nim{,V{,la}}}, {la}
void FAddr(anu y, As* r, anu c, As* a);         // {r{,e{,a{,b}}}} (Mat.R = r; ..)
void FSWAP(anu l, an r, an a);                  // Зеркалирование атомов длиной l относительно центра
void FLD(an r, anu D);                          // Создание числа из атома
void FLVD(an r, anu Dl, anu Dh);                // Создание числа из двух атомов и автонормализация
void FMOV(anu l, an r, an a);                   // Копирование числа и автонормализация
void FCOLD(anu f, anu l, an r, an a);           // Приведение к формату l = 1,2,4,8,16,32,64,128,256
anu CONST(anu f, an r, anu l, an c);            // Копирование из константы в переменную на выходе l
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
#define Anu(...) (anu)(sizeof((anu[]){0, ##__VA_ARGS__})-1), (anu[]){0, ##__VA_ARGS__}+1
#define Adr(...) (anu)((sizeof((As[]){0, ##__VA_ARGS__})/sizeof(As))-1), (As[]){0, ##__VA_ARGS__}+1
#define Faddr(...) FAddr(4, (As*)&Mat.R, Adr(__VA_ARGS__))
#define Fini(...) FInit(9, 3, &Mat.Ne, Anu(__VA_ARGS__))
#define Flong(...) FInit(0, 1, &Mat.V, Anu(__VA_ARGS__))
#define Fswap(l, x) FSWAP(l, x, x)
#define Const(f, r,...) CONST(f, r, Anu(__VA_ARGS__))
#define Fld(D) FLD(Mat.A, D)
#define Flvd(Dl, Dh) FLVD(Mat.A, Dl, Dh)
#define Fmov(l, x) FMOV(l, x, x)
#define Fcold(f, l, x) FCOLD(f, l, x, x)
#define FAdd(l, b) FADD(Mat.R, Mat.A, l, b)
#define FAddc(...) FADDc(Mat.R, Mat.A, Anu(__VA_ARGS__))
#define Fadd(r, l, b) FADD(r, r, l, b)
#define Faddc(r, ...) FADDc(r, r, Anu(__VA_ARGS__))
#define FSub(l, b) FSUB(Mat.R, Mat.A, l, b)
#define FSubc(...) FSUBc(Mat.R, Mat.A, Anu(__VA_ARGS__))
#define Fsub(r, l, b) FSUB(r, r, l, b)
#define Fsubc(r, ...) FSUBc(r, r, Anu(__VA_ARGS__))
#define FMul(l, b) FMUL(Mat.R, Mat.A, l, b)
#define FMulc(...) FMULc(Mat.R, Mat.A, Anu(__VA_ARGS__))
#define Fmul(r, l, b) FMUL(r, r, l, b)
#define Fmulc(r, ...) FMULc(r, r, Anu(__VA_ARGS__))
#define FDiv(l, b) FDIV(Mat.R, Mat.E, Mat.A, l, b)
#define FDivc(...) FDIVc(Mat.R, Mat.E, Mat.A, Anu(__VA_ARGS__))
#define Fdiv(r, e, l, b) FDIV(r, e, r, l, b)
#define Fdivc(r, e, ...) FDIVc(r, e, r, Anu(__VA_ARGS__))
#endif
