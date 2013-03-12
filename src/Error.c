/***************************************************************************************************************
 * FILE: Error.c
 *
 * DESCRIPTION
 * See comments in Error.h.
 *
 * AUTHOR INFORMATION
 * Kevin R. Burger
 *
 * Mailing Address:
 * Computer Science & Engineering
 * School of Computing, Informatics, and Decision Systems Engineering
 * Arizona State University
 * Tempe, AZ 85287-8809
 *
 * Email: burgerk@asu.edu
 * Web:   http://kevin.floorsoup.com
 **************************************************************************************************************/
#include <stdarg.h>  // For variadic function macros
#include <stdio.h>   // For printf()
#include <stdlib.h>  // For exit()
#include "Error.h"
#include "Main.h"
#include "String.h"

//==============================================================================================================
// CONSTANT DEFINITIONS
//==============================================================================================================

// Note: These are declared in Error.h.
const int cErrorArg          	= -1;
const int cErrorArgDup 			= -2;
const int cErrorArgInputFile	= -3;
const int cErrorArgInvOpt		= -4;
const int cErrorArgRot			= -5;
const int cErrorArgUnexpStr		= -6;
const int cErrorFileOpen		= -7;
const int cErrorFileOpenRead	= -8;

//==============================================================================================================
// FUNCTION DEFINITIONS
//==============================================================================================================

/*--------------------------------------------------------------------------------------------------------------
 * ErrorExit
 *------------------------------------------------------------------------------------------------------------*/
void ErrorExit(int pExitCode, char *pFmt, ...)
{
	char msg[1024];
	sprintf(msg, "%s: ", cBinary);
	va_list argp; va_start(argp, pFmt);
	for (char *fp = pFmt; fp && *fp; ++fp) {
		if (*fp != '%') {
			StrCatCh(msg, *fp);
		} else {
			switch (*++fp) {
				case 'c': StrCatCh(msg, (char)va_arg(argp, int)); break;
				case 'd': StrCatInt(msg, va_arg(argp, int)); break;
				case 's': strcat(msg, va_arg(argp, char *)); break;
			}
		}
	}
	va_end(argp);
	printf("%s\n", msg);
	exit(pExitCode);
}
