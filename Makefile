CC ?= /usr/bin/cc
CFLAGS += -Wall -Wextra -Wpedantic -Wmissing-prototypes -Wredundant-decls -Wshadow -Wpointer-arith -O3 -fomit-frame-pointer
NISTFLAGS += -Wno-unused-result -O3 -fomit-frame-pointer
RM = /bin/rm
OUTDIR = test/

SOURCES = kex.c kem.c indcpa.c polyvec.c poly.c ntt.c cbd.c reduce.c verify.c
SOURCESKECCAK = $(SOURCES) fips202.c symmetric-shake.c
HEADERS = params.h kex.h kem.h indcpa.h polyvec.h poly.h ntt.h cbd.h reduce.c verify.h symmetric.h
HEADERSKECCAK = $(HEADERS) fips202.h

.PHONY: all speed memory clean

all: \
  test_kyber512 \
  test_kyber768 \
  test_kyber1024 \
  test_kex512 \
  test_kex768 \
  test_kex1024 \
  test_vectors512 \
  test_vectors768 \
  test_vectors1024 \
  test_speed512 \
  test_speed768 \
  test_speed1024 \
  test_mem_indcpa512 \
  test_mem_indcpa768 \
  test_mem_indcpa1024 \
  test_mem_kem512 \
  test_mem_kem768 \
  test_mem_kem1024 \
  test_mem_kex512 \
  test_mem_kex768 \
  test_mem_kex1024

speed: \
  test_speed512 \
  test_speed768 \
  test_speed1024

memory: \
  test_mem_indcpa512 \
  test_mem_indcpa768 \
  test_mem_indcpa1024 \
  test_mem_kem512 \
  test_mem_kem768 \
  test_mem_kem1024 \
  test_mem_kex512 \
  test_mem_kex768 \
  test_mem_kex1024

$(OUTDIR):
	mkdir -p $(OUTDIR)

test_kyber512: $(SOURCESKECCAK) $(HEADERSKECCAK) test_kyber.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=2 $(SOURCESKECCAK) randombytes.c test_kyber.c -o $(OUTDIR)test_kyber512

test_kyber768: $(SOURCESKECCAK) $(HEADERSKECCAK) test_kyber.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=3 $(SOURCESKECCAK) randombytes.c test_kyber.c -o $(OUTDIR)test_kyber768

test_kyber1024: $(SOURCESKECCAK) $(HEADERSKECCAK) test_kyber.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=4 $(SOURCESKECCAK) randombytes.c test_kyber.c -o $(OUTDIR)test_kyber1024

test_kex512: $(SOURCESKECCAK) $(HEADERSKECCAK) test_kex.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=2 $(SOURCESKECCAK) randombytes.c test_kex.c -o $(OUTDIR)test_kex512

test_kex768: $(SOURCESKECCAK) $(HEADERSKECCAK) test_kex.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=3 $(SOURCESKECCAK) randombytes.c test_kex.c -o $(OUTDIR)test_kex768

test_kex1024: $(SOURCESKECCAK) $(HEADERSKECCAK) test_kex.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=4 $(SOURCESKECCAK) randombytes.c test_kex.c -o $(OUTDIR)test_kex1024

test_vectors512: $(SOURCESKECCAK) $(HEADERSKECCAK) test_vectors.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=2 $(SOURCESKECCAK) test_vectors.c -o $(OUTDIR)test_vectors512

test_vectors768: $(SOURCESKECCAK) $(HEADERSKECCAK) test_vectors.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=3 $(SOURCESKECCAK) test_vectors.c -o $(OUTDIR)test_vectors768

test_vectors1024: $(SOURCESKECCAK) $(HEADERSKECCAK) test_vectors.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=4 $(SOURCESKECCAK) test_vectors.c -o $(OUTDIR)test_vectors1024

test_speed512: $(SOURCESKECCAK) $(HEADERSKECCAK) cpucycles.h cpucycles.c speed_print.h speed_print.c test_speed.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=2 $(SOURCESKECCAK) randombytes.c cpucycles.c speed_print.c test_speed.c -o $(OUTDIR)test_speed512

test_speed768: $(SOURCESKECCAK) $(HEADERSKECCAK) cpucycles.h cpucycles.c speed_print.h speed_print.c test_speed.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=3 $(SOURCESKECCAK) randombytes.c cpucycles.c speed_print.c test_speed.c -o $(OUTDIR)test_speed768

