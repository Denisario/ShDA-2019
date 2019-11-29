#pragma once
#include "GRB.h"
#define GRB_ERROR_SERIES 600

#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'),
		6,
		Rule(//структура программы
			NS('S'), GRB_ERROR_SERIES + 0,
			2,	
			Rule::Chain(10, TS('d'), TS('i'), TS('I'), TS('('), NS('F'), TS(')'), TS('{'),NS('N'), TS('}'), NS('S')),
			Rule::Chain(5,  TS('d'), TS('M'), TS('{'), NS('N'),TS('}'))
		),

		Rule(//параметры
			NS('F'), GRB_ERROR_SERIES + 1,
			2,
			Rule::Chain(2, TS('i'), TS('I')),
			Rule::Chain(4, TS('i'), TS('I'), TS(','), NS('F'))

		),
		Rule(
			NS('N'), GRB_ERROR_SERIES+2,
			2,
			Rule::Chain(5,TS('a'), TS('i'), TS('I'),TS(';'), TS('N')),
			Rule::Chain(3,TS('r'), TS('L'), TS(';'))
		)
	);
}
