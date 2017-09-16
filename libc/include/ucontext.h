#ifndef _UCONTEXT_H
#define _UCONTEXT_H
#ifdef __cplusplus
extern "C" {
#endif

#include <signal.h>

#ifdef _GNU_SOURCE
#define ucontext __ucontext
#endif

struct __ucontext;

int  getcontext(struct __ucontext *);
void makecontext(struct __ucontext *, void (*)(void), int, ...);
int  setcontext(const struct __ucontext *);
int  swapcontext(struct __ucontext *, const struct __ucontext *);

#ifdef __cplusplus
}
#endif
#endif
