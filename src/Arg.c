/***************************************************************************************************************
 * FILE: Arg.c
 *
 * DESCRIPTION
 * See comments in Arg.h.
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
#include <stdbool.h>  // For bool, false, true
#include <stdio.h>    // For sprintf(), NULL
#include <string.h>   // For strchr(), strlen(), strstr()
#include "Arg.h"

//==============================================================================================================
// TYPE DEFINITIONS
//==============================================================================================================

typedef enum {
	tArgState_Arg,
	tArgState_End,
	tArgState_InvOpt,
	tArgState_LongOpt,
	tArgState_MissingArg,
	tArgState_OneHyphen,
	tArgState_ReqArg,
	tArgState_ShortOpt,
	tArgState_Start,
	tArgState_TwoHyphens,
	tArgState_UnexpStr,
	tArgState_ValidOpt
} tArgState;

//==============================================================================================================
// PUBLIC CONSTANT DEFINTIONS
//==============================================================================================================

// Note: These constants are declared in Arg.h.
const int cArg           = -1;
const int cArgEnd        = -2;
const int cArgInvOpt     = -3;
const int cArgLongOpt    = -4;
const int cArgMissingArg = -5;
const int cArgShortOpt   = -6;
const int cArgUnexpStr   = -7;

//==============================================================================================================
// FUNCTION DEFINITIONS
//==============================================================================================================

/*--------------------------------------------------------------------------------------------------------------
 * FUNCTION: ArgScan()
 *
 * DESCRIPTION
 * See comments in Arg.h.
 *
 * REMARKS
 * We scan the options and arguments on the command line using a finite state machine (FSM).
 *
 * Before starting the FSM, check to see if the entire command line has been scanned:
 *
 *     if (pScan->index >= pScan->argc) return cArgEnd;
 *
 * Otherwise, we define and initialize these variables:
 *
 * bool shortOpt = false;                  -- Set to true for a short option or false for a long option.
 * bool reqArg = false;                    -- Set to true when an option with a required arg is encountered.
 * tArgState nextState = tArgState_Start;  -- The state that the FSM will transition to.
 * tArgState state = tArgState_Start;      -- The current state of the FSM.
 * char *opt = pScan->argv[pScan->index];  -- Points to the first character of the string being scanned.
 * char *semicolon = NULL;                 -- Pointer to the semicolon following a long option in longOpts.
 * char *whichOpt = NULL;                  -- Pointer to the option string in shortOpts or longOpts.
 * size_t len = strlen(opt);               -- The length of the string being scanned.
 * int retVal = 0;                         -- The value to be returned by the function.
 *
 * States
 * ------
 * tArgState_Start:
 *     < Check: *opt == '-'
 *         -- String starts with "-", could be a short or long option.
 *         ++opt;
 *         nextState = tArgState_OneHyphen; >
 *     < Default:
 *         -- Any string not starting with "-" must be an argument.
 *         nextState = tArgState_Arg; >
 *
 * tArgState_Arg:
 *     < Default:
 *         -- Any string not starting with - is assumed to be an optionless argument.
 *         pScan = opt;
 *         retVal = cArg;
 *         nextState = tArgState_End; >
 *
 * tArgState_InvOpt:
 *     <Default:
 *         sprintf(pScan->error, "invalid option %s", pScan->argv[pScan->index]);
 *         retVal = cArgInvOpt;
 *         nextState = tArgState_End; >
 *
 * tArgState_LongOpt:
 *     -- On entry, opt is pointing to the first letter of the long option. whichOpt will be set to NULL if
 *     -- this is an invalid option, or, for a valid option, it will be pointing at the first letter of the
 *     -- option string in the pScan->longOpts string. Set reqArg to true or false depending on whether
 *     -- there is a ':' following the option string in longOpts.
 *     whichOpt = strstr(pScan->longOpts, opt);
 *     semicolon = whichOpt ? strchr(whichOpt, ';') : NULL;
 *     reqArg = semicolon ? *(semicolon - 1) == ':' : false;
 *     < Check: whichOpt != NULL
 *         nextState = tArgState_ValidOpt; >
 *     < Default:
 *         retVal = cArgInvOpt;
 *         nextState = tArgState_InvOpt; >
 *
 * tArgState_MissingArg:
 *     <Default:
 *         sprintf(pScan->error, "expecting argument following %s", pScan->opt);
 *         retVal = cArgMissingArg;
 *         nextState = tArgState_End; >
 *
 * tArgState_OneHyphen:
 *     < Check: *opt == '-'
 *         -- String starts with "--", could be a long option.
 *         ++opt;
 *         nextState = tArgState_TwoHyphens; >
 *     < Check: *opt == '\0' || len != 2
 *         -- We have either "-" or a hyphen followed by two or more characters. In both cases, we consider the
 *         -- string to be an unexpected string.
 *         nextState = tArgState_UnexpStr; >
 *     < Default:
 *         -- We have a hyphen followed by one character, so we will check to see if this is an expected short
 *         -- option.
 *         shortOpt = true;
 *         nextState = tArgState_ShortOpt; >
 *
 * tArgState_ReqArg:
 *     -- On entry, pScan->index has been incremented so pScan->argv[pScan->index] should be the required
 *     -- argument. We handle the case where the required argument is missing, e.g., $ binary -o -f, where -o
 *     -- should be followed by an argument.
 *     < Check: pScan->index >= pScan->argc
 *         nextState = tArgState_MissingArg; >
 *     < Check: *pScan->argv[pScan->index] == '-'
 *         nextState = tArgState_MissingArg; >
 *     < Default:
 *         -- Following the option, there is a string that does not start with a hyphen, so we will assume that it
 *         -- is an argument. Make pScan->arg point to it.
 *         pScan->arg = pScan->argv[pScan->index];
 *         retVal = shortOpt ? tArgState_ShortOpt : tArgState_LongOpt;
 *         nextState = tArgState_End; >
 *
 * tArgState_ShortOpt:
 *     -- On entry, opt is pointing to the letter of the short option. whichOpt will be set to NULL if this is
 *     -- an invalid option, or, for a valid option, it will be pointing at the option letter in the pScan->
 *     -- shortOpts string. Set reqArg to true or false depending on whether there is a ':' following the char-
 *     -- acter than whichOpt points to.
 *     whichOpt = strchr(pScan->shortOpts, *opt);
 *     reqArg = whichOpt ? *(whichOpt + 1) == ':' : false;
 *     < Check: whichOpt != NULL
 *         nextState = tArgState_ValidOpt; >
 *     < Default:
 *         retVal = cArgInvOpt;
 *         nextState = tArgState_InvOpt; >
 *
 * tArgState_TwoHyphens:
 *     < Check: *opt == '\0' || len < 4
 *         -- We have either "--" or "--" followed by only one character. In both cases, we consider the string to
 *         -- be an unexpected string.
 *         sprintf(pScan->error, "unexpected string %s", pScan->argv[pScan->index]);
 *         retVal = cArgUnexpStr;
 *         nextState = tArgState_End; >
 *     < Default:
 *         -- We have "--" followed by two or more characters, so we will check to see if this is an expected
 *         -- option.
 *         shortOpt = false;
 *         nextState = tArgState_LongOpt; >
 *
 * tArgState_UnexpStr:
 *     < Default:
 *         sprintf(pScan->error, "unexpected string %s", pScan->argv[pScan->index]);
 *         retVal = cArgUnexpStr;
 *         nextState = tArgState_End; >
 *
 * tArgState_ValidOpt:
 *     -- On entry, we know we have a valid option. reqArg is true if the option has a required argument and false
 *     -- otherwise.
 *     pScan->opt = pScan->argv[pScan->index];
 *     < Check: reqArg == true
 *         ++pScan->index;
 *         nextState = tArgState_ReqArg; >
 *     < Check: reqArg == false
 *         retVal = shortOpt ? tArgState_ShortOpt : tArgState_LongOpt;
 *         nextState = tArgState_End;
 *
 * tArgState_End:
 *     < Default:
 *         -- We have reached the end of the string or have an error. Increment pScan->index to the next
 *         -- element of pScan->argv and return.
 *         ++pScan->index;
 *         return retVal; >
 *------------------------------------------------------------------------------------------------------------*/
