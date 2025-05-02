#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "AVL.h"
#include "doubleHash.h"
#include "massiv.h"
#include <string>

DoubleHash doub;
AVLTree avl;
NotSortedMas nsm;
SortedMas sm;

void create() {
	std::cout << "Введите ключ: \n";
	std::string key, plv;
	std::cin >> key;
	std::cout << "Введите полином: \n";
	std::cin >> plv;
	doub.insert(key, plv);
	std::cout << "Логирование двойного хэша: ";
	doub.get_cnt();
	avl.insert(key, plv);
	std::cout << "Логирование АВЛ-дерева: ";
	avl.get_cnt();
	nsm.insert(key, plv);
	std::cout << "Логирование несортированного массива: ";
	nsm.get_cnt();
	sm.insert(key, plv);
	std::cout << "Логирование сортированного массива: ";
	sm.get_cnt();
	std::cout << '\n';
}


int main() {
	setlocale(LC_ALL, "Russian");
	while (1) {

		std::string oper;
		std::cout << "Выберите операцию: \n1 - создать полином, 2 - удалить полином, 3 - посчтитать арифметическое выражение, 4 - закончить работу\n";
		std::cin >> oper;

		if (oper == "1") {
			create();
			/*doub.display();
			std::cout << '\n';
			avl.print();
			std::cout << '\n';
			sm.display();
			std::cout << '\n';
			nsm.display();
			std::cout << '\n';*/
		}
		else if (oper == "2") {
			std::string key;
			std::cout << "Введите ключ: \n";
			std::cin >> key;
			doub.remove(key);
			std::cout << "Логирование двойного хэша: ";
			doub.get_cnt();
			avl.remove(key);
			std::cout << "Логирование АВЛ-дерева: ";
			avl.get_cnt();
			nsm.del(key);
			std::cout << "Логирование несортированного массива: ";
			nsm.get_cnt();
			sm.del(key);
			std::cout << "Логирование сортированного массива: ";
			sm.get_cnt();
			std::cout << '\n';
		}
		else if (oper == "3") {
			std::string s1, s2, aryth;
			Polynom pol1, pol2, res;
			while (1) {
				std::cout << "Введите выржаение в формате содержащем два ключа полинома, между которыми, через пробел, находится";
				std::cout << " арифметическая операция (сложение, вычитание, умножение)\n";

				try {
					std::cin >> s1 >> aryth >> s2;
					pol1 = doub[s1];
					pol2 = doub[s2];
					if (aryth == "+") {
						res = pol1 + pol2;
						break;
					}
					else if (aryth == "-") {
						res = pol1 - pol2;
						break;
					}
					else if (aryth == "*") {
						res = pol1 * pol2;
						break;
					}
					else {
						std::cout << "Некорректный ввод\n";
						continue;
					}
				}
				catch (const std::exception& e) {
					std::cout << e.what() << '\n';
				}
			}
			doub.set_cnt();
			avl.set_cnt();
			nsm.set_cnt();
			sm.set_cnt();
			res.display();
			std::cout << "Сохранить под именем:\n";
			std::cin >> s1;
			doub.insert(s1, res);
			std::cout << "Логирование двойного хэша: ";
			doub.get_cnt();
			avl.insert(s1, res);
			std::cout << "Логирование АВЛ-дерева: ";
			avl.get_cnt();
			nsm.insert(s1, res);
			std::cout << "Логирование несортированного массива: ";
			nsm.get_cnt();
			sm.insert(s1, res);
			std::cout << "Логирование сортированного массива: ";
			sm.get_cnt();
			std::cout << '\n';
		}
		else if (oper == "4") {
			break;
		}
		else
			std::cout << "Некорректный ввод\n";
		
	}
}