#include <iostream>
#include <string.h>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <string>
#include <time.h>
#include <stack>
using namespace std;

int task_manager()
{
	int task_number;
RENUMBER:	printf("Menu:\n     1.  T 1\n     2.  T 2\n     3.  T 3\n     4.  T 4\n");
	printf("Enter task number: ");
	scanf_s("%d", &task_number);
	if (task_number < 1 || task_number > 4)
	{
		system("cls");
		printf("There is only 4 options!\n\n");
		goto RENUMBER;
	}
	return task_number;
}

/*
Задача 1. Написати функцію-шаблон послідовного пошуку в масиві по ключу.
Функція повертає індекс останнього, знайденого елемента в масиві, рівного ключу.
Написати специфікацію функції-шаблон для типу char*.
*/
template<typename T1, typename T2> T2 search(const T1* array, T2 size, T1 key)
{
	T2 index = -1;
	for (T2 i = 0; i < size; i++)
	{
		if (array[i] == key)
		{
			index = i;
		}
	}
	return index;
}
template<> int search(const char* array, int size, char key)
{
	int index = -1;
	for (int i = 0; i < size; i++)
	{
		if (array[i] == key)
		{
			index = i;
		}
	}
	return index;
}
void task1()
{
	cout << "Test: \n";
	cout << " Enter key: ";
	char key;
	cin >> key;
	cout << " Enter char array: ";
	char* array = new char[100];
	cin >> array;
	int size = sizeof(array) / sizeof(char);

	int index;
	index = search(array, size, key);
	if (index == -1)
	{
		cout << "There is no match";
	}
	else
	{
		cout << index << endl;
	}
}

/*
Задача 2. Написати функцію-шаблон функцію впорядкування методом швидкого впорядкування.
Написати специфікацію функції-шаблон для типу char*.
*/
// функція для заміни елементів
template<typename T> void swap(T* a, T* b)
{
	T t = *a;
	*a = *b;
	*b = t;
}
template<> void swap(char* a, char* b)
{
	char t = *a;
	*a = *b;
	*b = t;
}
// функція перевпорядкування масиву (знайти точку розбиття)
template<typename T1, typename T2> T2 partition(T1* array, T2 low, T2 high)
{
	// вибрати крайній правий елемент як опорний
	T1 pivot = array[high];

	// вказівник на більший елемент
	T2 i = (low - 1);

	// обхід кожного елемента масиву
	// порівняння їх із опороним
	for (T2 j = low; j < high; j++) {
		if (array[j] <= pivot) {

			// якщо знайдено елемент, менший ніж опорний
            // поміняти його місцями на більший елемент, позначений i
			i++;

			// поміняти місцями елемент i на елемент j
			swap(&array[i], &array[j]);
		}
	}

	 // поміняти опорний елемент на більший елемент у i
	swap(&array[i + 1], &array[high]);

	// повернути точку розбитття
	return (i + 1);
}
template<> int partition(char* array, int low, int high)
{
	// вибрати крайній правий елемент як опорний
	char pivot = array[high];

	// покажчик для більшого елемента
	int i = (low - 1);

	// обійти кожен елемент масиву
	// порівняння їх із опорним
	for (int j = low; j < high; j++) {
		if (array[j] <= pivot) {

			//якщо знайдено елемент, менший за опорний
			// поміняйте його місцями з більшим елементом, позначеним i
			i++;

			//поміняти місцями елемент в i на елемент в j
			swap(&array[i], &array[j]);
		}
	}

	//поміняти опорний елемнт з більшим елементом у i
	swap(&array[i + 1], &array[high]);

	//повернути точку розбиття
	return (i + 1);
}
template<typename T1, typename T2> void quickSort(T1* array, T2 low, T2 high) {
	if (low < high) {

		// знайти такий опорний елемент, що
        // елементи, менші за опорний, знаходяться ліворуч від нього
        // елементи, більші за опорний, знаходяться праворуч від нього
		T2 pi = partition(array, low, high);
		
		// рекурсивний виклик ліворуч від опорного елемента
		quickSort(array, low, pi - 1);

		// рекурсивний виклик праворуч від опорного елемента
		quickSort(array, pi + 1, high);
	}
}
template<> void quickSort(char* array, int low, int high) {
	if (low < high) {

		// знайти такий опорний елемент, що
		// елементи, менші за опорний, знаходяться ліворуч від нього
		// елементи, більші за опорний, знаходяться праворуч від нього
		int pi = partition(array, low, high);

		// рекурсивний виклик ліворуч від опорного елемента
		quickSort(array, low, pi - 1);

		// рекурсивний виклик праворуч від опорного елемента
		quickSort(array, pi + 1, high);
	}
}
void task2()
{
	cout << "Test:" << endl;
	cout << " Enter char array: ";
	char* array = new char[100];
	cin >> array;
	int size = sizeof(array) / sizeof(char);
	cout << "Unsorted Array: \n";
	cout << array;

	// perform quicksort on data
	quickSort(array, 0, size - 1);
	cout << endl << "Sorted Array: \n";
	cout << array;
}

