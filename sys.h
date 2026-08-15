/* Math (C) 2026 A.Pozdnyakov GPLv3 - see LICENSE
 * E-mail: avp70ru@mail.ru
 * Данная программа является свободным программным обеспечением: вы можете
 * распространять ее и/или изменять согласно условиям Стандартной общественной
 * лицензии GNU (GPLv3). */
#ifndef SYS_H
#define SYS_H
#include <stdint.h>
//Begin 05.07.2026 in Russia
//  As		(As	 основа, бытие, существовать) अः
// anu		(anu	 атом) अणु 
// an		(anka	 цифра) अङ्क 
// n		(Nimitta знак{овое}) निमित्त 
// v		(Vṛddhi	 увеличение {разрядности вдвое}) वृद्धि
// Vikara	(Vikāra	 модификация, изменение состояния) विकार
//	  Не бытие как состояние определяется в любом представлении чисел
//	  Бесконечность как состояние возникает только в знаковом представлении чисел
//	  при нахождении состояний длина результата схлопывается до одного байта
//Mat.Nim	{00/XX} Без знаковое/Знаковое представление
//Mat.C		{00/XX} Нет переполнения/Переполнение результата
//Mat.{F, Fe}	{00/01} Число/Состояние результата
//Mat.{Z, Ze}	{00/FF} Если число то {+/-} иначе состояние {Не бытие/Бесконечность - байт равен 0/0x80}
//Mat.{Ll, Lh}	Длина первого операнда/результата
//Mat.L		Для удобства при использовании
typedef uintptr_t  As;						//         разрядность процессора
typedef uint8_t anu;                                		// 1   anu [0..FF]        		[1..8] бит
//typedef int8_t nanu;                             		// 1  n    [0,+1..+7F,80,-7F..-1]
typedef struct { anu l; union {anu m[1]; anu h;}; } vanu;       // 2  v    [0..FFFF]      		[1..16] бит
//typedef struct { anu l; union {anu m[1]; nanu h;}; } vnanu;	// 2 vn    [0,+1..+7FFF,8000,-7FFF..-1]
//typedef struct { anu l, m[1], h; };               		// 3       [0..FFFFFF]    		+[17..24] бит
//typedef struct { anu l, m[1] nanu h; };              		// 3       [0,+1..+7FFFFF,800000,-7FFFFF..-1]
typedef struct { anu l, m[2], h; } an;              		// 4   an  [0..FFFFFFFF]  		[1..32] бит
//typedef struct { anu l, m[2]; nanu h; } nan;      		// 4  n    [0,+1..+7FFFFFFF,80000000,-7FFFFFFF..-1]
//typedef struct { anu l, m[3..5], h; };            		// 5-7                    		+[33..56] бит
//typedef struct { anu l, m[3..5] nanu h; };			// 5-7n
typedef struct { anu l, m[6], h; } van;             		// 8  v    [0..FFFFFFFFFFFFFFFF]	[1..64] бит
//typedef struct { anu l, m[6]; nanu h; } vnan;			// 8 vn    [0,+1..+7FFFFFFFFFFFFFFF,8000000000000000,-7FFFFFFFFFFFFFFF..-1]
//typedef struct { anu l, m[1..253], h; };          		// 1-255                  		[1..2040] весь диапазон доступен
//typedef struct { anu l, m[1..253]; nanu h; };			// 1-255n
typedef struct { anu l, m[254], h; } MatBuf;        		// 256					+[2041..2048] бит
typedef struct { union {anu l; anu m[1]; anu h;}; } Sanu;	// 1       возможность работать с anu как со структурой
typedef struct { MatBuf Ho, Sr, Lo; anu Nim, C, L, Ll, Lh, Lc,
  F, Fe, Z, Ze, fa, fb, za, zb, br, ba, bb, be, *r, *a, *b, *e, *R, *A, *B, *E; } Cache;
extern Cache Mat;
void FINIT (anu Nim, anu l);
void FLD (anu *r, anu D);
void FLVD (anu *r, anu Dl, anu Dh);
void FRR (anu *r);
void FRL (anu *r);
void FMOV (anu lra, anu *r, anu *a);
void FSWAP (anu lra, anu *r, anu *a);
void VIKARA (anu lra, anu *r, anu *a);
void FCold (anu BigEndian, anu *r, anu *a);
void FADD (anu lb, anu *r, anu *a, anu *b);
void FSUB (anu lb, anu *r, anu *a, anu *b);
void FMUL (anu lb, anu *r, anu *a, anu *b);
void FDIV (anu lbe, anu *r, anu *a, anu *b, anu *e);
#endif
