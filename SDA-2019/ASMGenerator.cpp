#include "pch.h"
#include "ASMGenerator.h"
#include "Lexer.h"
#include "LT.h"
#include <fstream>
using namespace std;

namespace ASMGenerator {
	ofstream asmFile("../../Generator/asm.asm");
	string setName(Tables table, int pos) {
		string name;
		for (int j = 0; j < 4; j++) {
			name.push_back(table.IDTABLE->table[table.LEXTABLE->table[pos].idxTI].view->id[j]);
			if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[pos].idxTI].view->id) - 1) break;
		}
		name += "_";
		return name;
	}

	void AddSystemInfo() {
		asmFile << ASM_START_BLOCK;
		asmFile << ASM_LIBS_BLOCK;
		asmFile << endl << "includelib lib.lib" << endl;
	}

	void AddFuncInfo(Tables table) {
		asmFile << "\n\nExitProcess PROTO : DWORD\n";
		asmFile << "outint PROTO : DWORD\n";

		//for (int i = 0; i < table.LEXTABLE->size; i++) {
		//	if (table.LEXTABLE->table[i].lexema == LEX_DEF && table.LEXTABLE->table[i + 1].lexema == LEX_INT) {
		//		asmFile << table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].id<<':';
		//		
		//	}
		//	/*if (table.LEXTABLE->table[i].lexema == LEX_LEFTHESIS) {
		//		while (table.LEXTABLE->table[i].lexema != LEX_RIGHTHESIS) {
		//			if (table.LEXTABLE->table[i].lexema == LEX_INT && table.LEXTABLE->table[i + 1].lexema == LEX_ID) {
		//				asmFile << " " << table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].id << ": DWORD";
		//				if (table.LEXTABLE->table[i + 2].lexema == LEX_COMMA) asmFile << ",";
		//			}
		//			i++;
		//		}
		//	}*/
		//}
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
			if (table.IDTABLE->table[i].idtype != 2 || table.IDTABLE->table[i].idtype != 3) {
				if (table.IDTABLE->table[i].littype == -1 && table.IDTABLE->table[i].idtype == 1) {
					for (int j = 0; j < 4; j++) {
						name.push_back(table.IDTABLE->table[i].view->id[j]);
						if (j == strlen((char*)table.IDTABLE->table[i].view->id) - 1) break;
					}
					name += "_";
					asmFile << "\t" << setw(10) << name + table.IDTABLE->table[i].id << " SDWORD " << table.IDTABLE->table[i].value.vstr->str << " 0" << endl;
					name.clear();
				}
			}
		}

	}

	void AddCodeBlock() {
		asmFile << "\n.code" << endl;
	}


	int equ = 0;
	bool flag = false;
	void AddMainProc(Tables table) {
		string name;
		string functionName;
		bool isMain = false;
		int finish = 0;
		int delta = 0;
		int position = 0;
		for (int i = 0; i < table.LEXTABLE->size; i++) {
			switch (table.LEXTABLE->table[i].lexema)
			{
			case LEX_DEF://ÍÀ×ÀÒÜ ÎÒÑÞÄÀ
				if (table.LEXTABLE->table[i + 1].lexema == LEX_MAIN) break;
				for (int j = 0; j < 4; j++) {
					name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].view->id[j]);
					if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].view->id) - 1) break;
				}
				name += "_";
				asmFile << name + table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].id << " PROC";
				name.clear();

				if (table.LEXTABLE->table[i + 3].lexema == LEX_LEFTHESIS) {
					while (table.LEXTABLE->table[i].lexema != LEX_LEFTBRACE) {
						if (table.LEXTABLE->table[i].lexema == LEX_INT && table.LEXTABLE->table[i + 1].lexema == LEX_ID) {
							for (int j = 0; j < 4; j++) {
								name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].view->id[j]);
								if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].view->id) - 1) break;
							}
							functionName = name;
							name += "_";
							if (table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].idtype == 3) {
								asmFile << " " << name + table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].id << ": DWORD";
							}
							name.clear();
							if (table.LEXTABLE->table[i + 2].lexema == LEX_COMMA) asmFile << ",";
						}
						delta++;
						i++;
					}
					asmFile << endl;

				}




				break;

			case LEX_MAIN:
				asmFile << "\nmain PROC" << endl;
				isMain = true;
				break;

			case LEX_OUT:
				if (table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].littype == 1) {
					for (int j = 0; j < 4; j++) {
						name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].view->id[j]);
						if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].view->id) - 1) break;
					}
					name += "_";
					asmFile << "\n\tpush eax";
					asmFile << "\n\tcall outint\n";
					name.clear();
				}
				break;
			case LEX_RETURN:
				asmFile << "\tpop eax" << endl;
				asmFile << "\tret" << endl;
				if (!isMain) asmFile << "glob_" << functionName << " ENDP" << endl;

				break;
			case LEX_EQUAL:
				if (table.LEXTABLE->table[i + 1].lexema == LEX_ID && table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].littype == -1){
					functionName = table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].id;
				}

				equ = i;
				while (table.LEXTABLE->table[i].lexema != LEX_SEMICOLON) {
					if (table.LEXTABLE->table[i].lexema == LEX_ID&& table.LEXTABLE->table[i+1].lexema!=LEX_COMMA && table.LEXTABLE->table[i - 1].lexema != LEX_COMMA) {
						for (int j = 0; j < 4; j++) {
							name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].view->id[j]);
							if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].view->id) - 1) break;
						}
						name += "_";
						asmFile << "\tpush " << name + table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].id << endl;
						name.clear();
					}

					if (table.LEXTABLE->table[i-1].lexema == LEX_ID && table.LEXTABLE->table[i].lexema == LEX_RIGHTHESIS) {
						/*string funcName = table.IDTABLE->table[table.LEXTABLE->table[i-1].idxTI].id;*/
						position = i;
						while (table.LEXTABLE->table[i - 1].lexema != LEX_LEFTHESIS)
						{
							if (table.LEXTABLE->table[i - 1].lexema == LEX_ID) {
								for (int j = 0; j < 4; j++) {
									name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i - 1].idxTI].view->id[j]);
									if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i - 1].idxTI].view->id) - 1) break;
								}
								name += "_";
								asmFile << "\tpush " << name + table.IDTABLE->table[table.LEXTABLE->table[i - 1].idxTI].id << endl;
								name.clear();
							}
							i--;
						}
						i = position;
			/*			string funcName = table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].id;*/
						asmFile << "\tcall glob_" <<functionName << endl;
					}

					if (table.LEXTABLE->table[i - 1].lexema == LEX_ID && table.LEXTABLE->table[i + 1].lexema == LEX_LITERAL && table.LEXTABLE->table[i + 2].lexema == LEX_SEMICOLON) {
						for (int j = 0; j < 4; j++) {
							name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i - 1].idxTI].view->id[j]);
							if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i - 1].idxTI].view->id) - 1) break;
						}
						name += "_";
						asmFile << "\tmov " << name + table.IDTABLE->table[table.LEXTABLE->table[i - 1].idxTI].id << ", " << table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].value.vint << endl;
						name.clear();
					}

					if (table.LEXTABLE->table[i].lexema == LEX_PLUS) {
						asmFile << "\tpop ebx\n\tpop eax" << endl;
						asmFile << "\tadd eax, ebx" << endl;
						asmFile << "\tpush eax" << endl;
						name.clear();
					}
					if (table.LEXTABLE->table[i].lexema == LEX_MINUS) {
						asmFile << "\tpop ebx\n\tpop eax" << endl;
						asmFile << "\tsub eax, ebx" << endl;
						asmFile << "\tpush eax" << endl;
					}
					if (table.LEXTABLE->table[i].lexema == LEX_STAR) {
						asmFile << "\tpop ebx\n\tpop eax" << endl;
						asmFile << "\timul ebx" << endl;
						asmFile << "\tpush eax" << endl;
					}
					if (table.LEXTABLE->table[i].lexema == LEX_DIRSLASH) {
						asmFile << "\tpop ebx" << endl;
						asmFile << "\tmov edx, 0 " << endl;
						asmFile << "\tpop eax" << endl;
						asmFile << "\tidiv ebx" << endl;
						asmFile << "\tpush eax" << endl;
					}
					if (table.LEXTABLE->table[i].lexema == LEX_REM) {
						asmFile << "\tpop ebx" << endl;
						asmFile << "\tmov edx, 0 " << endl;
						asmFile << "\tpop eax" << endl;
						asmFile << "\tidiv ebx" << endl;
						asmFile << "\tpush edx" << endl;
						asmFile << "\tmov eax, edx" << endl;
					}

					i++;
				}
				break;
			case LEX_IF:
				break;
			default:
				/*throw ERROR_THROW(700);*/
				break;
			}
		}
	}
	void AddEndProc() {
		asmFile << "main ENDP" << ASM_MAIN_END_BLOCK << endl;
	}


	void Generate(Tables table) {
		AddSystemInfo();
		AddFuncInfo(table);
		AddConstInfo(table);
		AddDataInfo(table);
		AddCodeBlock();
		AddMainProc(table);
		AddEndProc();

	}
}