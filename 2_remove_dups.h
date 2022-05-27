#ifndef REMOVE_DUPS
#define REMOVE_DUPS

void RemoveDups(char* str){
	std::size_t old_pos = 0, new_pos = 0;

	while (str[old_pos] != '\0'){
		if (str[old_pos] != str[old_pos + 1]){
			str[new_pos++] = str[old_pos];
		}
		old_pos++;
	}

	for (; new_pos!=old_pos; new_pos++)
		str[new_pos] = '\0';
}

#endif //REMOVE_DUPS
