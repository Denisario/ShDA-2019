#include "pch.h"
#include "Error.h"
#include "In.h"
using namespace std;
namespace In
{	
	IN getin(wchar_t infile[])
	{
		ifstream fin(infile);
		IN newIn;
		if (!fin.is_open())
			throw ERROR_THROW(110);
		string sStr;
		string sText;
		int iCounterSeparate = 0;
		while (!fin.eof())
		{
			getline(fin, sStr);
			sText += sStr;
			sText += '\n';
			newIn.lines++;
		}

		int TMP = newIn.lines;
		while (TMP > 0) {
			TMP = TMP / 10;
			iCounterSeparate++;//таким образом мы узнаем количество разрядов числа, в котором записано количество линий
		}
		newIn.text = new unsigned char[sText.size() + 1 + newIn.lines*(iCounterSeparate + 2)];
		int iLine = 1, iColumn = 0; unsigned char* pPtrText = newIn.text;
		*pPtrText = '0';
		pPtrText++;
		*pPtrText = '1';
		pPtrText++;
		*pPtrText = ' ';
		pPtrText++;
		for (int i = 0; i < sText.size(); i++)
		{

			if (newIn.code[*((unsigned char*)&sText[i])] == IN::F)
			{
				cout << (int)*((unsigned char*)&sText[i]) << endl;
				cout << sText[i];
				throw ERROR_THROW_IN(111, iLine, iColumn)
			}
			else if (newIn.code[*((unsigned char*)&sText[i])] == IN::I) newIn.ignor++;
			else if (newIn.code[*((unsigned char*)&sText[i])] != IN::T)
			{
				*pPtrText = newIn.code[*((unsigned char*)&sText[i])];
				pPtrText++;
			}
			else
			{
				*pPtrText = sText[i];
				pPtrText++;
			}
			if (sText[i] == '\n')
			{
				iLine++;
				iColumn = 0;
				char cNumberLine[20];
				_itoa_s(iLine, cNumberLine, 10);

				for (int i = 0; i < strlen(cNumberLine); i++) {
					*pPtrText = cNumberLine[i];
					pPtrText++;
				}
				if (iLine < 10) {
					*pPtrText = '0';
					swap(*pPtrText, *(pPtrText - 1));
					pPtrText++;
				}
				*pPtrText = ' ';
				pPtrText++;
			}
			else iColumn++;
		}
		*pPtrText = '\0';
		newIn.size = strlen((char*)newIn.text);
		short separator = 0;
		
		int position = 0;

		unsigned char* ucTextFormated = new unsigned char[(newIn.size * 2) + 1];
		pPtrText = ucTextFormated;
		bool bSpaceAdded = true;
		bool bScope = false;
		for (int i = 0; i < newIn.size; i++)
		{
			if (*(newIn.text + i) != ' ')
			{
				if (*(newIn.text + i) == '\"')
				{
					if (!bScope) bScope = true;
					else bScope = false;
					if (bScope == false) position = i;
				}

				if (((*(newIn.text + i) == ';' || *(newIn.text + i) == ',') || (*(newIn.text + i) == '+') ||
					(*(newIn.text + i) == '-') || (*(newIn.text + i) == '*') || (*(newIn.text + i) == '=') ||
					(*(newIn.text + i) == '(') || (*(newIn.text + i) == ')') || (*(newIn.text + i) == '{') ||
					(*(newIn.text + i) == '}') || (*(newIn.text + i) == '\n') || (*(newIn.text + i) == '/')||
					(*(newIn.text + i) == ':')|| (*(newIn.text + i) == '[')|| (*(newIn.text + i) == ']') || (*(newIn.text + i) == '>')
					|| (*(newIn.text + i) == '<')) && (!bScope))
				{
					if ((*(newIn.text + i) == '/') && (*(newIn.text + i + 1) == '/')) {
						while (*(newIn.text + i) != '\n') {
							i++;
							*pPtrText = *(newIn.text + i);
							continue;
							
						}
					}					

					if (*(newIn.text + i) == '\n')
					{
						*pPtrText = ' ';
						pPtrText++;
						*pPtrText = *(newIn.text + i);
						pPtrText++;
						continue;
					}
					*pPtrText = ' ';
					pPtrText++;
					*pPtrText = *(newIn.text + i);
					pPtrText++;
					*pPtrText = ' ';
					pPtrText++;
					if (!bScope) bSpaceAdded = true;
				}
				else {
					*pPtrText = *(newIn.text + i);
					pPtrText++;
					bSpaceAdded = false;
				}
			}
			else {
				if (bScope) {
					*pPtrText = ' ';
					pPtrText++;
					continue;
				}
				if (!bSpaceAdded) {
					*pPtrText = ' ';
					pPtrText++;
					bSpaceAdded = true;
				}
			}
		}
		*pPtrText = '\0';
		bSpaceAdded = false;
		newIn.ucTextFormated = new unsigned char[strlen((char*)ucTextFormated) + 1];
		pPtrText = newIn.ucTextFormated;
		for (int i = 0; i < strlen((char*)ucTextFormated); i++)
		{
			if (ucTextFormated[i] != ' ') {
				*pPtrText = ucTextFormated[i];
				pPtrText++;
				bSpaceAdded = false;
			}
			else
			{
				if (!bSpaceAdded)
				{
					*pPtrText = ' ';
					pPtrText++;
					bSpaceAdded = true;
				}
			}
		}
		*pPtrText = '\0';
		int i = 0;
		pPtrText = newIn.ucTextFormated;
		long long int iCounterLexem = 0;
		unsigned char *finishInput = newIn.ucTextFormated;

		//for (int i = 0; i < strlen((char*)finishInput); i++) {
		//	if ((((finishInput[i] == '=')|| finishInput[i] == '<'||finishInput[i] == '>'|| finishInput[i] == '!')&&(finishInput[i + 2] == '='))||(((finishInput[i] == '&'))&&(finishInput[i+2]=='&'))
		//		|| (((finishInput[i] == '|')) && (finishInput[i + 2] == '|'))) {
		//		for (int j = i + 1; j < strlen((char*)finishInput); j++) {
		//			finishInput[j] = finishInput[j + 1];
		//		}

		//	}
		//}//доп. проверка для составных условных операторов
		for (int i = 0; i < strlen((char*)newIn.ucTextFormated); i++)
		{
			if (*pPtrText == ' ') iCounterLexem++;
			pPtrText++;
		}		
	
		newIn.counterLexem = iCounterLexem;
		return newIn;
	}
}
