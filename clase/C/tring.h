[4mstrcpy[24m(3)                  Library Functions Manual                  [4mstrcpy[24m(3)

[1mNAME[0m
       stpcpy, strcpy, strcat - copy or catenate a string

[1mLIBRARY[0m
       Standard C library ([4mlibc[24m, [4m-lc[24m)

[1mSYNOPSIS[0m
       [1m#include <string.h>[0m

       [1mchar *stpcpy(char *restrict [4m[22mdst[24m[1m, const char *restrict [4m[22msrc[24m[1m);[0m
       [1mchar *strcpy(char *restrict [4m[22mdst[24m[1m, const char *restrict [4m[22msrc[24m[1m);[0m
       [1mchar *strcat(char *restrict [4m[22mdst[24m[1m, const char *restrict [4m[22msrc[24m[1m);[0m

   Feature Test Macro Requirements for glibc (see [1mfeature_test_macros[22m(7)):

       [1mstpcpy[22m():
           Since glibc 2.10:
               _POSIX_C_SOURCE >= 200809L
           Before glibc 2.10:
               _GNU_SOURCE

[1mDESCRIPTION[0m
       [1mstpcpy[22m()
       [1mstrcpy[22m()
              These functions copy the string pointed to by [4msrc[24m, into a string
              at  the buffer pointed to by [4mdst[24m.  The programmer is responsible
              for allocating a  destination  buffer  large  enough,  that  is,
              [4mstrlen(src)[24m  [4m+[24m [4m1[24m.  For the difference between the two functions,
              see RETURN VALUE.

       [1mstrcat[22m()
              This function catenates the string pointed to by [4msrc[24m, after  the
              string  pointed  to  by  [4mdst[24m  (overwriting  its terminating null
              byte).  The programmer is responsible for allocating a  destina‐
              tion  buffer  large enough, that is, [4mstrlen(dst)[24m [4m+[24m [4mstrlen(src)[24m [4m+[0m
              [4m1[24m.

       An implementation of these functions might be:

           char *
           stpcpy(char *restrict dst, const char *restrict src)
           {
               char  *p;

               p = mempcpy(dst, src, strlen(src));
               *p = '\0';

               return p;
           }

           char *
           strcpy(char *restrict dst, const char *restrict src)
           {
               stpcpy(dst, src);
               return dst;
           }

           char *
           strcat(char *restrict dst, const char *restrict src)
           {
               stpcpy(dst + strlen(dst), src);
               return dst;
           }

[1mRETURN VALUE[0m
       [1mstpcpy[22m()
              This function returns a pointer to the terminating null byte  of
              the copied string.

       [1mstrcpy[22m()
       [1mstrcat[22m()
              These functions return [4mdst[24m.

[1mATTRIBUTES[0m
       For  an  explanation  of  the  terms  used in this section, see [1mattrib‐[0m
       [1mutes[22m(7).
       ┌───────────────────────────────────────────┬───────────────┬─────────┐
       │ [1mInterface                                 [22m│ [1mAttribute     [22m│ [1mValue   [22m│
       ├───────────────────────────────────────────┼───────────────┼─────────┤
       │ [1mstpcpy[22m(), [1mstrcpy[22m(), [1mstrcat[22m()              │ Thread safety │ MT-Safe │
       └───────────────────────────────────────────┴───────────────┴─────────┘

[1mSTANDARDS[0m
       [1mstpcpy[22m()
              POSIX.1-2008.

       [1mstrcpy[22m()
       [1mstrcat[22m()
              C11, POSIX.1-2008.

[1mSTANDARDS[0m
       [1mstpcpy[22m()
              POSIX.1-2008.

       [1mstrcpy[22m()
       [1mstrcat[22m()
              POSIX.1-2001, C89, SVr4, 4.3BSD.

[1mCAVEATS[0m
       The strings [4msrc[24m and [4mdst[24m may not overlap.

       If the destination buffer is not large enough, the  behavior  is  unde‐
       fined.  See [1m_FORTIFY_SOURCE [22min [1mfeature_test_macros[22m(7).

       [1mstrcat[22m() can be very inefficient.  Read about ]8;;https://www.joelonsoftware.com/2001/12/11/back-to-basics/\Shlemiel the painter]8;;\.

[1mEXAMPLES[0m
       #include <err.h>
       #include <stdio.h>
       #include <stdlib.h>
       #include <string.h>

       int
       main(void)
       {
           char    *p;
           char    *buf1;
           char    *buf2;
           size_t  len, maxsize;

           maxsize = strlen("Hello ") + strlen("world") + strlen("!") + 1;
           buf1 = malloc(sizeof(*buf1) * maxsize);
           if (buf1 == NULL)
               err(EXIT_FAILURE, "malloc()");
           buf2 = malloc(sizeof(*buf2) * maxsize);
           if (buf2 == NULL)
               err(EXIT_FAILURE, "malloc()");

           p = buf1;
           p = stpcpy(p, "Hello ");
           p = stpcpy(p, "world");
           p = stpcpy(p, "!");
           len = p - buf1;

           printf("[len = %zu]: ", len);
           puts(buf1);  // "Hello world!"
           free(buf1);

           strcpy(buf2, "Hello ");
           strcat(buf2, "world");
           strcat(buf2, "!");
           len = strlen(buf2);

           printf("[len = %zu]: ", len);
           puts(buf2);  // "Hello world!"
           free(buf2);

           exit(EXIT_SUCCESS);
       }

[1mSEE ALSO[0m
       [1mstrdup[22m(3), [1mstring[22m(3), [1mwcscpy[22m(3), [1mstring_copying[22m(7)

Linux man-pages 6.7               2023-10-31                         [4mstrcpy[24m(3)
