#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include "c_kzg_4844.h"

#ifdef WIN32
#define DLLEXPORT __declspec(dllexport)
#else
#define DLLEXPORT 
#endif

DLLEXPORT KZGSettings* load_trusted_setup_wrap(const char* file);

DLLEXPORT void free_trusted_setup_wrap(KZGSettings *s);

DLLEXPORT void blob_to_kzg_commitment_wrap(uint8_t out[48], const uint8_t blob[FIELD_ELEMENTS_PER_BLOB * 32], const KZGSettings *s);

DLLEXPORT int verify_aggregate_kzg_proof_wrap(const uint8_t blobs[], const uint8_t commitments[], size_t n, const uint8_t proof[48], const KZGSettings *s);

DLLEXPORT C_KZG_RET compute_aggregate_kzg_proof_wrap(uint8_t out[48], const uint8_t blobs[], size_t n, const KZGSettings *s);

DLLEXPORT int verify_kzg_proof_wrap(const uint8_t c[48], const uint8_t x[32], const uint8_t y[32], const uint8_t p[48], KZGSettings *s);
