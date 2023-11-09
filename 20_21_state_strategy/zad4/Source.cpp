#include<iostream>
#include<chrono>
#define MAX_VREDNOST 10

class SortAlgorithm {
public:
	virtual void sort(int* arr, int n) = 0;
	virtual ~SortAlgorithm() {}
};

class CountingSort : public SortAlgorithm {
public:
	void sort(int* arr, int n) override {
		int counter[MAX_VREDNOST];
		for (int i = 0; i < n; i++)
			counter[arr[i]] += 1;
		int i = 0;
		for (int value = 0; value < MAX_VREDNOST; value++) {
			for (int b = 0; b < counter[value]; b++) {
				arr[i++] = value;
			}
		}
	}
};

class SelectionSort : public SortAlgorithm {
public:
	void sort(int* arr, int n) override {
		for (int i = 0; i < n; i++) {
			int min = arr[i];
			int index_of_minimum = i;
			for (int j = i + 1; j < n; j++) {
				if (arr[j] < min) {
					min = arr[j];
					index_of_minimum = j;
				}
			}
			int tmp = arr[i];
			arr[i] = min;
			arr[index_of_minimum] = tmp;
		}
	}
};

class Arr {
	int* arr;
	int n;
	SortAlgorithm* algorithm;
public:
	Arr(int n): n(n), arr(new int[n]()) {}
	void setSortAlgorithm(SortAlgorithm* alg) {
		this->algorithm = alg;
	}
	int& operator[] (int index) { return arr[index]; }
	int operator[] (int index) const { return arr[index]; }
	void sort() { algorithm->sort(arr, n); }
	int size() const { return n; }
	~Arr() { 
		delete[] arr;
		arr = nullptr;
	}
};

int main() {
	Arr a(100000);
	Arr b(100000);

	for (int i = 0; i < a.size(); i++) {
		a[i] = rand() % MAX_VREDNOST;
		b[i] = rand() % MAX_VREDNOST;
	}

	auto start = std::chrono::system_clock::now();
	a.setSortAlgorithm(new SelectionSort());
	a.sort();
	auto end = std::chrono::system_clock::now();
	auto elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Speed of selection sort: " << elapsed << " microseconds\n";
	
	start = std::chrono::system_clock::now();
	b.setSortAlgorithm(new CountingSort());
	b.sort();
	end = std::chrono::system_clock::now();
	elapsed = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
	std::cout << "Speed of counting sort: " << elapsed << " microseconds\n";

	return 0;
}