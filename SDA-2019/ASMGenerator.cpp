#include "pch.h"
#include "ASMGenerator.h"
#include <fstream>
using namespace std;

namespace ASMGenerator {
	ofstream asmFile("asm.txt");
	void Add() {
		asmFile << ASM_START_BLOCK;
		asmFile << ASM_LIBS_BLOCK;
		asmFile << ASM_STACK_BLOCK;
		asmFile << ASM_CONST_BLOCK;
		asmFile << ASM_DATA_BLOCK;
		asmFile << ASM_MAIN_BLOCK;
		asmFile << ASM_MAIN_END_BLOCK;
	}
}