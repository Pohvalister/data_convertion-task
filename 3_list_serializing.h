#ifndef LIST_SERIALIZING_H
#define LIST_SERIALIZING_H
#include <iostream>

// структуру ListNode модифицировать нельзя
struct ListNode {
	ListNode *	prev;
	ListNode *	next;
	ListNode *	rand; // указатель на произвольный элемент данного списка, либо NULL
	std::string data;
};

class List {
public:
	void Serialize	(FILE * file); // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
	void Deserialize (FILE * file); // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

private:
	ListNode *	head;
	ListNode *	tail;
	int	count;

private:
	void clear();

	struct DataCollector;
};

#endif //LIST_SERIALIZING_H
