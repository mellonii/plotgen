#include <UUU/UUU.h>
#include <matplot/matplot.h>
#include <set>

void matplot_show(std::vector<double>& num1, std::vector<double>& num2, int i) {
    using namespace matplot;
	plot(num1);
	hold(on);

	plot(num2);
	hold(off);

    //show();
	std::string name = "graf_" + std::to_string(i) + ".jpg";
	//save(name);
	save(name);
}

void matplot_show_one(std::vector<double>& num) {
	using namespace matplot;
	plot(num);
	show();
}

#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

#include <chrono> 
#include <fstream>
void create_data(long int n, long int m){ // кол-во элементов, количество уникальности
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
std::vector <int> invert(int n)
{
	std::string line;
	std::vector <int> num(n);

	std::ifstream fin;
	fin.open("prog_1.txt");
	for (int i = 0; i < n; i += 1) {
		fin >> num[i];
	}
	fin.close();
	return num;
}

#include <unordered_set>
auto prog_1(int n, std::vector<int>& num) {
	//прога находит столовку, которую дольше остальных не посещали

	auto start_work = std::chrono::steady_clock::now();
	std::vector<int> as(200001, -1);
	for (int i = 0; i < n; i += 1) {
		as[num[i]] = n - i - 1;
	}
	std::distance(as.begin(), std::max_element(as.begin(), as.end()));
	auto end_work = std::chrono::steady_clock::now();
	return (end_work - start_work).count();
}
auto prog_2(int n, std::vector<int>& data) {

	auto start_work = std::chrono::steady_clock::now();
	std::unordered_set<int> unique;
	unique.reserve(200000+1);
	int idx_unique = n;
	for (int i = n - 1; 0 <= i; i -= 1) {
		if (unique.find(data[i]) != unique.end()) {
			idx_unique = data[i];
			unique.insert(idx_unique);
		}
	}
	auto end_work = std::chrono::steady_clock::now();
	return (end_work - start_work).count();
	//std::cout << idx_unique;
}

int main() {
	srand(time(NULL));
	std::ofstream out;
	out.open("otchet.md");
	out << "The program generates for each m (from 1 to 200000 with a step of m *= 2) n integers with values from 1 to 200000 with a step of n *= 1.318, where m is the number of unique values. "
		<< "Then it passes these values through the given two programs and calculates their operating time using chrono and builds graphs with axes n and t/n. \n\n"
		<< "Link to [github](https://github.com/mellonii/plotgen)\n"
		<< "Prepared by: Ishkuvatova Milena\n\n";

	std::vector <int> num;

	for (int m = 1; m <= 200000; m *= 2) {
		std::vector <double> y_1;
		std::vector <double> y_2;
		for (double i = 1; i <= 200000; i *= 1.318) {
			int n = ceil(i);
			create_data(n, m);
			auto start_work = std::chrono::steady_clock::now();
			num = invert(n);
			auto end_work = std::chrono::steady_clock::now();
			//std::chrono::duration_cast<std::chrono::milliseconds>(end_work - start_work).count() - время обращения к данным
			//std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end_work - start_work).count() << "ms ";
			//std::cout << num.size() << " " <<  prog_2(n, num) << "\n";
			y_1.push_back(prog_1(n, num) / (double)(n * 100000));
			y_2.push_back(prog_2(n, num) / (double)(n * 100000));
		}

		matplot_show(y_1, y_2, m);
		std::string name = "graf_" + std::to_string(m) + ".jpg";
		out << "M = " << m << "\n![["<< name <<"]] \n";
	}

	//matplot_show(y_1, y_2);

	//matplot_show_one(y_1);
	//matplot_show_one(y_2);
	
	out.close();

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