#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* funcNames[20];
int size = 0;

/*
int inscope = 0;
void entering(){
	inscope = 0;
}

void quitting(){
	int a = 0;
	while(a < inscope){
		funcNames[size-1] = "";
		size--;
		a++;		
	}
} 
*/

char * identChanger(char * ident){
	char * s1 = "*"; 
	char * s3 = malloc(strlen(s1) + strlen(ident) + 1);
        strcpy(s3, s1);
        strcat(s3, ident);
	return s3;
}

char * resultprint(char * s1, char * s2, char sign){

	if(s1[0] == '*' && s2[0] == '*') return "";
	else if(s1[0] == '*' && s2[0] != '*') return s2;
	else if(s1[0] != '*' && s2[0] == '*') return s1;

	char * res = malloc(256);
	int val1 = atoi(s1);
	int val2 = atoi(s2);
	
	float fval1 = atof(s1);
        float fval2 = atof(s2);
        if((fval1 != 0.0 || fval2 != 0.0) && fval1 != val1 && fval2 != val2){
                float val3;
                if(sign == '+'){
                        val3 = fval1 +fval2;
                }
                else if(sign == '-'){
                        val3 = fval1 - fval2;
                }
                else if(sign == '*'){
                        val3 = fval1 * fval2;
                }
                printf("%s %c %s => %f \n", s1, sign,  s2, val3);
                sprintf(res, "%f", val3);
                fval1 = 0.0;
                fval2 = 0.0;
                return res;
        }


	if( 0  != val1 && 0 != val2){
		int val3 = 0;
		if(sign == '+'){
			val3 = val1 + val2;
		}
		else if(sign == '-'){
			val3 = val1 - val2;
		}
		else if(sign == '*'){
			val3 = val1 * val2;
		}
		printf("%s %c %s => %d \n", s1, sign,  s2, val3);
		sprintf(res, "%d", val3);
		val1 = 0;
		val2 = 0;
		return res;
	}

	if(val1 == 0 && val2 == 0 && fval1 == 0.0 && fval2 == 0.0){
		char * s3 = malloc(strlen(s1) + strlen(s2) + 1);
		strcpy(s3, s1);
		strcat(s3, s2);
		printf("%s + %s => %s \n", s1, s2, s3);
		return s3;
	}
}

void Definition(char * funcName, int process){
	
	int there = 0;
	if(process == 1){
		int loc = 0;
		funcNames[size] = funcName;
		size++;
		//inscope++;	
	}
	else{
		int i;
		for(i = 0; i < size; i++){
			char * str = funcNames[i];
			there = (strcmp(str, funcName) != 0) ? 1:there;
		}
		if(there == 0){
			printf("ERROR: The function (%s) is not declared before \n", 
									funcName);
		}
	}
}





