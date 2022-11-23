#include <UUU/UUU.h>
#include <matplot/matplot.h>
#include <set>

void matplot_show() {
    using namespace matplot;
    auto x = transform(iota(1, 10), [](double x) { return pow(x, 2); });
    plot(x);
    title("My title");

    show();
}

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include <chrono> 
#include <fstream>

void create_data_1(long int n, long int m){ // кол-во элементов, количество уникальности
	std::ofstream out;          // поток для записи
	out.open("prog_1.txt"); // окрываем файл для записи
	if (out.is_open()) // 20000
	{
		for (long int i = 0; i < n; ++i) {
			out << rand() % m + 1 << " ";
		}
	}
	out.close();
}

#include <string>
#include <sstream>

std::vector <int> invert(int n)
{
	std::string line;
	std::vector <int> num(n);

	std::ifstream in("prog_1.txt"); // окрываем файл для чтения
	if (in.is_open())
	{
		while (getline(in, line))
		{
			//std::cout << line << std::endl;
		}
	}
	in.close();     // закрываем файл

	std::istringstream ss(line);
	for (int i = 0; i < n; ++i) {
		ss >> num[i];
	}
	return num;
}

void prog_1(int n, std::vector<int>& num) {
	//прога находит столовку, которую дольше остальных не посещали

	std::vector<int> as(200001, -1);
	for (int i = 0; i < n; i += 1) {
		as[num[i]] = n - i - 1;
	}

	//std::cout << std::distance(as.begin(), std::max_element(as.begin(), as.end()));
}

#include <unordered_set>

void prog_2(int n, std::vector<int>& num) {

	std::vector<int> data(n, 0);
	for (int i = 0; i < n; i += 1) {
		std::cin >> data[i];
		
	}
	std::unordered_set<int> unique;
	unique.reserve(200000);
	int idx_unique = n;
	for (int i = n - 1; 0 <= i; i -= 1) {
		if (unique.find(data[i]) != unique.end()) {
			idx_unique = data[i];
			unique.insert(idx_unique);
		}
	}
	//std::cout << idx_unique;
}


#include <unordered_set>
/*
void prog_2() {
	int n = 0;
	std::cin >> n;
	std::vector<int> data(n, 0);
	for (int i = 0; i < n; i += 1) {
		std::cin >> data[i];

	}
	std::unordered_set<int> unique;
	unique.reserve(200000);
	int idx_unique = n;
	for (int i = n - 1; 0 <= i; i -= 1) {
		if (!unique.contains(data[i])) {
			idx_unique = data[i];
			unique.insert(idx_unique);

		}

	}
	std::cout << idx_unique;

}*/

#include <algorithm>

int main() {
	std::vector <int> num;
	std::vector <std::vector <int>> second(10);
	for (int m = 1; m <= 10; m++) {
		for (int n = 1000; n <= 20000; n = n + 1000) {
			auto start_work = std::chrono::steady_clock::now();
			create_data_1(n, m);
			num = invert(n);
			prog_1(n, num);
			auto end_work = std::chrono::steady_clock::now();
			second[m - 1].push_back(std::chrono::duration_cast<std::chrono::milliseconds>(end_work - start_work).count());
			num.clear();
		}
	}
	for (int m = 0; m < 10; m++) {
		for (int i = 0; i < second.size(); i++) {
			std::cout << second[m][i] << " ";
		}
		std::cout << "\n";
	}

	return 0;
}
//генерим значения
//пропускаем их через две проги
//отлавливаем время работы
//строим статистику
//n - количество элементов на входе
//t - время работы при определенном количестве элементов
//n и t/n оси
// k - коэф уникальных значений к n - процент уникальных значений от всех значений
//автоматическое тестирование проги при разных значениях

/*
1 2 6 3 1 2 3 1 // уникальные значения - какие могут встречаться 

1 -> 8735
2 -> 4357
3 -> 34951
6 

n
unordered_map<int,int>{ не поределен хеш для вектора и тд (а мапу норм)
    m[1] = 7
    m[2] = 5
    m[3] = 6
    m[6] = 2
}


*/