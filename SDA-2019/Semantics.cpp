#include "pch.h"
#include "Lexer.h"
#include "LT.h"
#include "IT.h"
#include "Error.h"
#include <string>
#include <vector>
namespace Semantics {
	vector<string> resWords = { "int","str","def","var","out","retur","if","elif","else","main" };


	void startSem(Tables table) {
		//check main
		unsigned short usMain = 0;
		unsigned short line = 0;
		unsigned short counterFunction = 0;
		LT::Entry LexTable;
		IT::Entry IdTable;
		string id;
		for (int i = 0; i < table.LEXTABLE->size; i++) {
			LexTable = LT::GetEntry(table.LEXTABLE, i);
			if (LexTable.lexema == 'm') {
				++usMain;
				line = LexTable.sn;
			}
		}
		if (usMain == 0) {
			throw ERROR_THROW(300);
		}
		else if (usMain > 1) throw ERROR_THROW_IN(301, line, NULL);

		//check names in ID

		for (int i = 0; i < table.LEXTABLE->size; i++) {
			if ((LT::GetEntry(table.LEXTABLE, i).lexema == 't') && !(LT::GetEntry(table.LEXTABLE, i + 1).lexema == 'i')) {
				line = LT::GetEntry(table.LEXTABLE, i + 1).sn-1;
				throw ERROR_THROW_IN(302,line, NULL);
			}			
		}
		line = 0;
		//check unique of identifiers
		string semicolon=";", lexem, lexem2;
		for (int i = 0; i < table.IDTABLE->size; i++) {
			if (table.IDTABLE->table[i].littype == -1) {
				for (int j = i+1; j < table.IDTABLE->size; j++) {
					
					if ((!strcmp(table.IDTABLE->table[i].id, table.IDTABLE->table[j].id))&&(!strcmp(table.IDTABLE->table[i].view->id, table.IDTABLE->table[j].view->id))) {
						lexem = table.LEXTABLE->table[table.IDTABLE->table[i].idxfirstLE+1].lexema;
						lexem2 = table.LEXTABLE->table[table.IDTABLE->table[j].idxfirstLE+1].lexema;
						/*if (lexem==semicolon&&lexem2==semicolon) {
							throw ERROR_THROW(303);
						}*/
					}
				}
			}
			else {
				continue;
			}		
		}//rework
		//check type of returned literal and return

		int LTStartFunction = 0, LTFinishFunction = 0, type = 0, functionType = 0;

		for (int j = 0; j < table.LEXTABLE->size; j++) {
			if (LT::GetEntry(table.LEXTABLE, j).lexema == 'd'&&LT::GetEntry(table.LEXTABLE, j + 2).lexema == 'i') counterFunction++;
		}
		for (int k = 0; k < counterFunction; k++) {
			for (int i = LTFinishFunction; i < table.LEXTABLE->size; i++) {
				if (LT::GetEntry(table.LEXTABLE, i).lexema == 'd'&&LT::GetEntry(table.LEXTABLE, i + 2).lexema == 'i') {
					LTStartFunction = i;
					break;
				}

			}
			for (int i = LTFinishFunction+1; i < table.LEXTABLE->size; i++) {
				if (LT::GetEntry(table.LEXTABLE, i).lexema == '}') {
					LTFinishFunction = i;
					break;
				}
			}			
			type = table.IDTABLE->table[LT::GetEntry(table.LEXTABLE, LTStartFunction + 2).idxTI].iddatatype;
			functionType = table.IDTABLE->table[LT::GetEntry(table.LEXTABLE, LTFinishFunction-2).idxTI].idtype;
			cout << LTStartFunction << " " << LTFinishFunction <<" "<<type<<" "<<functionType<< endl;
			if (type != functionType&&functionType==1) throw ERROR_THROW(304);
		}
		//check return of main


		
		for (int i = 0; i < table.LEXTABLE->size; i++) {
			if (LT::GetEntry(table.LEXTABLE, i).lexema == 'm') {
				for (int j = i; j < table.LEXTABLE->size; j++) {
					if (LT::GetEntry(table.LEXTABLE, j).lexema == 'r'&&LT::GetEntry(table.LEXTABLE, j + 1).lexema == 'l') {
						if(table.IDTABLE->table[LT::GetEntry(table.LEXTABLE, j + 1).idxTI].value.vint!=0) throw ERROR_THROW(305);
					}
				}
			}			
		}
	}
}