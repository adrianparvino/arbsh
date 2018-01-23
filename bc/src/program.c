#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <arbprec/arbprec.h>

#include <bc/program.h>
#include <bc/parse.h>

BcStatus bc_program_init(BcProgram* p, const char* file) {

	BcStatus st;

	if (p == NULL) {
		return BC_STATUS_INVALID_PARAM;
	}

	p->file = file;

	p->list = bc_list_create();

	if (!p->list) {
		return BC_STATUS_MALLOC_FAIL;
	}

	st = bc_segarray_init(&p->funcs, sizeof(BcFunc), bc_func_free, bc_func_cmp);

	if (st) {
		goto func_err;
	}

	st = bc_segarray_init(&p->vars, sizeof(BcVar), bc_var_free, bc_var_cmp);

	if (st) {
		goto var_err;
	}

	st = bc_segarray_init(&p->arrays, sizeof(BcArray),
	                      bc_array_free, bc_array_cmp);

	if (st) {
		goto array_err;
	}

	st = bc_stack_init(&p->ctx_stack, sizeof(BcStmtList*), NULL);

	if (st) {
		goto stack_err;
	}

	return st;

stack_err:

	bc_segarray_free(&p->arrays);

array_err:

	bc_segarray_free(&p->vars);

var_err:

	bc_segarray_free(&p->funcs);

func_err:

	bc_list_free(p->list);
	p->list = NULL;

	return st;
}

BcStatus bc_program_func_add(BcProgram* p, BcFunc* func) {

	if (!p || !func) {
		return BC_STATUS_INVALID_PARAM;
	}

	return bc_segarray_add(&p->funcs, func);
}

BcStatus bc_program_var_add(BcProgram* p, BcVar* var) {

	if (!p || !var) {
		return BC_STATUS_INVALID_PARAM;
	}

	return bc_segarray_add(&p->vars, var);
}

BcStatus bc_program_array_add(BcProgram* p, BcArray* array) {

	if (!p || !array) {
		return BC_STATUS_INVALID_PARAM;
	}

	return bc_segarray_add(&p->arrays, array);
}

BcStatus bc_program_exec(BcProgram* p) {
	// TODO: Write this function.

	return BC_STATUS_SUCCESS;
}

void bc_program_free(BcProgram* p) {

	if (p == NULL) {
		return;
	}

	bc_list_free(p->list);

	bc_segarray_free(&p->funcs);
	bc_segarray_free(&p->vars);
	bc_segarray_free(&p->arrays);

	bc_stack_free(&p->ctx_stack);
}
