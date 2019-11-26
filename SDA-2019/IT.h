#pragma once
#include "pch.h"
#include "LT.h"
#define ID_MAXSIZE 6
#define TI_MAXSIZE 4096
#define TI_INT_DEFAULT 0x000000
#define TI_STR_DEFAULT 0x00
#define TI_NULLIDX 0xffffff
#define TI_STR_MAXSIZE 255

namespace IT
{
	enum IDDATATYPE
	{
		INT = 1, STR = 2
	};
	enum IDTYPE
	{
		V = 1,                        //переменная
		F = 2,                        //функция
		P = 3,                        //параметр
		L = 4                         //литерал
	};
	enum LITERALTYPE {
		S=1,
		D=2,
		O=3
	};
	struct Entry
	{
		int idxfirstLE;               //индекс первой строки в ТЛ
		char id[ID_MAXSIZE];          //идентификатор
		IDDATATYPE iddatatype;        //тип данных
		IDTYPE idtype;                //тип идентификатора
		LITERALTYPE littype;
		Entry* view = NULL;
		union
		{
			int vint;
			struct
			{
				char len;
				char str[TI_STR_MAXSIZE - 1];

			}vstr[TI_STR_MAXSIZE];
		}value;
	};
	struct IdTable
	{
		int maxsize;
		int size;
		Entry* table;
	};
	IdTable* Create(int size);
	void Add(IdTable* idtable, Entry);
	int GetIndxLastElement(IdTable* idtable);
	void Delete(IdTable* idtable);
}