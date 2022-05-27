#include <iostream>

#include "1_int_to_bin.h"
#include "2_remove_dups.h"

int main()
{
	// first usage
	std::cout << toBin(0) << std::endl;

	// second usage
	char data[] = "AAA BBB AAA";
	RemoveDups(data);
	printf("%s\n", data);

	//third usage

	return 0;
}
