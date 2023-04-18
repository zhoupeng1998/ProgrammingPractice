#ifndef CALC_H
#define CALC_H

#if defined(_WIN32) || defined(__CYGWIN__)
#define MYDLL_API __declspec(dllexport)
#define HIDDEN
#else
#define MYDLL_API __attribute__((visibility("default")))
#define HIDDEN __attribute__((visibility("hidden")))
#endif

#ifdef __cplusplus
extern "C" {
#endif

MYDLL_API extern int myadd(int a, int b);
MYDLL_API extern int mysub(int a, int b);
MYDLL_API extern int mymul(int a, int b);
MYDLL_API extern int mydiv(int a, int b);
MYDLL_API extern void printnum(int a);
HIDDEN extern void hiddenfunc();

#ifdef __cplusplus
}
#endif

#endif