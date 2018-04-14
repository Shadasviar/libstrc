#ifndef CROSS_DEF_H
#define CROSS_DEF_H

#if __unix__
#define xdata __xdata
#define at __at
#define sfr __sfr
#define sbit __sbit
#define interrupt __interrupt
#define critical __critical
#endif

#endif //CROSS_DEF_H

