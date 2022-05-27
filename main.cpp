#include <iostream>

#include "1_int_to_bin.h"
#include "2_remove_dups.h"
#include "3_list_serializing.h"

int main()
{
	// first usage
	std::cout << toBin(0) << std::endl;

	// second usage
	char data[] = "AAA BBB AAA";
	RemoveDups(data);
	printf("%s\n", data);

	//third usage
	List list;
	FILE* tmp_file = tmpfile();
	list.Serialize(tmp_file);
	list.Deserialize(tmp_file);

	return 0;
}
