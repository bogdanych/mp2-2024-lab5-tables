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
	std::cout << "������� ����: \n";
	std::string key, plv;
	std::cin >> key;
	std::cout << "������� �������: \n";
	std::cin >> plv;
	doub.insert(key, plv);
	std::cout << "����������� �������� ����: ";
	doub.get_cnt();
	avl.insert(key, plv);
	std::cout << "����������� ���-������: ";
	avl.get_cnt();
	nsm.insert(key, plv);
	std::cout << "����������� ���������������� �������: ";
	nsm.get_cnt();
	sm.insert(key, plv);
	std::cout << "����������� �������������� �������: ";
	sm.get_cnt();
	std::cout << '\n';
}


int main() {
	setlocale(LC_ALL, "Russian");
	while (1) {

		std::string oper;
		std::cout << "�������� ��������: \n1 - ������� �������, 2 - ������� �������, 3 - ���������� �������������� ���������, 4 - ��������� ������\n";
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
			std::cout << "������� ����: \n";
			std::cin >> key;
			doub.remove(key);
			std::cout << "����������� �������� ����: ";
			doub.get_cnt();
			avl.remove(key);
			std::cout << "����������� ���-������: ";
			avl.get_cnt();
			nsm.del(key);
			std::cout << "����������� ���������������� �������: ";
			nsm.get_cnt();
			sm.del(key);
			std::cout << "����������� �������������� �������: ";
			sm.get_cnt();
			std::cout << '\n';
		}
		else if (oper == "3") {
			std::string s1, s2, aryth;
			Polynom pol1, pol2, res;
			while (1) {
				std::cout << "������� ��������� � ������� ���������� ��� ����� ��������, ����� ��������, ����� ������, ���������";
				std::cout << " �������������� �������� (��������, ���������, ���������)\n";

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
						std::cout << "������������ ����\n";
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
			std::cout << "��������� ��� ������:\n";
			std::cin >> s1;
			doub.insert(s1, res);
			std::cout << "����������� �������� ����: ";
			doub.get_cnt();
			avl.insert(s1, res);
			std::cout << "����������� ���-������: ";
			avl.get_cnt();
			nsm.insert(s1, res);
			std::cout << "����������� ���������������� �������: ";
			nsm.get_cnt();
			sm.insert(s1, res);
			std::cout << "����������� �������������� �������: ";
			sm.get_cnt();
			std::cout << '\n';
		}
		else if (oper == "4") {
			break;
		}
		else
			std::cout << "������������ ����\n";

	}
}