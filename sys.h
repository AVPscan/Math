/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3).
 */
#ifndef SYS_H
#define SYS_H
#include <stdint.h>
//Begin 05.07.2026 in Russia
//  As (As   основа, бытие, существовать) अः      n      (Nimitta знак{овое}) निमित्त 
// anu (anu  атом) अणु                                                            v      (Vṛddhi  увеличение {разрядности вдвое}) वृद्धि
// an  (anka цифра) अङ्क                                                      Vikara (Vikāra  модификация, изменение состояния) विकार
//	   Не бытие как состояние определяется в любом представлении чисел. Бесконечность как состояние возникает
// только в знаковом представлении чисел. При нахождении состояний длина схлопывается до одного байта.
//Mat.Nim         {00/XX} Без знаковое/Знаковое представление
//Mat.Over        {00/XX} Возможность роста размера результата
//Mat.C           {00/XX} Нет переполнения/Переполнение
//Mat.{F, Fre}    {00/01} Число/Состояние
//Mat.{Z, Zre}    {00/FF} Если число то {+/-} иначе состояние {Не бытие 0x00/0x80 Бесконечность}
//Mat.{l, cl}     длина операнда a, на выходе длина результата r {l = l + ((cl) ? 255 : 0);}
//Mat.lb          длина операнда b {не полдежит изменению внутри функций}
//Mat.lre         FDIV длина остатка re, FCold длина результата r
typedef uintptr_t  As;                                          //        разрядность процессора
typedef uint8_t anu;                                            // 1   anu [0..FF]        	    бит	[1..8] 10^2
//typedef int8_t nanu;                                           //1  n    [0,+1..+7F,80,-7F..-1]
typedef struct { anu l; union {anu m[1]; anu h;}; } vanu;       // 2  v    [0..FFFF]      	    бит	[1..16] 10^4
//typedef struct { anu l; union {anu m[1]; nanu h;}; } vnanu;    //2 vn    [0,+1..+7FFF,8000,-7FFF..-1]
//typedef struct { anu l, m[1], h; };                            //3       [0..FFFFFF]    	  + бит	[17..24] 10^7
//typedef struct { anu l, m[1] nanu h; };                        //3       [0,+1..+7FFFFF,800000,-7FFFFF..-1]
typedef struct { anu l, m[2], h; } an;                          // 4   an  [0..FFFFFFFF]  	    бит	[1..32] 10^9
//typedef struct { anu l, m[2]; nanu h; } nan;                   //4  n    [0,+1..+7FFFFFFF,80000000,-7FFFFFFF..-1]
//typedef struct { anu l, m[3..5], h; };                         //5..7                         +++ бит [33..56] 10^12, 10^14, 10^16
//typedef struct { anu l, m[3..5] nanu h; };                     //5..7n
typedef struct { anu l, m[6], h; } van;                         // 8  v    [0..FFFFFFFFFFFFFFFF]    бит [1..64] 10^19
//typedef struct { anu l, m[6]; nanu h; } vnan;                  //8 vn    [0,+1..+7FFFFFFFFFFFFFFF,8000000000000000,-7FFFFFFFFFFFFFFF..-1]
//typedef struct { anu l, m[1..253], h; };                       //3..255      + весь диапазон доступен [17..2040] 10^614
//typedef struct { anu l, m[1..253]; nanu h; };                  //3..255n
typedef struct { anu l, m[254], h; } MatBuf;                    // 256                            + бит [2041..2048] 10^616 v{10^1228}
typedef struct { union {anu l; anu m[1]; anu h;}; } Sanu;       // 1       возможность работать с anu как со структурой
typedef struct { MatBuf Ho, Sr, Lo; anu Nim, Over, C, F, N, Fre, Nre,
  l, cl, lb, lre, fa, fb, na, nb, dr, da, db, *r, *a, *b, *re, *R, *A, *B, *RE; } Cache; extern Cache Mat;
void FINIT (anu lb, anu n, anu o);
void FLD (anu *r, anu D);
void FLVD (anu *r, anu Dl, anu Dh);
void FRR (anu *r);
void FRL (anu *r);
void FMOV (anu lb, anu *r, anu *b);
void FSWAP (anu lb, anu *r, anu *b);
void VIKARA (anu lb, anu *r, anu *b);
void FCold (anu BigEndian, anu lb, anu *r, anu *b);
void FADD (anu lb, anu *r, anu *a, anu *b);
void FSUB (anu lb, anu *r, anu *a, anu *b);
void FMUL (anu lb, anu *r, anu *a, anu *b);
void FDIV (anu lb, anu *r, anu *a, anu *b, anu *re);
#endif
