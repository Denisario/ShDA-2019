#pragma once
#include "pch.h"
using namespace std;

#define ERROR_THROW(id) Error::getError(id);	//throw ERROR_THROW(id)
#define ERROR_THROW_IN(id, line, column) Error::getErrorIn(id, line, column);	//throw ERROR_TROW(id,line, column)
#define ERROR_ENTRY(id,m) {id, m,{-1,-1}}		//элемент таблицы ошибок
#define ERROR_MAXSIZE_MESSAGE 200				//длина макс сообщения об ошибке
#define ERROR_ENTRY_NODEF(id) ERROR_ENTRY(id,"Неопред ошибка")					//-1 неопред элемент табл ошибок
//#define ERROR_ENTRY_NODEF10(id) - 10 неопределеных	элементы табл ошибок
#define ERROR_ENTRY_NODEF10(id) ERROR_ENTRY_NODEF(id+0), ERROR_ENTRY_NODEF(id+1), \
								ERROR_ENTRY_NODEF(id+2), ERROR_ENTRY_NODEF(id+3), \
								ERROR_ENTRY_NODEF(id+4), ERROR_ENTRY_NODEF(id+5), \
								ERROR_ENTRY_NODEF(id+6), ERROR_ENTRY_NODEF(id+7), \
								ERROR_ENTRY_NODEF(id+8), ERROR_ENTRY_NODEF(id+9)
//#define ERROR_ENTRY_NODEF100(id) - 100 неопределеных элементы табл ошибок
#define ERROR_ENTRY_NODEF100(id) ERROR_ENTRY_NODEF10(id+0), ERROR_ENTRY_NODEF10(id+10), ERROR_ENTRY_NODEF10(id+20), \
								ERROR_ENTRY_NODEF10(id+30), ERROR_ENTRY_NODEF10(id+40), ERROR_ENTRY_NODEF10(id+50), \
								ERROR_ENTRY_NODEF10(id+60), ERROR_ENTRY_NODEF10(id+70), ERROR_ENTRY_NODEF10(id+80), \
								ERROR_ENTRY_NODEF10(id+90)
#define ERROR_MAX_ENTRY 1000					//кол-во элементов в табл ошибок

namespace Error {
	struct ERROR {								//тип исключения для throw ERROR_THROW | ERROR_THROW_IN и catch(ERROR)
		int id;									//код ошибки
		char message[200];                      //сообщение об ошибке
		struct IN {								//расширение для ошибок при обработке входных данных
			short line;							//номер строки
			short column;						//номер позиции в строке
		}inext;
	};
	ERROR getError(int id);								//сформировать	ERROR для ERROR_THROW
	ERROR getErrorIn(int id, int line, int column);		//сформировать	ERROR для ERROR_THROW_IN
}