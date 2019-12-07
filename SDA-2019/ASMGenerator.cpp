#include "pch.h"
#include "ASMGenerator.h"
#include "Lexer.h"
#include "LT.h"
#include <fstream>
using namespace std;

namespace ASMGenerator {
	ofstream asmFile("asm.txt");
	void AddSystemInfo() {
		asmFile << ASM_START_BLOCK;
		asmFile << ASM_LIBS_BLOCK;
		asmFile << ASM_STACK_BLOCK;
	}

	void AddConstInfo(Tables table) {
		asmFile << ASM_CONST_BLOCK;
		for (int i = 0; i < table.LEXTABLE->size; i++) {
			if (table.LEXTABLE->table[i].lexema == LEX_LITERAL && table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].littype == 2) {
				asmFile << "\t" << table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].id << " BYTE " << table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].value.vstr->str << " , 0" << endl;
			}
			if (table.LEXTABLE->table[i].lexema == LEX_LITERAL && table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].littype == 1) {
				asmFile << "\t" << table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].id << " SDWORD " << table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].value.vstr->str << " 0" << endl;
			}
		}
	}

	void AddDataInfo(Tables table) {
		asmFile << ASM_DATA_BLOCK;
		string name;
		for (int i = 0; i < table.IDTABLE->size; i++) {
			/*for (int j = 0; j < 4; j++) {
				name = table.IDTABLE->table[i].view->id;
			}*/
			if (table.IDTABLE->table[i].idtype == 1) {
				
				asmFile << "\t" << table.IDTABLE->table[i].id << " SDWORD " << table.IDTABLE->table[i].value.vstr->str << " 0" << endl;
				name.clear();
			}
		}
	}


	void Generate(Tables table) {
		AddSystemInfo();
		AddConstInfo(table);
		AddDataInfo(table);
	}
}