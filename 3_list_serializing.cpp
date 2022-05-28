#include "3_list_serializing.h"

#include <cassert>
#include <unordered_map>
#include <vector>

namespace {
	struct FileHandler{
		explicit FileHandler(FILE* const f)
		: file(f){}
		FILE * const file;

		void put (const int val) const{ // мб назвать как гетеры?
			fwrite(&val, sizeof(int), 1, file);
		}
		void put (const std::vector<int>& vec) const{
			int len = vec.size();
			fwrite(&len, sizeof(int), 1, file);
			fwrite((int *) &vec[0], sizeof(int), len, file);
		}
		void put (const std::string& str) const{
			int len = str.size();
			fwrite(&len, sizeof(int), 1, file);
			fwrite(str.c_str(), sizeof(char), len, file);
		}

		int getVal() const{
			int val;
			fread(&val, sizeof(int), 1, file);
			return val;
		}

		std::vector<int> getVec() const{
			int len;//getVal
			fread(&len, sizeof(int), 1, file);
			if (!len)
				return  {};

			int *tmp = new int[len];
			fread(tmp, sizeof(int), len, file);
			return std::vector<int>(tmp, tmp + len);
		}

		std::string getStr() const{
			int len;
			fread(&len, sizeof(int), 1, file);
			if (!len)
				return "";

			char* tmp = new char[len + 1];
			fread(tmp, sizeof(char), len, file);
			tmp[len] = '\0';
			return std::string(tmp);
		}
	};
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

//заполняет файл внутренними данными, сохраняя своё состояние
void List::Serialize(FILE* file){
	FileHandler file_handler(file);
	if (head == NULL){
		assert(tail == NULL);
		file_handler.put(0);
		return;
	}

	std::unordered_map<ListNode*, int> number_comp;

	ListNode* curr = head;
	int counter = 1;
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
		std::cout<<"data put: "<< curr->data << '\n';
		file_handler.put(curr->data);
		curr = curr->next;
	}
	file_handler.put(curr->data);
}

//перезаписывает имеющиеся данные новыми из файла
void List::Deserialize(FILE* file){
	FileHandler file_handler(file);
	clear();

	int amount = file_handler.getVal();
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
/* данные при сенриализации находятся в виде:
 * 	1) количество нод
 * 	2) вектор rand ссылок, в порядке их появления при проходе списка
 * 	3) строки, следующие друг за другом (в порядке их появления при переборе списка)
 */
