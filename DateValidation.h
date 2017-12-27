/*
 * DateValidation.h
 *
 *  Created on: 25 Dec. 2017
 *      Author: jiang
 */

#ifndef DATEVALIDATION_H_
#define DATEVALIDATION_H_

#include <time.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

bool needToStop();
bool readDate();
void setLogPath(char* path);
void setInputPath(char* path);
void setTimer(double timer);
#endif /* DATEVALIDATION_H_ */
