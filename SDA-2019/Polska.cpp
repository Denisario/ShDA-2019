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
		}
	}
	return fl;
}
bool PN::PolishNotation(int lextable_pos, Tables& tab) {
	std::stack<LT::Entry> st;							//ñòåê äëÿ îïåðàòîðîâ
	LT::Entry outstr[20];								//âûõîäíàÿ ñòðîêà
	int len = 0,										//îáùàÿ äëèíà
		lenout = 0,										//äëèíà âûõîäíîé ñòðîêè
		semicolonid;									//èä äëÿ ýëåìåíòà òàáëèöû ñ òî÷êîé ñ çàïÿòîé
	char skob = 0;										//êîë-âî ñêîáîê
	int indoffunk;										//èíäåêñ äëÿ çàìåíû íà ýëåìåíò ñ ôóíêöèåé
	for (int i = lextable_pos; tab.LEXTABLE->table[i].lexema != LEX_SEMICOLON; i++) {
		len = i;										//ïîäñ÷¸ò äëèíû âûðàæåíèÿ
		semicolonid = i + 1;
	}
	len++;
	for (int i = lextable_pos; i < len; i++) {
		switch (tab.LEXTABLE->table[i].lexema)				//îïðåäåëÿåì îïåðàöèþ
		{
		case LEX_RIGHTHESIS:						//åñëè ïðàâàÿ ñêîáêà - âûòàëêèâàíèå âñåãî äî ëåâîé ñêîáêè
		{
			while (st.top().lexema != '(') {
				outstr[lenout++] = st.top();		//çàïèñûâàåì â âûõîäíóþ ñòðîêó î÷åðåäíîé ñèìâîë ìåæäó ñêîáêàìè
				skob++;
				st.pop();							//óäàëÿåì âåðøèíó ñòåêà
			}
			st.pop();								//óäàëÿåì ëåâóþ ñêîáêó â ñòåêå
			break;
		}
		case LEX_ID:								//èä
		case LEX_LITERAL:							//ëèòåðàë
		{
			if (tab.LEXTABLE->table[i + 1].lexema == LEX_LEFTHESIS) {	//ñëåä - ëåâàÿ ñêîáêà
				indoffunk = i;										//çíà÷èò, ôóíêöèÿ
				i += 2;												//ïåðåõîäèì ê ïàðàìåòðàì
				while (tab.LEXTABLE->table[i].lexema != LEX_RIGHTHESIS) {//ïîêà âíóòðè àðãóìåíòîâ ôóíêöèè, ïåðåïèñûâàåì èõ â ñòðîêó
					if (tab.LEXTABLE->table[i].lexema != LEX_COMMA) {
						outstr[lenout++] = tab.LEXTABLE->table[i++];
					}
					else
					{
						skob++;
						i++;						//èãíîðèðóåì çàïÿòûå
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
			st.push(tab.LEXTABLE->table[i]);							//ïîìåùàåì â ñòåê ëåâóþ ñêîáêó
			skob++;
			break;
		}

		case LEX_PLUS:
		case LEX_MINUS:
		case LEX_STAR:
		case LEX_DIRSLASH:
		case LEX_REM:
		{
			if (!st.size())						//åñëè ïóñòîé ñòåê
				st.push(tab.LEXTABLE->table[i]);		//ïðîñòî çàïèñûâàåì â âûõîäíóþ ñòðîêó
			else {
				int pr, id;
				id = st.top().lexema;
				pr = prior(id);				//îïðåäåëÿåì ïðèîðèòåò îïåðàöèè â ñòåêå
				if (prior(tab.LEXTABLE->table[i].lexema) > pr)//åñëè ïðèîðèòåò äîáàâëÿåìîé îïåðàöèè áîëüøå îïåðàöèè íà âåðøèíå ñòåêà
					st.push(tab.LEXTABLE->table[i]);			 //äîáàâëÿåì îïåðàöèè â ñòåê
				else {									 //åñëè ìåíüøå, òî çàïèñûâàåì èç ñòåêà â âûõîäíóþ ñòðîêó âñå îïåðàöèè 
														 //ñ áîëüøèì èëè ðàâíûì ïðèîðèòåòîì
					while (st.size() && prior(tab.LEXTABLE->table[i].lexema) <= prior(id))
					{
						outstr[lenout] = st.top();
						st.pop();
						lenout++;
					}
					st.push(tab.LEXTABLE->table[i]);			 //äîáàâëÿåì â ñòåê òåêóùóþ îïåðàöèþ
				}
			}
			break;
		}
		}
	}
	while (st.size()) {
		outstr[lenout++] = st.top();									//âûâîä â ñòðîêó âñåõ çíàêîâ èç ñòåêà
		st.pop();
	}
	for (int i = lextable_pos, k = 0; i < lextable_pos + lenout; i++) {
		if ((tab.LEXTABLE->table[i].lexema == LEX_ID && tab.IDTABLE->table[tab.LEXTABLE->table[i].idxTI].idtype == 2) ) {}
		else {
			tab.LEXTABLE->table[i] = outstr[k];									//çàïèñü â òàáëèöó ëåêñåì ïîëüñêîé çàïèñè
			k++;
		}
	}
	tab.LEXTABLE->table[lextable_pos + lenout] = tab.LEXTABLE->table[semicolonid];//âñòàâêà ýëåìåíòà ñ òî÷êîé ñ çàïÿòîé
	//for (int i = 0; i < skob; i++)
	//{
	//	for (int j = lextable_pos + lenout + 1; j < tab.LEXTABLE->size; j++)	//ñäâèãàåì íà ëèøíåå ìåñòî, îñòàâøååñÿ îò ñêîáîê
	//	{
	//		tab.LEXTABLE->table[j] = tab.LEXTABLE->table[j + 1];
	//	}
	//	tab.LEXTABLE->size--;
	//}
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
}

void PN::Print(Tables tables)
{
	std::ofstream pol("pol.txt");
	for (int i = 0; i < tables.LEXTABLE->size; i++) {
		pol << tables.LEXTABLE->table[i].lexema;
		if (tables.LEXTABLE->table[i].sn != tables.LEXTABLE->table[i + 1].sn) pol << endl;
	}
}
