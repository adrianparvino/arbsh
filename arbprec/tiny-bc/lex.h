#include <stdlib.h>

typedef enum BcLexStatus {

	BC_LEX_STATUS_SUCCESS,

	BC_LEX_STATUS_INVALID_PARAM,

	BC_LEX_STATUS_MALLOC_FAIL,

	BC_LEX_STATUS_INVALID_TOKEN,

	BC_LEX_STATUS_NO_STRING_END,

} BcLexStatus;

typedef enum BcLexTokenType {

	BC_LEX_OP_INC,
	BC_LEX_OP_DEC,

	BC_LEX_OP_NEG,

	BC_LEX_OP_POWER,

	BC_LEX_OP_MULTIPLY,
	BC_LEX_OP_DIVIDE,
	BC_LEX_OP_MODULUS,

	BC_LEX_OP_PLUS,
	BC_LEX_OP_MINUS,

	BC_LEX_OP_ASSIGN,
	BC_LEX_OP_ASSIGN_PLUS,
	BC_LEX_OP_ASSIGN_MINUS,
	BC_LEX_OP_ASSIGN_MULTIPLY,
	BC_LEX_OP_ASSIGN_DIVIDE,
	BC_LEX_OP_ASSIGN_MODULUS,
	BC_LEX_OP_ASSIGN_POWER,

	BC_LEX_OP_REL_EQUAL,
	BC_LEX_OP_REL_LESS_EQ,
	BC_LEX_OP_REL_GREATER_EQ,
	BC_LEX_OP_REL_NOT_EQ,
	BC_LEX_OP_REL_LESS,
	BC_LEX_OP_REL_GREATER,

	BC_LEX_NEWLINE,

	BC_LEX_WHITESPACE,

	BC_LEX_LEFT_PAREN,
	BC_LEX_RIGHT_PAREN,

	BC_LEX_STRING,
	BC_LEX_LETTER,
	BC_LEX_NUMBER,

	BC_LEX_KEY_DEFINE,
	BC_LEX_KEY_BREAK,
	BC_LEX_KEY_QUIT,
	BC_LEX_KEY_LENGTH,
	BC_LEX_KEY_RETURN,
	BC_LEX_KEY_FOR,
	BC_LEX_KEY_IF,
	BC_LEX_KEY_WHILE,
	BC_LEX_KEY_SQRT,
	BC_LEX_KEY_SCALE,
	BC_LEX_KEY_IBASE,
	BC_LEX_KEY_OBASE,
	BC_LEX_KEY_AUTO,

	BC_LEX_EOF,

	BC_LEX_INVALID,

} BcLexTokenType;

typedef union BcLexData {

	char* string;

} BcLexData;

typedef struct BcLexToken {

	BcLexTokenType type;
	BcLexData data;

} BcLexToken;

typedef struct BcLex {

	const char* buffer;
	size_t idx;

} BcLex;

BcLexStatus bc_lex_init(BcLex* lex, const char* text);

BcLexStatus bc_lex_next(BcLex* lex, BcLexToken* token);


