#include "pch.h"
#include "polska.h"
#include "Lexer.h"
#include "LT.h"
#include "IT.h"
#include "Error.h"
#include <string>
#include <vector>

bool PN::searchExpression(Tables Tables) {
	bool fl = false;
	for (int i = 0; i < Tables.LEXTABLE->size; i++) {
		if (Tables.LEXTABLE->table[i].lexema == LEX_EQUAL) {
			fl = PolishNotation(++i, Tables);
		}if (Tables.LEXTABLE->table[i].lexema == LEX_RETURN) {
			fl = PolishNotation(i, Tables);
		}
	}
	return fl;
}
bool PN::PolishNotation(int lextable_pos, Tables& tab) {
	std::stack<LT::Entry> st;							
	LT::Entry outstr[20];								
	int len = 0,									
		lenout = 0,									
		semicolonid;								
	char skob = 0;									
	int indoffunk;									
	for (int i = lextable_pos; tab.LEXTABLE->table[i].lexema != LEX_SEMICOLON; i++) {
		len = i;									
		semicolonid = i + 1;
	}
	len++;
	for (int i = lextable_pos; i < len; i++) {
		switch (tab.LEXTABLE->table[i].lexema)				
		{
		case LEX_RIGHTHESIS:					
		{
			while (st.top().lexema != '(') {
				outstr[lenout++] = st.top();		
				skob++;
				st.pop();						
			}
			st.pop();							
			break;
		}
		case LEX_ID:								
		case LEX_LITERAL:							
		{
			if (tab.LEXTABLE->table[i + 1].lexema == LEX_LEFTHESIS&& tab.LEXTABLE->table[i + 3].lexema != LEX_COMMA) {
				indoffunk = i;									
				i += 2;												
				while (tab.LEXTABLE->table[i].lexema != LEX_RIGHTHESIS) {
					if (tab.LEXTABLE->table[i].lexema != LEX_COMMA) {
						outstr[lenout++] = tab.LEXTABLE->table[i++];
					}
					else
					{
						skob++;
						i++;					
					}
				}
				outstr[lenout++] = tab.LEXTABLE->table[indoffunk];
				skob += 2;

			}
			else {
				outstr[lenout++] = tab.LEXTABLE->table[i];
			}
			break;
		}
		case LEX_LEFTHESIS:
		{
			if (tab.LEXTABLE->table[i + 2].lexema == LEX_COMMA) return 1;
			st.push(tab.LEXTABLE->table[i]);						
			skob++;
			break;
		}

		case LEX_PLUS:
		case LEX_MINUS:
		case LEX_STAR:
		case LEX_DIRSLASH:
		case LEX_REM:
		case LEX_RETURN:
		{
			if (!st.size())					
				st.push(tab.LEXTABLE->table[i]);	
			else {
				int pr, id;
				id = st.top().lexema;
				pr = prior(id);				
				if (prior(tab.LEXTABLE->table[i].lexema) > pr)
					st.push(tab.LEXTABLE->table[i]);			
				else {									
													
					while (st.size() && prior(tab.LEXTABLE->table[i].lexema) <= prior(id))
					{
						outstr[lenout] = st.top();
						st.pop();
						lenout++;
					}
					st.push(tab.LEXTABLE->table[i]);			
				}
			}
			break;
		}
		}
	}
	while (st.size()) {
		outstr[lenout++] = st.top();								
		st.pop();
	}
	for (int i = lextable_pos, k = 0; i < lextable_pos + lenout; i++) {
		if ((tab.LEXTABLE->table[i].lexema == LEX_ID && tab.IDTABLE->table[tab.LEXTABLE->table[i].idxTI].idtype == 2) ) {}
		else {
			tab.LEXTABLE->table[i] = outstr[k];
			k++;
		}
	}
	tab.LEXTABLE->table[lextable_pos + lenout] = tab.LEXTABLE->table[semicolonid];
	return 1;
}
int PN::prior(char l) {
	if (l == ')' || l == '(')
		return 1;
	if (l == '+' || l == '-')
		return 2;
	if (l == '*' || l == '/'|| l == ':')
		return 3;
	if (l == ':')
		return 4;
	if (l == 'r')
		return 0;
}

void PN::Print(Tables tables)
{	
	std::ofstream pol("pol.txt");
	for (int i = 0; i < tables.LEXTABLE->size; i++) {
		pol << tables.LEXTABLE->table[i].lexema;
		if (tables.LEXTABLE->table[i].sn != tables.LEXTABLE->table[i + 1].sn) pol << endl;
	}
}