test_speed1024: $(SOURCESKECCAK) $(HEADERSKECCAK) cpucycles.h cpucycles.c speed_print.h speed_print.c test_speed.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=4 $(SOURCESKECCAK) randombytes.c cpucycles.c speed_print.c test_speed.c -o $(OUTDIR)test_speed1024

test_mem_indcpa512: $(SOURCESKECCAK) $(HEADERSKECCAK) test_mem_indcpa.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=2 $(SOURCESKECCAK) randombytes.c test_mem_indcpa.c -o $(OUTDIR)test_mem_indcpa512

test_mem_indcpa768: $(SOURCESKECCAK) $(HEADERSKECCAK) test_mem_indcpa.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=3 $(SOURCESKECCAK) randombytes.c test_mem_indcpa.c -o $(OUTDIR)test_mem_indcpa768

test_mem_indcpa1024: $(SOURCESKECCAK) $(HEADERSKECCAK) test_mem_indcpa.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=4 $(SOURCESKECCAK) randombytes.c test_mem_indcpa.c -o $(OUTDIR)test_mem_indcpa1024

test_mem_kem512: $(SOURCESKECCAK) $(HEADERSKECCAK) test_mem_kem.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=2 $(SOURCESKECCAK) randombytes.c test_mem_kem.c -o $(OUTDIR)test_mem_kem512

test_mem_kem768: $(SOURCESKECCAK) $(HEADERSKECCAK) test_mem_kem.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=3 $(SOURCESKECCAK) randombytes.c test_mem_kem.c -o $(OUTDIR)test_mem_kem768

test_mem_kem1024: $(SOURCESKECCAK) $(HEADERSKECCAK) test_mem_kem.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=4 $(SOURCESKECCAK) randombytes.c test_mem_kem.c -o $(OUTDIR)test_mem_kem1024

test_mem_kex512: $(SOURCESKECCAK) $(HEADERSKECCAK) test_mem_kex.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=2 $(SOURCESKECCAK) randombytes.c test_mem_kex.c -o $(OUTDIR)test_mem_kex512

test_mem_kex768: $(SOURCESKECCAK) $(HEADERSKECCAK) test_mem_kex.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=3 $(SOURCESKECCAK) randombytes.c test_mem_kex.c -o $(OUTDIR)test_mem_kex768

test_mem_kex1024: $(SOURCESKECCAK) $(HEADERSKECCAK) test_mem_kex.c randombytes.c | $(OUTDIR)
	$(CC) $(CFLAGS) -DKYBER_K=4 $(SOURCESKECCAK) randombytes.c test_mem_kex.c -o $(OUTDIR)test_mem_kex1024

clean:
	-$(RM) -rf *.gcno *.gcda *.lcov *.o *.so
	-$(RM) -rf $(OUTDIR)test_kyber512
	-$(RM) -rf $(OUTDIR)test_kyber768
	-$(RM) -rf $(OUTDIR)test_kyber1024
	-$(RM) -rf $(OUTDIR)test_kex512
	-$(RM) -rf $(OUTDIR)test_kex768
	-$(RM) -rf $(OUTDIR)test_kex1024
	-$(RM) -rf $(OUTDIR)test_vectors512
	-$(RM) -rf $(OUTDIR)test_vectors768
	-$(RM) -rf $(OUTDIR)test_vectors1024
	-$(RM) -rf $(OUTDIR)test_speed512
	-$(RM) -rf $(OUTDIR)test_speed768
	-$(RM) -rf $(OUTDIR)test_speed1024
	-$(RM) -rf $(OUTDIR)test_mem_indcpa512
	-$(RM) -rf $(OUTDIR)test_mem_indcpa768
	-$(RM) -rf $(OUTDIR)test_mem_indcpa1024
	-$(RM) -rf $(OUTDIR)test_mem_kem512
	-$(RM) -rf $(OUTDIR)test_mem_kem768
	-$(RM) -rf $(OUTDIR)test_mem_kem1024
	-$(RM) -rf $(OUTDIR)test_mem_kex512
	-$(RM) -rf $(OUTDIR)test_mem_kex768
	-$(RM) -rf $(OUTDIR)test_mem_kex1024
	-$(RM) -rf $(OUTDIR)