/*
Задача 3. Створити параметризований масив з конструкторами, деструктором і перевантаженими операторами [], =, +, +=,-,-=.
*/
template<typename T> class Arr
{
	T* ar;
	int size;
	int state;
public:
	Arr() : ar(nullptr), size(0), state(0) {}
	Arr(int n)
	{
		if (n > 0)
		{
			size = n;
			ar = new T[size];
			for (int i = 0; i < size; i++)
			{
				ar[i] = 0;
			}
		}
		state = -1;
	}
	Arr(int n, T value)
	{
		if (n > 0)
		{
			size = n;
			ar = new T[size];
			for (int i = 0; i < size; i++)
			{
				ar[i] = value;
			}
		}
		state = -1;
	}
	~Arr()
	{
		if (ar) delete[] ar;
	}

	T& operator[](const int index)
	{
		if (index < 0)
		{
			state = -1;
			return ar[size - 1];
		}
		return ar[index];
	}
	Arr operator=(Arr& s)
	{
		size = s.size;
		ar = new T[size];
		for (int i = 0; i < size; i++)
		{
			ar[i] = s.ar[i];
		}
		return *this;
	}
	Arr operator+(Arr& s)
	{
		if (size > s.size)
		{
			size = s.size;
		}
		Arr temp(size);
		for (int i = 0; i < size; i++)
		{
			temp.ar[i] = ar[i] + s.ar[i];
		}
		return temp;
	}
	Arr operator+=(Arr& s)
	{
		if (size > s.size)
		{
			size = s.size;
		}
		for (int i = 0; i < size; i++)
		{
			ar[i] = ar[i] + s.ar[i];
		}
		return *this;
	}
	Arr operator-(Arr& s)
	{
		if (size > s.size)
		{
			size = s.size;
		}
		Arr temp(size);
		for (int i = 0; i < size; i++)
		{
			temp.ar[i] = ar[i] - s.ar[i];
		}
		return temp;
	}
	Arr operator-=(Arr& s)
	{
		if (size > s.size)
		{
			size = s.size;
		}
		for (int i = 0; i < size; i++)
		{
			ar[i] = ar[i] - s.ar[i];
		}
		return *this;
	}
	Arr(Arr& src)
	{
		size = src.size;
		ar = new T[size];
		state = 0;
		for (int i = 0; i < size; i++) ar[i] = src.ar[i];
	}
	Arr(Arr&& src)
	{
		size = src.size;
		ar = new T[size];
		state = 0;
		for (int i = 0; i < size; i++) ar[i] = src.ar[i];
	}

	void Output()
	{
		for (int i = 0; i < size; i++)
		{
			cout << "   " << ar[i];
		}
		cout << endl;
	}
};
void task3()
{
	cout << "Test:" << endl;
	cout << " Enter array size: ";
	int size;
	cin >> size;
	cout << " Enter array value: ";
	int value;
	cin >> value;

	Arr<int> ar1 = Arr<int>();
	Arr<int> ar2 = Arr<int>(size);
	Arr<int> ar3 = Arr<int>(size, value);

	cout << "ar1(): ";
	ar1.Output();
	cout << "ar2(size): ";
	ar2.Output();
	cout << "ar3(size, value): ";
	ar3.Output();

	ar2 += ar3;
	cout << "ar2 += ar3: ";
	ar2.Output();
	ar2 -= ar3;
	cout << "ar2 -= ar3: ";
	ar2.Output();
	cout << "ar3[1]: " << ar3[1] << endl;
	Arr<int> ar4 = ar2 + ar3;
	cout << "ar4 = ar2 + ar3: ";
	ar4.Output();
	Arr<int> ar5 = ar2 - ar3;
	cout << "ar5 = ar2 - ar3: ";
	ar5.Output();
}

/*
Задача 4. Побудувати клас, що описує бінарне дерево стандартної форми.
Побудувати клас ітератор, що дозволяє обходити дерево. Написати програму, яка проходить по бінарному дереву використовуючи ітератор.
*/
class Node
{
public:
	int data;
	Node* left;
	Node* right;

	Node(int value)
	{
		data = value;
		left = NULL;
		right = NULL;
	}
};
class Iterator
{
public:
	Iterator(Node* root)
	{
		if (root->data != NULL)
		{
			cout << root->data << "   ";
			MoveLeft(root);
			MoveRight(root);
		}
	}
	void MoveLeft(Node* current)
	{
		if (current->left != NULL)
		{
			current = current->left;
			cout << current->data << "   ";
			MoveLeft(current);
			MoveRight(current);
		}
		else
		{
			return;
		}
	}
	void MoveRight(Node* current)
	{
		if (current->right != NULL)
		{
			current = current->right;
			cout << current->data << "   ";
			MoveLeft(current);
			MoveRight(current);
		}
		else
		{
			return;
		}
	}
};
void task4()
{
	Node* root = new Node(1);
	cout << root->data << endl;
	root->left = new Node(2);
	cout << root->left->data << "      ";
	root->right = new Node(3);
	cout << root->right->data << endl;
	root->left->left = new Node(4);
	cout << root->left->left->data << "  ";
	root->left->right = new Node(5);
	cout << root->left->right->data << endl;

	Iterator it(root);
}

int main()
{
TASK:	int task_number = task_manager();
	switch (task_number)
	{
	case 1:
		task1();
		break;
	case 2:
		task2();
		break;
	case 3:
		task3();
		break;
	case 4:
		task4();
		break;
	default:
		break;
	}

	string answer;
FIN:	printf("\nDo you want to do one more task? Enter '1' if you do, and '0' if you don`t: ");
	cin >> answer;
	if (answer == "1")
	{
		system("cls");
		goto TASK;
	}
	if (answer == "0")
	{
		system("cls");
		printf("Bye!");
	}
	else
	{
		printf("Please enter 'yes' or 'no'\n");
		goto FIN;
	}
}