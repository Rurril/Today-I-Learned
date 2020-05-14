#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "RLizard.h"
#include "randombytes.h"
#include "sha512.h"

uint16_t seed[PublicKey];
uint16_t count = 0;

// Sample code for generating keys
#ifdef NOISE_D1
#define SAMPLE_DG Sample_D1
const uint16_t CDF_TABLE[4] = { 190, 437, 504, 511 }; // out of [0, 511]
const uint8_t TABLE_LENGTH = 4;

uint16_t SAMPLE_DG() {
	uint16_t rnd = seed[count == PublicKey ? count = 0 : count++] & 0x01ff;
	uint16_t sign = seed[count == PublicKey ? count = 0 : count++] & 0x01;
	uint16_t sample = 0;
	for (uint8_t i = 0; i < TABLE_LENGTH - 1; ++i) {
		sample += (CDF_TABLE[i] - rnd) >> 15;
	}
	sample = ((-sign) ^ sample) + sign;
	return sample;
}
#endif
#ifdef NOISE_D2
#define SAMPLE_DG Sample_D2
const uint16_t CDF_TABLE[6] = { 279, 722, 941, 1009, 1022, 1023 }; // out of [0, 1023]
const size_t TABLE_LENGTH = 6;

uint16_t Sample_D2() {
	uint16_t rnd = seed[count == PublicKey ? count = 0 : count++] & 0x03ff;
	uint16_t sign = seed[count == PublicKey ? count = 0 : count++] & 0x01;
	uint16_t sample = 0;
	for (size_t i = 0; i < TABLE_LENGTH - 1; ++i) {
		sample += (CDF_TABLE[i] - rnd) >> 15;
	}
	sample = ((-sign) ^ sample) + sign;
	return sample;
}
#endif
#ifdef NOISE_D3
#define SAMPLE_DG Sample_D3
const uint16_t CDF_TABLE[8] = { 407, 1127, 1623, 1889, 2000, 2036, 2045, 2047 }; // out of [0, 2047]
const size_t TABLE_LENGTH = 8;

uint16_t Sample_D3() {
	uint16_t rnd = seed[count == PublicKey ? count = 0 : count++] & 0x07ff;
	uint16_t sign = seed[count == PublicKey ? count = 0 : count++] & 0x01;
	uint16_t sample = 0;
	for (size_t i = 0; i < TABLE_LENGTH - 1; ++i) {
		sample += (CDF_TABLE[i] - rnd) >> 15;
	}
	sample = ((-sign) ^ sample) + sign;
	return sample;
}
#endif
#ifdef NOISE_D4
#define SAMPLE_DG Sample_D4
const uint16_t CDF_TABLE[10] = { 154, 443, 676, 838, 936, 987, 1010, 1019, 1022, 1023 }; // out of [0, 1023]
const size_t TABLE_LENGTH = 10;

uint16_t Sample_D4() {
	uint16_t rnd = seed[count == PublicKey ? count = 0 : count++] & 0x03ff;
	uint16_t sign = seed[count == PublicKey ? count = 0 : count++] & 0x01;
	uint16_t sample = 0;
	for (size_t i = 0; i < TABLE_LENGTH - 1; ++i) {
		sample += (CDF_TABLE[i] - rnd) >> 15;
	}
	sample = ((-sign) ^ sample) + sign;
	return sample;
}
#endif


/**
  * @param	pk		[in] public key for encryption. pk = (a, b)
  * @param	sk		[in] private key for decryption sk = (s, t)
  */
