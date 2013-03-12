/***************************************************************************************************************
 * FILE: Arg.h
 *
 * DESCRIPTION
 * Functions for scanning the command line for options and arguments.
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
 * Web:   http: kevin.floorsoup.com
 **************************************************************************************************************/
#ifndef ARG_H
#define ARG_H

//==============================================================================================================
//  TYPE DEFINITIONS
//==============================================================================================================

typedef struct {
	char   *arg;			// A pointer to an argument found on the command line.
	int 	argc;			// The argc param to main().
	char  **argv;			// The argv param to main().
	char 	error[1024];	// An error message indicating what was wrong on the command line.
	int 	index;			// The index of the argv[] element being examined.
	char   *longOpts;		// A string containing the list of long options.
	char   *opt;			// For a valid option, points to the option string in argv.
	char   *shortOpts;		// A string containing the list of short options.
} tArgScan;

//==============================================================================================================
// CONSTANT DECLARATIONS
//==============================================================================================================

extern const int cArg;
extern const int cArgEnd;
extern const int cArgInvOpt;
extern const int cArgLongOpt;
extern const int cArgMissingArg;
extern const int cArgShortOpt;
extern const int cArgUnexpStr;

//==============================================================================================================
// FUNCTION DECLARATIONS
//==============================================================================================================

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: ArgScan()
 *
 * DESCRIPTION
 * The input parameter is a pointer to a tArgScan struct object containing these data members.
 *
 *     arg          If an optionless argument (an argument not associated with an option) is encountered in a
 *                  call to ArgScan(), this member will be a pointer to the argument string in pScan->argv[].
 *     argc         The value of the argc parameter to main().
 *     argv         The value of the argv parameter to main(). This is a 1D array of pointers to the strings
 *                  on the command line.
 *     error        If an error is detected during a call to ArgScan(), this string will contain an error mes-
 *                  sage indicating what was wrong.
 *     index        The index in pScan->argv[] of the option string to be examined on this call to ArgScan().
 *     longOpts     A pointer to a string listing the valid long options. A GNU-style long option begins with
 *                  two hyphens and is followed by two or more characters, e.g., --help. The format of the list
 *                  of long options is "opt;opt;opt;...;opt;" where each long option, including the last, is
 *                  terminated with a semicolon. If an option has a required argument, the option string is
 *                  followed by a colon, e.g., "fliph;rotl:;rotr:;smaller" specifies that valid long options are
 *                  --fliph, --rotl arg, --rotr arg, and --smaller.
 *     opt          If ArgScan() finds a valid option, whether short or long, this member is a pointer to the
 *                  option string in pScan->argv[].
 *     shortOpts    A pointer to a string listing the valid short options. The format is the same as in longOpts
 *                  except terminating semicolons are omitted. For example, "ho:v" specifies the valid short
 *                  options are -h, -o arg, and -v.
 *
 * Before returning from ArgScan(), index is set to the index of the next option to be examined on the next
 * call. When the entire command line has been scanned, on the last call to ArgScan(), it will return cArgEnd.
 *
 * The return values are,
 *
 * cArg              An optionless argument was scanned. pScan->arg is a pointer to the argument string in
 *                   pScan->argv[].
 * cArgEnd           The end of the command line has been successfully reached.
 * cArgInvOpt        An invalid short or long option was encountered. pScan->error will contain an error
 *                   message indicating what the invalid option is.
 * cArgLongOpt       A valid long option was scanned. pScan->opt will be a point to the option string in
 *                   pScan->argv[]. If the option has an argument, pScan->arg will point to the string in
 *                   pScan->argv[].
 * cArgMissingArg    A valid option requiring an argument was scanned, but the requisite argument was omitted.
 *                   pScan->error will contain an error message.
 * cArgShortOpt      A valid short option was scanned. pScan->opt will be a point to the option string in
 *                   pScan->argv[]. If the option has an argument, pScan->arg will point to the string in
 *                   pScan->argv[].
 * cArgUnexpStr      An unexpected string was encountered on the command line. pScan->error will contain an
 *                   error message indicating what the unexpected string is.
 *------------------------------------------------------------------------------------------------------------*/
int ArgScan(tArgScan *pScan);

#endif
