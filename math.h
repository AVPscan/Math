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
// Mat.F{Fe}    [0,1,2] {0} число/состояние {1} небытиё {2} бесконечность результата{остатка}
// Mat.N{Ne}     [0/X]  {0} для чисел без знака или положительное иначе отрицательное {+/-}
// Mat.TF        [0/X]  {0} не равенство
// Mat.TN        [0/X]  {0} больше или равно иначе меньше
// Mat.l{le}    [0.255] длина первого операнда a, длина результата r{остатка e}
// Mat.lb       [0.255] длина последнего обработанного второго операнда
// Mat.b        адрес последнего обработанного второго операнда
// Mat.Nim, Mat.V, Mat.B{ARE} не подлежат изменению внутри функций

typedef uintptr_t As;                           // основа, разрядность процессора
typedef uint8_t anu;                            // атом, минимальная единица
typedef anu* an;                                // число, начальный адрес расположения
typedef struct { anu Nim, V, lb, l, le, C, F, N, Fe, Ne, TF, TN,
  i,j,k,o,p,q,u,x,y,z,H[255],L[255],S[255]; an e,r,a,ae,be,b, B, A, R, E; } Math;

extern Math Mat;
#define MCINIT Math Mat = {0};
#define Anu(...) (anu)(sizeof((anu[]){0, ##__VA_ARGS__})-1), (anu[]){0, ##__VA_ARGS__}+1
#define Adr(...) (anu)((sizeof((As[]){0, ##__VA_ARGS__})/sizeof(As))-1), (As[]){0, ##__VA_ARGS__}+1
void FInit(anu x, anu y, an r, anu c, an a);            // Универсальный примитив
void FAddr(anu y, As* r, anu c, As* a);                 // Faddr({(As)b{,(As)a{,(As)r{,(As)e}}}});
#define Faddr(...) FAddr(4,(As*)&Mat.b,Adr(__VA_ARGS__))// Установка адресов B A R E и Mat.b = Mat.B
#define Fset(...) FInit(0,4,&Mat.Nim,Anu(__VA_ARGS__))  // Fset({Nim{,V{,lb{,la}}}});
#define Fini(...) FInit(12,4,&Mat.i,Anu(__VA_ARGS__))   // Nim=V=lb=l..Ne=0 Fini({Nim{,V{,lb{,la}}}});
#define Flong(...) FInit(0,3,&Mat.lb,Anu(__VA_ARGS__))  // Flong({lb{,la{,le}}});

void FSWAP(an r, anu l, an b);                  // Зеркалирование атомов длиной l относительно центра числа
anu FMOV(an a, anu l, an b);                    // Копирование a[lnew] = b[l], lnew <= l  8,16,32,64|128,256,512,1024,2048 бит
anu FOLD(anu f, an a, anu l, an b);             // Приведение к формату lnew >= l            0,1,3,7|15,31,63,127,255 атомов
anu FVAR(anu f, an a, anu l, an c);             // Копирование из константы в переменную lnew <= l  | a = 0
#define Fswap(l, x) FSWAP(x, l, x)                      // Fswap(l, x); Fswap(l, x); -> {}
#define Fmov(l, x) FMOV(x, l, x)                        // lnew <= l                     | Mat.u ? 0:Mat.z ? -:+
#define Fold(f, l, x) FOLD(f, x, l, x)                  // lnew >= l                     | Mat.u ? 0:Mat.z ? -:+
#define FVar(f, r, ...) FVAR(f, r, Anu(__VA_ARGS__))    // r = Num{LittleEnd/BigEnd}     | r = 0
#define Fvle(r, ...) FVar(0, r, __VA_ARGS__)            // r = Num{LittleEndian}         | r = 0
#define Fvbe(r, ...) FVar(1, r, __VA_ARGS__)            // r = Num{BigEndian}            | r = 0

anu FSin(anu s, anu x);                                 // 127sin(s:x) [-127..127] интерполяция x [0..255], s [0/X] знак x
#define FCos(s, x) FSin(((x)&128)?!(s):(s), ((x)^128))  // 127cos(s:x)  2pi = 512, шаг 360/512 = 0,703125 градуса.
void FSIN(an r, anu l, an b);                           // r = 127sin(b)
void FCOS(an r, anu l, an b);                           // r = 127cos(b)

void FTST(an a, anu l, an b);                           // a[Mat.l] ? b[l]  Mat.TF? =:Mat.TN? <:>
#define FGE(x, l, y) (FTST(x, l, y),!Mat.TN)            // x >= y
#define FLE(x, l, y) (FTST(x, l, y),(Mat.TN | Mat.TF))  // x <= y
#define FGT(x, l, y) (FTST(x, l, y),!(Mat.TN | Mat.TF)) // x > y
#define FLT(x, l, y) (FTST(x, l, y),Mat.TN)             // x < y
#define FEQ(x, l, y) (FTST(x, l, y),Mat.TF)             // x = y
#define FNE(x, l, y) (FTST(x, l, y),!Mat.TF)            // x != y

