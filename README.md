# Задачи
> 1. Напишите функцию, которая принимает на вход знаковое целое число и печатает его двоичное представление, не используя библиотечных классов или функций.

В файле [1_int_to_bin.h](1_int_to_bin.h) реализована шаблонная функция `char* toBin(T val)`, которая по типу стандратного целого знакового числа возвращает строку, содержащую это число в бинарном виде. Длина строки зависит от размера входного числа.

> 2. Напишите функцию, удаляющую последовательно дублирующиеся символы в строке: `void RemoveDups(char* str);`

Реализация функции находится в файле [2_remove_dups.h](2_remove_dups.h)

> 3. Реализуйте функции сериализации и десериализации двусвязного списка в бинарном формате в файл. Алгоритмическая сложность решения должна быть меньше квадратичной.

```cpp
// структуру ListNode модифицировать нельзя
struct ListNode {
	ListNode *	prev;
	ListNode *	next;
	ListNode *	rand; // указатель на произвольный элемент данного списка, либо NULL
	std::string	data;
};

class List {
public:

	void Serialize	(FILE * file); // сохранение в файл (файл открыт с помощью fopen(path, "wb"))
	void Deserialize (FILE * file); // загрузка из файла (файл открыт с помощью fopen(path, "rb"))

private:
	ListNode *	head = NULL;
	ListNode *	tail = NULL;
	int	count = 0;
};
```

В файле [3_list_serializing.cpp](3_list_serializing.cpp) находятся реализации функций.
Используемый формат бинарных данных: | число вершин в List | структура List | данные data | , где
* структура List - вектор номеров вершин, в которые направлены указатели rand из текущей (по порядку, отсчитывая от head)
* данные data - перечисление полей data всех вершин (по порядку, отсчитывая от head) в формате: | длина строки | массив char символов строки |

Запись/Считывание бинарных данных осуществляется через сопоставление адреса вершин ListNode их номерам по порядку в List. Таким образом, алгоритм делает 3 прохода по List:
1) сопоставление адресов
2) запись/считывание rand ссылок (в std::unordered_map/std::vector)
3) запись/считывание строк data
Получается, алгоритм работает за линейное время от числа вершин

# Тестирование
В папке [tests](./tests) находится CMake проект с google тестами для проверки решений. 
> Установка [Google Test](https://github.com/google/googletest)
> ```console
>	git clone https://github.com/google/googletest.git <путь до папки с проектом>/tests/googletest
> ```

