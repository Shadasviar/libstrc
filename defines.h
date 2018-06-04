#ifndef DEF_H
#define DEF_H

#if __SDCC_VERSION_MAJOR <= 1

#define __interrupt interrupt
#define __sfr sfr
#define __at at
#define __bit bit
#define __asm__(x) _asm x _endasm;
#define __xdata xdata

#else 
#define __asm__(x) __asm__(#x)
#endif

#endif /* DEF_H */