int ArgScan(tArgScan *pScan)
{
	if (pScan->index >= pScan->argc) return cArgEnd;

	bool shortOpt = false;                  // Set to true for a short option or false for a long option.
 	bool reqArg = false;                    // Set to true when an option with a required arg is encountered.
	tArgState nextState = tArgState_Start;  // The state that the FSM will transition to.
 	tArgState state = tArgState_Start;      // The current state of the FSM.
	char *opt = pScan->argv[pScan->index];  // Points to the first character of the string being scanned.
 	char *semicolon = NULL;                 // Pointer to the semicolon following a long option in longOpts.
 	char *whichOpt = NULL;                  // Pointer to the option string in shortOpts or longOpts.
	size_t len = strlen(opt);               // The length of the string being scanned.
	int retVal = 0;                         // The value to be returned by the function.

	while (state != tArgState_End) {
		switch (state) {
			case tArgState_Start:
				if (*opt == '-') {
					// String starts with "-", could be a short or long option.
					++opt;
					nextState = tArgState_OneHyphen;
				} else {
					// Any string not starting with "-" must be an argument.
					nextState = tArgState_Arg;
				}
				break;

 			case tArgState_Arg:
				// Any string not starting with "-" is assumed to be an optionless argument.
				pScan->arg = opt;
				retVal = cArg;
				nextState = tArgState_End;
				break;

 			case tArgState_InvOpt:
				sprintf(pScan->error, "invalid option %s", pScan->argv[pScan->index]);
				retVal = cArgInvOpt;
				nextState = tArgState_End;
				break;

			case tArgState_LongOpt:
				// On entry, opt is pointing to the first letter of the long option. whichOpt will be set to NULL if
				// this is an invalid option, or, for a valid option, it will be pointing at the first letter of the
				// option string in the pScan->longOpts string. Set reqArg to true or false depending on whether
				// there is a ':' following the option string in longOpts.
				whichOpt = strstr(pScan->longOpts, opt);
				semicolon = whichOpt ? strchr(whichOpt, ';') : NULL;
				reqArg = semicolon ? *(semicolon - 1) == ':' : false;
				if (whichOpt) {
					nextState = tArgState_ValidOpt;
				} else {
					retVal = cArgInvOpt;
					nextState = tArgState_InvOpt;
				}
				break;

 			case tArgState_MissingArg:
				sprintf(pScan->error, "expecting argument following %s", pScan->opt);
 				retVal = cArgMissingArg;
 				nextState = tArgState_End;
				break;

 			case tArgState_OneHyphen:
				if (*opt == '-') {
					// String starts with "--", could be a long option.
					++opt;
					nextState = tArgState_TwoHyphens;
				} else if (*opt == '\0' || len != 2) {
					// We have either "-" or a hyphen followed by two or more characters. In both cases, we
					// consider the string to be an unexpected string.
					nextState = tArgState_UnexpStr;
				} else {
					// We have a hyphen followed by one character, so we will check to see if this is an
					// expected short option.
					shortOpt = true;
					nextState = tArgState_ShortOpt;
				}
				break;

			case tArgState_ReqArg:
				// On entry, pScan->index has been incremented so pScan->argv[pScan->index] should be
				// the required argument. We handle the case where the required argument is missing, e.g.,
				// $ binary -o -f, where -o should be followed by an argument.
				if (pScan->index >= pScan->argc) {
					nextState = tArgState_MissingArg;
				} else if (*pScan->argv[pScan->index] == '-') {
					nextState = tArgState_MissingArg;
				} else {
					// Following the option, there is a string that does not start with a hyphen, so we will
					// assume that it is an argument. Make pScan->arg point to it.
					pScan->arg = pScan->argv[pScan->index];
					retVal = shortOpt ? tArgState_ShortOpt : tArgState_LongOpt;
					nextState = tArgState_End;
				}
				break;

			case tArgState_ShortOpt:
				// On entry, opt is pointing to the letter of the short option. whichOpt will be set to NULL
				// if this is an invalid option, or, for a valid option, it will be pointing at the option
				// letter in the pScan->shortOpts string. Set reqArg to true or false depending on whether
				// there is a ':' following the character than whichOpt points to.
				whichOpt = strchr(pScan->shortOpts, *opt);
				reqArg = whichOpt ? *(whichOpt + 1) == ':' : false;
				if (whichOpt) {
					nextState = tArgState_ValidOpt;
				} else {
					retVal = cArgInvOpt;
					nextState = tArgState_InvOpt;
				}
				break;

 			case tArgState_TwoHyphens:
				if (*opt == '\0' || len < 4) {
					// We have either "--" or "--" followed by only one character. In both cases, we consider
					// the string to be an unexpected string.
 					sprintf(pScan->error, "unexpected string %s", pScan->argv[pScan->index]);
					retVal = cArgUnexpStr;
					nextState = tArgState_End;
				} else {
					// We have "--" followed by two or more characters, so we will check to see if this is an
					// expected option.
					shortOpt = false;
					nextState = tArgState_LongOpt;
				}
				break;

 			case tArgState_UnexpStr:
				sprintf(pScan->error, "unexpected string %s", pScan->argv[pScan->index]);
				retVal = cArgUnexpStr;
				nextState = tArgState_End;
				break;

 			case tArgState_ValidOpt:
				// On entry, we know we have a valid option. reqArg is true if the option has a required arg-
				// ument and false otherwise.
				pScan->opt = pScan->argv[pScan->index];
				if (reqArg) {
					++pScan->index;
					nextState = tArgState_ReqArg;
				} else {
					retVal = shortOpt ? tArgState_ShortOpt : tArgState_LongOpt;
					nextState = tArgState_End;
				}
				break;

			case tArgState_End:
				break;
		}
		state = nextState;
	}

	// tArgState_End:
	// We have reached the end of the string or have an error. Increment pScan->index to the next element of
	// pScan->argv and return.
	++pScan->index;
 	return retVal;
}
