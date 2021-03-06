#include <iostream>
#include <cstdlib>

#include "1_int_to_bin.h"
#include "2_remove_dups.h"
#include "3_list_serializing.h"

int main()
{
	// first task usage
	int val;
	std::cin>>val;
	std::cout << toBin<short>(val) << std::endl;

	// second task usage
	char data[] = "AAA BBB AAA";
	RemoveDups(data);
	printf("%s\n", data);

	//third task usage
	List list;
	list.clear();
	FILE* tmp_file = tmpfile();
	list.Serialize(tmp_file);
	rewind(tmp_file);
	list.Deserialize(tmp_file);

	return 0;
}
