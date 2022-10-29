#include "_HashCode.h"

const int HASH_SEED = 5381;
const int HASH_MULTIPLIER = 33;
const int HASH_MASK = unsigned(-1) >> 1;

int hashCode(const std::string& key) {
	unsigned hash = HASH_SEED;
	for (int i = 0; i < key.length(); ++i) {
		hash = HASH_MULTIPLIER * hash + key[i];
	}
	return int(hash & HASH_MASK);
}

int hashCode(char key) {
	return hashCode(std::string(1, key));
}

int hashCode(int key) {
	return key & HASH_MASK;	//	非負にするだけ(HASH_MASKの最上位ビットは0なので必ず非負になる)
}

int hashCode(bool key) {
	return hashCode(int(key));
}
