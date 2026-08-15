[![Cross-Platform Build & Release](https://github.com/AVPscan/Math/actions/workflows/release.yml/badge.svg)](https://github.com/AVPscan/Math/actions/workflows/release.yml)


# Math Library

*Библиотека для работы с целыми числами произвольной точности*

```c
Begin 05.07.2026 in Russia

  As            (As      основа, бытие, существовать) अः
 anu            (anu     атом) अणु 
 an             (anka    цифра) अङ्क 
 n              (Nimitta знак{овое}) निमित्त 
 v              (Vṛddhi  увеличение {разрядности вдвое}) वृद्धि
 Vikara         (Vikāra  модификация, изменение состояния) विकार
	  Не бытие как состояние определяется в любом представлении чисел
	  Бесконечность как состояние возникает только в знаковом представлении чисел
	  при нахождении состояний длина результата схлопывается до одного байта
Mat.Nim         {00/XX} Без знаковое/Знаковое представление
Mat.C           {00/XX} Нет переполнения/Переполнение результата
Mat.{F, Fe}     {00/01} Число/Состояние результата
Mat.{Z, Ze}     {00/FF} Если число то {+/-} иначе состояние {Не бытие/Бесконечность}
Mat.{Ll, Lh}    Длина первого операнда на входе и результата на выходе
Mat.L           Для удобства при использовании

typedef uintptr_t  As;                                          //         разрядность процессора
typedef uint8_t anu;                                            // 1   anu [0..FF]        		    [1..8] бит
//typedef int8_t nanu;                                          // 1  n    [0,+1..+7F,80,-7F..-1]
typedef struct { anu l; union {anu m[1]; anu h;}; } vanu;       // 2  v    [0..FFFF]      		    [1..16] бит
//typedef struct { anu l; union {anu m[1]; nanu h;}; } vnanu;   // 2 vn    [0,+1..+7FFF,8000,-7FFF..-1]
//typedef struct { anu l, m[1], h; };                           // 3       [0..FFFFFF]    		    +[17..24] бит
//typedef struct { anu l, m[1] nanu h; };              		   // 3       [0,+1..+7FFFFF,800000,-7FFFFF..-1]
typedef struct { anu l, m[2], h; } an;              		       // 4   an  [0..FFFFFFFF]  		[1..32] бит
//typedef struct { anu l, m[2]; nanu h; } nan;      		       // 4  n    [0,+1..+7FFFFFFF,80000000,-7FFFFFFF..-1]
//typedef struct { anu l, m[3..5], h; };            		       // 5-7                    		+[33..56] бит
//typedef struct { anu l, m[3..5] nanu h; };			           // 5-7n
typedef struct { anu l, m[6], h; } van;             		       // 8  v    [0..FFFFFFFFFFFFFFFF]  [1..64] бит
//typedef struct { anu l, m[6]; nanu h; } vnan;			       // 8 vn    [0,+1..+7FFFFFFFFFFFFFFF,8000000000000000,-7FFFFFFFFFFFFFFF..-1]
//typedef struct { anu l, m[1..253], h; };          		       // 1-255                          [1..2040] весь диапазон доступен
//typedef struct { anu l, m[1..253]; nanu h; };			       // 1-255n
typedef struct { anu l, m[254], h; } MatBuf;        		       // 256					        +[2041..2048] бит
typedef struct { union {anu l; anu m[1]; anu h;}; } Sanu;	       // 1       возможность работать с anu как со структурой
typedef struct { MatBuf Ho, Sr, Lo; anu Nim, C, L, Ll, Lh, Lc,
  F, Fe, Z, Ze, fa, fb, za, zb, br, ba, bb, be, *r, *a, *b, *e, *R, *A, *B, *E; } Cache;

```

## Лицензия

Распространяется под условиями Стандартной общественной лицензии GNU (GPLv3). Автор (C) 2026 А. Поздняков.
