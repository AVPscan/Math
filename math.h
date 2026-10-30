/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3).
 */
#ifndef MATH_H
#define MATH_H
#include <stdint.h>

// Begin 05.07.2026 in Russia                  As (As      अः    основа, бытие, существовать)
// anu (anu     अणु   атом)                      an (anka    अङ्क   цифра, число)
// Nim (Nimitta निमित्त {знаковое} представление)  V (Vṛddhi  वृद्धि  изменение {разрядности})
// [{0..0}0]   Нет энергии - состояние {нет пары} находится в любом представлении чисел
// [{0..0}128] Бесконечность - состояние {нет пары} находится только в знаковом представлении
// Mat.Nim       [0/X]  {без знаковое/знаковое} представление чисел
// Mat.V         [0/X]  {запрет/разрешение} изменения разрядности результата
// Mat.C         [0/X]  {нет переполнения/переполнение} результата
// Mat.F{Fe}    [0,1,2] {0} число/состояние {1} не бытиё {2} бесконечность результата{остатка}
// Mat.N{Ne}     [0/X]  {0} для чисел без знаковое или положительное иначе отрицательное
// Mat.l        [0.255] длина первого операнда a, длина результата r
// Mat.le       [0.255] длина остатка e
// Mat.lb       [0.255] длина последнего обработанного второго операнда
// Mat.b        адрес последнего обработанного второго операнда
// Mat.Nim, Mat.V, Mat.R{EAB} не подлежат изменению внутри функций

typedef uintptr_t As;                           // основа, разрядность процессора
typedef uint8_t anu;                            // атом, минимальная единица
typedef anu* an;                                // число, начальный адрес расположения
typedef struct { anu Nim, V, l, lb, le, C, F, N, Fe, Ne,
  S[255],H[255],L[255],na,nb,i,j,k,t,u,x,y,z; an r,e,a,ae,be, b, R, E, A, B; } Math;
void FAddr(anu y, As* r, anu c, As* a);
void FInit(anu x, anu y, an r, anu c, an a);
void FSWAP(anu l, an r, an a);                  // Зеркалирование атомов длиной l относительно центра
anu FMOV(anu l, an r, an a);                    // Копирование l атомов |8,16,32,64|128,256,512,1024,2048 бит
anu FCOLD(anu f, anu l, an r, an a);            // Приведение к формату l = 0,1,3,7|15,31,63,127,255 атомов
anu FIV(anu f, an r, anu l, an c);              // Копирование из константы в переменную на выходе l
void FADD(an r, an a, anu l, an b);             // Сложение  r = a + b { r += Mat.B -> Fadd(r); }
void FCADD(an r, an a, anu l, an c);            //       r = a + Const { r += 256 -> Fadd(r, 0,1); }
void FSUB(an r, an a, anu l, an b);             // Вычитание r = a - b
void FCSUB(an r, an a, anu l, an c);            //       r = a - Const
void FCMP(an a, anu l, an b);                   // Сравнение a и b             -> Mat.F = ; Mat.N < else >
void FCCMP(an a, anu l, an c);                  // Сравнение a и Const | Mat.B -> Mat.F = ; Mat.N < else >
anu FEQ(an a, anu l, an c);                     // a = Const1;Const2;...;ConstN           | a = Mat.B
anu FRANGE(an a, anu l, an c);                  // a  {[Const1;Const2];}...{;a >= ConstN} | a>= Mat.B
void FMUL(an r, an a, anu l, an b);             // Умножение r = a * b
void FCMUL(an r, an a, anu l, an c);            //       r = a * Const
void FDIV(an r, an e, an a, anu l, an b);       // Деление r = a / b, e = a mod b - Евклид {+}
void FCDIV(an r, an e, an a, anu l, an c);      //       r = a / Const, e = a mod Const
extern Math Mat;
#define MATH_CACHE_INIT Math Mat = {0};
#define Anu(...) (anu)(sizeof((anu[]){0, ##__VA_ARGS__})-1), (anu[]){0, ##__VA_ARGS__}+1
#define Adr(...) (anu)((sizeof((As[]){0, ##__VA_ARGS__})/sizeof(As))-1), (As[]){0, ##__VA_ARGS__}+1
#define Faddr(...) FAddr(4, (As*)&Mat.R, Adr(__VA_ARGS__))          // Faddr({(As)r{,(As)e{,(As)a{,(As)b}}}});
#define Fset(...) FInit(0, 4, &Mat.Nim, Anu(__VA_ARGS__))           // Fset({Nim{,V{,la{,lb}}}});
#define Fini(...) FInit(10, 4, (an)Mat.S, Anu(__VA_ARGS__))         // Nim=V=l=lb..Ne=0 Fini({Nim{,V{,la{,lb}}}});
#define Flong(...) FInit(0, 2, &Mat.l, Anu(__VA_ARGS__))            // Flong({la{,lb}});
#define Fswap(l, x) FSWAP(l, x, x)
#define Fmov(l, x) FMOV(l, x, x)
#define Fcold(f, l, x) FCOLD(f, l, x, x)
#define Fiv(f, r, ...) FIV(f, r, Anu(__VA_ARGS__))
#define Fv(r, ...) FIV(0, r, Anu(__VA_ARGS__))
#define Fbv(r, ...) FIV(1, r, Anu(__VA_ARGS__))
#define FAdd(r, a, ...) FCADD(r, a, Anu(__VA_ARGS__))               // r = a + Const       | r = a + Mat.B
#define Fadd(r, ...) FCADD(r, r, Anu(__VA_ARGS__))                  // r += Const          | r += Mat.B
#define FSub(r, a, ...) FCSUB(r, a, Anu(__VA_ARGS__))               // r = a - Const       | r = a - Mat.B
#define Fsub(r, ...) FCSUB(r, r, Anu(__VA_ARGS__))                  // r -= Const          | r -= Mat.B
#define Fcmp(a, ...) FCCMP(a, Anu(__VA_ARGS__))                     // a ? Const           | a ? Mat.B -> Mat.F, Mat.N
#define Feq(a, ...) FEQ(a, Anu(__VA_ARGS__))                        // a = Const           | a = Mat.B
#define Frange(a, ...) FRANGE(a, Anu(__VA_ARGS__))                  // a {[..];}.{a >= ..} | a >= Mat.B
#define Fgt(a, ...) (Fcmp(a, __VA_ARGS__), !(Mat.N | Mat.F))        // a > Const           | a > Mat.B
#define Fle(a, ...) (Fcmp(a, __VA_ARGS__), (Mat.N | Mat.F))         // a<= Const           | a <=Mat.B
#define FMul(r, a, ...) FCMUL(r, a, Anu(__VA_ARGS__))               // r = a * Const       | r = a * Mat.B
#define Fmul(r, ...) FCMUL(r, r, Anu(__VA_ARGS__))                  // r *= Const          | r *= Mat.B
#define FDiv(r, e, a, ...) FCDIV(r, e, a, Anu(__VA_ARGS__))         // r = a / Const       | r = a / Mat.B
#define Fdiv(r, e, ...) FCDIV(r, e, r, Anu(__VA_ARGS__))            // r /= Const          | r /= Mat.B
#endif
