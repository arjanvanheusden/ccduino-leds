/*
 * shell.h
 *
 *  Created on: Dec 10, 2014
 *      Author: arjan
 */

#ifndef MODULES_SHELL_H_
#define MODULES_SHELL_H_

typedef struct tdShellInput{
	char ** inputStringArray;
	char inpNr;
} tdShellInput;


tdShellInput * getInputFromShell(void);

void shell_process(char * str);

#endif /* MODULES_SHELL_H_ */
