#include "kem.h"
#include "kex.h"
#include "params.h"
#include "indcpa.h"
#include "polyvec.h"
#include "poly.h"
#include "cpucycles.h"
#include "speed_print.h"

#define NTESTS 1000

uint64_t t[NTESTS];
uint64_t tm[NTESTS];
uint8_t seed[KYBER_SYMBYTES] = {0};

int main(void)
{
  unsigned int i;
  uint8_t pk[CRYPTO_PUBLICKEYBYTES];
  uint8_t sk[CRYPTO_SECRETKEYBYTES];
  uint8_t ct[CRYPTO_CIPHERTEXTBYTES];
  uint8_t key[CRYPTO_BYTES];
  uint8_t kexsenda[KEX_AKE_SENDABYTES];
  uint8_t kexsendb[KEX_AKE_SENDBBYTES];
  uint8_t kexkey[KEX_SSBYTES];
  polyvec matrix[KYBER_K];
  poly ap;

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    gen_matrix(matrix, seed, 0);
    tm[i] = clock() - tm[i];
  }
  print_results("gen_a", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    poly_getnoise_eta1(&ap, seed, 0);
    tm[i] = clock() - tm[i];
  }
  print_results("poly_getnoise_eta1", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    poly_getnoise_eta2(&ap, seed, 0);
    tm[i] = clock() - tm[i];
  }
  print_results("poly_getnoise_eta2", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    poly_ntt(&ap);
    tm[i] = clock() - tm[i];
  }
  print_results("NTT", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    poly_invntt_tomont(&ap);
    tm[i] = clock() - tm[i];
  }
  print_results("INVNTT", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    polyvec_basemul_acc_montgomery(&ap, &matrix[0], &matrix[1]);
    tm[i] = clock() - tm[i];
  }
  print_results("polyvec_basemul_acc_montgomery", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    poly_tomsg(ct,&ap);
    tm[i] = clock() - tm[i];
  }
  print_results("poly_tomsg", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    poly_frommsg(&ap,ct);
    tm[i] = clock() - tm[i];
  }
  print_results("poly_frommsg", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    poly_compress(ct,&ap);
    tm[i] = clock() - tm[i];
  }
  print_results("poly_compress", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    poly_decompress(&ap,ct);
    tm[i] = clock() - tm[i];
  }
  print_results("poly_decompress", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    polyvec_compress(ct,&matrix[0]);
    tm[i] = clock() - tm[i];
  }
  print_results("polyvec_compress", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    polyvec_decompress(&matrix[0],ct);
    tm[i] = clock() - tm[i];
  }
  print_results("polyvec_decompress", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    indcpa_keypair(pk, sk);
    tm[i] = clock() - tm[i];
  }
  print_results("indcpa_keypair", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    indcpa_enc(ct, key, pk, seed);
    tm[i] = clock() - tm[i];
  }
  print_results("indcpa_enc", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    indcpa_dec(key, ct, sk);
    tm[i] = clock() - tm[i];
  }
  print_results("indcpa_dec", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    crypto_kem_keypair(pk, sk);
    tm[i] = clock() - tm[i];
  }
  print_results("kyber_keypair", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    crypto_kem_enc(ct, key, pk);
    tm[i] = clock() - tm[i];
  }
  print_results("kyber_encaps", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    crypto_kem_dec(key, ct, sk);
    tm[i] = clock() - tm[i];
  }
  print_results("kyber_decaps", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    kex_uake_initA(kexsenda, key, sk, pk);
    tm[i] = clock() - tm[i];
  }
  print_results("kex_uake_initA", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    kex_uake_sharedB(kexsendb, kexkey, kexsenda, sk);
    tm[i] = clock() - tm[i];
  }
  print_results("kex_uake_sharedB", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    kex_uake_sharedA(kexkey, kexsendb, key, sk);
    tm[i] = clock() - tm[i];
  }
  print_results("kex_uake_sharedA", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    kex_ake_initA(kexsenda, key, sk, pk);
    tm[i] = clock() - tm[i];
  }
  print_results("kex_ake_initA", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    kex_ake_sharedB(kexsendb, kexkey, kexsenda, sk, pk);
    tm[i] = clock() - tm[i];
  }
  print_results("kex_ake_sharedB", tm, t, NTESTS);

  for (i = 0; i < NTESTS; i++) {
    t[i] = cpucycles();
    tm[i] = clock();
    kex_ake_sharedA(kexkey, kexsendb, key, sk, sk);
    tm[i] = clock() - tm[i];
  }
  print_results("kex_ake_sharedA", tm, t, NTESTS);

  return 0;
}
