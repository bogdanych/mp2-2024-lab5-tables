#pragma once


struct Node {
public:
    double data; // ������ ����
    int ind; // ������ �������� ��������� �������
    Node* next; // ��������� �� ��������� ����
    // ������� ���������. ��������
    Node(double value, int index) : data(value), ind(index), next(nullptr) {}
};


class ListIterator {
public:
    ListIterator(Node* ptr) : m_ptr(ptr) {}

    double& operator*() const {
        return m_ptr->data;
    }

    ListIterator operator++(int) {
        ListIterator temp = *this;
        m_ptr = m_ptr->next;  // ������� � ���������� ����
        return temp;
    }

    ListIterator& operator++() {
        m_ptr = m_ptr->next;  // ������� � ���������� ����
        return *this;
    }

    bool operator==(const ListIterator& other) const {
        return m_ptr == other.m_ptr;
    }

    bool operator!=(const ListIterator& other) const {
        return m_ptr != other.m_ptr;
    }

    int ind() {
        return m_ptr->ind;
    }

private:
    Node* m_ptr;
};


class List {
    Node* head = nullptr;
    Node* ptr = nullptr;
public:
    List() : head(nullptr) {}

    List(std::initializer_list<double> lst) {
        int i = 0;
        for (auto& el : lst) {
            push_back(el, i++);
        }
    }

    List(const List& l) : head(nullptr), ptr(nullptr) {
        if (l.head != nullptr) {
            Node* rp = l.head;
            head = new Node{ rp->data, rp->ind };
            Node* lp = head;
            ptr = head;
            while (rp->next != nullptr) {
                rp = rp->next;
                lp->next = new Node{ rp->data,  rp->ind };
                lp = lp->next;
            }
        }
    }

    ~List() {
        clear();
    }

    bool operator==(const List& l) {
        auto it1 = l.begin(), it2 = begin();
        for (; it1 != nullptr && it2 != nullptr && *it1 == *it2 && it1.ind() == it2.ind(); ++it1, ++it2) {}
        return (it1 == nullptr && it2 == nullptr);
    }

    bool operator!=(const List& l) {
        return !(*this == l);
    }

    void operator=(const List& l) {
        if (this != &l) {
            clear();
            for (auto it = l.begin(); it != l.end(); ++it) {
                push_back(*it, it.ind());
            }
        }
    }

    int ind() {
        return ptr->ind;
    }

    void clear() {
        Node* current = head;
        while (current != nullptr) {
            Node* temp = current;
            current = current->next;
            delete temp;
        }
        head = nullptr;
    }

    //���������, ��������� �� ind
    void append(double value, int ind) {
        Node* newNode = new Node(value, ind);
        Node* current = head;
        if (current == nullptr) {
            head = newNode;
            ptr = head;
        }
        else {
            while (current->next != nullptr && ind > current->next->ind) {
                current = current->next;
            }
            if (ind < head->ind) {
                newNode->next = head;
                head = newNode;

            }
            else if (current->next != nullptr && current->next->ind == ind)
                current->next->data += value; //���� ������� ���������� �������, �� ���������� ��������
            else if (current->ind == ind)
                current->data += value; // current == head
            else {
                newNode->next = current->next;
                current->next = newNode; // "����������" newNode
            }
            if (ptr->ind < ind)
                ptr = ptr->next;
        }
    }

    // ��������� � �����
    void push_back(double value, int ind) {
        Node* newNode = new Node(value, ind);
        if (head == nullptr) {
            head = newNode;
            ptr = head;
        }
        else {
            newNode->next = ptr->next;
            ptr->next = newNode;
            ptr = ptr->next;
        }

    }

    // ����������� ��������� ������
    void display() {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << '(' << current->ind << ") " << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }

    // ��������� �� ������ �����
    ListIterator begin() const {
        return ListIterator(head);
    }

    // ��������� �� nullptr
    ListIterator end() const {
        return ListIterator(nullptr);
    }
};