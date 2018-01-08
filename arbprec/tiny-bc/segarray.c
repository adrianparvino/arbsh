#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "segarray.h"

static BcStatus bc_segarray_addArray(BcSegArray* sa);
static inline void bc_segarray_moveLast(BcSegArray* sa, uint32_t end1);
static void bc_segarray_move(BcSegArray* sa, uint32_t idx1, uint32_t num_elems);

BcStatus bc_segarray_init(BcSegArray* sa, size_t esize, BcSegArrayCmpFunc cmp) {

	// Check for invalid params.
	if (sa == NULL || esize == 0 || cmp == NULL) {
		return BC_STATUS_INVALID_PARAM;
	}

	// Set the fields.
	sa->esize = esize;
	sa->cmp = cmp;
	sa->num = 0;

	// Init the stack.
	BcStatus status = bc_stack_init(&sa->stack, sizeof(uint8_t*));

	// Check for error.
	if (status != BC_STATUS_SUCCESS) {
		return status;
	}

	// Add an array.
	status = bc_segarray_addArray(sa);

	return status;
}

BcStatus bc_segarrary_add(BcSegArray* sa, void* data) {

	BcStatus status;

	// Check for invalid params.
	if (sa == NULL || data == NULL) {
		return BC_STATUS_INVALID_PARAM;
	}

	// Get the insert index and split it.
	uint32_t idx = bc_segarray_find(sa, data);
	uint32_t idx1 = BC_SEGARRAY_IDX1(idx);
	uint32_t idx2 = BC_SEGARRAY_IDX2(idx);

	// Get the indices of the end.
	uint32_t end = sa->num;
	uint32_t end1 = BC_SEGARRAY_IDX1(end);
	uint32_t end2 = BC_SEGARRAY_IDX2(end);

	// If we need to expand...
	if (end2 == 0) {

		// Do the expand.
		status = bc_segarray_addArray(sa);

		// Check for error.
		if (status != BC_STATUS_SUCCESS) {
			return status;
		}

		// Move the last element of the previous array.
		if ((end1 != 0 && end2 == 0) && idx != end) {
			bc_segarray_moveLast(sa, end1);
		}
	}

	uint32_t last = BC_SEGARRAY_SEG_SIZE - 1;

	uint32_t move_idx = end2 == 0 ? end1 - 1 : end1;
	while (move_idx > idx1) {
		bc_segarray_move(sa, move_idx, last);
		bc_segarray_moveLast(sa, move_idx);
		--move_idx;
	}

	if (idx2 != last) {
		bc_segarray_move(sa, idx1, last - idx2);
	}

	memcpy(bc_segarray_item2(sa, idx1, idx2), data, sa->esize);

	return BC_STATUS_SUCCESS;
}

void* bc_segarray_item(BcSegArray* sa, uint32_t idx) {
	return bc_segarray_item2(sa, BC_SEGARRAY_IDX1(idx), BC_SEGARRAY_IDX2(idx));
}

void* bc_segarray_item2(BcSegArray* sa, uint32_t idx1, uint32_t idx2) {

	// Check for NULL or out of bounds.
	uint32_t num = sa->num;
	if (sa == NULL || idx1 > BC_SEGARRAY_IDX1(num) || idx2 >= BC_SEGARRAY_IDX2(num)) {
		return NULL;
	}

	// Get the pointer.
	uint8_t* ptr = ((uint8_t**) sa->stack.stack)[idx1];

	// Check for error.
	if (ptr == NULL) {
		return NULL;
	}

	// Calculate the return pointer.
	return ptr + sa->esize * idx2;
}

uint32_t bc_segarray_find(BcSegArray* sa, void* data) {

	// Cache this.
	BcSegArrayCmpFunc cmp = sa->cmp;

	// Set the high and low.
	uint32_t low = 0;
	uint32_t high = sa->num;

	// Loop until the index is found.
	while (low < high) {

		// Calculate the mid point.
		uint32_t mid = (low + high) / 2;

		// Get the pointer.
		uint8_t* ptr = bc_segarray_item(sa, mid);

		// Figure out what to do.
		if (cmp(ptr, data) > 0) {
			high = mid;
		}
		else {
			low = mid + 1;
		}
	}

	return low;
}

void bc_segarray_free(BcSegArray* sa) {

	// Check for NULL.
	if (sa == NULL) {
		return;
	}

	// Clear these.
	sa->esize = 0;
	sa->cmp = NULL;

	// Loop through the arrays and free them all.
	uint32_t num_arrays = BC_SEGARRAY_IDX1(sa->num - 1);
	for (uint32_t i = num_arrays - 1; i < num_arrays; --i) {
		uint8_t** ptr = bc_stack_item(&sa->stack, i);
		free(*ptr);
	}

	// Free the stack.
	bc_stack_free(&sa->stack);
}

static BcStatus bc_segarray_addArray(BcSegArray* sa) {

	// Malloc space.
	uint8_t* ptr = malloc(sa->esize * BC_SEGARRAY_SEG_SIZE);

	// Check for error.
	if (ptr == NULL) {
		return BC_STATUS_MALLOC_FAIL;
	}

	// Push the array onto the stack.
	return bc_stack_push(&sa->stack, &ptr);
}

static void bc_segarray_moveLast(BcSegArray* sa, uint32_t end1) {
	uint8_t** ptr = (uint8_t**) sa->stack.stack;
	uint8_t* dest = ptr[end1];
	uint8_t* src = ptr[end1 - 1] + sa->esize * BC_SEGARRAY_SEG_SIZE;
	memcpy(dest, src, sa->esize);
}

static void bc_segarray_move(BcSegArray* sa, uint32_t idx1, uint32_t num_elems) {

	assert(num_elems < BC_SEGARRAY_SEG_SIZE);

	uint8_t* ptr = ((uint8_t**) sa->stack.stack)[idx1];

	size_t esize = sa->esize;

	size_t move_size = esize * num_elems;

	uint8_t* dest = ptr + esize * BC_SEGARRAY_SEG_SIZE - move_size;
	uint8_t* src = dest - esize;

	memmove(dest, src, move_size);
}
