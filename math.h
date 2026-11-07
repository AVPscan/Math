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
// Mat.N{Ne}     [0/X]  {0} для чисел без знака или положительное иначе отрицательное {+/-}
// Mat.CF        [0/X]  {0} не равенство
// Mat.CN        [0/X]  {0} больше или равно иначе меньше
// Mat.l{le}    [0.255] длина первого операнда a, длина результата r{остатка e}
// Mat.lb       [0.255] длина последнего обработанного второго операнда
// Mat.b        адрес последнего обработанного второго операнда
// Mat.Nim, Mat.V, Mat.B{ARE} не подлежат изменению внутри функций
typedef uintptr_t As;                           // основа, разрядность процессора
typedef uint8_t anu;                            // атом, минимальная единица
typedef anu* an;                                // число, начальный адрес расположения
typedef struct { anu Nim, V, lb, l, le, C, F, N, Fe, Ne, CF, CN,
  na,nb,i,j,k,t,x,y,H[255],L[255],S[255]; an b,a,r,e,ae,be, B, A, R, E; } Math;

extern Math Mat;
#define MATH_CACHE_INIT Math Mat = {0};
#define Anu(...) (anu)(sizeof((anu[]){0, ##__VA_ARGS__})-1), (anu[]){0, ##__VA_ARGS__}+1
#define Adr(...) (anu)((sizeof((As[]){0, ##__VA_ARGS__})/sizeof(As))-1), (As[]){0, ##__VA_ARGS__}+1
void FAddr(anu y, As* r, anu c, As* a);
void FInit(anu x, anu y, an r, anu c, an a);
#define Faddr(...) FAddr(4, (As*)&Mat.B, Adr(__VA_ARGS__))      // Faddr({(As)b{,(As)a{,(As)r{,(As)e}}}});
#define Fset(...) FInit(0, 4, &Mat.Nim, Anu(__VA_ARGS__))       // Fset({Nim{,V{,lb{,la}}}});
#define Fini(...) FInit(12, 4, &Mat.i, Anu(__VA_ARGS__))        // Nim=V=lb=l..Ne=0 Fini({Nim{,V{,lb{,la}}}});
#define Flong(...) FInit(0, 3, &Mat.lb, Anu(__VA_ARGS__))       // Flong({lb{,la{,le}}});
void FSWAP(an r, anu l, an a);                                  // Зеркалирование атомов длиной l
anu FMOV(an r, anu l, an a);                    // Копирование l атомов |8,16,32,64|128,256,512,1024,2048 бит
anu FOLD(anu f, an r, anu l, an a);             // Приведение к формату l = 0,1,3,7|15,31,63,127,255 атомов
anu FVAR(anu f, an r, anu l, an c);             // Копирование из константы в переменную l -> new l
#define Fswap(l, x) FSWAP(x, l, x)                      // Fswap(l, x); Fswap(l, x); -> {}
#define Fmov(l, x) FMOV(x, l, x)                        // Mat.na [0,1,2] Mat.nb [+/-] l -> new l
#define Fold(f, l, x) FOLD(f, x, l, x)                  // Mat.na [0,1,2] Mat.nb [+/-] l -> new l >= l
#define FVar(f, r, ...) FVAR(f, r, Anu(__VA_ARGS__))    // r = Const{LittleEnd/BigEnd}     | r = 0
#define Fvle(r, ...) FVar(0, r, __VA_ARGS__)            // r = Const{LittleEndian}         | r = 0
#define Fvbe(r, ...) FVar(1, r, __VA_ARGS__)            // r = Const{BigEndian}            | r = 0
void FADD(an r, an a, anu l, an b);                     // r = a + b { r += Mat.B -> Fadd(r); }
void FSUB(an r, an a, anu l, an b);                     // r = a - b { r -= 256 -> Fsub(r, 0,1); }
void FMUL(an r, an a, anu l, an b);                     // r = a * b
void FDIV(an r, an e, an a, anu l, an b);               // r = a / b, e = a mod b - Евклид {+}
void FCADD(an r, an a, anu l, an c);                    // r = a + Const                   | r = a + Mat.B
void FCSUB(an r, an a, anu l, an c);                    // r = a - Const                   | r = a - Mat.B
void FCMUL(an r, an a, anu l, an c);                    // r = a * Const                   | r = a * Mat.B
void FCDIV(an r, an e, an a, anu l, an c);              // r = a / Const, e = a mod Const  | r = a / Mat.B
#define FAdd(r, a, ...) FCADD(r, a, Anu(__VA_ARGS__))   // r = a + Const                   | r = a + Mat.B
#define Fadd(r, ...) FCADD(r, r, Anu(__VA_ARGS__))      // r += Const                      | r += Mat.B
#define FSub(r, a, ...) FCSUB(r, a, Anu(__VA_ARGS__))   // r = a - Const                   | r = a - Mat.B
#define Fsub(r, ...) FCSUB(r, r, Anu(__VA_ARGS__))      // r -= Const                      | r -= Mat.B
#define FMul(r, a, ...) FCMUL(r, a, Anu(__VA_ARGS__))   // r = a * Const                   | r = a * Mat.B
#define Fmul(r, ...) FCMUL(r, r, Anu(__VA_ARGS__))              // r *= Const              | r *= Mat.B
#define FDiv(r, e, a, ...) FCDIV(r, e, a, Anu(__VA_ARGS__))     // r = a / Const           | r = a / Mat.B
#define Fdiv(r, e, ...) FCDIV(r, e, r, Anu(__VA_ARGS__))        // r /= Const              | r /= Mat.B
void FCMP(an a, anu l, an b);                                   // a[Mat.l]?b[l]  Mat.CF = / Mat.CN < || >=
void FTST(an a, anu l, an c);                   //a?Const  Mat.CF = / Mat.CN < || >=       | a ? Mat.B
anu FEQ(an a, anu l, an c);                     //a=(an)c[l]{Const1;Const2;...ConstN}      | a = Mat.B
anu FGE(an a, anu l, an c);                     //a?(an)c[l]{{[Const1,Const2]^k}{>=ConstN}}| a>= Mat.B
#define Ftst(a, ...) FTST(a, Anu(__VA_ARGS__))  //a?Const  Mat.CF = / Mat.CN < || >=       | a ? Mat.B
#define Flt(a, ...) (Ftst(a, __VA_ARGS__), (Mat.CN && !Mat.CF)) // a < Const               | a < Mat.B
#define Fgt(a, ...) (Ftst(a, __VA_ARGS__), !(Mat.CN | Mat.CF))  // a > Const               | a > Mat.B
#define Fle(a, ...) (Ftst(a, __VA_ARGS__), (Mat.CN | Mat.CF))   // a<= Const               | a<= Mat.B
#define Feq(a, ...) FEQ(a, Anu(__VA_ARGS__))                    // a = {Const1{,ConstN}}   | a = Mat.B
#define Fge(a, ...) FGE(a, Anu(__VA_ARGS__))                    // a ? {[..]^k}{>=ConstN}  | a>= Mat.B
#endif
