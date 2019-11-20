#pragma once
#include "pch.h"
#include "Error.h"
#define LEXEMA_FIXSIZE 1
#define LT_MAXSIZE 4096
#define LT_TI_NULLIDX 0xffffff
#define LEX_INT 'i'
#define LEX_STR 'i'
#define LEX_ID 'I'
#define LEX_LITERAL 'L'
#define LEX_DEF 'd'
#define LEX_RETURN 'r'
#define LEX_OUT 'o'
#define LEX_VAR 'v'
#define LEX_SEMICOLON ';'
#define LEX_COMMA ','
#define LEX_LEFTBRACE '{'
#define LEX_BRACELET '}'
#define LEX_LEFTHESIS '('
#define LEX_RIGHTHESIS ')'
#define LEX_PLUS '+'
#define LEX_MINUS '-'
#define LEX_STAR '*'
#define LEX_DIRSLASH '/'
#define LEX_REM ':'
#define LEX_EQUAL '='
#define LEX_MAIN 'M'
#define LEX_IF 'f'
#define LEX_ELIF 'e'
#define LEX_ELSE 's'
#define LEX_STARTBLOCK '['
#define LEX_ENDBLOCK ']'

#pragma once
namespace LT {
	struct Entry {
		char lexema;                                          //лексема
		int sn;                                               //номер строки в исходном тексте
		int idxTI;                                            //индекс в ТИ
		char vType = '`';                                     //тип
		int priority = -1;                                    //приоритет
	};
	struct LexTable
	{
		int maxsize;
		int size;
		Entry* table;
		unsigned char* LexemText;
	};

	LexTable* Create(int size);
	void Add(LexTable* lextable, Entry entry);
	Entry GetEntry(LexTable* lextable, int n);
	void Delete(LexTable* lextable);
}
