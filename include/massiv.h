#pragma once

#include <string>
#include <iostream>
#include "vector.h"
#include "polynoms.h"

class SortedMas {
	Vector<Polynom> pols;
	Vector<std::string> s;
	int size;
	int oper = 0;

	int get_index(const std::string& key) {
		int l = 0, r = size - 1;
		int mid;
		while (l <= r) {
			oper += 2;
			mid = (l + r) >> 1;
			if (s[mid] <= key) {
				oper++;
				r = mid - 1;
			}
			else {
				oper += 2;
				l = mid + 1;
			}
		}
		oper++;
		if (l < size && s[l] == key) {
			return l;
		}
		return -1;
	}

public:
	SortedMas() : size(0) {}

	void insert(const std::string& key, const Polynom& pol) {
		int it = get_index(key); oper++;

		oper++;
		if (it != -1) {
			oper++;
			if (pols[it] == pol)
				return;
			del(key, it); // ������� ���������
		}

		s.push_back(key);
		pols.push_back(pol);
		size++;
		oper++;

		for (int i = size - 1; i > 0 && s[i] > s[i - 1]; i--) {
			swap(s[i], s[i - 1]);
			std::swap(pols[i], pols[i - 1]);
			oper += 2;
		}
	}

	void del(const std::string& key, int it = -1) {
		oper++;
		if (it == -1) {
			it = get_index(key);
			oper++;
		}
		oper++;
		if (it != -1) {
			for (; it < size - 1; it++) {
				std::swap(s[it], s[it + 1]);
				std::swap(pols[it], pols[it + 1]);
				oper += 2;
			}
			s.pop_back();
			pols.pop_back();
			size--;
			oper++;
		}
	}

	bool search(const std::string& key) {
		return (get_index(key) != -1);
	}

	Polynom& operator[] (const std::string& key)
	{
		int ind = get_index(key);
		if (ind != -1)
			return pols[ind];
		throw std::exception("������� �� ������");
	}

	void display() {
		for (int i = 0; i < size; i++) {
			std::cout << s[i] << ' ';
			pols[i].display();
		}
	}

	void get_cnt() {
		std::cout << oper << '\n';
		oper = 0;
	}

	void set_cnt() {
		oper = 0;
	}
};


class NotSortedMas {
	Vector<Polynom> pols;
	Vector<std::string> s;
	int size;
	int oper = 0;

	int get_index(const std::string& key) {
		for (int i = 0; i < size; i++, oper++) {
			oper++;
			if (s[i] == key) {
				return i;
			}
		}
		return -1;
	}

public:
	NotSortedMas() : size(0) {}

	void insert(const std::string& key, const Polynom& pol) {
		int it = get_index(key); oper++;

		oper++;
		if (it != -1) {
			if (pols[it] == pol)
				return;
			del(key, it);
		}

		s.push_back(key);
		pols.push_back(pol);
		size++;
		oper++;
	}

	bool search(const std::string& key) {
		return (get_index(key) != -1);
	}

	void del(const std::string& key, int it = -1) {
		oper++;
		if (it == -1) {
			it = get_index(key);
			oper++;
		}
		oper++;
		if (it != -1) {
			for (; it < size - 1; it++, oper += 2) {
				std::swap(s[it], s[it + 1]);
				std::swap(pols[it], pols[it + 1]);
			}
			s.pop_back();
			pols.pop_back();
			size--;
			oper++;
		}
	}

	Polynom& operator[] (const std::string& key)
	{
		int ind = get_index(key);
		if (ind != -1)
			return pols[ind];
		throw std::exception("������� �� ������");
	}

	void display() {
		for (int i = 0; i < size; i++) {
			std::cout << s[i] << ' ';
			pols[i].display();
		}
	}

	void get_cnt() {
		std::cout << oper << '\n';
		oper = 0;
	}

	void set_cnt() {
		oper = 0;
	}
};