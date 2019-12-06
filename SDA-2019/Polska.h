#pragma once
#include "pch.h"
#include "FST.h"
#include "Lexer.h"

struct PN {
	bool PolishNotation(int lextable_pos, Tables& tab);
	bool searchExpression(Tables tables);
	int prior(char);
	void Print(Tables tables);
};