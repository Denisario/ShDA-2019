#pragma once
#include "GRB.h"
#define GRB_ERROR_SERIES 600

#define NS(n)	GRB::Rule::Chain::N(n)
#define TS(n)	GRB::Rule::Chain::T(n)
#define ISNS(n)	GRB::Rule::Chain::isN(n)

namespace GRB
{
	Greibach greibach(NS('S'), TS('$'),
		7,
		Rule(
			NS('S'), GRB_ERROR_SERIES + 1,
			2,	
			Rule::Chain(10, TS('d'), TS('t'), TS('i'), TS('('), NS('F'), TS(')'), TS('{'),NS('N'), TS('}'), NS('S')),
			Rule::Chain(5,  TS('d'), TS('m'), TS('{'), NS('N'),TS('}'))
		),

		Rule(
			NS('F'), GRB_ERROR_SERIES + 2,
			2,
			Rule::Chain(2, TS('t'), TS('i')),
			Rule::Chain(4, TS('t'), TS('i'), TS(','), NS('F'))
		),
		Rule(
			NS('N'), GRB_ERROR_SERIES+3,
			11,
			Rule::Chain(5,TS('a'), TS('t'), TS('i'),TS(';'), NS('N')),
			Rule::Chain(4,TS('a'), TS('t'), TS('i'),TS(';')),
			Rule::Chain(5,TS('i'), TS('='), NS('E'),TS(';'), NS('N')),
			Rule::Chain(4, TS('i'), TS('='), NS('E'), TS(';')),
			Rule::Chain(3,TS('r'), NS('E'), TS(';')),
			Rule::Chain(6,TS('o'), TS('('), NS('E'),TS(')'),TS(';'), NS('N')),
			Rule::Chain(5,TS('o'), TS('('), NS('E'),TS(')'),TS(';')),
			Rule::Chain(6,TS('n'), TS('('), NS('E'),TS(')'),TS(';'), NS('N')),
			Rule::Chain(5,TS('n'), TS('('), NS('E'),TS(')'),TS(';')),
			Rule::Chain(8, TS('f'), TS('('), NS('E'), TS(')'), TS('['), NS('N'), TS(']'), NS('N')),
			Rule::Chain(12, TS('f'), TS('('), NS('E'), TS(')'), TS('['), NS('N'), TS(']'),TS('s'), TS('['), NS('N'), TS(']'), NS('N'))
			
		),
		Rule(
			NS('W'), GRB_ERROR_SERIES+4,
			4,
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('i'),TS(','), NS('W')),
			Rule::Chain(3, TS('l'),TS(','), NS('W'))
		),
		Rule(
			NS('E'), GRB_ERROR_SERIES + 5,    // ошибка в выражении
			8,                               // 
			Rule::Chain(1, TS('i')),
			Rule::Chain(1, TS('l')),
			Rule::Chain(3, TS('('), NS('E'), TS(')')),
			Rule::Chain(4, TS('i'), TS('('), NS('W'), TS(')')),
			Rule::Chain(2, TS('i'), NS('M')),
			Rule::Chain(2, TS('l'), NS('M')),
			Rule::Chain(4, TS('('), NS('E'), TS(')'), NS('M')),
			Rule::Chain(5, TS('i'), TS('('), NS('W'), TS(')'), NS('M'))
		),
		Rule(
			NS('M'), GRB_ERROR_SERIES + 6,    // оператор
			10,								  //
			Rule::Chain(2, TS('+'), NS('E')),
			Rule::Chain(2, TS('-'), NS('E')),
			Rule::Chain(2, TS('*'), NS('E')),
			Rule::Chain(2, TS('/'), NS('E')),
			Rule::Chain(2, TS(':'), NS('E')),
			Rule::Chain(3, TS('+'), NS('E'), NS('M')),
			Rule::Chain(3, TS('-'), NS('E'), NS('M')),
			Rule::Chain(3, TS('*'), NS('E'), NS('M')),
			Rule::Chain(3, TS('/'), NS('E'), NS('M')),
			Rule::Chain(3, TS(':'), NS('E'), NS('M'))
		)
	);
}
