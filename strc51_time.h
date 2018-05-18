#ifndef TIME_H
#define TIME_H

/* sleep in milliseconds. 
 * The MOST PRECISIOUS ARE SECONDS! 
 * This function has VERY LARGE time speed unprecision.
 * use it only for short times, 
 * if need more then some seconds use sleep.
 */
void msleep(int n);

/* sleep in seconds */
void sleep(int n);

void init_time();

/* put call of it in your counter interrupt
 * catcher function. 
 */
void counter_timer();

/* Get only milliseconds in the current second. */
int getmsecs();
long getsecs();

struct time {
    long secs;
    int msecs;
};

void gettime(struct time* out);

/* Return 1 if a > b, 0 if a == b, -1 if a < b */
int cmp_time(struct time *a, struct time *b);

/* Return a - b */
void diff_time(struct time *a, struct time *b, struct time *out);

#endif /* TIME_H */
