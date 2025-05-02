#pragma once

#include "polynoms.h"
#include "vector.h"
#include <string>
#include <vector>
#include <iostream>
#include <cmath>

int oper = 0;

int binpow(long long a, int n, int mod) {
    long long res = 1;
    while (n) {
        if (n % 2 == 1) {
            res *= a;
            res %= mod;
        }
        a *= a;
        a %= mod;
        n >>= 1;
    }
    return res;
}


int hashf(const std::string& s, int mod) {
    long long ans = 0;
    for (int i = 0; i < s.size(); i++, oper++) {
        // ������� �� 256 ���������
        ans += 1ll * s[i] * binpow(256ll, i, mod);
        ans %= mod;
        oper++;
    }
    return ans;
}

int hash1(const std::string& key, int mod) {
    return hashf(key, mod);
}

int hash2(const std::string& key, int mod) {
    return 1 + hashf(key, mod - 1);
}

bool is_simple(int n) {
    for (int i = 2; i * i <= n; i++, oper++) {
        oper++;
        if (n % i == 0)
            return 0;
    }
    return 1;
}


class DoubleHash {
private:
    Vector<std::string> table;
    Vector<Polynom> pol_table;
    Vector<int> is_del;
    int size;
    int currentSize;

    void increase_size() {
        // �� �������� �����������, �.�. �� ��������������� �� �������
        int new_size = size * 2 + 1;
        // ���� ��������� ������� �����
        while (!is_simple(new_size)) {
            oper++;
            new_size++;
        }
        Vector<std::string> new_table(new_size);
        Vector<Polynom> new_pol_table(new_size);

        for (int i = 0; i < size; i++, oper++) {
            oper++;
            if (table[i] != "" && is_del[i] == false) {
                int index1 = hash1(table[i], new_size);
                int index2 = hash2(table[i], new_size);
                int index = index1;
                oper++;

                while (new_table[index] != "") {
                    index = (index + index2) % new_size;
                    oper += 2;
                }
                new_pol_table[index] = pol_table[i];
                new_table[index] = table[i];
                oper++;
            }
        }
        is_del.resize(new_size, false);
        table = new_table;
        pol_table = new_pol_table;
        size = new_size;
        oper += 3;
    }

    int get_index(const std::string& key) {
        int index1 = hash1(key, size);
        int index2 = hash2(key, size);
        int index = index1;
        oper++;

        for (int i = 0; i < size; i++) {
            oper += 2;
            if (table[index] == key && is_del[index] == 0) {
                return index;
            }
            oper++;
            if (table[index] == "" && is_del[index] == 0) {
                return -1;
            }
            index = (index + index2) % size;
            oper++;
        }

        return -1;
    }

public:
    DoubleHash() : size(11), currentSize(0) {
        table.resize(size);
        pol_table.resize(size);
        is_del.resize(size, 0);
    }

    void insert(const std::string& key, const Polynom& pol) {
        // �� ����� �������� ��������� ����� ���� �������
        // �������� �������, ����� �� ������������� � ����� (������� ������)
        oper++;
        if (currentSize >= size / 2) {
            increase_size();
        }

        currentSize++;

        int index1 = hash1(key, size);
        int index2 = hash2(key, size);
        int index = index1;
        oper++;

        while (table[index] != "" && is_del[index] == 0) {
            oper += 2;
            if (table[index] == key) {
                pol_table[index] = pol; // ��������
                is_del[index] = 0;
                oper++;
                return;
            }
            index = (index + index2) % size;
            oper++;
        }

        pol_table[index] = pol;
        table[index] = key;
        is_del[index] = 0;

        oper++;
        //display();
    }

    void remove(const std::string& key) {
        int index1 = hash1(key, size);
        int index2 = hash2(key, size);
        int index = index1;

        oper++;

        int i;
        // �������������� ��������� ��� �������� �������, ���� �� ��������� ������ �� �����
        for (i = 0; i < size; i++, oper++) {
            oper++;
            if (table[index] == key) {
                break;
            }
            oper++;
            if (table[index] == "" && is_del[index] == 0) {
                return;
            }
            index = (index + index2) % size;
            oper++;
        }

        // ���� ������ ���� � �� ����� - ������ � ���������� �������
        oper++;
        if (i < size) {
            currentSize--;
            is_del[index] = 1;
        }
    }

    bool search(const std::string& key) {
        return (get_index(key) != -1);
    }

    Polynom& operator[] (const std::string& key)
    {
        int ind = get_index(key);
        if (ind != -1)
            return pol_table[ind];
        throw std::exception("������� �� ������");
    }

    void display() {
        for (int i = 0; i < size; i++) {
            //std::cout << table[i] << ' ';
            if (table[i] != "" && is_del[i] == 0) {
                std::cout << "Index " << i << ": ";
                pol_table[i].display();
            }
        }
    }

    void set_cnt() {
        oper = 0;
    }

    void get_cnt() {
        std::cout << oper << '\n';
        oper = 0;
    }
};