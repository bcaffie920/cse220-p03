/***************************************************************************************************************
 * FILE: Error.h
 *
 * DESCRIPTION
 * Functions for error handling.
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
 * Web:   http: kevin.floorsoup.com
 **************************************************************************************************************/
#ifndef ERROR_H
#define ERROR_H

//==============================================================================================================
// CONSTANT DECLARATIONS
//==============================================================================================================

extern const int cErrorArg;
extern const int cErrorArgDup;
extern const int cErrorArgInputFile;
extern const int cErrorArgInvOpt;
extern const int cErrorArgRot;
extern const int cErrorArgUnexpStr;
extern const int cErrorFileOpen;
extern const int cErrorFileOpenRead;

//==============================================================================================================
// FUNCTION DECLARATIONS
//==============================================================================================================

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: ErrorExit
 *
 * DESCRIPTION
 * Called when an error occurs and the program must be terminated. This function works similarly to printf(). A
 * typical call would be something like,
 *
 *     ErrorExit(-1, "An error code %d occurred in %s", err_code, some_string_var);
 *
 *
 * pExitCode would be initialized to -1 when the function is called. pFmt would be initialized to "An error code
 * %d occurred in %s", and there would be two variadic arguments: err_code which had better be an int variable
 * (we don't do any type checking), and some_string_var which must be of data type char *.
 *
 * PARAMETERS
 * pExitCode	A nonzero integer which is sent back to the OS to indicate what error occurred.
 * pFmt			A format string similar to that of printf(). Valid format specifiers are %c, %d, and %s.
 *
 * NOTES
 * This is a variadic function because the ... following the required pFmt parameter states that there may be
 * 0, 1, 2, ... optional parameters. Variadic arguments are handled by preprocessor macros defined in stdarg.h,
 * in particular: va_list, va_start, va_arg, and va_end.
 *------------------------------------------------------------------------------------------------------------*/
void ErrorExit(int pExitCode, char *pFmt, ...);

#endif
