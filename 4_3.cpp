//На вокзале есть некоторое количество тупиков, куда прибывают электрички.Этот вокзал является их конечной станцией.
//Дано расписание движения электричек, в котором для каждой электрички указано время ее прибытия, а также время отправления в следующий рейс.
//Электрички в расписании упорядочены по времени прибытия.Когда электричка прибывает, ее ставят в свободный тупик с минимальным номером.
//При этом если электричка из какого - то тупика отправилась в момент времени X, то электричку, которая прибывает в момент времени X, 
//в этот тупик ставить нельзя, а электричку, прибывающую в момент X + 1 — можно.В данный момент на вокзале достаточное количество тупиков 
//для работы по расписанию.Напишите программу, которая по данному расписанию определяет, какое минимальное количество тупиков требуется для работы вокзала.

#include "stdafx.h"
#include <iostream>
#include <assert.h>
using namespace std;
struct train {
	int a = 0;
	int b = 0;
	train() = default;
	train(int x, int y) : a(x), b(y) {}
	void set(int x, int y) { a = x; b = y; }
};


bool IsLess(const train& l, const train& r) {

	return l.a < r.a;

}


template<class T, class Compare>
class Heap {
public:
	Heap(T* mas, int size, Compare cmp);  // конструктор кучи
	~Heap();
	int getsize();
	
	T ExtractMin(Compare cmp);

private:
	void Heapify(int i, Compare cmp);
	void BuildHeap(int i, Compare cmp);
	T * mas;
	int RealSize;
	int HeapSize;
};
template<class T, class Compare>
Heap<T, Compare>::Heap(T* mas2, int size, Compare cmp) : RealSize(0)
{
	mas = mas2;
	HeapSize = size;
	BuildHeap(0, cmp);
}
template<class T, class Compare>
Heap<T, Compare>::~Heap()
{
	delete[] mas;
}
template<class T, class Compare>
int Heap<T, Compare>::getsize() {
	return HeapSize;
}

template<class T, class Compare>
void Heap<T, Compare>::Heapify(int i, Compare cmp)
{
	int left = 2 * i + 1;
	int right = 2 * i + 2;
	int largest = i;
	if (left < HeapSize && cmp(mas[left], mas[i])) largest = left;
	if (right < HeapSize && cmp(mas[right], mas[largest])) largest = right;

	if (largest != i) {
		std::swap(mas[i], mas[largest]);
		Heapify(largest, cmp);
	}
}
template<class T, class Compare>
T Heap<T, Compare>::ExtractMin(Compare cmp)
{
	assert(HeapSize != 0);
	// Запоминаем значение корня. 
	T result = mas[0];
	// Переносим последний элемент в корень.
	mas[0] = mas[HeapSize - 1];
	HeapSize--;
	// Вызываем heapify для корня, 
	if (HeapSize != 0) {
		Heapify(0, cmp);
	}
	return result;
}

template<class T, class Compare>
void Heap<T, Compare>::BuildHeap(int i, Compare cmp)
{
	for (int i = HeapSize / 2 - 1; i >= 0; --i) {
		Heapify(i, cmp);
	}
}
template<class T, class Compare >
int search(Heap<T, Compare>* A, int size, Compare cmp) {
	int count = 1, max = 0;
	//while (A->getsize() != 0) {
	train tmp = A->ExtractMin(cmp);
	train prev, cur, next, tmp2; bool flag = 0, flag2 = 0;
	for (int i = A->getsize(); i>0; i--) {
		//prev = cur;
		if (flag == 0)
			cur = A->ExtractMin(cmp);
		flag = 0;
		if (cur.a <= tmp.b)
		{
			if (flag2 == 0)
				tmp2 = tmp;
			flag2 = 1;
			count++;
			if (A->getsize() != 0)
			{
				next = A->ExtractMin(cmp);
				if (next.a > tmp.b) {
					tmp = cur;
					flag2 = 0;

				}
				flag = 1;
				if (cur.b < tmp2.b)
					tmp2 = cur;
				//tmp2 = cur;
				prev = cur;
				cur = next;
			}
			if (cur.a>tmp2.b && (tmp.a != prev.a || flag2 == 0))
			{
				tmp = tmp2; flag2 = 0;
			}
		}

		if (cur.a > tmp.b&&flag == 0)
		{

			if (count>max)
				max = count;
			count = 1;
			tmp = cur; //flag = 1;
					   //break;
		}

	}
	if (count>max)
		max = count;
	//cout << count;

	return max;
}

int main()
{
	int a = 0, b = 0, size = 0;
	cin >> size;
	train* mas = new train[size];
	for (int i = 0; i < size; ++i) {
		cin >> a >> b;
		mas[i].set(a, b);
	}
	Heap<train, bool(*)(const train&, const train&)> A(mas, size, IsLess);
	cout << search<train, bool(*)(const train&, const train&)>(&A, size, IsLess) << endl;
	return 0;
}
