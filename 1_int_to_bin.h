#ifndef INT_TO_BIN
#define INT_TO_BIN

std::string toBin(int val){
	std::string answ;
	bool add = false, neg = false;
	if (val < 0){
		val *= -1;
		add = neg = true;
	}
	do {
		bool byte = val % 2;
		answ += (byte xor add xor neg ? '1' : '0');
		val /= 2;
	} while(val != 0);

	if (neg)
		answ = "1" + answ;

	return answ;
}

#endif //INT_TO_BIN