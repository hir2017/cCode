/*
 ============================================================================
 Name        : DllTest.c
 Author      : Tester
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "DateValidation.h"

int main(void) {
	bool toStop = needToStop();
	printf("!!!Hello World!!!----%d\n",toStop); /* prints !!!Hello World!!! */


	setLogPath("C:\\test\\log");
	setInputPath("C:\\test\\timer");
	setTimer(3600.0);
	toStop = needToStop();
	printf("!!!Hello World!!!----%d\n",toStop); /* prints !!!Hello World!!! */

	return 1;
}
