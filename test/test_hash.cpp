#include <gtest.h>
#include "doubleHash.h"

TEST(DoubleHash, can_create_default) {
	ASSERT_NO_THROW(DoubleHash());
}

TEST(DoubleHash, can_insert_element) {
	DoubleHash hash;
	ASSERT_NO_THROW(hash.insert("56", Polynom("xyz")));
}

TEST(DoubleHash, find_exist_element) {
	DoubleHash hash;
	hash.insert("56", Polynom("xyz"));
	ASSERT_EQ(1, hash.search("56"));
}

TEST(DoubleHash, not_find_not_exist_element) {
	DoubleHash hash;
	hash.insert("56", Polynom("xyz"));
	ASSERT_EQ(0, hash.search("1"));
}

TEST(DoubleHash, search_after_delete) {
	DoubleHash hash;
	hash.insert("56", Polynom("xyz"));
	hash.remove("56");
	ASSERT_EQ(0, hash.search("1"));
}

TEST(DoubleHash, delete_not_exist_element) {
	DoubleHash hash;
	ASSERT_NO_THROW(hash.remove("56"));
}

TEST(DoubleHash, search_pol) {
	DoubleHash hash;
	Polynom pol("xyz");
	hash.insert("1", pol);
	ASSERT_EQ(hash["1"] == pol, 1);
}

TEST(DoubleHash, search_pol_2) {
	DoubleHash hash;
	Polynom pol("xyz");
	hash.insert("1", pol);
	ASSERT_EQ(hash["1"] != Polynom("123"), 1);
}

TEST(DoubleHash, second_insert) {
	DoubleHash hash;
	Polynom pol("xyz");
	hash.insert("1", pol);
	ASSERT_NO_THROW(hash.insert("1", pol));
	hash.insert("1", pol);
	ASSERT_EQ(hash["1"] == pol, 1);
}

TEST(DoubleHash, second_insert_2) {
	DoubleHash hash;
	Polynom pol("xyz");
	hash.insert("1", pol);
	hash.insert("1", Polynom("x^9"));
	ASSERT_EQ(hash["1"] != pol, 1);
	ASSERT_EQ(hash["1"] == Polynom("x^9"), 1);
}

TEST(DoubleHash, second_insert_3) {
	DoubleHash hash;
	Polynom pol("xyz");
	hash.insert("1", pol);
	hash.insert("1", Polynom("x^9"));
	ASSERT_EQ(hash["1"] != pol, 1);
	ASSERT_EQ(hash["1"] == Polynom("x^9"), 1);
}

TEST(DoubleHash, insert_lot_elements) {
	DoubleHash hash;
	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		hash.insert(s, Polynom(s));
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		ASSERT_EQ(hash[s] == Polynom(s), 1);
	}
}

TEST(DoubleHash, insert_and_delete_lot_elements) {
	DoubleHash hash;
	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		hash.insert(s, Polynom(s));
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		hash.remove(s);
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		ASSERT_EQ(hash.search(s), 0);
	}
}

TEST(DoubleHash, polynom_ne_nayden) {
	DoubleHash hash;
	ASSERT_ANY_THROW(hash["1"]);
}

TEST(DoubleHash, insert_after_delete) {
	DoubleHash hash;
	hash.insert("1", Polynom("xyz"));
	hash.remove("1");
	hash.insert("1", Polynom("xyz"));
	ASSERT_EQ(hash["1"] == Polynom("xyz"), 1);
}