void crypto_kem_keypair(unsigned char *pk, unsigned char *sk) {
    uint8_t count1 = 0;
    uint8_t hw = 0;
    uint16_t neg_start = 0;
    uint8_t back_position = HS;

    uint16_t seed1[32]; // 수정 1,2번 
	uint8_t sk_t[LWE_N] = { 0 };
    uint16_t pk_a[LWE_N];
    uint16_t pk_b[LWE_N];

    uint16_t i = 0;
    uint8_t j = 0;


    // Generate a random polynomial a
    randombytes((unsigned char*)pk_a, PublicKey);
    for (i = 0; i < LWE_N; ++i) {
        pk_a[i] <<= _16_LOG_Q;
    }


   // Initialize b as an error polynomial e
    // randombytes((unsigned char*)seed, PublicKey * 2);
    for (i = 0; i < LWE_N; ++i) {
        pk_b[i] = SAMPLE_DG() << _16_LOG_Q;
    }

	// Generate a random polynomial seed1
    randombytes((unsigned char*)seed1, 32);


    // Set a secret polynomial s
    while (hw < HS) {
        i = seed1[count1++] & (LWE_N - 1);
        if (sk_t[i] == 0) {
            sk_t[i] = (seed1[count1++] & 0x02) - 1;
            hw++;
        }
        if (count1 >= 15) {
            randombytes((unsigned char*)seed1, 32);
            count1 = 0;
        }
    }


	// Generate a secret polynomial s_idx
    for (i = 0; i < LWE_N; ++i) {
        if (sk_t[i] == 0x01)
            ((uint16_t*)sk)[neg_start++] = i;
        else if (sk_t[i] == 0xff)
            ((uint16_t*)sk)[--back_position] = i;
    }
    sk[(HS * 2) + (LWE_N / 8)] = (unsigned char)neg_start;


    // // Generate a random vector t = sk + HS * 2
    // randombytes(sk + HS * 2, LWE_N / 8);


    // Add -a * s to b. Resulting b = -a * s + e
    for (j = 0; j < HS; ++j) {
        uint16_t deg = ((uint16_t*)sk)[j];
        uint16_t branch = (2 * ((j - neg_start) >> sft & 0x1) - 1);

        ((uint16_t*)sk)[j] = (sk[j * 2] << 8 | sk[j * 2 + 1]);

        for (i = 0; i < LWE_N - deg; ++i)
			pk_b[deg + i] -= branch * pk_a[i];
        for (i = LWE_N - deg; i < LWE_N; ++i)
			pk_b[deg + i - LWE_N] += branch * pk_a[i];
    }

    for (i = 0; i < LWE_N; ++i) {
        pk[i * 2] = pk_a[i] >> 8;
        pk[i * 2 + 1] = pk_a[i] & 0xff;
        pk[PublicKey + (i * 2)] = pk_b[i] >> 8;
        pk[PublicKey + (i * 2 + 1)] = pk_b[i] & 0xff;
	}

}




/**
  * @param	ct		[out] data to be encrypted. ct = (c1, c2, d)
  * @param	ss		[out] shared secret
  * @param	pk		[in] public key for encryption. pk = (a, b)
  */
