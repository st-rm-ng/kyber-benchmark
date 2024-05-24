# Kyber Benchmark
This project is a part of bachelor's thesis **Lattice-based Post-Quantum Cryptography**.

---

## Abstract
The concept of quantum computing is one of the most important technologies of the near future, and with it comes new challenges in the field of cybersecurity. Quantum computers are capable of compromising almost all current public-key encryption systems. For this reason, quantum-resistant cryptographic algorithms, tools, techniques, and strategies have begun to be developed and implemented to protect our ICT infrastructure. One of these algorithms is CRYSTALS-Kyber, which is based on lattices and has been selected for the NIST PQC Standardization Process. This program is optimised version of CRYSTALS-Kyber [official reference implementation](https://github.com/pq-crystals/kyber) and the aim of this implementation is to make it as small as possible to be able to test is on various different devices with various CPU architecture and various operating systems.

---

## Prerequisities
The program requires the `OpenSSL` library for some tests to work, which can be installed in the following ways:

Using `APT`
```bash
sudo apt install openssl 
```

Using `Homebrew`
```bash
brew install openssl 
```

---

## Tests compilation
The project can be compiled using tool `Make` as a whole or by the type of individual tests:

All tests
```bash
make
```

Tests of time complexity
```bash
make speed
```

Tests of spacial complexity
```bash
make memory
```

---

## Executables
These produce executable files in `test/` folder:
```commandline
test/test_kyber$ALG
test/test_kex$ALG
test/test_vectors$ALG
test/test_speed$ALG
test/test_mem_indcpa$ALG
test/test_mem_kem$ALG
test/test_mem_kex$ALG
```
Where `$ALG` stands for parameter sets `512`, `768` and `1024`.
- `test_kyber$ALG` tests 1000 times to generate keys, encapsulate a random key and correctly decapsulate it again. Also, the program tests that the keys cannot correctly be decapsulated using a random secret key or a ciphertext where a single random byte was randomly distorted in order to test for trivial failures of the CCA security. The program will abort with an error message and return 1 if there was an error. Otherwise it will output the key and ciphertext sizes and return 0.
- `test/test_kex$ALG` tests the authenticated key exchange schemes derived from the Kyber KEM.
- `test/test_vectors$ALG` generates 10000 sets of test vectors containing keys, ciphertexts and shared secrets whose byte-strings are output in hexadecimal. The required random bytes come from a simple deterministic expansion of a fixed seed defined in `test_vectors.c`.
- `test/test_speed$ALG` reports the median and average cycle counts and time in milliseconds of 1000 executions of various internal functions and functions for key generation, encapsulation and decapsulation.
- `test/test_mem_indcpa$ALG` tests and reports how much space (kilobytes) in operation memory (RAM) takes full process of encryption.
- `test/test_mem_kem$ALG` tests and reports how much space (kilobytes) in operation memory (RAM) takes full process of encapsulation.
- `test/test_mem_kex$ALG` tests and reports how much space (kilobytes) in operation memory (RAM) takes full process of key exchange.

---

## License
This project is licensed by [Public Domain](https://creativecommons.org/share-your-work/public-domain/cc0/) or [Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0.html) license.