#include"pch.h"
#include"Parm.h"
#include"Error.h"
#include<iostream>
using namespace std;
using namespace Parm;

PARM Parm::getParm(int argc, _TCHAR * argv[]) {
	PARM parm;
	wcscpy_s(parm.in, L"");
	wcscpy_s(parm.out, L"");
	wcscpy_s(parm.log, L"");
	if (argc == 1)
	{
		throw ERROR_THROW(100);
	}
	for (int i = 1; i < argc; i++)
	{
		if (wcslen(argv[i]) >= PARM_MAX_SIZE) {
			throw ERROR_THROW(104);
		}
		else if (wcsstr(argv[i], PARM_IN) == argv[i]) {
			wcscpy_s(parm.in, argv[i] + wcslen(PARM_IN));
		}
		else if (wcsstr(argv[i], PARM_OUT) == argv[i]) {
			wcscpy_s(parm.out, argv[i] + wcslen(PARM_OUT));
		}
		if (wcsstr(argv[i], PARM_LOG) == argv[i]) {
			wcscpy_s(parm.log, argv[i] + wcslen(PARM_LOG));
		}
	}
	if (wcslen(parm.in) == 0) {
		throw ERROR_THROW(100);
	}
	if (wcslen(parm.out) == 0) {
		if (wcslen(parm.in) + wcslen(PARM_OUT_DEFAULT_EXT) >= PARM_MAX_SIZE) {
			throw ERROR_THROW(104);
		}

		wcsncat_s(parm.out, PARM_OUT_DEFAULT_EXT, 7);

	}
	if (wcslen(parm.log) == 0) {
		if (wcslen(parm.in) + wcslen(PARM_LOG_DEFAULT_EXT) >= PARM_MAX_SIZE) {
			throw ERROR_THROW(104);
		}
		wcsncat_s(parm.log, PARM_LOG_DEFAULT_EXT, 7);
	}
	return parm;
}