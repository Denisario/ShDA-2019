#pragma once
#include "pch.h"
#include "LT.h"
#include "In.h"
#include "IT.h"
struct Tables {
	IT::IdTable* IDTABLE;
	LT::LexTable* LEXTABLE;
};
struct ListId
{
	IT::Entry id;
	IT::Entry* pNext = nullptr;
};
namespace Lexer {
	void initTypeLexem(const char* text, std::string tmp, LT::LexTable* tableOfLexem, int numberOfstring, int poz, IT::IdTable* newIdTable, int*typeData, int*typeID, int*littype);
	Tables createTables(In::IN newIN);
	void Print(Tables tables);
	void CheckLTIT(Tables tables);
}