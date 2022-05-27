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

protected:
	ListNode *	head = NULL;
	ListNode *	tail = NULL;
	int	count = 0;

public:
	void clear();

	struct DataCollector;
};

#endif //LIST_SERIALIZING_H
