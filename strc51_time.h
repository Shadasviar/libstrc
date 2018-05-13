#ifndef TIME_H
#define TIME_H

/* sleep in milliseconds. 
 * The MOST PRECISIOUS ARE SECONDS! 
 * This function has VERY LARGE time speed unprecision.
 * This function is UNSAFE every near 10min time part.
 */
void msleep(int n);

/* sleep in seconds */
void sleep(int n);

void init_time();

/* put call of it in your counter interrupt
 * catcher function. 
 */
void counter_timer();

#endif /* TIME_H */
