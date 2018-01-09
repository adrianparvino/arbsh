#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "program.h"

static BcStatus bc_program_expand(BcProgram* program);
static void bc_program_list_init(BcStmtList* list);
static void bc_program_list_free(BcStmtList* list);
static int bc_program_func_cmp(void* func1, void* func2);
static void bc_program_func_free(BcFunc* func);
static int bc_program_var_cmp(void* var1, void* var2);
static void bc_program_var_free(BcVar* var);
static int bc_program_array_cmp(void* array1, void* array2);
static void bc_program_array_free(BcArray* array);

BcStatus bc_program_init(BcProgram* p) {

	BcStatus st;

	if (p == NULL) {
		return BC_STATUS_INVALID_PARAM;
	}

	p->first = malloc(sizeof(BcStmtList));

	if (p->first == NULL) {
		return BC_STATUS_MALLOC_FAIL;
	}

	bc_program_list_init(p->first);
	p->cur = p->first;

	st = bc_segarray_init(&p->funcs, sizeof(BcFunc), bc_program_func_cmp);
	if (st) {
		return st;
	}

	st = bc_segarray_init(&p->vars, sizeof(BcVar), bc_program_var_cmp);
	if (st) {
		return st;
	}

	st = bc_segarray_init(&p->arrays, sizeof(BcArray), bc_program_array_cmp);

	return st;
}

BcStatus bc_program_insert(BcProgram* p, BcStmt* stmt) {

	if (p == NULL || stmt == NULL) {
		return BC_STATUS_INVALID_PARAM;
	}

	if (p->cur->num_stmts == BC_PROGRAM_MAX_STMTS) {

		BcStatus status = bc_program_expand(p);

		if (status != BC_STATUS_SUCCESS) {
			return status;
		}
	}

	BcStmtList* cur = p->cur;
	memcpy(cur->stmts + cur->num_stmts, stmt, sizeof(BcStmt));

	return BC_STATUS_SUCCESS;
}

void bc_program_free(BcProgram* p) {

	if (p == NULL) {
		return;
	}

	BcStmtList* temp;
	BcStmtList* cur = p->first;

	while (cur != NULL) {
		temp = cur->next;
		bc_program_list_free(cur);
		cur = temp;
	}

	p->cur = NULL;
	p->first = NULL;

	uint32_t num = p->funcs.num;
	for (uint32_t i = 0; i < num; ++i) {
		bc_program_func_free(bc_segarray_item(&p->funcs, i));
	}

	num = p->vars.num;
	for (uint32_t i = 0; i < num; ++i) {
		bc_program_var_free(bc_segarray_item(&p->vars, i));
	}

	num = p->arrays.num;
	for (uint32_t i = 0; i < num; ++i) {
		bc_program_array_free(bc_segarray_item(&p->arrays, i));
	}
}

static BcStatus bc_program_expand(BcProgram* program) {

	if (program == NULL) {
		return BC_STATUS_INVALID_PARAM;
	}

	BcStmtList* next = malloc(sizeof(BcStmtList));

	if (next == NULL) {
		return BC_STATUS_MALLOC_FAIL;
	}

	bc_program_list_init(next);

	program->cur->next = next;
	program->cur = next;

	return BC_STATUS_SUCCESS;
}

static void bc_program_list_init(BcStmtList* list) {

	if (list == NULL) {
		return;
	}

	list->next = NULL;
	list->num_stmts = 0;
}

static void bc_program_list_free(BcStmtList* list) {

	if (list == NULL) {
		return;
	}

	// TODO: Write this function.
}

static int bc_program_func_cmp(void* func1, void* func2) {

	assert(func1 && func2);

	BcFunc* f1 = (BcFunc*) func1;
	char* f2name = (char*) func2;

	return strcmp(f1->name, f2name);
}

static void bc_program_func_free(BcFunc* func) {

	if (func == NULL) {
		return;
	}

	// TODO: Write this function.
}

static int bc_program_var_cmp(void* var1, void* var2) {

	assert(var1 && var2);

	BcFunc* v1 = (BcFunc*) var1;
	char* v2name = (char*) var2;

	return strcmp(v1->name, v2name);
}

static void bc_program_var_free(BcVar* var) {

	if (var == NULL) {
		return;
	}

	// TODO: Write this function.
}

static int bc_program_array_cmp(void* array1, void* array2) {

	assert(array1 && array2);

	BcFunc* a1 = (BcFunc*) array1;
	char* a2name = (char*) array2;

	return strcmp(a1->name, a2name);
}

static void bc_program_array_free(BcArray* array) {

	if (array == NULL) {
		return;
	}

	// TODO: Write this function.
}
