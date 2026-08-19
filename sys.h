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
//  As (As   основа, бытие, существовать) अः       n (Nimitta знак{овое}) निमित्त 
// anu (anu  атом) अणु                                                             v (Vṛddhi  увеличение {разрядности}) वृद्धि
//  an (anka цифра, число) अङ्क                          Vikara (Vikāra  модификация, изменение состояния) विकार
//	   Не бытие как состояние определяется в любом представлении чисел. Бесконечность как состояние
// возникает только в знаковом представлении чисел. При нахождении состояний длина схлопывается до одного байта.
//Mat.Nim         {00/XX} Без знаковое/Знаковое представление
//Mat.V           {00/XX} Возможность увеличения разрядности результата по мере необходимости
//Mat.C           {00/XX} Нет переполнения/Переполнение
//Mat.{F, Fre}    {00/01} Число/Состояние {Результата/Остатка}
//Mat.{Z, Zre}    {00/FF} Если число то {+/-} иначе состояние {Не бытие 0x00/0x80 Бесконечность}
//Mat.{l, cl}     длина операнда a, на выходе длина результата r {l = Mat.l + ((Mat.cl) ? 255 : 0);}
//Mat.lb          длина операнда b {не полдежит изменению внутри функций}
//Mat.lre         FDIV длина остатка re, FCold длина результата r
typedef uintptr_t  As;                                          //     As  базис,разрядность процессора
typedef uint8_t* an;						//     an  число,начальный адрес расположения
typedef uint8_t anu;                                            /*1   anu  атом,часть числа [0..FF]бит [1..8] 10^2
typedef int8_t nanu;                                            //1  n    [0,+1..+7F,80,-7F..-1]
typedef struct { anu l; union {anu m[1]; anu h;}; } vanu;       //2  v    [0..FFFF]      	   бит [1..16] 10^4
typedef struct { anu l; union {anu m[1]; nanu h;}; } vnanu;	//2 vn    [0,+1..+7FFF,8000,-7FFF..-1]
typedef struct { anu l, m[1], h; };                             //3       [0..FFFFFF]    	 + бит [1..24] 10^7
typedef struct { anu l, m[1] nanu h; };                         //3  n    [0,+1..+7FFFFF,800000,-7FFFFF..-1]
typedef struct { anu l, m[2], h; };                             //4       [0..FFFFFFFF]  	   бит [1..32] 10^9
typedef struct { anu l, m[2]; nanu h; };                        //4  n    [0,+1..+7FFFFFFF,80000000,-7FFFFFFF..-1]
typedef struct { anu l, m[3..5], h; };                          //5..7                         +++ бит [1..56] 10^12, 10^14, 10^16
typedef struct { anu l, m[6], h; };                             //8       [0..FFFFFFFFFFFFFFFF]    бит [1..64] 10^19
typedef struct { anu l, m[6]; nanu h; };                        //8  n    [0,+1..+7FFFFFFFFFFFFFFF,8000000000000000,-7FFFFFFFFFFFFFFF..-1]
typedef struct { anu l, m[1..253], h; };                        //3..255      + весь диапазон доступен [1..2040] 10^614 v{10^1228} */
typedef struct { anu l, m[254], h; } MatBuf;                    // 256     для внутренних буферов ибо нужен дополнительный байт для сдвига
typedef struct { MatBuf Ho, Sr, Lo; anu lb, Nim, V, C, F, N,
  Fre, Nre, cl, l, lre, fa, fb, na, nb, dr, da, db; an r, a, b, re, R, A, B, RE; } Cache; extern Cache Mat;
void _MatInit (anu c, an a);
void FLD (an r, anu D);
void FLVD (an r, anu Dl, anu Dh);
void FMOV (anu lb, an r, an b);
void VIKARA (anu lb, an r, an b);
void FSWAP (anu lb, an r, an b);
void FCold (anu BigEndian, anu lb, an r, an b);
void FRR (an r);
void FRL (an r);
void FADD (anu lb, an r, an a, an b);
void FSUB (anu lb, an r, an a, an b);
void FMUL (anu lb, an r, an a, an b);
void FDIV (anu lb, an r, an a, an b, an re);
#define _anu(...) (anu)((sizeof((anu[]){0, ##__VA_ARGS__}) / sizeof(anu)) - 1), (anu[]){0, ##__VA_ARGS__} + 1
#define FINI(...) _MatInit(_anu(__VA_ARGS__))
#endif
