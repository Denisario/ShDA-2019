#include "pch.h"
#include "Log.h"
#include "Error.h"
#include "FST.h"
#include "In.h"
#include "Lexer.h"
#include "IT.h"
#include "LT.h"
#include "Parm.h"
int _tmain(int argc, _TCHAR **argv)
{
	setlocale(LC_ALL, "rus");
	Log::LOG log = Log::INITLOG;
	try
	{
		Parm::PARM parm = Parm::getParm(argc, argv);
		In::IN in = In::getin(parm.in);
		log = Log::getlog(parm.log);
		Log::WriteLog(log);
		Log::WriteParm(log, parm);
		Log::WriteIn(log, in);	
		Tables tables = createTables(in);
		Print(tables);
		Log::writeOut(parm, in);
		Log::Close(log);

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;
}