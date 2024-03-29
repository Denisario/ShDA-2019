#include "pch.h"
#include "FST.h"
#include "LT.h"
#include "IT.h"
#include "In.h"
#include "Lexer.h"
#include "Error.h"
#include <string>
using namespace fst;
using namespace std;
using namespace LT;
namespace  Lexer {
	int counterLiteral = 0;
	int counterTokenInProgram = 0;
	int haveMain = 0;
	int counterID = 0;
	bool haveIF = false;
	stack <IT::Entry> stackCall;
	char* stringToChar(string str) {
		char* massChar = new char[255];
		for (int i = 0; i < str.length(); i++) {
			if (str[i] == '\\'&&str[i+1]=='"') continue;
			massChar[i] = str[i];			
		}
		massChar[str.length()] = '\0';
		return massChar;
	}
	Entry createStructLexem(char type, int number, int numberInTableId, char vType = '$', int priority = -1) {
		Entry newLexem;
		newLexem.lexema = type;
		newLexem.sn = number;
		newLexem.idxTI = numberInTableId;
		newLexem.vType = vType;
		newLexem.priority = priority;
		return newLexem;

	}
	IT::Entry createStructId(char* id, int line, int*typeData, int*typeID, int*littype, char lexema[TI_STR_MAXSIZE] = NULL, IT::Entry* view = NULL) {
		IT::Entry newItEntry;
		int counterSymbol = 0;
		for (int i = 0; i < strlen(id); i++)
		{
			newItEntry.id[i] = id[i];
			counterSymbol++;
		}
		newItEntry.id[counterSymbol] = '\0';
		if (typeData) newItEntry.iddatatype = (IT::IDDATATYPE)*typeData;
		if (typeID) newItEntry.idtype = (IT::IDTYPE)*typeID;
		if (littype) newItEntry.littype = (IT::LITERALTYPE)*littype;
		newItEntry.idxfirstLE = line;
		newItEntry.view = view;
		if ((int)newItEntry.idtype != 4) {
			if ((int)newItEntry.iddatatype == 1)
			{
				newItEntry.value.vint = TI_INT_DEFAULT;
			}
			else
			{
				newItEntry.value.vstr->len = 0;
				newItEntry.value.vstr->str[0] = TI_STR_DEFAULT;
				newItEntry.value.vstr->str[1] = '\0';
			}
		}
		else
		{
			if (((int)newItEntry.iddatatype == 1) && ((int)newItEntry.littype == 1))
			{
				newItEntry.value.vint = atoi(lexema);
			}
			else if ((int)newItEntry.littype == 3) {
				string sVal = lexema;
				string result = sVal.substr(1, strlen(lexema) - 1);

				newItEntry.value.vint = atoi(stringToChar(result));
			}
			else
			{
				newItEntry.value.vstr->len = strlen(lexema);
				strcpy_s(newItEntry.value.vstr->str, lexema);
			}
		}
		return newItEntry;
	}

