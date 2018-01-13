#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include "erl_nif.h"

// type aliases for 32 bit and 64 bit unsigned integers
typedef uint32_t Fnv32Type;
typedef uint64_t Fnv64Type;

#define FNV_32_PRIME ((Fnv32Type)16777619u)
#define FNV_64_PRIME ((Fnv64Type)1099511628211u)

#define FNV1_32_OFFSET_BASIS ((Fnv32Type)2166136261u)
#define FNV1_64_OFFSET_BASIS ((Fnv64Type)14695981039346656037u)

Fnv32Type fnv32_hash(unsigned char *str, unsigned int length);
Fnv32Type fnv32a_hash(unsigned char *str, unsigned int length);
Fnv64Type fnv64_hash(unsigned char *str, unsigned int length);
Fnv64Type fnv64a_hash(unsigned char *str, unsigned int length);

Fnv32Type fnv32_hash(unsigned char *str, unsigned int length) {
	Fnv32Type hash 		= FNV1_32_OFFSET_BASIS;
	Fnv32Type fnv_prime 	= FNV_32_PRIME;
	unsigned int i 		= 0;
	for (i = 0; i < length; i++) {
		hash *= fnv_prime;
		hash ^= str[i];
	}
	return hash;
}

Fnv32Type fnv32a_hash(unsigned char *str, unsigned int length) {
	Fnv32Type hash 		= FNV1_32_OFFSET_BASIS;
	Fnv32Type fnv_prime 	= FNV_32_PRIME;
	unsigned int i 		= 0;
	for (i = 0; i < length; i++) {
		hash ^= str[i];
		hash *= fnv_prime;
	}
	return hash;
}

Fnv64Type fnv64_hash(unsigned char *str, unsigned int length) {
	Fnv64Type hash 		= FNV1_64_OFFSET_BASIS;
	Fnv64Type fnv_prime 	= FNV_64_PRIME;
	unsigned int i 		= 0;
	for (i = 0; i < length; i++) {
		hash *= fnv_prime;
		hash ^= str[i];
	}
	return hash;
}

Fnv64Type fnv64a_hash(unsigned char *str, unsigned int length) {
	Fnv64Type hash 		= FNV1_64_OFFSET_BASIS;
	Fnv64Type fnv_prime 	= FNV_64_PRIME;
	unsigned int i 		= 0;
	for (i = 0; i < length; i++) {
		hash ^= str[i];
		hash *= fnv_prime;
	}
	return hash;
}


static ERL_NIF_TERM fnv32(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
	ErlNifBinary bin;
	if (!enif_inspect_binary(env, argv[argc-1], &bin))
		return enif_make_badarg(env);

	Fnv32Type hash = fnv32_hash(bin.data, bin.size);
	return enif_make_uint(env, hash);
}

static ERL_NIF_TERM fnv32a(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
        ErlNifBinary bin;
	if (!enif_inspect_binary(env, argv[argc-1], &bin))
		return enif_make_badarg(env);

	Fnv32Type hash = fnv32a_hash(bin.data, bin.size);
	return enif_make_uint(env, hash);
}

static ERL_NIF_TERM fnv64(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
        ErlNifBinary bin;
	if (!enif_inspect_binary(env, argv[argc-1], &bin))
		return enif_make_badarg(env);

	Fnv64Type hash = fnv64_hash(bin.data, bin.size);
	return enif_make_uint64(env, (ErlNifUInt64)hash);
}

static ERL_NIF_TERM fnv64a(ErlNifEnv* env, int argc, const ERL_NIF_TERM argv[]) {
        ErlNifBinary bin;
	if (!enif_inspect_binary(env, argv[argc-1], &bin))
		return enif_make_badarg(env);

	Fnv64Type hash = fnv64a_hash(bin.data, bin.size);
	return enif_make_uint64(env, (ErlNifUInt64)hash);
}

static ErlNifFunc nif_funcs[] = {
	{"fnv32", 1, fnv32},
	{"fnv32a", 1, fnv32a},
	{"fnv64", 1, fnv64},
	{"fnv64a", 1, fnv64a}
};

ERL_NIF_INIT(erl_fnv,nif_funcs,NULL,NULL,NULL,NULL);
