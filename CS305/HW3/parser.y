%{

#define YYDEBUG 1
#ifndef YYSTYPE
#define YYSTYPE char*
#endif
#include <stdio.h>
void yyerror(const char * msg){
	printf("%s\n",msg);
}
char* resultprint(char*,char*,char);
void Definition(char*, int);
char* identChanger(char*);
%} 
%token tFOR tIN tSEMICOLON tLPAR tLBRKT tLT tSTAR tPLUS tPERCENT tINT tREAL tSTRING tWHILE tVAR tCOMMA tRPAR tRBRKT tRBRACE tGT tEQ tMINUS tNOT tIDENT tIF tCOLON tLBRACE tELSE tEQCHECK tFUNCTION 
%left tMINUS tPLUS 
%left tSTAR 
%left tPERCENT 
%left tLT tGT tEQCHECK 
%left tNOT 
%% 

prog		: statementList 
; 

statementList	: statementList statement
             	| statementList tSEMICOLON
		| 
; 

statement	: assign 
		| if 
		| expr 
		| while 
		| for 
		| functionCall 
		| functionDeclaration
; 

assign		: tIDENT tEQ expr
      		| tVAR tIDENT tEQ expr
; 

if		: ifPart elsePart 
; 

ifPart		: tIF tLPAR expr tRPAR statementBlock 
; 

elsePart	: tELSE statementBlock
        	| 
; 

while		: tWHILE tLPAR expr tRPAR statementBlock 
; 

for		: tFOR tLPAR tIDENT tIN expr tRPAR statementBlock
   		| tFOR tLPAR tVAR tIDENT tIN expr tRPAR statementBlock
; 

functionDeclaration	: tFUNCTION tIDENT tLPAR exprList tRPAR statementBlock {Definition($2, 1);}
                   	| tFUNCTION tIDENT tLPAR tRPAR statementBlock {Definition($2, 1);}
; 

statementBlock	: tLBRACE statementList tRBRACE  
; 

functionCall	: tIDENT tLPAR exprList tRPAR {Definition($1, 0);}
            	| tIDENT tLPAR tRPAR {Definition($1, 0);}
; 

expr		: tIDENT	{$$ = identChanger($1);}
    		| tREAL 	{$$ = $1;}
    		| tINT		{$$ = $1;}
    		| tSTRING 	{$$ = $1;}
    		| tLBRKT tRBRKT 
		| tLBRKT exprList tRBRKT 
    		| tLBRACE tRBRACE 
		| tLBRACE propertyList tRBRACE 
		| tNOT expr 
    		| expr tPLUS expr 	{$$ = resultprint($1, $3, '+');}
    		| expr tMINUS expr 	{$$ = resultprint($1, $3, '-');}
    		| expr tSTAR expr 	{$$ = resultprint($1, $3, '*');}
    		| expr tEQCHECK expr 
		| expr tLT expr 
		| expr tGT expr
; 

exprList	: expr
        	| exprList tCOMMA expr
; 

propertyList	: tIDENT tCOLON expr
            	| propertyList tCOMMA tIDENT tCOLON expr
;
 
%% 

int main() {
	return yyparse();
}