	void initTypeLexem(const char* text, string tmp, LexTable* tableOfLexem, int numberOfstring, int poz, IT::IdTable* newIdTable, int*typeData, int*typeID, int*littype)
	{

		FST fstInt(text, 4,
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('n', 2)),
			NODE(1, RELATION('t', 3)),
			NODE());
		FST fstStr(text, 4,
			NODE(1, RELATION('s', 1)),
			NODE(1, RELATION('t', 2)),
			NODE(1, RELATION('r', 3)),
			NODE());
		FST fstDef(text, 4,
			NODE(1, RELATION('d', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('f', 3)),
			NODE()
		);
		FST fstReturn(text, 7,
			NODE(1, RELATION('r', 1)),
			NODE(1, RELATION('e', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('u', 4)),
			NODE(1, RELATION('r', 5)),
			NODE(1, RELATION('n', 6)),
			NODE()
		);
		FST fstOut(text, 4,
			NODE(1, RELATION('o', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('t', 3)),
			NODE()
		);
		FST fstOutn(text, 5,
			NODE(1, RELATION('o', 1)),
			NODE(1, RELATION('u', 2)),
			NODE(1, RELATION('t', 3)),
			NODE(1, RELATION('n', 4)),
			NODE()
		);
		FST fstMain(text, 5,
			NODE(1, RELATION('M', 1)),
			NODE(1, RELATION('a', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('n', 4)),
			NODE()
		);
		FST fstCheckLines(text, 11,
			NODE(1, RELATION('c', 1)),
			NODE(1, RELATION('h', 2)),
			NODE(1, RELATION('e', 3)),
			NODE(1, RELATION('c', 4)),
			NODE(1, RELATION('k', 5)),
			NODE(1, RELATION('L', 6)),
			NODE(1, RELATION('i', 7)),
			NODE(1, RELATION('n', 8)),
			NODE(1, RELATION('e', 9)),
			NODE(1, RELATION('s', 10)),
			NODE()
		);
		FST fstIsGreather(text, 11,
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('s', 2)),
			NODE(1, RELATION('G', 3)),
			NODE(1, RELATION('r', 4)),
			NODE(1, RELATION('e', 5)),
			NODE(1, RELATION('a', 6)),
			NODE(1, RELATION('t', 7)),
			NODE(1, RELATION('h', 8)),
			NODE(1, RELATION('e', 9)),
			NODE(1, RELATION('r', 10)),
			NODE()
		);
		FST fstSemicolon(text, 2,
			NODE(1, RELATION(';', 1)),
			NODE()
		);
		FST fstComma(text, 2,
			NODE(1, RELATION(',', 1)),
			NODE()
		);
		FST fstLeftbrace(text, 2,
			NODE(1, RELATION('{', 1)),
			NODE()
		);
		FST fstBracelet(text, 2,
			NODE(1, RELATION('}', 1)),
			NODE()
		);
		FST fstLefthesis(text, 2,
			NODE(1, RELATION('(', 1)),
			NODE()
		);
		FST fstRighthesis(text, 2,
			NODE(1, RELATION(')', 1)),
			NODE()
		);
		FST fstPlus(text, 2,
			NODE(1, RELATION('+', 1)),
			NODE()
		);
		FST fstMinus(text, 2,
			NODE(1, RELATION('-', 1)),
			NODE()
		);
		FST fstStar(text, 2,
			NODE(1, RELATION('*', 1)),
			NODE()
		);
		FST fstDirslash(text, 2,
			NODE(1, RELATION('/', 1)),
			NODE()
		);

		FST fstStartBlock(text, 2,
			NODE(1, RELATION('[', 1)),
			NODE()
		);

		FST fstEndBlock(text, 2,
			NODE(1, RELATION(']', 1)),
			NODE()
		);

		FST fstIf(text, 3,
			NODE(1, RELATION('i', 1)),
			NODE(1, RELATION('f', 2)),
			NODE()
		);

		FST fstElif(text, 5,
			NODE(1, RELATION('e', 1)),
			NODE(1, RELATION('l', 2)),
			NODE(1, RELATION('i', 3)),
			NODE(1, RELATION('f', 4)),
			NODE()
		);

		FST fstElse(text, 5,
			NODE(1, RELATION('e', 1)),
			NODE(1, RELATION('l', 2)),
			NODE(1, RELATION('s', 3)),
			NODE(1, RELATION('e', 4)),
			NODE()
		);

		FST fstRem(text, 2,
			NODE(1, RELATION(':', 1)),
			NODE()
		);

		FST fstVar(text, 4,
			NODE(1, RELATION('v', 1)),
			NODE(1, RELATION('a', 2)),
			NODE(1, RELATION('r', 3)),
			NODE()
		);

		FST fstOctalLiteral(text, 3,
			NODE(1, RELATION('0', 1)),
			NODE(15, RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1), RELATION('6', 1), RELATION('7', 1),
				RELATION('0', 2), RELATION('1', 2), RELATION('2', 2), RELATION('3', 2), RELATION('4', 2), RELATION('5', 2), RELATION('6', 2), RELATION('7', 2)),
			NODE()
		);

		FST fstLiteralOfInteger(text, 2,
			NODE(19, RELATION('1', 0), RELATION('2', 0), RELATION('3', 0), RELATION('4', 0), RELATION('5', 0), RELATION('6', 0),
				RELATION('7', 0), RELATION('8', 0), RELATION('9', 0),
				RELATION('0', 1), RELATION('1', 1), RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1), RELATION('6', 1),
				RELATION('7', 1), RELATION('8', 1), RELATION('9', 1)),
			NODE()
		);
		FST fstId(text, 2,
			NODE(62, RELATION('a', 0), RELATION('b', 0), RELATION('c', 0), RELATION('d', 0), RELATION('e', 0),
				RELATION('f', 0), RELATION('g', 0), RELATION('h', 0), RELATION('i', 0), RELATION('j', 0), RELATION('k', 0),
				RELATION('l', 0), RELATION('m', 0), RELATION('n', 0), RELATION('o', 0), RELATION('p', 0), RELATION('q', 0),
				RELATION('r', 0), RELATION('s', 0), RELATION('t', 0), RELATION('u', 0), RELATION('v', 0), RELATION('w', 0),
				RELATION('x', 0), RELATION('y', 0), RELATION('z', 0),
				RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1), RELATION('e', 1),
				RELATION('f', 1), RELATION('g', 1), RELATION('h', 1), RELATION('i', 1), RELATION('j', 1), RELATION('k', 1),
				RELATION('l', 1), RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1), RELATION('q', 1),
				RELATION('r', 1), RELATION('s', 1), RELATION('t', 1), RELATION('u', 1), RELATION('v', 1), RELATION('w', 1),
				RELATION('x', 1), RELATION('y', 1), RELATION('z', 1), RELATION('0', 1), RELATION('1', 1), RELATION('2', 1),
				RELATION('3', 1), RELATION('4', 1), RELATION('5', 1), RELATION('6', 1), RELATION('7', 1), RELATION('8', 1),
				RELATION('9', 1)),
			NODE()
		);
		FST fstEqual(text, 2,
			NODE(1, RELATION('=', 1)),
			NODE()
		);		

		FST fstGreater(text, 2,
			NODE(1, RELATION('>', 1)),
			NODE()
		);
		FST fstLesser(text, 2,
			NODE(1, RELATION('<', 1)),
			NODE()
		);		

		FST fstLiteralOfString(text, 3,
			NODE(1, RELATION('\"', 1)),
			NODE(84,
				RELATION('\"', 2),
				RELATION('a', 1), RELATION('b', 1), RELATION('c', 1), RELATION('d', 1),
				RELATION('e', 1), RELATION('f', 1), RELATION('g', 1), RELATION('h', 1),
				RELATION('i', 1), RELATION('j', 1),	RELATION('k', 1), RELATION('l', 1),
				RELATION('m', 1), RELATION('n', 1), RELATION('o', 1), RELATION('p', 1),
				RELATION('q', 1), RELATION('r', 1), RELATION('s', 1), RELATION('t', 1),
				RELATION('u', 1), RELATION('v', 1), RELATION('w', 1), RELATION('x', 1),
				RELATION('y', 1), RELATION('z', 1),
				RELATION('0', 1), RELATION('1', 1),
				RELATION('2', 1), RELATION('3', 1), RELATION('4', 1), RELATION('5', 1),
				RELATION('6', 1), RELATION('7', 1), RELATION('8', 1), RELATION('9', 1),
				RELATION('A', 1), RELATION('B', 1), RELATION('C', 1), RELATION('D', 1),
				RELATION('E', 1), RELATION('F', 1), RELATION('G', 1), RELATION('H', 1),
				RELATION('I', 1), RELATION('J', 1),	RELATION('K', 1), RELATION('L', 1),
				RELATION('M', 1), RELATION('N', 1), RELATION('O', 1), RELATION('P', 1),
				RELATION('R', 1), RELATION('S', 1), RELATION('T', 1), RELATION('U', 1),
				RELATION('V', 1), RELATION('W', 1), RELATION('X', 1), RELATION('Y', 1),
				RELATION('Z', 1), RELATION(' ', 1),	RELATION('_', 1), RELATION('.', 1),
				RELATION(':', 1), RELATION(';', 1),	RELATION('!', 1), RELATION('?', 1),
				RELATION('+', 1), RELATION('-', 1),	RELATION('*', 1), RELATION('/', 1),
				RELATION('=', 1), RELATION('>', 1),	RELATION('<', 1), RELATION('@', 1),
				RELATION('(', 1), RELATION(')', 1),	RELATION('[', 1), RELATION(']', 1),
				RELATION('|', 1), RELATION('=', 1), RELATION(',', 1)
			),
			NODE()
		);
		if (execute(fstInt)) {
			Add(tableOfLexem, createStructLexem(LEX_INT, numberOfstring, LT_TI_NULLIDX));
			*typeData = 1;
			return;
		}
		if (execute(fstStr)) {
			Add(tableOfLexem, createStructLexem(LEX_STR, numberOfstring, LT_TI_NULLIDX));
			*typeData = 2;
			return;
		}
		if (execute(fstDef)) {
			Add(tableOfLexem, createStructLexem(LEX_DEF, numberOfstring, LT_TI_NULLIDX));
			*typeID = 2;
			return;
		}

		if (execute(fstVar)) {
			Add(tableOfLexem, createStructLexem(LEX_VAR, numberOfstring, LT_TI_NULLIDX));
			*typeID = 1;
			return;
		}
		if (execute(fstReturn)) {
			Add(tableOfLexem, createStructLexem(LEX_RETURN, numberOfstring, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstOut)) {
			Add(tableOfLexem, createStructLexem(LEX_OUT, numberOfstring, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstCheckLines)) {
			Add(tableOfLexem, createStructLexem(LEX_CHECK, numberOfstring, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstIsGreather)) {
			Add(tableOfLexem, createStructLexem(LEX_GREATHER, numberOfstring, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstOutn)) {
			Add(tableOfLexem, createStructLexem(LEX_OUTN, numberOfstring, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstMain)) {
			Add(tableOfLexem, createStructLexem(LEX_MAIN, numberOfstring, LT_TI_NULLIDX));
			haveMain = true;
			char  gl[6] = "Main";
			stackCall.push(createStructId(gl, -1, NULL, NULL, NULL, gl, NULL));
			return;
		}
		if (execute(fstSemicolon)) {
			Add(tableOfLexem, createStructLexem(LEX_SEMICOLON, numberOfstring, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstComma)) {
			Add(tableOfLexem, createStructLexem(LEX_COMMA, numberOfstring, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstLeftbrace)) {
			Add(tableOfLexem, createStructLexem(LEX_LEFTBRACE, numberOfstring, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstBracelet)) {
			Add(tableOfLexem, createStructLexem(LEX_BRACELET, numberOfstring, LT_TI_NULLIDX));
			stackCall.pop();
			return;
		}
		if (execute(fstLefthesis)) {
			Add(tableOfLexem, createStructLexem(LEX_LEFTHESIS, numberOfstring, LT_TI_NULLIDX, '(', 1));
			if (*(typeID) == 2) *typeID = 3;
			return;
		}
		if (execute(fstRighthesis)) {
			Add(tableOfLexem, createStructLexem(LEX_RIGHTHESIS, numberOfstring, LT_TI_NULLIDX, ')', 1));
			if (*typeID == 3) *typeID = -1;
			return;
		}
		if (execute(fstPlus)) {
			Add(tableOfLexem, createStructLexem(LEX_PLUS, numberOfstring, LT_TI_NULLIDX, '+', 2));
			return;
		}
		if (execute(fstMinus)) {
			Add(tableOfLexem, createStructLexem(LEX_MINUS, numberOfstring, LT_TI_NULLIDX, '-', 2));
			return;
		}
		if (execute(fstStar)) {
			Add(tableOfLexem, createStructLexem(LEX_STAR, numberOfstring, LT_TI_NULLIDX, '*', 3));
			return;
		}
		if (execute(fstEqual)) {
			Add(tableOfLexem, createStructLexem(LEX_EQUAL, numberOfstring, LT_TI_NULLIDX, '='));
			return;
		}	
		if (execute(fstGreater)) {
			Add(tableOfLexem, createStructLexem(LEX_GREATER, numberOfstring, LT_TI_NULLIDX, '>', 2));
			return;
		}
		if (execute(fstLesser)) {
			Add(tableOfLexem, createStructLexem(LEX_LESS, numberOfstring, LT_TI_NULLIDX, '<', 2));
			return;
		}
		if (execute(fstDirslash)) {
			Add(tableOfLexem, createStructLexem(LEX_DIRSLASH, numberOfstring, LT_TI_NULLIDX, '/', 3));
			return;
		}
		if (execute(fstStartBlock)) {
			Add(tableOfLexem, createStructLexem(LEX_STARTBLOCK, numberOfstring, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstEndBlock)) {
			Add(tableOfLexem, createStructLexem(LEX_ENDBLOCK, numberOfstring, LT_TI_NULLIDX));
			return;
		}
		if (execute(fstIf)) {
			Add(tableOfLexem, createStructLexem(LEX_IF, numberOfstring, LT_TI_NULLIDX));
			haveIF = true;
			return;
		}
		if (execute(fstElif)) {
			Add(tableOfLexem, createStructLexem(LEX_ELIF, numberOfstring, LT_TI_NULLIDX));
			haveIF = false;
			return;
		}
		if (execute(fstElse)) {
			Add(tableOfLexem, createStructLexem(LEX_ELSE, numberOfstring, LT_TI_NULLIDX));
			return;
		}

		if (execute(fstRem)) {
			Add(tableOfLexem, createStructLexem(LEX_REM, numberOfstring, LT_TI_NULLIDX, ':', 3));
			return;
		}	
		

		if (execute(fstLiteralOfInteger)) {
			int*t = new int;
			int*t2 = new int;
			int*t3 = new int;
			*t = 1;
			*t2 = 4;
			*t3 = 1;
			string numberLi = "lI";
			string num = to_string(counterLiteral++);
			/*_itoa_s(counterTokenInProgram, numberLi, 10);*/
			IT::Entry newEntry = createStructId(stringToChar(numberLi + num), tableOfLexem->size, t, t2, t3, (char*)text);

			IT::Add(newIdTable, newEntry);
			for (int i = 0; i < newIdTable->size; i++)
			{
				if (!strcmp(newEntry.id, newIdTable->table[i].id)) 	Add(tableOfLexem, createStructLexem(LEX_LITERAL, numberOfstring, counterID++));
			}
			counterTokenInProgram++;
			delete t;
			delete t2;
			delete t3;
			return;
		}
		if (execute(fstOctalLiteral)) {
			int*t = new int;
			int*t2 = new int;
			int*t3 = new int;
			*t = 1;
			*t2 = 4;
			*t3 = 3;
			string numberLi = "lo";
			string num = to_string(counterLiteral++);
			/*_itoa_s(counterTokenInProgram, numberLi, 10);*/
			IT::Entry newEntry;
			newEntry = createStructId(stringToChar(numberLi + num), tableOfLexem->size, t, t2, t3, (char*)text);
			newEntry.littype = (IT::LITERALTYPE)3;
			IT::Add(newIdTable, newEntry);
			for (int i = 0; i < newIdTable->size; i++)
			{
				if (!strcmp(newEntry.id, newIdTable->table[i].id)) 	Add(tableOfLexem, createStructLexem(LEX_LITERAL, numberOfstring, counterID++));
			}
			counterTokenInProgram++;
			delete t;
			delete t2;
			return;
		}
		if (execute(fstLiteralOfString)) {
			int size = strlen(text);
			if (size > 257) throw ERROR_THROW(204);
			int*t = new int;
			int*t2 = new int;
			int*t3 = new int;
			*t = 2;
			*t2 = 4;
			*t3 = 2;
			string numberLi = "lS";
			string num = to_string(counterLiteral++);

			/*_itoa_s(counterTokenInProgram, numberLi, 10);*/
			IT::Entry newEntry = createStructId(stringToChar(numberLi + num), tableOfLexem->size, t, t2, t3, (char*)text);
			newEntry.littype = (IT::LITERALTYPE)2;
			IT::Add(newIdTable, newEntry);
			for (int i = 0; i < newIdTable->size; i++)
			{
				if (!strcmp(newEntry.id, newIdTable->table[i].id)) 	Add(tableOfLexem, createStructLexem(LEX_LITERAL, numberOfstring, counterID++));
			}
			counterTokenInProgram++;
			delete t;
			delete t2;
			delete t3;
			return;
		}
		if (execute(fstId)) {
			string name;
			for (int j = 0; j < 5; j++) {
				name.push_back(text[j]);
				if (j == strlen(text - 1))break;
			}
			IT::Entry* view = new IT::Entry;
			*view = stackCall.top();
			int *type = new int;
			IT::Entry newEntry = createStructId(stringToChar(name), counterID++, typeData, typeID, littype, NULL, view);
			if ((*typeID == 2)) {
				stackCall.push(newEntry);
			}
			IT::Add(newIdTable, newEntry);

			bool idInTable = false;

			for (int i = 0; i < newIdTable->maxsize; i++)
			{
				if (!strcmp(newEntry.id, newIdTable->table[i].id) && (newEntry.view == newIdTable->table[i].view)) idInTable = true;
			}

			Add(tableOfLexem, createStructLexem(LEX_ID, numberOfstring, newIdTable->size - 1));
			return;
		}
		cout << text;
		throw ERROR_THROW_IN(200, numberOfstring, poz);

	}

	Tables createTables(In::IN newIN)
	{
		char global[6] = "globa";
		stackCall.push(createStructId(global, -1, NULL, NULL, NULL, NULL));
		cout << newIN.ucTextFormated;

		int* typeData = new int;
		int* typeID = new int;
		int* littype = new int;
		*littype = -1;
		*typeData = -1;
		*typeID = -1;
		unsigned char* input = newIN.ucTextFormated;

		string currentString;
		int indOfFirstSpace = 0;
		bool isFirstSpaceDetected = false;
		int numberSymbol = -1;
		bool scope = false;
		LexTable* newTable = Create(newIN.counterLexem);
		IT::IdTable* newIdTable = IT::Create(newIN.counterLexem);
		ListId* newListId = new ListId;
		ListId* pHeadListId = NULL;
		int numberOfString = 0;
		int counterLexem = 0;
		for (int i = 0; i < strlen((char*)input); i++) {
			if (input[i] != '\n')
			{
				numberSymbol++;
				currentString = currentString + (char)input[i];
				if (!isFirstSpaceDetected) if (input[i] == ' ') {
					indOfFirstSpace = numberSymbol;
					isFirstSpaceDetected = true;
				}
			}
			else
			{
				numberOfString++;
				string currentLexem;
				for (int j = indOfFirstSpace + 1; j < currentString.length(); j++)
				{
					if (currentString[j] == '\"') {
						if (!scope)	scope = true;
						else scope = false;
					}
					if ((currentString[j] != ' ')) currentLexem = currentLexem + currentString[j];
					else {
						if (scope) currentLexem = currentLexem + currentString[j];
						else {
							initTypeLexem(stringToChar(currentLexem), currentString, newTable, numberOfString, (j - indOfFirstSpace - currentLexem.length()), newIdTable, typeData, typeID, littype);
							counterLexem++;
							currentLexem.clear();
						}

					}


				}

				currentString.clear();
				indOfFirstSpace = 0;
				isFirstSpaceDetected = false;
				numberSymbol = -1;

			}
		}
		newTable->LexemText = new unsigned char[counterLexem * 3 + 10];
		unsigned char* LexemText = newTable->LexemText;
		numberOfString = newTable->table->sn;
		int currentNumberString = 1;
		*LexemText = '0';
		LexemText++;
		*LexemText = '1';
		LexemText++;
		*LexemText = ' ';
		LexemText++;
		for (int i = 0; i < newTable->size; i++)
		{
			if (currentNumberString == newTable->table[i].sn)
			{
				*LexemText = newTable->table[i].lexema;
				LexemText++;

			}
			else
			{
				currentNumberString = newTable->table[i].sn;
				*LexemText = '\n';
				LexemText++;
				if (currentNumberString < 10)
				{
					*LexemText = '0';
					LexemText++;
					char str[2];
					_itoa_s(currentNumberString, str, 10);
					*LexemText = str[0];
					LexemText++;
					*LexemText = ' ';
					LexemText++;

				}
				else {
					char str[100];
					_itoa_s(currentNumberString, str, 10);
					for (int j = 0; j < strlen(str); j++)
					{
						*LexemText = str[j];
						LexemText++;

					}
					*LexemText = ' ';
					LexemText++;
				}
				*LexemText = newTable->table[i].lexema;
				LexemText++;

			}
		}
		*LexemText = '\0';
		Tables newTables;
		newTables.IDTABLE = newIdTable;
		newTables.LEXTABLE = newTable;
		LexemText = newTables.LEXTABLE->LexemText;


		/*if (haveMain != 1) throw ERROR_THROW(8);*/
		return newTables;
	}

	void Print(Tables tables)
	{
		const char* temp;
		std::ofstream fout("Lex.txt");
		std::ofstream lt("LT.txt");
		std::ofstream it("IT.txt");
		fout << tables.LEXTABLE->LexemText << endl << endl;
		lt << setw(3) << "�" << setw(10) << "�������" << setw(15) << "����� ������" << setw(10) << "IDxTi" << endl;

		lt << "---------------------------------------" << endl;
		lt << "---------------------------------------" << endl;
		for (int i = 0; i < tables.LEXTABLE->size; i++)
		{
			lt << setw(3) << i << setw(10) << tables.LEXTABLE->table[i].lexema << setw(15)
				<< tables.LEXTABLE->table[i].sn << setw(10) << tables.LEXTABLE->table[i].idxTI << endl;
			lt << "---------------------------------------" << endl;
		}
		for (int i = 0; i < tables.IDTABLE->size; i++)
		{
			temp = (const char*)tables.LEXTABLE->table[i].lexema;
			it << setw(3) << i << ". �������������: " << setw(6) << tables.IDTABLE->table[i].id << ". ���: " << setw(3) << tables.IDTABLE->table[i].idtype << ". ��������: " << "��� ���������� :" << tables.IDTABLE->table[i].iddatatype;
			if ((int)tables.IDTABLE->table[i].iddatatype == 1) it << setw(11) << tables.IDTABLE->table[i].value.vint;
			else it << setw(11) << tables.IDTABLE->table[i].value.vstr->str;
			if (tables.IDTABLE->table[i].view)it << ". ������� ���������: " << setw(6) << tables.IDTABLE->table[i].view->id;
			else it << "                           ";
			it << ". ����� ������� ���������: " << setw(2) << tables.IDTABLE->table[i].idxfirstLE << "  . ��� ��������: " << tables.IDTABLE->table[i].littype << endl;
		}

	}

	void CheckLTIT(Tables table) {
		int equals = 0;
		for (int i = 0; i < table.LEXTABLE->size; i++) {
			if (table.LEXTABLE->table[i].lexema == LEX_EQUAL) equals++;
		}


		int id = 0;
		int tmp;
		for (int i = 0; i < table.LEXTABLE->size; i++) {
			if (table.LEXTABLE->table[i].lexema == LEX_ID || table.LEXTABLE->table[i].lexema == LEX_LITERAL) {
				table.IDTABLE->table[id++].idxfirstLE = i;
			}
		}
		int startPos = 0, finishPos = 0, counterFunc = 0, startParam=0, finish=0;
		string name;
		int posInLT = 0;
		for (int i = 0; i < table.LEXTABLE->size; i++) {
			if (table.LEXTABLE->table[i].lexema == 'd') counterFunc++;

		}
		for (int k = 0; k < counterFunc; k++) {
			for (int i = finishPos; i < table.LEXTABLE->size; i++) {
				if (LT::GetEntry(table.LEXTABLE, i).lexema == '{') {
					startPos = i;
					break;
				}
			}			

			for (int i = finishPos + 1; i < table.LEXTABLE->size; i++) {
				if (LT::GetEntry(table.LEXTABLE, i).lexema == '}') {
					finishPos = i;
					break;
				}
			}
			int type = 0;
			string paramName;
			int smPos = 0;

			for (int q = 0; q < equals; q++) {

				int d = 0;

				for (int i = 0; i < table.LEXTABLE->size; i++) {
					if (table.LEXTABLE->table[i].lexema == LEX_SEMICOLON) {
						if (table.LEXTABLE->table[i].sn - table.LEXTABLE->table[i + 1].sn == 0) {
							smPos = i;
							while (table.LEXTABLE->table[i + 1].sn == table.LEXTABLE->table[i].sn) {
								d++;
								i++;
							}
							break;
						}
					}
				}

				for (int i = 0; i < table.LEXTABLE->size; i++) {
					if (table.LEXTABLE->table[i].lexema == LEX_SEMICOLON) {
						if (table.LEXTABLE->table[i].sn - table.LEXTABLE->table[i + 1].sn == 0) {

							while (table.LEXTABLE->table[i + 1].sn == table.LEXTABLE->table[i].sn) {
								table.LEXTABLE->table[i] = table.LEXTABLE->table[i + d];
								i++;

							}
							cout << i << endl;
							cout << d << endl;
							for (int j = i; j < table.LEXTABLE->size; j++) {
								table.LEXTABLE->table[j] = table.LEXTABLE->table[j + d];

							}
						}
					}
				}
				table.LEXTABLE->size -= d;
				d = 0;
			}
			
			for (int i = startPos; i < finishPos; i++) {
				for (int j = 0; j < startPos; j++) {
					if (table.LEXTABLE->table[j].lexema == LEX_ID && table.IDTABLE->table[table.LEXTABLE->table[j].idxTI].idtype == 3) {
						for (int k = j + 1; k < finishPos; k++) {
							if (table.LEXTABLE->table[k].lexema == LEX_ID) {
								if (!strcmp(table.IDTABLE->table[table.LEXTABLE->table[j].idxTI].id , table.IDTABLE->table[table.LEXTABLE->table[k].idxTI].id)) {
									table.IDTABLE->table[table.LEXTABLE->table[k].idxTI].littype = (IT::LITERALTYPE)1;
								}								
							}
							if (table.LEXTABLE->table[k].lexema == LEX_BRACELET) break;
						}
					}
				}

				if (table.LEXTABLE->table[i - 1].lexema == 't'&&table.LEXTABLE->table[i].lexema == 'i') {
					name = table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].id;
					type = table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].iddatatype;
					for (int j = i + 1; j < finishPos; j++) {
						
						if (table.LEXTABLE->table[j].lexema == 'i') {
							posInLT = table.LEXTABLE->table[j].idxTI;
							if (table.IDTABLE->table[table.LEXTABLE->table[j].idxTI].id == name) {
								table.IDTABLE->table[table.LEXTABLE->table[j].idxTI].littype = (IT::LITERALTYPE)3;
								if (table.IDTABLE->table[table.LEXTABLE->table[j].idxTI].iddatatype == 1) table.IDTABLE->table[table.LEXTABLE->table[j].idxTI].littype = (IT::LITERALTYPE)type;
								if (table.IDTABLE->table[table.LEXTABLE->table[j].idxTI].iddatatype == 2) table.IDTABLE->table[table.LEXTABLE->table[j].idxTI].littype = (IT::LITERALTYPE)type;
								table.IDTABLE->table[table.LEXTABLE->table[j].idxTI].idxfirstLE = i;
								
							}
						}
					}
				}
			}
		}

	}
}