void FADD(an r, an a, anu l, an b);                     // r = a + b        | r += Mat.b -> Fadd(r);
void FSUB(an r, an a, anu l, an b);                     // r = a - b        | r -= 256 -> Fsub(r, 0,1);
void FMUL(an r, an a, anu l, an b);                     // r = a * b        | r *= Mat.b -> Fmul(r);
void FDIV(an r, an e, an a, anu l, an b);               // r = a / b  Евклид {+}  e = a mod b
void FSQR(an r, an e, anu l, an b);                     // r = SQRT(b),+e  if b<0 then 𝄵 z = ir - e
#define Fsqr(e, l, b) FSQR(b, e, l, b)                  // b = SQRT(b),+e   Im z = r = SQRT(|b|), Re z = -e

void FCSIN(an r, anu l, an c);                          // r = 127sin((an)c[l]{Num})     | !l r = 127sin(Mat.b)
void FCCOS(an r, anu l, an c);                          // r = 127cos((an)c[l]{Num})     | !l r = 127cos(Mat.b)
#define Fsin(r, ...) FCSIN(r, Anu(__VA_ARGS__))                // r = 127sin(Num)        | r = 127sin(Mat.b)
#define Fcos(r, ...) FCCOS(r, Anu(__VA_ARGS__))                // r = 127cos(Num)        | r = 127cos(Mat.b)

void FCTST(an a, anu l, an c);                  // a?(an)c[l]{Num} Mat.TF? =:Mat.TN? <:> | !l a ? Mat.b
#define Ftst(x, ...) FCTST(x, Anu(__VA_ARGS__)) // x ? Num         Mat.TF? =:Mat.TN? <:> | !l x ? Mat.b
#define Fge(x, ...) (Ftst(x, __VA_ARGS__),!Mat.TN)              // x >= Num              | x >= Mat.b
#define Fle(x, ...) (Ftst(x, __VA_ARGS__),(Mat.TN | Mat.TF))    // x <= Num              | x <= Mat.b
#define Fgt(x, ...) (Ftst(x, __VA_ARGS__),!(Mat.TN | Mat.TF))   // x > Num               | x > Mat.b
#define Flt(x, ...) (Ftst(x, __VA_ARGS__),Mat.TN)               // x < Num               | x < Mat.b
#define Feq(x, ...) (Ftst(x, __VA_ARGS__),Mat.TF)               // x = Num               | x = Mat.b
#define Fne(x, ...) (Ftst(x, __VA_ARGS__),!Mat.TF)              // x != Num              | x != Mat.b

anu FCGE(an a, anu l, an c);                    // a ? (an)c[l]{[Num1,Num2]^k...}{[NumN} | !l a >= Mat.b
anu FCLT(an a, anu l, an c);                    // a ? (an)c[l]{)Num1,Num2(^k...}{)NumN} | !l a < Mat.b
void FCEQ(an a, anu l, an c);                   // a = (an)c[l]{Num1...{,NumN}}          | !l a = Mat.b
#define FGe(x, ...) FCGE(x, Anu(__VA_ARGS__))           // x ? {[Num1;Num2]^k...}{[NumN} | x >= Mat.b
#define FLt(x, ...) FCLT(x, Anu(__VA_ARGS__))           // x ? {)Num1,Num2(^k...}{)NumN} | x < Mat.b
#define FEq(x, ...) (FCEQ(x, Anu(__VA_ARGS__)),Mat.TF)          // x = {Num1...{,NumN}}  | x = Mat.b
#define FNe(x, ...) (FCEQ(x, Anu(__VA_ARGS__)),!Mat.TF)         // x != {Num1...{,NumN}} | x != Mat.b

void FCADD(an r, an a, anu l, an c);                            // r = a + (an)c[l]{Num} | !l r = a + Mat.b
void FCSUB(an r, an a, anu l, an c);                            // r = a - (an)c[l]{Num} | !l r = a - Mat.b
void FCMUL(an r, an a, anu l, an c);                            // r = a * (an)c[l]{Num} | !l r = a * Mat.b
void FCDIV(an r, an e, an a, anu l, an c);                      // r = a / (an)c[l]{Num} | !l r = a / Mat.b
#define FAdd(r, a, ...) FCADD(r, a, Anu(__VA_ARGS__))           // r = a + Num           | r = a + Mat.b
#define FSub(r, a, ...) FCSUB(r, a, Anu(__VA_ARGS__))           // r = a - Num           | r = a - Mat.b
#define FMul(r, a, ...) FCMUL(r, a, Anu(__VA_ARGS__))           // r = a * Num           | r = a * Mat.b
#define FDiv(r, e, a, ...) FCDIV(r, e, a, Anu(__VA_ARGS__))     // r = a / Num, e =...   | r = a / Mat.b
#define Fadd(r, ...) FCADD(r, r, Anu(__VA_ARGS__))              // r += Num              | r += Mat.b
#define Fsub(r, ...) FCSUB(r, r, Anu(__VA_ARGS__))              // r -= Num              | r -= Mat.b
#define Fmul(r, ...) FCMUL(r, r, Anu(__VA_ARGS__))              // r *= Num              | r *= Mat.b
#define Fdiv(r, e, ...) FCDIV(r, e, r, Anu(__VA_ARGS__))        // r /= Num, e =...      | r /= Mat.b, e =...
#endif
