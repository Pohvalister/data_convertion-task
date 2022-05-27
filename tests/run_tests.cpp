#include <gtest/gtest.h>
#include <bitset>
#include <algorithm>

#include "../1_int_to_bin.h"

TEST(int_to_bin, basic_work){
	ASSERT_EQ(toBin(0),"0");
	ASSERT_EQ(toBin(1), "1");
	ASSERT_EQ(toBin(-1), "11");
}

TEST(int_to_bin, bitset_comparison){
	for (int i = 0; i < 10; i++){
		int val_to_compare = rand();
		val_to_compare *= ( i%2 ? 1 : -1 );
		std::string examer = std::bitset<sizeof(int) * 8>(val_to_compare).to_string();
		std::string examed = toBin(val_to_compare);
		std::cout << "testing int: " << val_to_compare << '\n';
		EXPECT_EQ(examer, examed);
	}
}

#include "../2_remove_dups.h"

TEST(remove_dups, basic_work){
	char data[] = "AAA BBB AAA";
	RemoveDups(data);
	printf("%s\n", data);

	std::string examed(data);
	ASSERT_EQ(examed,"A B A");

}

TEST(remove_dups, unique_copy_comparison){
	for (int i = 0; i < 10; i++){
		int letters_amount = rand() % 50;
		char* data = new char[letters_amount];
		for (int j = 0; j < letters_amount - 1; j++)
			data[j] = rand() % ('d' - 'a') + 'a';
		data[letters_amount - 1]='\0';

		printf("%s\n", data);

		std::string examer1(data);
		std::string examer2;
		std::unique_copy(examer1.begin(), examer1.end(), std::back_inserter(examer2));
		RemoveDups(data);
		printf("%s\n", data);
		printf("\n");
		std::string examed(data);

		ASSERT_EQ(examer2, examed);

	}
}