void crypto_kem_enc(unsigned char *ct, unsigned char *ss, unsigned char *pk) {
	uint16_t i, j;
	uint8_t hw = 0;
    int neg_start = 0, back_position = HR;

	uint8_t r[LWE_N] = { 0, };
	uint16_t r_idx[HR];
	uint16_t c1[LWE_N] = { 0, };
	uint16_t c2[LWE_N] = { 0, };

    uint16_t pk_a[LWE_N];
    uint16_t pk_b[LWE_N];

	uint64_t hash[LAMBDA / 32];
	uint64_t *hash_t = NULL;
	uint64_t delta[LWE_N / 64];

	TupleElement tuple;
	unsigned char *S = "";


    // Generate a polynomial delta
    randombytes((unsigned char*)delta, LWE_N / 8);


	// Compute r = H(delta)
	hash_t = (uint64_t *)calloc(LWE_N >> 6, sizeof(uint64_t));
	tuple.input = (unsigned char*)delta;
	tuple.inputBitLen = LWE_N;
	TupleHash256(&tuple, 1, (unsigned char*)hash_t, LWE_N, S, strlen(S) * 8);


	#if defined(RING_CATEGORY1) || defined(RING_CATEGORY3_N1024)
		i = 0;
		do {
			j = (uint16_t)hash_t[i] & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 10) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 12) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 22) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 24) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 34) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 36) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 46) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 48) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 58) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			i++;
			if (i == LWE_N / 64) {
				i = 0;
				tuple.input = (unsigned char*)hash_t;
				tuple.inputBitLen = LWE_N;
				TupleHash256(&tuple, 1, (unsigned char*)hash_t, LWE_N, S, strlen(S) * 8);
			}
		} while (hw < HR);
	#endif
	#if defined(RING_CATEGORY3_N2048) || defined(RING_CATEGORY5)
		i = 0;
		do {
			j = (uint16_t)hash_t[i] & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 11) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 13) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 24) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 26) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 37) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 39) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 50) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			i++;
			if (i == LWE_N / 64) {
				i = 0;
				tuple.input = (unsigned char*)hash_t;
				tuple.inputBitLen = LWE_N;
				TupleHash256(&tuple, 1, (unsigned char*)hash_t, LWE_N, S, strlen(S) * 8);
			}
		} while (hw < HR);
	#endif
	

	// Generate r_idx
	for (j = 0; j < LWE_N; ++j) {
		if (r[j] == 0x01)
			r_idx[neg_start++] = j;
		else if (r[j] == 0xff)
			r_idx[--back_position] = j;
	
		// Set pk
		// pk에 넣어놓은 값들을 다시 pk_a와 pk_b에 세팅을 함으로서 encryption하려는 것. 
		pk_a[j] = pk[j * 2] << 8 | pk[j * 2 + 1];
		pk_b[j] = pk[PublicKey + j * 2] << 8 | pk[PublicKey + j * 2 + 1];
	}


	// Compute d = H'(delta)
	sha512((unsigned char*)delta, LAMBDA / 4, (unsigned char*)hash, LAMBDA / 4);

	// delta 값은 dec 와 enc 둘다 동일한 것으로 확인이 끝났다. 
	// 
	// for(int q=0; q<128; q++)printSerial(((unsigned char*) delta) + q);
	// println();
	// for(int q=0; q<32; q++)printSerial(((unsigned char*) hash) + q);
	// println();
	
	// Initialize c2 as q/2 * delta
	for (i = 0; i < LWE_N / 64; ++i){ 
		for (j = 0; j < 64; ++j) { 
			c2[64 * i + j] = ((delta[i] >> j)) << _16_LOG_T;
		} 
	}

	// Compute a * r, b * r, and then add to c1 and c2, respectively.
    register uint16_t *paj, *pbj, *pc1j, *pc2j;
    for (i = 0; i < HR; ++i) {
        uint16_t deg = r_idx[i];
        uint16_t branch = (2 * ((i - neg_start) >> sft & 0x1) - 1);
        paj = pk_a;
        pbj = pk_b;
        pc1j = c1 + deg;
        pc2j = c2 + deg;
        if ((2 * ((i - neg_start) >> sft & 0x1) - 1) == 1)
        {
            for (j = 0; j < LWE_N - deg; ++j) {
                *(pc1j++) += *(paj++);
                *(pc2j++) += *(pbj++);
            }
            pc1j = c1;
            pc2j = c2;
        	for (j = LWE_N - deg; j < LWE_N; ++j) {
                *(pc1j++) -= *(paj++);
                *(pc2j++) -= *(pbj++);
            }
        }
        else
        {
            for (j = 0; j < LWE_N - deg; ++j) {
                *(pc1j++) -= *(paj++);
                *(pc2j++) -= *(pbj++);
            }
            pc1j = c1;
            pc2j = c2;
            for (j = LWE_N - deg; j < LWE_N; ++j) {
                *(pc1j++) += *(paj++);
                *(pc2j++) += *(pbj++);
        	}
        }
    }


	// Compute c1 and c2 from mod q to mod p
	// Compute ct = (c1, c2, d)
	#ifdef RING_CATEGORY1
		for (i = 0; i < LWE_N; ++i) {
			ct[i] = ((c1[i] + RD_ADD) & RD_AND) >> 8;
			ct[LWE_N + i] = ((c2[i] + RD_ADD) & RD_AND) >> 8;
		}
	#endif
	#if defined(RING_CATEGORY3_N1024) || defined(RING_CATEGORY3_N2048) || defined(RING_CATEGORY5)
		for (i = 0; i < LWE_N; ++i) {
			c1[i] = (c1[i] + RD_ADD) & RD_AND;
			ct[i * 2] = c1[i] >> 8;
			ct[i * 2 + 1] = c1[i] & 0xff;
			c2[i] = (c2[i] + RD_ADD) & RD_AND;
			ct[(LWE_N * 2) + i * 2] = c2[i] >> 8;
			ct[(LWE_N * 2) + i * 2 + 1] = c2[i] & 0xff;
		}
	#endif

	#ifdef RING_CATEGORY1
		for (j = 0; j < 4; ++j) {
			ct[LWE_N + LWE_N + j * 8] = (unsigned char)(hash[j] >> 56);
			ct[LWE_N + LWE_N + j * 8 + 1] = (unsigned char)(hash[j] >> 48);
			ct[LWE_N + LWE_N + j * 8 + 2] = (unsigned char)(hash[j] >> 40);
			ct[LWE_N + LWE_N + j * 8 + 3] = (unsigned char)(hash[j] >> 32);
			ct[LWE_N + LWE_N + j * 8 + 4] = (unsigned char)(hash[j] >> 24);
			ct[LWE_N + LWE_N + j * 8 + 5] = (unsigned char)(hash[j] >> 16);
			ct[LWE_N + LWE_N + j * 8 + 6] = (unsigned char)(hash[j] >> 8);
			ct[LWE_N + LWE_N + j * 8 + 7] = (unsigned char)(hash[j] & 0xff);
		}
	#endif
	#if defined(RING_CATEGORY3_N1024) || defined(RING_CATEGORY3_N2048) || defined(RING_CATEGORY5)
		for (j = 0; j < LAMBDA / 32; ++j) {
			ct[(LWE_N * 2) + (LWE_N * 2) + j * 8] = (unsigned char)(hash[j] >> 56);
			ct[(LWE_N * 2) + (LWE_N * 2) + j * 8 + 1] = (unsigned char)(hash[j] >> 48);
			ct[(LWE_N * 2) + (LWE_N * 2) + j * 8 + 2] = (unsigned char)(hash[j] >> 40);
			ct[(LWE_N * 2) + (LWE_N * 2) + j * 8 + 3] = (unsigned char)(hash[j] >> 32);
			ct[(LWE_N * 2) + (LWE_N * 2) + j * 8 + 4] = (unsigned char)(hash[j] >> 24);
			ct[(LWE_N * 2) + (LWE_N * 2) + j * 8 + 5] = (unsigned char)(hash[j] >> 16);
			ct[(LWE_N * 2) + (LWE_N * 2) + j * 8 + 6] = (unsigned char)(hash[j] >> 8);
			ct[(LWE_N * 2) + (LWE_N * 2) + j * 8 + 7] = (unsigned char)(hash[j] & 0xff);
		}
	#endif

	// 할당하기 전에 hash_t를 확인해보자.
	// 새롭게 hash_t를 하기 전에 메모리를 반납하고 다시 진행해본 결과 완료되었다.
	
	
	free(hash_t);
	//  Compute G(c1, c2, d, delta)
	hash_t = (uint64_t *)calloc((LWE_N + LWE_N + (LAMBDA / 4) + (LWE_N / 8)) / 8, sizeof(uint64_t));
	memcpy((unsigned char*)hash_t, (unsigned char*)ct, LWE_N + LWE_N + (LAMBDA / 4)); //ct에 있는 것을 그대로 붙여넣기 하는 것. 			
	memcpy((unsigned char*)hash_t + LWE_N + LWE_N + (LAMBDA / 4), (unsigned char*)delta, (LWE_N / 8)); // delta에 있는 것을 붙여넣기 


	// 모든 입력값이 다 같은데,,, 어떻게 다른 결과가 나오는 거지? 
	// for(int q=0; q<2048; q++)printSerial(((unsigned char*) hash_t) + q);
	// println();
	// for(int q=LWE_N+LWE_N; q<LWE_N+LWE_N+(LAMBDA/4); q++)printSerial(((unsigned char*) hash_t) + q);
	// println();
	// for(int q=LWE_N+LWE_N+(LAMBDA/4); q<LWE_N+LWE_N+(LAMBDA/4)+(LWE_N/8); q++)printSerial(((unsigned char*) hash_t) + q);
	// println();

	sha512((unsigned char*)hash_t, LWE_N + LWE_N + (LAMBDA / 4) + (LWE_N / 8), (unsigned char*)hash, (LAMBDA / 4));

	// for(int q=0; q<32; q++)printSerial(((unsigned char*) hash) + q);
	// println();


	// Compute K = G(c1, c2, d, delta)
	for (i = 0; i < LAMBDA / 32; ++i) {
		ss[i * 8] = (unsigned char)(hash[i] >> 56);
		ss[i * 8 + 1] = (unsigned char)(hash[i] >> 48);
		ss[i * 8 + 2] = (unsigned char)(hash[i] >> 40);
		ss[i * 8 + 3] = (unsigned char)(hash[i] >> 32);
		ss[i * 8 + 4] = (unsigned char)(hash[i] >> 24);
		ss[i * 8 + 5] = (unsigned char)(hash[i] >> 16);
		ss[i * 8 + 6] = (unsigned char)(hash[i] >> 8);
		// &0xff를 통해서 LSB 쪽의 1바이트 값을 놔두고 나머지는 모두 0으로 만든다. 
		// 솔직히 굳이 할 연산인가 싶기는 하다. 
		ss[i * 8 + 7] = (unsigned char)(hash[i] & 0xff);
	}

	free(hash_t);


}



