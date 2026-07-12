#ifndef _ARENA_C_
#define _ARENA_C_

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#define max(a, b) (((a) > (b)) ? (a) : (b))

typedef struct arena_s {
	void *start;
	size_t capacity;
	size_t size;
	struct arena_s *next;
} arena;

arena *arena_create(size_t capacity) {
	arena *a = malloc(sizeof(arena));

	if(capacity == 0) {
		a->start = NULL;
	}
	else {
		a->start = malloc(capacity);
	}
	
	a->capacity = capacity;
	a->size = 0;
	a->next = NULL;

	return a;
}

void arena_delete(arena *a) {
	if(a != NULL) {
		if(a->start != NULL) {
			free(a->start);
		}
		arena_delete(a->next);
		free(a);
	}
}

void arena_clear(arena *a) {
	if(a != NULL) {
		a->size = 0;
		arena_clear(a->next);
	}
}

void *arena_allocate(arena *a, size_t size) {
	assert(a != NULL);
	assert(size != 0);
	
	if(a->start == NULL) {
		a->start = malloc(size);
		a->capacity = size;
	}

	if(a->size + size <= a->capacity) {
		void *res = a->start + a->size;
		a->size += size;
		return res;
	}
	
	if(a->next != NULL) {
		return arena_allocate(a->next, size);
	}

	a->next = arena_create(max(a->capacity, size));

	return arena_allocate(a->next, size);
}

#endif
