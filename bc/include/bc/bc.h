#ifndef BC_H
#define BC_H

#include <stdint.h>

typedef enum BcStatus {

	BC_STATUS_SUCCESS,

	BC_STATUS_INVALID_OPTION,
	BC_STATUS_MALLOC_FAIL,
	BC_STATUS_INVALID_PARAM,

	BC_STATUS_VM_FILE_ERR,
	BC_STATUS_VM_FILE_READ_ERR,
	BC_STATUS_VM_DIVIDE_BY_ZERO,
	BC_STATUS_VM_NEG_SQRT,
	BC_STATUS_VM_MISMATCHED_PARAMS,
	BC_STATUS_VM_UNDEFINED_FUNC,

	BC_STATUS_LEX_INVALID_TOKEN,
	BC_STATUS_LEX_NO_STRING_END,
	BC_STATUS_LEX_NO_COMMENT_END,
	BC_STATUS_LEX_EOF,

	BC_STATUS_PARSE_INVALID_TOKEN,
	BC_STATUS_PARSE_INVALID_EXPR,
	BC_STATUS_PARSE_INVALID_PRINT,
	BC_STATUS_PARSE_INVALID_FUNC,
	BC_STATUS_PARSE_EOF,
	BC_STATUS_PARSE_BUG,

} BcStatus;

void bc_error(BcStatus status);
void bc_error_file(const char* file, uint32_t line, BcStatus status);

#endif // BC_H