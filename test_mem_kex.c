#include <sys/resource.h>
#include <stdio.h>
#include "kem.h"
#include "kex.h"
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
    uint8_t pkb[CRYPTO_PUBLICKEYBYTES];
    uint8_t skb[CRYPTO_SECRETKEYBYTES];
    uint8_t pka[CRYPTO_PUBLICKEYBYTES];
    uint8_t ska[CRYPTO_SECRETKEYBYTES];
    uint8_t eska[CRYPTO_SECRETKEYBYTES];
    uint8_t uake_senda[KEX_UAKE_SENDABYTES];
    uint8_t uake_sendb[KEX_UAKE_SENDBBYTES];
    uint8_t ake_senda[KEX_AKE_SENDABYTES];
    uint8_t ake_sendb[KEX_AKE_SENDBBYTES];
    uint8_t tk[KEX_SSBYTES];
    uint8_t ka[KEX_SSBYTES];
    uint8_t kb[KEX_SSBYTES];

    // Generate static keys
    crypto_kem_keypair(pkb, skb);
    crypto_kem_keypair(pka, ska);

    // Unilaterally authenticated key exchange
    kex_uake_initA(uake_senda, tk, eska, pkb);
    kex_uake_sharedB(uake_sendb, kb, uake_senda, skb);
    kex_uake_sharedA(ka, uake_sendb, tk, eska);

    // Mutually authenticated key exchange
    kex_ake_initA(ake_senda, tk, eska, pkb);
    kex_ake_sharedB(ake_sendb, kb, ake_senda, skb, pka);
    kex_ake_sharedA(ka, ake_sendb, tk, eska, ska);

    /* Measurement and Output */
    long resource_mem_usage = (get_mem_usage() / DIV);
    printf("KEX memory usage: %ld KB\n", resource_mem_usage);

    return 0;
}
