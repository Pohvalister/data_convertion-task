#include <gtest/gtest.h>
#include <bitset>
#include <algorithm>

#define ITER_COUNT 100

#include "../1_int_to_bin.h"

//	Базовое тестирование работоспособности функции toBin
TEST(int_to_bin, basic_work){
	EXPECT_EQ(toBin<char>(0),	"00000000");
	EXPECT_EQ(toBin<char>(1),	"00000001");
	EXPECT_EQ(toBin<char>(-1),	"11111111");
	EXPECT_EQ(toBin<short>(-25),	"1111111111100111");

	//toBin<unsigned int>(0); //expect не компилируется
}

//	Сравнение результатов работы фунции toBin с результатами stl реализации std::bitset
TEST(int_to_bin, bitset_comparison){
	for (int i = 0; i < ITER_COUNT; i++){
		int val_to_compare = rand();
		val_to_compare *= ( i%2 ? 1 : -1 );
		std::string examer = std::bitset<sizeof(int) * 8>(val_to_compare).to_string();
		std::string examed (toBin<int>(val_to_compare));
		EXPECT_EQ(examer, examed);
	}
}

#include "../2_remove_dups.h"

//	Базовое тестирование функции RemoveDups
TEST(remove_dups, basic_work){
	char data[] = "AAA BBB AAA";
	RemoveDups(data);
	//printf("%s\n", data);

	std::string examed(data);
	EXPECT_EQ(examed,"A B A");
}

//	Сравнение результатов RemoveDups с stl реализацией std::unique_copy
TEST(remove_dups, unique_copy_comparison){
	for (int i = 0; i < ITER_COUNT; i++){
		int letters_amount = rand() % 50 + 1;
		char* data = new char[letters_amount];
		for (int j = 0; j < letters_amount - 1; j++)
			data[j] = rand() % ('d' - 'a') + 'a';
		data[letters_amount - 1]='\0';
//		printf("%s\n", data);

		std::string examer1(data);
		std::string examer2;
		std::unique_copy(examer1.begin(), examer1.end(), std::back_inserter(examer2));
		RemoveDups(data);
//		printf("%s\n", data);
//		printf("\n");
		std::string examed(data);

		EXPECT_EQ(examer2, examed);
		delete[] data;
	}
}

#include "../3_list_serializing.h"

class list_serializing : public ::testing::Test{
protected:
	static ListNode* generateNode(const std::string& d, ListNode* p = NULL, ListNode* n = NULL, ListNode* r = NULL){
		auto* answ = new ListNode();
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
		if (ln1.data != ln2.data) return false;
		if (!((ln1.prev == NULL && ln2.prev == NULL) || (ln1.prev->data == ln2.prev->data))) return false;
		if (!((ln1.next == NULL && ln2.next == NULL) || (ln1.next->data == ln2.next->data))) return false;
		if (!((ln1.rand == NULL && ln2.rand == NULL) || (ln1.rand->data == ln2.rand->data))) return false;
		return true;
	}

	// Расширение функций класса List для более удобного тестирования Serialize/Deserialize
	struct T_List : public List{
		void setConfig(ListNode* h, ListNode* t){
			head = h;
			tail = t;
			if (h == NULL)
				count = 0;
			else{
				count = 1;
				while (h != t){
					count++;
					h = h->next;
				}
			}
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
		rewind(tmp_file);
		rewind(tmp_file1);

		empty_list.setConfig(NULL, NULL);

		ListNode* tmp_node = generateNode("small_list's only element");
		small_list.setConfig(tmp_node, tmp_node);

		ListNode* chain_start = generateNode("big_list head");
		ListNode* chain_end = insertAdditionalNodes(chain_start, 20);
		chain_end = insertAdditionalNodes(chain_end, 5);
		big_list.setConfig(chain_start, chain_end);
	}

protected:
	T_List empty_list, small_list, big_list;
	FILE* tmp_file = tmpfile();
	FILE* tmp_file1 = tmpfile();
};

//	Базовая проверка работы функций Serialize/Deserialize
TEST_F(list_serializing, work_checking){
	List list;
	EXPECT_NO_FATAL_FAILURE(list.Serialize(tmp_file));
	list.clear();
	rewind(tmp_file);
	EXPECT_NO_FATAL_FAILURE(list.Deserialize(tmp_file));
}

//	Проверка переноса списка из одного элемента
TEST_F(list_serializing, one_elem_work){
	small_list.Serialize(tmp_file);
	rewind(tmp_file);
	T_List new_list;
	new_list.Deserialize(tmp_file);
	EXPECT_EQ(small_list, new_list);
}

// Перенос списка из многих элементов через несколько файлов и несколько раз
TEST_F(list_serializing, many_elem_work){
	big_list.Serialize(tmp_file);
	big_list.Serialize(tmp_file1);
	rewind(tmp_file);
	rewind(tmp_file1);

	T_List new_list1, new_list2;
	new_list1.Deserialize(tmp_file);
	new_list2.Deserialize(tmp_file1);
	EXPECT_EQ(new_list1, new_list2);
	EXPECT_EQ(big_list, new_list1);
	rewind(tmp_file1);
	new_list2.Deserialize(tmp_file1);
	EXPECT_EQ(new_list1, new_list2);
}

// Генерация случайных списков для переноса через файл
TEST_F(list_serializing, randomed_lists){
	for (int i = 0; i < ITER_COUNT; i++){
		int chain_checkpoints_amount = rand() % 10 + 1;
		ListNode* chain_start = generateNode("Node_1");
		ListNode* chain_end = insertAdditionalNodes(chain_start, rand() % 20);
		for (int j = 0; j < chain_checkpoints_amount; j++)
			chain_end = insertAdditionalNodes(chain_end, rand() % 20);

		T_List generated_list;
		generated_list.setConfig(chain_start, chain_end);

		rewind(tmp_file);
		generated_list.Serialize(tmp_file);
		rewind(tmp_file);
		T_List output_list;
		output_list.Deserialize(tmp_file);
		EXPECT_EQ(generated_list, output_list);
	}
}

