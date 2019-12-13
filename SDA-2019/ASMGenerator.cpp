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
		asmFile << "outstr PROTO : DWORD\n";
		asmFile << "outintn PROTO : DWORD\n";
		asmFile << "outstrn PROTO : DWORD\n";
		asmFile << "catlines	PROTO: DWORD, : DWORD, :DWORD";


		asmFile << ASM_STACK_BLOCK;
	}

	void AddConstInfo(Tables table) {
		asmFile << ASM_CONST_BLOCK;
		asmFile << "\tdivisionByZero db 'ERROR: DIVIDE BY ZERO', 0" << endl;
		asmFile << "\tbelowZeroNum db 'ERROR: NUM IS BELOVER THAN ZERO', 0" << endl;
		for (int i = 0; i < table.LEXTABLE->size; i++) {
			if (table.LEXTABLE->table[i].lexema == LEX_LITERAL && table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].littype == 2) {
				asmFile << "\t" << table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].id << " BYTE " << table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].value.vstr->str << " , 0" << endl;
			}
			if (table.LEXTABLE->table[i].lexema == LEX_LITERAL && table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].littype == 1) {
				asmFile << "\t" << table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].id << " SDWORD " << table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].value.vint << endl;
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
	bool isIf = false;
	bool isElse = false;
	bool isPol = false;
	bool hasDivide = false;
	bool callFunc = false;
	int funcPos = 0;
	
	void AddMainProc(Tables table) {
		string name;
		string functionName;
		string nameOfEqu;
		string name1;
		bool isMain = false;
		int finish = 0;
		int  deltaIf= 0;
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
					asmFile << "\tpush " << name << table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].id;
					asmFile << "\n\tcall outint\n";
					asmFile << "\n\tpop " << name << table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].id<<endl;
					name.clear();
				}
				if (table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].littype == 2) {
					asmFile << "\tpush offset " << table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI-1].id;
					asmFile << "\n\tcall outstr\n";
					name.clear();
				}
				break;
			case LEX_OUTN:
				if (table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].littype == 1) {
					for (int j = 0; j < 4; j++) {
						name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].view->id[j]);
						if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].view->id) - 1) break;
					}
					name += "_";
					asmFile << "\tpush "<<name<< table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].id;
					asmFile << "\n\tcall outintn\n";
					name.clear();
				}
				if (table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].littype == 2) {
					for (int j = 0; j < 4; j++) {
						name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].view->id[j]);
						if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].view->id) - 1) break;
					}
					name += "_";
					asmFile << "\tpush offset " <<table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI - 1].id;
					asmFile << "\n\tcall outstrn\n";
					name.clear();
				}
				break;
			case LEX_RETURN:
				
				if (hasDivide) {
					asmFile << "\tpop eax" << endl;
					asmFile << "\tret" << endl;
					asmFile << "\tcall exitProcess" << endl;
					asmFile << "\tfinish:" << endl;
					asmFile << "\tpush offset divisionByZero" << endl;
					asmFile << "\tcall outstr" << endl;
					asmFile << "\tcall exitProcess" << endl;					
				}
				asmFile << "\tret" << endl;
				asmFile << "\tbelow:" << endl;
				asmFile << "\tpush offset belowZeroNum" << endl;
				asmFile << "\tcall outstr" << endl;
				asmFile << "\tcall exitProcess" << endl;
				hasDivide = false;
				
				if (!isMain) asmFile << "glob_" << functionName << " ENDP" << endl;

				break;
			case LEX_EQUAL:
				if (table.LEXTABLE->table[i + 1].lexema == LEX_ID && table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].littype == -1){
					functionName = table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].id;
				}				
			

				equ = i;
				for (int j = 0; j < 4; j++) {
					nameOfEqu.push_back(table.IDTABLE->table[table.LEXTABLE->table[ equ-1 ].idxTI].view->id[j]);
					if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[equ - 1].idxTI].view->id) - 1) break;
				}
				nameOfEqu += "_";
				name1 = table.IDTABLE->table[table.LEXTABLE->table[equ - 1].idxTI].id;
				while (table.LEXTABLE->table[i].lexema != LEX_SEMICOLON) {
					if (table.LEXTABLE->table[i].lexema == LEX_ID&& table.LEXTABLE->table[i+1].lexema!=LEX_COMMA && table.LEXTABLE->table[i - 1].lexema != LEX_COMMA) {
						isPol = false;
						for (int j = 0; j < 4; j++) {
							name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].view->id[j]);
							if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].view->id) - 1) break;
						}
						name += "_";
						
							asmFile << "\tpush " << name + table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].id << endl;				
							
						name.clear();
					}
					if (table.LEXTABLE->table[i-1].lexema != LEX_EQUAL&&table.LEXTABLE->table[i].lexema == LEX_LITERAL && table.LEXTABLE->table[i + 1].lexema != LEX_COMMA && table.LEXTABLE->table[i - 1].lexema != LEX_COMMA) {
						isPol = false;						
						asmFile << "\tpush " << table.IDTABLE->table[table.LEXTABLE->table[i].idxTI].id << endl;
						name.clear();
					}

					if (table.LEXTABLE->table[i].lexema == LEX_ID && table.LEXTABLE->table[i + 1].lexema == LEX_LEFTHESIS) {
						funcPos = i;
						for (int j = 0; j < 4; j++) {
							name.push_back(table.IDTABLE->table[table.LEXTABLE->table[equ-1].idxTI].view->id[j]);
							if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[equ-1].idxTI].view->id) - 1) break;
						}
						name += "_";
						while (table.LEXTABLE->table[i + 1].lexema != LEX_RIGHTHESIS) {
							if (table.LEXTABLE->table[i + 1].lexema == LEX_LITERAL) {
								asmFile << "\tpush " <<table.IDTABLE->table[table.LEXTABLE->table[i+1].idxTI].id << endl;
							}
							i++;							
						}
						
							asmFile << "\tcall glob_" << table.IDTABLE->table[table.LEXTABLE->table[funcPos].idxTI].id << endl;
							asmFile << "\tmov " << name + table.IDTABLE->table[table.LEXTABLE->table[equ - 1].idxTI].id << ", eax" << endl;					
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
						for (int j = 0; j < 4; j++) {
							name.push_back(table.IDTABLE->table[table.LEXTABLE->table[equ - 1].idxTI].view->id[j]);
							if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[equ - 1].idxTI].view->id) - 1) break;
						}
						name += "_";
						asmFile << "\tcall glob_" <<functionName << endl;
						asmFile << "\tmov " << name + table.IDTABLE->table[table.LEXTABLE->table[equ - 1].idxTI].id << ", eax" << endl;
						name.clear();
					}

					if (table.LEXTABLE->table[i - 1].lexema == LEX_ID && table.LEXTABLE->table[i + 1].lexema == LEX_LITERAL && table.LEXTABLE->table[i + 2].lexema == LEX_SEMICOLON) {
						isPol = false;
						if (table.IDTABLE->table[table.LEXTABLE->table[i - 1].idxTI].iddatatype == 1){
							for (int j = 0; j < 4; j++) {
								name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i - 1].idxTI].view->id[j]);
								if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i - 1].idxTI].view->id) - 1) break;
							}
							name += "_";
							asmFile << "\tmov " << name + table.IDTABLE->table[table.LEXTABLE->table[i - 1].idxTI].id << ", " << table.IDTABLE->table[table.LEXTABLE->table[i + 1].idxTI].value.vint << endl;							
							name.clear();
						}
						
						
					}

					if (table.LEXTABLE->table[i].lexema == LEX_PLUS&&table.IDTABLE->table[table.LEXTABLE->table[i-2].idxTI].iddatatype!=2) {
						isPol = true;
						asmFile << "\tpop ebx\n\tpop eax" << endl;
						asmFile << "\tadd eax, ebx" << endl;
						asmFile << "\tpush eax" << endl;
						name.clear();
					}else if(table.LEXTABLE->table[i].lexema == LEX_PLUS && table.IDTABLE->table[table.LEXTABLE->table[i - 2].idxTI].iddatatype == 2){
						isPol = true;
						asmFile << "pop eax " <<endl;
						asmFile << "pop ebx " <<endl;
						asmFile << "call catlines " <<endl;						
					}
					if (table.LEXTABLE->table[i].lexema == LEX_MINUS) {
						isPol = true;
						asmFile << "\tpop ebx\n\tpop eax" << endl;
						asmFile << "\tsub eax, ebx" << endl;
						asmFile << "\tpush eax" << endl;
					}
					if (table.LEXTABLE->table[i].lexema == LEX_STAR) {
						isPol = true;
						asmFile << "\tpop ebx\n\tpop eax" << endl;
						asmFile << "\timul ebx" << endl;
						asmFile << "\tpush eax" << endl;
					}
					if (table.LEXTABLE->table[i].lexema == LEX_DIRSLASH) {
						isPol = true;
						hasDivide = true;
						asmFile << "\tpop ebx" << endl;
						asmFile << "\tmov edx, 0 " << endl;
						asmFile << "\tpop eax" << endl;
						asmFile << "\tcmp ebx, 0" << endl;
						asmFile << "\tje finish" << endl;						
						asmFile << "\tidiv ebx" << endl;
						asmFile << "\tpush eax" << endl;
					}
					if (table.LEXTABLE->table[i].lexema == LEX_REM) {
						isPol = true;
						asmFile << "\tpop ebx" << endl;
						asmFile << "\tmov edx, 0 " << endl;
						asmFile << "\tpop eax" << endl;
						asmFile << "\tidiv ebx" << endl;
						asmFile << "\tpush edx" << endl;
						asmFile << "\tmov eax, edx" << endl;
					}

					i++;
				}
				if (isPol) {
					asmFile << "\tpop eax" << endl;
					asmFile << "\tcmp eax, 0" << endl;
					asmFile << "\tjl below" << endl;
					asmFile << "\tmov " << nameOfEqu + name1 << ", eax" << endl;
				}
				nameOfEqu.clear();
				break;
			case LEX_IF:
				isIf = true;
				for (int j = 0; j < 4; j++) {
					name.push_back(table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].view->id[j]);
					if (j == strlen((char*)table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].view->id) - 1) break;
				}
				name += "_";
				if (table.LEXTABLE->table[i + 3].lexema == LEX_GREATER) {
					asmFile << "\tpush " << name + table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].id << endl;
					asmFile << "\tpush " << name + table.IDTABLE->table[table.LEXTABLE->table[i + 4].idxTI].id << endl;
					asmFile << "\tpop ecx" << endl;
					asmFile << "\tpop edx" << endl;
					asmFile << "\tcmp edx, ecx" << endl;
					asmFile << "\tjg trueResult" << endl;
					asmFile << "\tjl falseResult" << endl;
				}
				if (table.LEXTABLE->table[i + 3].lexema == LEX_LESS) {
					asmFile << "\tpush " << name + table.IDTABLE->table[table.LEXTABLE->table[i + 2].idxTI].id << endl;
					asmFile << "\tpush " << name + table.IDTABLE->table[table.LEXTABLE->table[i + 4].idxTI].id << endl;
					asmFile << "\tpop ecx" << endl;
					asmFile << "\tpop edx" << endl;
					asmFile << "\tcmp ecx, edx" << endl;
					asmFile << "\tjg trueResult" << endl;
					asmFile << "\tjl falseResult" << endl;
				}
				name.clear();
							
				asmFile << "\ttrueResult:" << endl;
				break;
				i = deltaIf;
			
			case LEX_ELSE:
				isIf = false;
				isElse = true;
				asmFile << "\tfalseResult:" << endl;
				break;
			case LEX_ENDBLOCK:
				if(isIf) asmFile << "\tjmp code" << endl;
				asmFile << "\tleave"<<endl;
				if (isElse) asmFile << "\tcode:" << endl;
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