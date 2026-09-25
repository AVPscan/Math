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
// anu (anu     अणु   атом)                      an (anka    अङ्क цифра, число)
// Nim (Nimitta निमित्त {знаковое} представление)  V (Vṛddhi  वृद्धि     увеличение {разрядности})
// [{0..0} 0 ] Нет энергии - состояние {нет пары} находится в любом представлении чисел
// [{0..0}128] Бесконечность - состояние {нет пары} находится только в знаковом представлении
// Mat.Nim      [00/XX] {без знаковое/знаковое} представление чисел
// Mat.V        [00/XX] Зарет увеличения разрядности результата
// Mat.C        [00/XX] {нет переноса/перенос}
// Mat.F{Fe}    [0,1,2] {0}число/состояние{{1}не бытиё,{2}бесконечность} результата{остатка}
// Mat.N{Ne}    [00/XX] для чисел без знаковое или положительное{00} иначе {FF}отрицательное
// Mat.l        [0.255] длина первого операнда a, длина результата r
// Mat.le       [0.255] длина остатка e
// Mat.lb       [0.255] длина последнего обработанного второго операнда
// Mat.b        адрес последнего обработанного второго операнда
// Mat.Nim, Mat.V, Mat.R{EAB} не подлежат изменению внутри функций
typedef uintptr_t As;                           // основа, разрядность процессора
typedef uint8_t anu;                            // атом, минимальная единица
typedef anu* an;                                // число, начальный адрес расположения
typedef struct { anu l, m[254], h; } MatBuf;    // 256 атомов
typedef struct { anu Nim, V, l, lb, le, C, F, N, Fe, Ne,  // Fset({Nim{,V{,la{,lb}}}});
  na, nb, x, y, i, j, k, t; MatBuf H, L, S;               // Flong({la{,lb}});
  an R, E, A, B, r, e, a, b, ae, be; } Math;    // Структура реализации автомата
void FInit(anu x, anu y, an r, anu c, an a);    // Fini({Nim{,V{,la{,lb}}}}); Nim=V=l=lb..Ne=0
void FAddr(anu y, As* r, anu c, As* a);         // Faddr({(As)r{,(As)e{,(As)a{,(As)b}}}});
void FSWAP(anu l, an r, an a);                  // Зеркалирование атомов длиной l относительно центра
anu FMOV(anu l, an r, an a);                    // Копирование числа и автонормализация
anu FCOLD(anu f, anu l, an r, an a);            // Приведение к формату l = 1,2,4,8,16,32,64,128,256
anu FVI(anu f, an r, anu l, an c);              // Копирование из константы в переменную на выходе l
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
#define Fset(...) FInit(0, 4, &Mat.Nim, Anu(__VA_ARGS__))
#define Fini(...) FInit(10, 4, &Mat.na, Anu(__VA_ARGS__))
#define Flong(...) FInit(0, 2, &Mat.l, Anu(__VA_ARGS__))
#define Fswap(l, x) FSWAP(l, x, x)
#define Fmov(l, x) FMOV(l, x, x)
#define Fcold(f, l, x) FCOLD(f, l, x, x)
#define Fvar(f, r,...) FVI(f, r, Anu(__VA_ARGS__))
#define Fvi(r,...) FVI(0, r, Anu(__VA_ARGS__))
#define Fbvi(r,...) FVI(1, r, Anu(__VA_ARGS__))
#define FAdd() FADD(Mat.R, Mat.A, Mat.lb, Mat.B)
#define FAddc(...) FADDc(Mat.R, Mat.A, Anu(__VA_ARGS__))
#define Fadd(r) FADD(r, r, Mat.lb, Mat.B)
#define Faddc(r, ...) FADDc(r, r, Anu(__VA_ARGS__))
#define FSub() FSUB(Mat.R, Mat.A, Mat.lb, Mat.B)
#define FSubc(...) FSUBc(Mat.R, Mat.A, Anu(__VA_ARGS__))
#define Fsub(r) FSUB(r, r, Mat.lb, Mat.B)
#define Fsubc(r, ...) FSUBc(r, r, Anu(__VA_ARGS__))
#define FMul() FMUL(Mat.R, Mat.A, Mat.lb, Mat.B)
#define FMulc(...) FMULc(Mat.R, Mat.A, Anu(__VA_ARGS__))
#define Fmul(r) FMUL(r, r, Mat.lb, Mat.B)
#define Fmulc(r, ...) FMULc(r, r, Anu(__VA_ARGS__))
#define FDiv() FDIV(Mat.R, Mat.E, Mat.A, Mat.lb, Mat.B)
#define FDivc(...) FDIVc(Mat.R, Mat.E, Mat.A, Anu(__VA_ARGS__))
#define Fdiv(r, e) FDIV(r, e, r, Mat.lb, Mat.B)
#define Fdivc(r, e, ...) FDIVc(r, e, r, Anu(__VA_ARGS__))
#endif
