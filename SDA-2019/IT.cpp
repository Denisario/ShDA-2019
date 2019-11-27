#include "pch.h"
#include "Lexer.h"
#include "IT.h"
#include "Error.h"
#include <iomanip>
using namespace IT;
IdTable* IT::Create(int size) {
	IdTable* newIdTable = new IdTable;
	newIdTable->maxsize = size;
	newIdTable->table = new Entry[size];
	newIdTable->size = 0;
	return newIdTable;
}

void IT::Add(IdTable * idtable, Entry newEntry)
{
	if (idtable->size > idtable->maxsize) throw ERROR_THROW(200);
		idtable->table[idtable->size] = newEntry;
	idtable->size++;
}

int IT::GetIndxLastElement(IdTable * idtable)
{
	return (idtable->size - 1);
}

void IT::Delete(IdTable* idtable)
{
	delete idtable->table;
	delete idtable;
}


