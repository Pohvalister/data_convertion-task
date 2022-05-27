#include <gtest/gtest.h>
#include <bitset>
#include <algorithm>
#include <iostream>

#include <cstdio>
#include <cstdlib>
#include "../1_int_to_bin.h"

TEST(int_to_bin, basic_work){
	EXPECT_EQ(std::string (toBin<char>(0)),	"00000000");
	EXPECT_EQ(std::string (toBin<char>(1)),	"00000001");
	EXPECT_EQ(std::string (toBin<char>(-1)),	"11111111");
}

TEST(int_to_bin, bitset_comparison){
	for (int i = 0; i < 10; i++){
		int val_to_compare = rand();
		val_to_compare *= ( i%2 ? 1 : -1 );
		std::string examer = std::bitset<sizeof(int) * 8>(val_to_compare).to_string();
		std::string examed (toBin<int>(val_to_compare));
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
	EXPECT_EQ(examed,"A B A");

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

		EXPECT_EQ(examer2, examed);
	}
}

#include "../3_list_serializing.h"


class list_serializing : public ::testing::Test{
protected:
	static ListNode* generateNode(std::string d, ListNode* p, ListNode* n, ListNode* r){
		ListNode* answ = new ListNode();
		answ->data = d;
		answ->prev = p;
		answ->next = n;
		answ->rand = r;
		return answ;
	}
	static ListNode* insertAdditionalNodes(ListNode* first_node, int amount){
		ListNode* endingPointer = first_node->next;
		ListNode* curr = first_node;
		for (int i = 0; i < amount; i++){
			ListNode* new_curr = generateNode("Node_" + std::to_string(rand()), curr, endingPointer, first_node);
			curr->next = new_curr;
			curr = new_curr;
		}
		return curr;
	}
	static bool compare(ListNode ln1, ListNode ln2){
		bool answ = (ln1.data == ln2.data);
		answ &= (ln1.prev == NULL && ln2.prev == NULL) || (ln1.prev->data == ln2.prev->data);//неправильное сравнение
		answ &= (ln1.next == NULL && ln2.next == NULL) || (ln1.next->data == ln2.next->data);
		answ &= (ln1.rand == NULL && ln2.rand == NULL) || (ln1.next->rand == ln2.next->rand);
		return answ;
	}

	struct T_List : public List{
		void setConfig(int c, ListNode* h, ListNode* t){
			count = c;
			head = h;
			tail = t;
		}

		bool operator==(const T_List& l2) const{
			bool answ = true;
			ListNode* curr1 = head;
			ListNode* curr2 = l2.head;
			while (curr1 != tail){
				answ &= compare(*curr1, *curr2);
				curr1 = curr1->next;
				curr2 = curr2->next;
			}
			answ &= compare(*curr1, *curr2);
			return answ;
		}
	};

protected:
	void SetUp(){
		srand(time(0));
		tmp_file = tmpfile();
		rewind(tmp_file);
		tmp_file1 = tmpfile();
		rewind(tmp_file1);

		empty_list.setConfig(0, NULL, NULL);
		ListNode* tmp_node = generateNode("Hello", NULL, NULL, NULL);
		small_list.setConfig(1, tmp_node, tmp_node);
		ListNode* chain_start = generateNode("head", NULL, NULL, NULL);
		ListNode* chain_end = insertAdditionalNodes(chain_start, 20);
		chain_end = insertAdditionalNodes(chain_end, 5);
		big_list.setConfig(26, chain_start, chain_end);
	}

protected:
	T_List empty_list, small_list, big_list;
	FILE* tmp_file;
	FILE* tmp_file1;
};

TEST_F(list_serializing, work_checking){
	List list;
	EXPECT_NO_FATAL_FAILURE(list.Serialize(tmp_file));
	list.clear();
	rewind(tmp_file);
	EXPECT_NO_FATAL_FAILURE(list.Deserialize(tmp_file));
}

TEST_F(list_serializing, basic_work){
	small_list.Serialize(tmp_file1);
	rewind(tmp_file1);
	T_List new_list;
	new_list.Deserialize(tmp_file1);
	EXPECT_EQ(small_list, new_list);

	rewind(tmp_file1);
	big_list.Serialize(tmp_file);
	big_list.Serialize(tmp_file1);
	rewind(tmp_file);
	rewind(tmp_file1);
	T_List new_list1, new_list2;
	new_list1.Deserialize(tmp_file);
	new_list2.Deserialize(tmp_file1);
	EXPECT_EQ(new_list1, new_list2);
}

TEST_F(list_serializing, randomed_lists){

}

