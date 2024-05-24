#include <sys/resource.h>
#include <stdio.h>
#include "kem.h"
#include "params.h"
#include "indcpa.h"

// setting divider based on operating system
#ifdef __linux__
#define DIV 1
#elif __APPLE__
#define DIV 1000
#endif

/**
 * Gets self resource usage structure and returns max resource usage
 * @return (long) max memory usage of resource in bytes (MacOs) or kilobytes (Linux) based on operating system
 */
static long get_mem_usage(void) {
    struct rusage mem_usage;

    getrusage(RUSAGE_SELF, &mem_usage);
    return mem_usage.ru_maxrss;
}

uint8_t seed[KYBER_SYMBYTES] = {0};

int main(void) {
    /* Program */
    uint8_t pk[CRYPTO_PUBLICKEYBYTES];
    uint8_t sk[CRYPTO_SECRETKEYBYTES];
    uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
    uint8_t key[CRYPTO_BYTES];

    indcpa_keypair(pk, sk);
    indcpa_enc(ct, key, pk, seed);
    indcpa_dec(key, ct, sk);

    /* Measurement and Output */
    long resource_mem_usage = (get_mem_usage() / DIV);
    printf("IND-CPA memory usage: %ld KB\n", resource_mem_usage);

    return 0;
}
