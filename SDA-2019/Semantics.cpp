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
			throw ERROR_THROW(300)
		}
		else if (usMain > 1) throw ERROR_THROW_IN(301, line, NULL);

		//check names in ID

		for (int i = 0; i < table.IDTABLE->size; i++) {
			id = table.IDTABLE->table[i].id;
			for (int j = 0; j < resWords.size(); j++) {
				if (id == resWords[j]) {
					unsigned short idinlt;
					line = table.LEXTABLE->table[table.IDTABLE->table[i].idxfirstLE].sn;
					throw ERROR_THROW_IN(302, line, NULL);
				}
			}
		}
	}
}