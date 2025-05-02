#include <gtest.h>
#include "AVL.h"

TEST(AVLTree, can_create_default) {
	ASSERT_NO_THROW(AVLTree());
}

TEST(AVLTree, can_insert_element) {
	AVLTree avl;
	ASSERT_NO_THROW(avl.insert("56", Polynom("xyz")));
}

TEST(AVLTree, find_exist_element) {
	AVLTree avl;
	avl.insert("56", Polynom("xyz"));
	ASSERT_EQ(1, avl.search("56"));
}

TEST(AVLTree, not_find_not_exist_element) {
	AVLTree avl;
	avl.insert("56", Polynom("xyz"));
	ASSERT_EQ(0, avl.search("1"));
}

TEST(AVLTree, search_after_delete) {
	AVLTree avl;
	avl.insert("56", Polynom("xyz"));
	avl.remove("56");
	ASSERT_EQ(0, avl.search("1"));
}

TEST(AVLTree, delete_not_exist_element) {
	AVLTree avl;
	ASSERT_NO_THROW(avl.remove("56"));
}

TEST(AVLTree, search_pol) {
	AVLTree avl;
	Polynom pol("xyz");
	avl.insert("1", pol);
	ASSERT_EQ(avl["1"] == pol, 1);
}

TEST(AVLTree, search_pol_2) {
	AVLTree avl;
	Polynom pol("xyz");
	avl.insert("1", pol);
	ASSERT_EQ(avl["1"] != Polynom("123"), 1);
}

TEST(AVLTree, second_insert) {
	AVLTree avl;
	Polynom pol("xyz");
	avl.insert("1", pol);
	ASSERT_NO_THROW(avl.insert("1", pol));
	avl.insert("1", pol);
	ASSERT_EQ(avl["1"] == pol, 1);
}

TEST(AVLTree, second_insert_2) {
	AVLTree avl;
	Polynom pol("xyz");
	avl.insert("1", pol);
	avl.insert("1", Polynom("x^9"));
	ASSERT_EQ(avl["1"] != pol, 1);
	ASSERT_EQ(avl["1"] == Polynom("x^9"), 1);
}

TEST(AVLTree, second_insert_3) {
	AVLTree avl;
	Polynom pol("xyz");
	avl.insert("1", pol);
	avl.insert("1", Polynom("x^9"));
	ASSERT_EQ(avl["1"] != pol, 1);
	ASSERT_EQ(avl["1"] == Polynom("x^9"), 1);
}

TEST(AVLTree, insert_lot_elements) {
	AVLTree avl;
	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		avl.insert(s, Polynom(s));
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		ASSERT_EQ(avl[s] == Polynom(s), 1);
	}
}

TEST(AVLTree, insert_and_delete_lot_elements) {
	AVLTree avl;
	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		avl.insert(s, Polynom(s));
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		avl.remove(s);
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		ASSERT_EQ(avl.search(s), 0);
	}
}

TEST(AVLTree, polynom_ne_nayden) {
	AVLTree avl;
	ASSERT_ANY_THROW(avl["1"]);
}

TEST(AVLTree, insert_after_delete) {
	AVLTree avl;
	avl.insert("1", Polynom("xyz"));
	avl.remove("1");
	avl.insert("1", Polynom("xyz"));
	ASSERT_EQ(avl["1"] == Polynom("xyz"), 1);
}