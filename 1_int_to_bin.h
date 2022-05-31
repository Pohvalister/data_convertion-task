#ifndef INT_TO_BIN
#define INT_TO_BIN

namespace {
	template <typename I>
	int getSizeOf();

	template<>
	int getSizeOf<long long>(){
		return 64;
	}

	template<>
	int getSizeOf<long>(){
		return 32;
	}

	template<>
	int getSizeOf<int>(){
		return 32;
	}

	template<>
	int getSizeOf<short>(){
		return 16;
	}

	template<>
	int getSizeOf<char>(){
		return 8;
	}
}

template <typename T>
std::string toBin(T val){
	std::string answ(getSizeOf<T>(), '\0');
	bool add = false, neg = false;
	if (val < 0){
		val *= -1;
		add = neg = true;
	}
	for (int i = getSizeOf<T>() - 1; i >= 0 ; i--){
		bool byte = val % 2;
		answ[i] = (byte ^ add ^ neg ? '1' : '0') ;
		add = ! byte & add;
		val /= 2;
	}
	return answ;
}

#endif //INT_TO_BIN