/**
  * @param	ss		[out] shared secret
  * @param	ct		[in] encrypted data  ct = (c1, c2, d)
  * @param	sk		[in] private/public key for decryption. sk = (S, T), pk = (A, B)
  */
void crypto_kem_dec(unsigned char *ss, unsigned char *ct, unsigned char *sk) {
	int i, j, hw = 0;
    uint8_t neg_start = sk[(HS * 2) + (LWE_N / 8)], back_position = HR;
	
	uint8_t r[LWE_N] = { 0, };

	uint16_t decomp_delta[LWE_N];
	uint16_t c1[LWE_N] = { 0, };
	uint16_t c2[LWE_N] = { 0, };

    uint16_t r_idx[HR];

	uint16_t pk_a[LWE_N];
    uint16_t pk_b[LWE_N];

	uint64_t delta[LWE_N / 64] = { 0, };
	uint64_t hash[LAMBDA / 32];
	uint64_t *hash_t = NULL;
	uint64_t d[LAMBDA / 32];

	TupleElement tuple;
	unsigned char *S = "";


	#ifdef RING_CATEGORY1
		for (j = 0; j < LWE_N; ++j) {
			decomp_delta[j] = ct[LWE_N + j] << 8; 	// Initialize delta as c2
			c1[j] = ct[j] << 8;
		}


    // Compute delta = (delta + c1 * s)
    for (i = 0; i < HS; ++i) {
		uint16_t deg = (sk[i * 2] << 8) + sk[i * 2 + 1];
        uint16_t branch = (2 * ((i - neg_start) >> sft & 0x1) - 1);

        for (j = 0; j < LWE_N - deg; ++j) { decomp_delta[deg + j] += branch * c1[j]; }
        for (j = LWE_N - deg; j < LWE_N; ++j) { decomp_delta[deg + j - LWE_N] -= branch * c1[j]; }
    }
	#endif
	#if defined(RING_CATEGORY3_N1024) || defined(RING_CATEGORY3_N2048) || defined(RING_CATEGORY5)
		for (i = 0; i < LWE_N; ++i) {
			decomp_delta[i] = ct[(LWE_N * 2) + i * 2] << 8 | ct[(LWE_N * 2) + i * 2 + 1];	// Initialize delta as c2
			c1[i] = ct[i * 2] << 8 | ct[i * 2 + 1];
		}


		// Compute delta = (delta + c1 * s)
		for (i = 0; i < HS; ++i) {
			uint16_t deg = (sk[i * 2] << 8) + sk[i * 2 + 1];
			uint16_t branch = (2 * ((i - neg_start) >> sft & 0x1) - 1);

			for (j = 0; j < LWE_N - deg; ++j) { decomp_delta[deg + j] += branch * c1[j]; }
			for (j = LWE_N - deg; j < LWE_N; ++j) { decomp_delta[deg + j - LWE_N] -= branch * c1[j]; }
		}
	#endif


	// Compute delta = 2/p * delta
	for (j = 0; j < LWE_N; ++j) {
		decomp_delta[j] += DEC_ADD;
		decomp_delta[j] >>= _16_LOG_T;
	}
	

	// Set delta
	for (j = 0; j < LWE_N / 64; ++j) {
		for (i = 0; i < 64; ++i) {
            delta[j] ^= ((uint64_t)decomp_delta[64 * j + i]) << i;
		}
	}


	// Compute r' = H(delta)
	// hash_t 에다가 8bytes 짜리 배열 크기 16개 - 512bytes를 배정한다. 
	hash_t = (uint64_t *)calloc(LWE_N / 64, sizeof(uint64_t));
	tuple.input = (unsigned char*)delta;
	tuple.inputBitLen = LWE_N;
	TupleHash256(&tuple, 1, (unsigned char*)hash_t, LWE_N, S, strlen(S) * 8);


	#if defined(RING_CATEGORY1) || defined(RING_CATEGORY3_N1024) 
		i = 0;
		do {
			j = (uint16_t)hash_t[i] & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 10) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 12) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 22) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 24) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 34) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 36) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 46) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 48) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 58) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			i++;
			if (i == LWE_N / 64) {
				i = 0;
				tuple.input = (unsigned char*)hash_t;
				tuple.inputBitLen = LWE_N;
				TupleHash256(&tuple, 1, (unsigned char*)hash_t, LWE_N, S, strlen(S) * 8);
			}
		} while (hw < HR);
	#endif
	#if defined(RING_CATEGORY3_N2048) || defined(RING_CATEGORY5)
		i = 0;
		do {
			j = (uint16_t)hash_t[i] & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 11) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 13) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 24) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 26) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 37) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			j = (uint16_t)(hash_t[i] >> 39) & (LWE_N - 1);
			if (r[j] == 0) {
				r[j] = ((uint16_t)(hash_t[i] >> 50) & 0x02) - 1;
				hw++;
				if (hw == HR) {
					i++;
					break;
				}
			}
			i++;
			if (i == LWE_N / 64) {
				i = 0;
				tuple.input = (unsigned char*)hash_t;
				tuple.inputBitLen = LWE_N;
				TupleHash256(&tuple, 1, (unsigned char*)hash_t, LWE_N, S, strlen(S) * 8);
			}
		} while (hw < HR);
	#endif


	// Compute d' = H'(delta)
	sha512((unsigned char*)delta, LAMBDA / 4, (unsigned char*)hash, LAMBDA / 4);

	// for(int q=0; q<32; q++)printSerial(((unsigned char*) hash) + q);
	// println();

	// Set d
	#ifdef RING_CATEGORY1
		for (i = 0; i < LAMBDA / 32; ++i) {
			d[i] = (((uint64_t)(ct[LWE_N + LWE_N + i * 8] & 0xff) << 56) + ((uint64_t)(ct[LWE_N + LWE_N + i * 8 + 1] & 0xff) << 48) + ((uint64_t)(ct[LWE_N + LWE_N + i * 8 + 2] & 0xff) << 40)
				+ ((uint64_t)(ct[LWE_N + LWE_N + i * 8 + 3] & 0xff) << 32) + ((uint64_t)(ct[LWE_N + LWE_N + i * 8 + 4] & 0xff) << 24) + ((uint64_t)(ct[LWE_N + LWE_N + i * 8 + 5] & 0xff) << 16)
				+ ((uint64_t)(ct[LWE_N + LWE_N + i * 8 + 6] & 0xff) << 8) + ((uint64_t)ct[LWE_N + LWE_N + i * 8 + 7] & 0xff));
		}
	#endif
	#if defined(RING_CATEGORY3_N1024) || defined(RING_CATEGORY3_N2048) || defined(RING_CATEGORY5)
		for (i = 0; i < LAMBDA / 32; ++i) {
			d[i] = (((uint64_t)(ct[(LWE_N * 2) + (LWE_N * 2) + i * 8] & 0xff) << 56) + ((uint64_t)(ct[(LWE_N * 2) + (LWE_N * 2) + i * 8 + 1] & 0xff) << 48)
				+ ((uint64_t)(ct[(LWE_N * 2) + (LWE_N * 2) + i * 8 + 2] & 0xff) << 40) + ((uint64_t)(ct[(LWE_N * 2) + (LWE_N * 2) + i * 8 + 3] & 0xff) << 32)
				+ ((uint64_t)(ct[(LWE_N * 2) + (LWE_N * 2) + i * 8 + 4] & 0xff) << 24) + ((uint64_t)(ct[(LWE_N * 2) + (LWE_N * 2) + i * 8 + 5] & 0xff) << 16)
				+ ((uint64_t)(ct[(LWE_N * 2) + (LWE_N * 2) + i * 8 + 6] & 0xff) << 8) + ((uint64_t)ct[(LWE_N * 2) + (LWE_N * 2) + i * 8 + 7] & 0xff));
		}
	#endif


    // Generate r_idx
    neg_start = 0;
	for (j = 0; j < LWE_N; ++j) {
        if (r[j] == 0x01)
            r_idx[neg_start++] = j;
        else if (r[j] == 0xff)
            r_idx[--back_position] = j;

		// Set pk
        pk_a[j] = sk[CRYPTO_SECRETKEYBYTES + j * 2] << 8 | sk[CRYPTO_SECRETKEYBYTES + j * 2 + 1];
        pk_b[j] = sk[CRYPTO_SECRETKEYBYTES + PublicKey + j * 2] << 8 | sk[CRYPTO_SECRETKEYBYTES + PublicKey + j * 2 + 1];
    }

	
    memset(c1, 0, sizeof(uint16_t) * LWE_N);
	// Initialize c2' as q/2 * delta
	for (i = 0; i < LWE_N; ++i) { c2[i] = decomp_delta[i] << _16_LOG_T; }


	// Compute a * r and b * r, and then add to c1' and c2', respectively.
    for (i = 0; i < HR; ++i) {
		uint16_t deg = r_idx[i];
		uint16_t branch = (2 * ((i - neg_start) >> sft & 0x1) - 1);


        for (j = 0; j < LWE_N - deg; ++j) {
            c1[deg + j] += branch * pk_a[j];
            c2[deg + j] += branch * pk_b[j];
        }
        for (j = LWE_N - deg; j < LWE_N; ++j) {
            c1[deg + j - LWE_N] -= branch * pk_a[j];
            c2[deg + j - LWE_N] -= branch * pk_b[j];
        }
    }


	// Compute c1' and c2' from mod q to mod p
    for (j = 0; j < LWE_N; ++j) {
        c1[j] = (c1[j] + RD_ADD) & RD_AND;
        c2[j] = (c2[j] + RD_ADD) & RD_AND;
    }

	//여기까지 hash_t는 동일한 값을 가진다. 
	// 
	free(hash_t); 

	hash_t = (uint64_t *)calloc((LWE_N + LWE_N + (LAMBDA / 4) + (LWE_N / 8)) / 8, sizeof(uint64_t));
	memcpy((unsigned char*)hash_t, (unsigned char*)ct, LWE_N + LWE_N + (LAMBDA / 4));		
	memcpy((unsigned char*)hash_t + LWE_N + LWE_N + (LAMBDA / 4), (unsigned char*)delta, (LWE_N / 8));	

	

	sha512((unsigned char*)hash_t, LWE_N + LWE_N + (LAMBDA / 4) + (LWE_N / 8), (unsigned char*)hash, (LAMBDA / 4));

	// for(int q=0; q<32; q++)printSerial(((unsigned char*) hash) + q);
	// println();

	for (i = 0; i < 4; ++i) {
		ss[i * 8] = (unsigned char)(hash[i] >> 56);
		ss[i * 8 + 1] = (unsigned char)(hash[i] >> 48);
		ss[i * 8 + 2] = (unsigned char)(hash[i] >> 40);
		ss[i * 8 + 3] = (unsigned char)(hash[i] >> 32);
		ss[i * 8 + 4] = (unsigned char)(hash[i] >> 24);
		ss[i * 8 + 5] = (unsigned char)(hash[i] >> 16);
		ss[i * 8 + 6] = (unsigned char)(hash[i] >> 8);
		ss[i * 8 + 7] = (unsigned char)(hash[i] & 0xff);
	}
	free(hash_t);
	

}
