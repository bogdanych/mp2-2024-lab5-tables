#include <gtest.h>
#include "massiv.h"

TEST(SortedMas, can_create_default) {
	ASSERT_NO_THROW(SortedMas);
}

TEST(SortedMas, can_insert_element) {
	SortedMas sm;
	ASSERT_NO_THROW(sm.insert("56", Polynom("xyz")));
}

TEST(SortedMas, find_exist_element) {
	SortedMas sm;
	sm.insert("56", Polynom("xyz"));
	ASSERT_EQ(1, sm.search("56"));
}

TEST(SortedMas, not_find_not_exist_element) {
	SortedMas sm;
	sm.insert("56", Polynom("xyz"));
	ASSERT_EQ(0, sm.search("1"));
}

TEST(SortedMas, search_after_delete) {
	SortedMas sm;
	sm.insert("56", Polynom("xyz"));
	sm.del("56");
	ASSERT_EQ(0, sm.search("1"));
}

TEST(SortedMas, delete_not_exist_element) {
	SortedMas sm;
	ASSERT_NO_THROW(sm.del("56"));
}

TEST(SortedMas, search_pol) {
	SortedMas sm;
	Polynom pol("xyz");
	sm.insert("1", pol);
	ASSERT_EQ(sm["1"] == pol, 1);
}

TEST(SortedMas, search_pol_2) {
	SortedMas sm;
	Polynom pol("xyz");
	sm.insert("1", pol);
	ASSERT_EQ(sm["1"] != Polynom("123"), 1);
}

TEST(SortedMas, second_insert) {
	SortedMas sm;
	Polynom pol("xyz");
	sm.insert("1", pol);
	ASSERT_NO_THROW(sm.insert("1", pol));
	sm.insert("1", pol);
	ASSERT_EQ(sm["1"] == pol, 1);
}

TEST(SortedMas, second_insert_2) {
	SortedMas sm;
	Polynom pol("xyz");
	sm.insert("1", pol);
	sm.insert("1", Polynom("x^9"));
	ASSERT_EQ(sm["1"] != pol, 1);
	ASSERT_EQ(sm["1"] == Polynom("x^9"), 1);
}

TEST(SortedMas, second_insert_3) {
	SortedMas sm;
	Polynom pol("xyz");
	sm.insert("1", pol);
	sm.insert("1", Polynom("x^9"));
	ASSERT_EQ(sm["1"] != pol, 1);
	ASSERT_EQ(sm["1"] == Polynom("x^9"), 1);
}

TEST(SortedMas, insert_lot_elements) {
	SortedMas sm;
	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		sm.insert(s, Polynom(s));
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		ASSERT_EQ(sm[s] == Polynom(s), 1);
	}
}

TEST(SortedMas, insert_and_delete_lot_elements) {
	SortedMas sm;
	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		sm.insert(s, Polynom(s));
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		sm.del(s);
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		ASSERT_EQ(sm.search(s), 0);
	}
}

TEST(SortedMas, polynom_ne_nayden) {
	SortedMas sm;
	ASSERT_ANY_THROW(sm["1"]);
}

TEST(SortedMas, insert_after_delete) {
	SortedMas sm;
	sm.insert("1", Polynom("xyz"));
	sm.del("1");
	sm.insert("1", Polynom("xyz"));
	ASSERT_EQ(sm["1"] == Polynom("xyz"), 1);
}