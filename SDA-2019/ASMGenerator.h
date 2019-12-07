#pragma once
#include <string>
#include <vector>
#include "LT.h"
#include "Lexer.h"

#define ASM_START_BLOCK                       ".586\n.model flat,stdcall\n"
#define ASM_LIBS_BLOCK                        "includelib libucrt.lib\nincludelib kernel32.lib\n"
#define ASM_CONST_BLOCK                       "\n.const\n"
#define ASM_STACK_BLOCK                       "\n.stack 4096\n"
#define ASM_DATA_BLOCK                        "\n.data\n"
#define ASM_MAIN_BLOCK                        "\nmain PROC\n"
#define ASM_MAIN_END_BLOCK                    "\nend main\n"


namespace ASMGenerator {
	void AddSystemInfo();
	void AddConstInfo(Tables table);
	void AddDataInfo(Tables table);
	void Generate(Tables table);
}
