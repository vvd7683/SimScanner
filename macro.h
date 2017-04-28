#ifndef MACRO_H
#define MACRO_H

#define PRED(x)     ((x) - 1)
#define SUCC(x)     ((x) + 1)

#define COUNT(arr)  (sizeof((arr))/sizeof((*arr)))
#define ZEROARR(arr) (memset(arr, 0, sizeof(arr)))

#endif // MACRO_H
