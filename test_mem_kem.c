#include <sys/resource.h>
#include <stdio.h>
#include "kem.h"
#include "params.h"

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

int main(void) {
    /* Program */
    uint8_t pk[CRYPTO_PUBLICKEYBYTES];
    uint8_t sk[CRYPTO_SECRETKEYBYTES];
    uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
    uint8_t key[CRYPTO_BYTES];

    crypto_kem_keypair(pk, sk);
    crypto_kem_enc(ct, key, pk);
    crypto_kem_dec(key, ct, sk);

    /* Measurement and Output */
    long resource_mem_usage = (get_mem_usage() / DIV);
    printf("KEM memory usage: %ld KB\n", resource_mem_usage);

    return 0;
}
