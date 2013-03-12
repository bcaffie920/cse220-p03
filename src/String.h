/***************************************************************************************************************
 * FILE: String.h
 *
 * DESCRIPTION
 * String handling functions.
 *
 * AUTHOR INFORMATION
 * Kevin R. Burger [KRB]
 *
 * Mailing Address:
 * Computer Science & Engineering
 * School of Computing, Informatics, and Decision Systems Engineering
 * Arizona State University
 * Tempe, AZ 85287-8809
 *
 * Email: burgerk@asu
 * Web:   http://kevin.floorsoup.com
 **************************************************************************************************************/
#ifndef STRING_H  // Preprocessor guard to prevent String.h from being included more than once.
#define STRING_H

/*
 * A header file can always #include other header files, in particular, when that other header file contains
 * some piece of code that is ABSOLUTELY NECESSARY in the current header file. But you should not just #include
 * header files willy nilly, including them just for some rainy day when you may actually NEED the stuff de-
 * clared in the other header file. Why? Because it slows down the compilation of your code. Remember, header
 * files contain code. Code must be compiled. The more code that must be compiled, the longer it takes the com-
 * piler to compile a source code file. How to reduce the amount of time it takes the compiler to compile a
 * source code file? Reduce the amount of code in the source code file. One way to reduce the amount of code in
 * a source code file. Don't #include header files that contain code that you DO NOT NEED. (Note: you might be
 * able to use precompiled header files to get around this, but I don't care, it's still bad programming style,
 * so don't do it.)
 *
 * Header File Rule: Only #include a header file in a .h or .c file IFF that header file contains some piece
 * of code that is ABSOLUTELY NECESSARY in the .h or .c file in order for it to be compilable.
 *
 * Note that violating this Header File Rule will not banish you to the lowest depths of hell, but if you do it
 * enough, you *will* go blind.
 *
 * Now's probably the time for me to also mention the difference between,
 *
 * #include <afile.h>
 * #include "anotherfile.h"
 *
 * The former syntax <> is used for header files that are part of the C Standard Library, e.g., string.h,
 * stdio.h, stdlib.h, and math.h. The latter syntax is for header files that you create which are part of your
 * project.
 *
 * When the compiler sees a header file name in <> it will look in the system include directory(ies) for the
 * header file. Most of the header files for the C Standard Library are found in /usr/include. It won't look in
 * the current directory for these header files. On the other hand, when the compiler sees the header file name
 * inside "", it will NOT look in the system include directory for the file, but rather in your current direct-
 * ory (or some other directory you specify to the compiler by throwing the -I option at the gcc compiler).
 */
#include <string.h>

//==============================================================================================================
// PREPROCESSOR MACROS
//==============================================================================================================

/*
 * streq is a preprocessor macro function definition.
 *
 * The strcmp() library function is used to compare two strings. It returns one of three integers: (1) 0 if the
 * two strings are equal; (2) a negative integer if s1 < s2; or (3) a positive integer if s1 > s2. To compare
 * two strings for equality, then, one could write something like,
 *
 *     char *s1 = "Fred";
 *     char *s2 = "Fred";
 *
 *     if (strcmp(s1, s2) == 0) {
 *         -- the strings are equal
 *     }
 *
 * or
 *
 *     if (!strcmp(s1, s2)) {
 *         -- the strings are equal
 *     }
 *
 * I think that both of those look kinda sleazy, so my streq macro permits me to write this as,
 *
 *     if (streq(s1, s2)) {
 *         -- the strings are equal
 *     }
 *
 * It's just a matter of personal preference, but that's my reason. You may also ask why I didn't just write a
 * function named streq() and that would be a valid question. I didn't because it takes time to call a function,
 * whereas a preprocessor macro is simply textual substitution of one string for another.
 */
#define streq(s1,s2) (!strcmp((s1),(s2)))

//==============================================================================================================
// FUNCTION DECLARATIONS
//==============================================================================================================

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: StrCatCh
 *
 * DESCRIPTION
 * Concatenates pCh onto the end of pString and returns pString.
 *
 * NOTE
 * pString had better be large enough to store the concatenated char.
 *------------------------------------------------------------------------------------------------------------*/
char *StrCatCh(char *pString, char pChar);

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: StrCatInt
 *
 * DESCRIPTION
 * Concatenates pInt (turned into a string) onto the end of pString and returns pString.
 *
 * NOTE
 * pString had better be large enough to store the concatenated int.
 *------------------------------------------------------------------------------------------------------------*/
char *StrCatInt(char *pString, int pInt);

#endif
