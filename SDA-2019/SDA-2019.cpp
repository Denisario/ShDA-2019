#include "pch.h"
#include "Log.h"
#include "Error.h"
#include "FST.h"
#include "In.h"
#include "Lexer.h"
#include "IT.h"
#include "LT.h"
#include "Parm.h"
#include "MFST.h"
#include "Semantics.h"
#include "ASMGenerator.h"
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
		cout << in.ucTextFormated;
		Tables tables = createTables(in);
		Print(tables);
		Semantics::startSem(tables);
		/*MFST_TRACE_START*/
		Log::Close(log);
		/*MFST::Mfst mfst(tables, GRB::getGreibach());
		mfst.start();*/
		ASMGenerator::Add();

	}
	catch (Error::ERROR e)
	{
		Log::WriteError(log, e);
	}
	system("pause");
	return 0;
}