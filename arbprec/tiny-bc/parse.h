#ifndef BC_PARSE_H
#define BC_PARSE_H

#include <stdbool.h>
#include <stdint.h>

#include "stack.h"
#include "program.h"
#include "lex.h"

#define BC_PARSE_TOP_FLAG(parse)  \
	(*((uint8_t*) bc_stack_top(&(parse)->flag_stack)))

#define BC_PARSE_FLAG_FUNC_INNER (0x01)

#define BC_PARSE_FUNC_INNER(parse)  \
	(BC_PARSE_TOP_FLAG(parse) & BC_PARSE_FLAG_FUNC_INNER)

#define BC_PARSE_FLAG_FUNC (0x02)

#define BC_PARSE_FUNC(parse)  \
	(BC_PARSE_TOP_FLAG(parse) & BC_PARSE_FLAG_FUNC)

#define BC_PARSE_FLAG_HEADER (0x04)

#define BC_PARSE_HEADER(parse)  \
	(BC_PARSE_TOP_FLAG(parse) & BC_PARSE_FLAG_HEADER)

#define BC_PARSE_FLAG_AUTO (0x08)

#define BC_PARSE_AUTO(parse)  \
	(BC_PARSE_TOP_FLAG(parse) & BC_PARSE_FLAG_AUTO)

#define BC_PARSE_FLAG_LOOP (0x10)

#define BC_PARSE_LOOP(parse)  \
	(BC_PARSE_TOP_FLAG(parse) & BC_PARSE_FLAG_LOOP)

#define BC_PARSE_FLAG_LOOP_INNER (0x20)

#define BC_PARSE_LOOP_INNER(parse) \
	(BC_PARSE_TOP_FLAG(parse) & BC_PARSE_FLAG_LOOP_INNER)

#define BC_PARSE_FLAG_IF (0x40)

#define BC_PARSE_IF(parse)  \
	(BC_PARSE_TOP_FLAG(parse) & BC_PARSE_FLAG_IF)

#define BC_PARSE_CAN_EXEC(parse)  \
	(!(BC_PARSE_TOP_FLAG(parse) & (BC_PARSE_FLAG_FUNC_INNER |  \
	                               BC_PARSE_FLAG_FUNC |        \
	                               BC_PARSE_FLAG_HEADER |      \
	                               BC_PARSE_FLAG_LOOP |        \
	                               BC_PARSE_FLAG_LOOP_INNER |  \
	                               BC_PARSE_FLAG_IF)))

// We can calculate the conversion between tokens and exprs
// by subtracting the position of the first operator in the
// lex enum and adding the position of the first in the expr
// enum. WARNING: This only works for binary operators.
#define BC_PARSE_TOKEN_TO_EXPR(type) ((type) - BC_LEX_OP_POWER + BC_EXPR_POWER)

typedef struct BcOp {

	uint8_t prec;
	bool left;

} BcOp;

typedef struct BcParse {

	BcProgram* program;
	BcLex lex;
	BcLexToken token;

	BcStack flag_stack;

	BcStack ctx_stack;

	BcFunc* func;

	BcStmt partial;

} BcParse;

BcStatus bc_parse_init(BcParse* parse, BcProgram* program);
BcStatus bc_parse_text(BcParse* parse, const char* text);

BcStatus bc_parse_parse(BcParse* parse, BcProgram* program);

void bc_parse_free(BcParse* parse);

#endif // BC_PARSE_H
