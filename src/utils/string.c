#ifndef _STRING_C_
#define _STRING_C_

#include <assert.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "arena.c"

#define min(a, b) (((a) < (b)) ? (a) : (b))

typedef struct {
	char* data;
	size_t size;
} string;

string string_create(arena *a, size_t size) {
	assert(a != NULL);
	assert(size != 0);

	char *data = arena_allocate(a, size + 1);
	data[size] = '\0';
	string s = {.data = data, .size = size};
	return s;
}

string string_explicit(arena *a, char chars[]) {
	assert(a != NULL);
	
	size_t size = strlen(chars);
	char *data = arena_allocate(a, size + 1);
	for (size_t i = 0; i < size + 1; i++) {
		data[i] = chars[i];
	}
	string s = {.data = data, .size = size};
	return s;
}

char string_get(string s, size_t i) {
	assert(i < s.size);
	
	return s.data[i];
}

void string_set(string s, size_t i, char c) {
	assert(i < s.size);
	
	s.data[i] = c;
}

string string_copy(arena *a, string s) {
	assert(a != NULL);

	char *data_copy = arena_allocate(a, s.size + 1);
	for (size_t i = 0; i < s.size + 1; i++) {
		data_copy[i] = s.data[i];
	}

	string s_copy = {.data = data_copy, .size = s.size};
	return s_copy;
}

string string_concat(arena *a, string s1, string s2) {
	assert(a != NULL);

	char *data_concat = arena_allocate(a, s1.size + s2.size + 1);
	for (size_t i = 0; i < s1.size; i++) {
		data_concat[i] = s1.data[i];
	}
	for (size_t i = 0; i < s2.size + 1; i++) {
		data_concat[i + s1.size] = s2.data[i];
	}

	string s_concat = {.data = data_concat, .size = s1.size + s2.size};
	return s_concat;
}

string string_slice(string s, size_t start, size_t end) {
	assert(start < s.size);
	assert(end <= s.size);
	assert(start < end);

	string s_slice = {.data = s.data + start, .size = end - start};
	return s_slice;
}

#endif
