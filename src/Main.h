/***************************************************************************************************************
 * FILE: Main.h
 *
 * DESCRIPTION
 * Global declarations.
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
#ifndef MAIN_H
#define MAIN_H
#include <stdbool.h>

 typedef struct {
	int		argc;			// argc from main()
	char  **argv;			// argv from main()
	bool	fliph;			// --fliph was specified
	bool	flipv;			// --flipv
	bool	h;				// -h, --help
	char   *inFile;			// The file name of the input BMP image
	bool	o;				// -o file, --output file
	char   *outFile;		// The output file name following -o or --output
	int		rotArg;			// The argument n following --rotr
	bool	rotr;			// --rotr n
	bool	v;				// -v, --version
} tCmdLine;

//==============================================================================================================
// CONSTANT DECLARATIONS
//==============================================================================================================

extern const char *cBinary;
extern const char *cVersion;
extern const char *cVersion;

#endif
