#pragma once

#ifdef MYDLL_EXPORTS
#define MYDLL_API __declspec(dllexport)
#else
#define MYDLL_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

MYDLL_API int myadd(int a, int b);
MYDLL_API int mysub(int a, int b);
MYDLL_API int mymul(int a, int b);
MYDLL_API int mydiv(int a, int b);
MYDLL_API void printnum(int a);

#ifdef __cplusplus
}
#endif