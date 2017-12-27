/*
 * DateValidation.c
 *
 *  Created on: 25 Dec. 2017
 *      Author: jiang
 */


#include "DateValidation.h"

#define FileName "time.txt"
#define LogFile "log.txt"
#define TimeFormat "%4d-%2d-%2d %2d:%2d:%2d"

FILE *fLog;
char logStr[200];

char logPath[200];
char inputPath[200];
double timeInSecond=7200.0;

void setLogPath(char* path){
	sprintf(logPath,"%s\\%s",path,LogFile);
}

void setInputPath(char* path){
	sprintf(inputPath,"%s\\%s",path,FileName);
}

void setTimer(double timer){
	timeInSecond = timer;
}

bool needToStop(){
	if(logPath[0]==0){
		sprintf(logPath,"%s",LogFile);
	}
	fLog = fopen(logPath, "a+"); // a+ (create + append) option will allow appending which is useful in a log file
	bool rtn = readDate();
	fclose(fLog);
	return rtn;
}

bool readDate(){
	bool newsInTwoHours = false;
	time_t now;
	time(&now);
	struct tm *gmt = gmtime(&now);
	time_t gmtNow = mktime(gmt);

	sprintf(logStr, "current GMT time is %4d-%2d-%2d %2d:%2d:%2d",gmt->tm_year + 1900,gmt->tm_mon+1,gmt->tm_mday,gmt->tm_hour,gmt->tm_min,gmt->tm_sec);
	fprintf(fLog, "%s\n",logStr);

	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    struct tm timeInFile;

    if(inputPath[0]==0){
    	sprintf(inputPath,"%s",FileName);
    }
    fp = fopen(inputPath, "r");
    if (fp == NULL){
    	sprintf(logStr, "open file : %s failed",inputPath);
    	fprintf(fLog, "%s\n",logStr);
        exit(-1);
    }

    int year,month,day,hour,min,sec;
    while ((read = getline(&line, &len, fp)) != -1) {
    	fprintf(fLog, "%s\n",line);

        if(sscanf(line, TimeFormat,&year,&month,&day,&hour,&min,&sec) !=6){
        	sprintf(logStr, "convert to time fails : %s. Format should be yyyy-mm-dd hh:MM:ss",line);
        	fprintf(fLog, "%s\n",logStr);
        	continue;
        }
        timeInFile.tm_year = year-1900;
        timeInFile.tm_mon = month -1;
        timeInFile.tm_mday = day;
        timeInFile.tm_hour = hour;
        timeInFile.tm_min = min;
        timeInFile.tm_sec = sec;

        time_t time_ = mktime(&timeInFile);
        double diff = difftime(time_,gmtNow);
        if(diff<=0) continue;
        if(diff>timeInSecond) break;
        newsInTwoHours = true;
        break;
    }

    fclose(fp);
    if (line)
        free(line);
    return newsInTwoHours;
}


