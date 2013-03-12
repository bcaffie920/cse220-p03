/***************************************************************************************************************
 * FILE: String.c
 *
 * DESCRIPTION
 * See comments in String.h.
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
#include <stdio.h>   // For sprintf()
#include "String.h"

/*
 * Notice that String.c does not really need to include String.h, but it is a good idea to do so. It permits
 * the compiler to check that declarations in String.h are consistent with the definitions in this file. For
 * example,
 *
 * String.c
 * ---------
 * #include "String.h"
 *
 * void SomeFunction(int someParameter) { ... }
 *
 * String.h
 * ---------
 * int SomeFunction (void) { ... }
 *
 * Notice that the declaration in String.h is inconsistent with the definition in String.c (look at the return
 * data type and the data type of the parameter). Well, this is obviously wrong, so by including String.h in
 * String.c, the compiler will catch these errors and flag them for you. Saves you a bunch o' time.
 *
 * When I write C code, I always create a .h file for every .c file, unless that .c file does not contain any
 * definitions that are used in another .c file. If you think about it, you might begin to wonder why a .c file
 * containing definitions would not contain a definition for something that is going to be used in a different
 * .c file. Why would that .c file exist? Generally, the only .c file that won't have a matching header file
 * is Main.c.
 */

//==============================================================================================================
// FUNCTION DEFINITIONS
//==============================================================================================================

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: StrCatCh()
 *------------------------------------------------------------------------------------------------------------*/
char *StrCatCh(char *pString, char pCh)
{
    char buf[2] = { pCh, '\0' };
    strcat(pString, buf);
    return pString;
}

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: StrCatInt()
 *------------------------------------------------------------------------------------------------------------*/
char *StrCatInt(char *pString, int pInt)
{
    char buf[32];
    sprintf(buf, "%d", pInt);
    strcat(pString, buf);
    return pString;
}
