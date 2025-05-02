#include <gtest.h>
#include "massiv.h"

TEST(NotSortedMas, can_create_default) {
	ASSERT_NO_THROW(NotSortedMas);
}

TEST(NotSortedMas, can_insert_element) {
	NotSortedMas nsm;
	ASSERT_NO_THROW(nsm.insert("56", Polynom("xyz")));
}

TEST(NotSortedMas, find_exist_element) {
	NotSortedMas nsm;
	nsm.insert("56", Polynom("xyz"));
	ASSERT_EQ(1, nsm.search("56"));
}

TEST(NotSortedMas, not_find_not_exist_element) {
	NotSortedMas nsm;
	nsm.insert("56", Polynom("xyz"));
	ASSERT_EQ(0, nsm.search("1"));
}

TEST(NotSortedMas, search_after_delete) {
	NotSortedMas nsm;
	nsm.insert("56", Polynom("xyz"));
	nsm.del("56");
	ASSERT_EQ(0, nsm.search("1"));
}

TEST(NotSortedMas, delete_not_exist_element) {
	NotSortedMas nsm;
	ASSERT_NO_THROW(nsm.del("56"));
}

TEST(NotSortedMas, search_pol) {
	NotSortedMas nsm;
	Polynom pol("xyz");
	nsm.insert("1", pol);
	ASSERT_EQ(nsm["1"] == pol, 1);
}

TEST(NotSortedMas, search_pol_2) {
	NotSortedMas nsm;
	Polynom pol("xyz");
	nsm.insert("1", pol);
	ASSERT_EQ(nsm["1"] != Polynom("123"), 1);
}

TEST(NotSortedMas, second_insert) {
	NotSortedMas nsm;
	Polynom pol("xyz");
	nsm.insert("1", pol);
	ASSERT_NO_THROW(nsm.insert("1", pol));
	nsm.insert("1", pol);
	ASSERT_EQ(nsm["1"] == pol, 1);
}

TEST(NotSortedMas, second_insert_2) {
	NotSortedMas nsm;
	Polynom pol("xyz");
	nsm.insert("1", pol);
	nsm.insert("1", Polynom("x^9"));
	ASSERT_EQ(nsm["1"] != pol, 1);
	ASSERT_EQ(nsm["1"] == Polynom("x^9"), 1);
}

TEST(NotSortedMas, second_insert_3) {
	NotSortedMas nsm;
	Polynom pol("xyz");
	nsm.insert("1", pol);
	nsm.insert("1", Polynom("x^9"));
	ASSERT_EQ(nsm["1"] != pol, 1);
	ASSERT_EQ(nsm["1"] == Polynom("x^9"), 1);
}

TEST(NotSortedMas, insert_lot_elements) {
	NotSortedMas nsm;
	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		nsm.insert(s, Polynom(s));
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		ASSERT_EQ(nsm[s] == Polynom(s), 1);
	}
}

TEST(NotSortedMas, insert_and_delete_lot_elements) {
	NotSortedMas nsm;
	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		nsm.insert(s, Polynom(s));
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		nsm.del(s);
	}

	for (int i = 0; i < 100; i++) {
		std::string s = std::to_string(i);
		ASSERT_EQ(nsm.search(s), 0);
	}
}

TEST(NotSortedMas, polynom_ne_nayden) {
	NotSortedMas nsm;
	ASSERT_ANY_THROW(nsm["1"]);
}

TEST(NotSortedMas, insert_after_delete) {
	NotSortedMas nsm;
	nsm.insert("1", Polynom("xyz"));
	nsm.del("1");
	nsm.insert("1", Polynom("xyz"));
	ASSERT_EQ(nsm["1"] == Polynom("xyz"), 1);
}