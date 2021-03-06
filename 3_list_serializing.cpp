#include "3_list_serializing.h"

#include <cassert>
#include <unordered_map>
#include <vector>

namespace {
	struct FileHandler{
		explicit FileHandler(FILE* const f)
		: file(f){}
		FILE * const file;

		void put (const std::size_t val) const{
			fwrite(&val, sizeof(std::size_t), 1, file);
		}
		void put (const std::vector<int>& vec) const{
			std::size_t len = vec.size();
			put(len);
			fwrite((int *) &vec[0], sizeof(int), len, file);
		}
		void put (const std::string& str) const{
			std::size_t len = str.size();
			put(len);
			fwrite(str.c_str(), sizeof(char), len, file);
		}

		std::size_t getVal() const{
			std::size_t val;
			fread(&val, sizeof(std::size_t), 1, file);
			return val;
		}

		std::vector<int> getVec() const{
			std::size_t len = getVal();
			if (!len)
				return  {};

			std::vector<int> answ(len);
			fread(&answ[0], sizeof(int), len, file);
			return answ;
		}

		std::string getStr() const{
			std::size_t len = getVal();
			if (!len)
				return "";

			std::string answ(len, '\0');
			fread(&answ[0], sizeof(char), len, file);
			return answ;
		}
	};
}

List::~List(){
	clear();
}

void List::clear(){
	if (head == NULL){
		assert(tail == NULL);
		return;
	}

	while (head != tail){
		ListNode* new_head = head->next;
		delete head;
		head = new_head;
	}
	delete head;
	head = NULL;
	tail = NULL;
	count = 0;
}

//заполняет файл необходимыми данными, сохраняя своё состояние
void List::Serialize(FILE* file){
	FileHandler file_handler(file);
	if (head == NULL){
		assert(tail == NULL);
		file_handler.put(0);
		return;
	}

	std::unordered_map<ListNode*, std::size_t> number_comp;

	ListNode* curr = head;
	std::size_t counter = 1;
	while (curr != tail){
		assert(number_comp.find(curr) == number_comp.end());
		number_comp[curr] = counter++;
		curr = curr->next;
	}
	number_comp[tail] = counter;
	number_comp[NULL] = 0;

	file_handler.put(counter);

	std::vector<int> structure(counter);
	curr = head;
	counter = 0;
	while (curr != tail){
		structure[counter++] = number_comp[curr->rand];
		curr = curr->next;
	}
	structure[counter] = number_comp[tail->rand];

	file_handler.put(structure);

	curr = head;
	counter = 0;
	while(curr != tail){
		file_handler.put(curr->data);
		curr = curr->next;
	}
	file_handler.put(curr->data);
}

//перезаписывает свои данные новыми из файла
void List::Deserialize(FILE* file){
	FileHandler file_handler(file);
	clear();

	std::size_t amount = file_handler.getVal();
	if (!amount)
		return;

	std::vector<ListNode*> pointer_comp(amount + 1);
	pointer_comp[0]=NULL;
	head = new ListNode();
	ListNode* curr = head;
	for (int i = 1; i < amount; i++){
		pointer_comp[i] = curr;
		auto new_curr = new ListNode();
		new_curr->prev = curr;
		curr->next = new_curr;
		curr = new_curr;
	}
	tail = curr;
	pointer_comp[amount] = tail;

	std::vector<int> structure = file_handler.getVec();
	curr = head;
	for (int rand_num : structure){
		curr->rand = pointer_comp[rand_num];
		curr->data = file_handler.getStr();
		curr = curr->next;
	}
	count = amount;
}
