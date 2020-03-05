%{
#include <stdio.h>
void yyerror(const char * msg) {
 printf("");
}
%} 
%token tFOR tIN tIF tSEMICOLON tLPAR tLBRKT tLBRACE tLT tSTAR tPLUS tCOLON tINT 
tREAL tSTRING tWHILE tVAR tELSE tCOMMA tRPAR tRBRKT tRBRACE tGT tEQ tMINUS tNOT 
tIDENT tFUNCTION tEQCHECK
%start prog
%left tLT tGT tEQCHECK tNOT
%left tPLUS tMINUS
%left tSTAR
%%

prog		:	statementList
;
statementList	:	statementList statement
		|	statementList tSEMICOLON statement
		|	statement
;
statement	:	assign | if | expr | statBlock | while | for
		| 	funcCall | funcDeclare
;
assign		:	tIDENT tEQ expr
		|	tVAR tIDENT tEQ expr
;
if		:	ifPart elsePart
;
ifPart		:	tIF tLPAR expr tRPAR statBlock
;
elsePart 	:	tELSE statBlock
;
while		:	tWHILE tLPAR expr tRPAR statBlock
;
for		:	tFOR tLPAR tIDENT tIN expr tRPAR statBlock
		|	tFOR tLPAR tVAR tIDENT tIN expr tRPAR statBlock
;
funcDeclare	:	tFUNCTION tIDENT tLPAR exprList tRPAR statBlock
		|	tFUNCTION tIDENT tLPAR tRPAR statBlock
;
statBlock	:	tLBRACE statementList tRBRACE
;
funcCall	:	tIDENT tLPAR exprList tRPAR
		|	tIDENT tLPAR tRPAR
;
expr		:	tIDENT | tREAL | tINT | tSTRING | tLBRKT tRBRKT 
		|	tLBRKT exprList tRBRKT | tLBRACE tRBRACE 
		| 	tLBRACE propertyList tRBRACE | tNOT expr | expr tPLUS expr
		|	expr tMINUS expr | expr tSTAR expr | expr tLT expr 
		|	expr tGT expr | expr tEQCHECK expr
;
exprList	:	expr | exprList tCOMMA expr
;
propertyList	:	tIDENT tCOLON expr | propertyList tCOMMA tIDENT tCOLON expr 
;
%% 

int main () {

  if(yyparse()) {
    printf("ERROR \n");
  }

  else {
    printf("OK \n");
  }
}
