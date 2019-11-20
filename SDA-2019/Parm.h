#pragma once
#include <tchar.h>
#define PARM_IN L"-in:"			//ключ для файла исходного кода
#define PARM_OUT L"-out:"		//ключ для файла объектоного кода
#define PARM_LOG L"-log:"		//ключ для файла журнала
#define PARM_MAX_SIZE 100		//максимальная длина строки параметра
#define PARM_OUT_DEFAULT_EXT L"out.txt"	//расширение файла объектоного кода по умолчанию
#define PARM_LOG_DEFAULT_EXT L"log.txt"	//расширение файла протокола по умлочанию

namespace Parm {					//обработка входных параметров
	struct PARM {				//входные параметры
		wchar_t in[PARM_MAX_SIZE];		//-in: имя файла исходного кода
		wchar_t out[PARM_MAX_SIZE];		//-out: имя файла исходного кода
		wchar_t log[PARM_MAX_SIZE];		//-log: имя файла исходного кода
	};
	//СФОРМИРОВАТЬ STRUCT PARM НА ОСНОВЕ ПАРАМЕТРОВ ФУНКЦИИ main
	PARM getParm(int argc, _TCHAR* argv[]);
}
