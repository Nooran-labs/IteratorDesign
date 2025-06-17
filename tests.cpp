/*
Mail - noorangnaim@gmail.com
*/

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "MyContainer.hpp"

#include <vector>
#include <string>
#include <sstream>

using namespace nooran;
using namespace std;

// Helper function to capture the textual representation of the container
// so we can easily compare it in string form
// Example: [1, 2, 3]
template<typename T>
string captureOutput(const MyContainer<T>& c) {
    ostringstream oss;
    oss << c;
    return oss.str();
}

// Template function that tests all iterator types (ascending, descending, etc.)
// against expected results
// Also checks invalid access at the end of each iterator
// Example usage in each SUBCASE
// Each order is passed as an expected vector
// Throws tested for dereferencing end iterators

// This lets us avoid repeating tests for each order
// Works for any type T (int, string, double, etc.)
template<typename T>
void testIterators(const MyContainer<T>& c,
                   const vector<T>& expected_asc,
                   const vector<T>& expected_desc,
                   const vector<T>& expected_side,
                   const vector<T>& expected_rev,
                   const vector<T>& expected_order,
                   const vector<T>& expected_mid) {
    vector<T> result;

    SUBCASE("Ascending Order") {
        result.clear();
        for (auto it = c.begin_ascending_order(); it != c.end_ascending_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_asc);

        auto it = c.end_ascending_order();
        CHECK_THROWS_AS(*it, out_of_range);
        CHECK_THROWS_AS(++it, out_of_range);
        CHECK_THROWS_AS(it++, out_of_range);
    }

    SUBCASE("Descending Order") {
        result.clear();
        for (auto it = c.begin_descending_order(); it != c.end_descending_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_desc);

        auto it = c.end_descending_order();
        CHECK_THROWS_AS(*it, out_of_range);
        CHECK_THROWS_AS(++it, out_of_range);
        CHECK_THROWS_AS(it++, out_of_range);
    }

    SUBCASE("SideCross Order") {
        result.clear();
        for (auto it = c.begin_side_cross_order(); it != c.end_side_cross_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_side);

        auto it = c.end_side_cross_order();
        CHECK_THROWS_AS(*it, out_of_range);
        CHECK_THROWS_AS(++it, out_of_range);
        CHECK_THROWS_AS(it++, out_of_range);
    }

    SUBCASE("Reverse Order") {
        result.clear();
        for (auto it = c.begin_reverse_order(); it != c.end_reverse_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_rev);

        auto it = c.end_reverse_order();
        CHECK_THROWS_AS(*it, out_of_range);
        CHECK_THROWS_AS(++it, out_of_range);
        CHECK_THROWS_AS(it++, out_of_range);
    }

    SUBCASE("Order Iterator") {
        result.clear();
        for (auto it = c.begin_order(); it != c.end_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_order);

        auto it = c.end_order();
        CHECK_THROWS_AS(*it, out_of_range);
        CHECK_THROWS_AS(++it, out_of_range);
        CHECK_THROWS_AS(it++, out_of_range);
    }

    SUBCASE("Middle Out Order") {
        result.clear();
        for (auto it = c.begin_middle_out_order(); it != c.end_middle_out_order(); ++it) {
            result.push_back(*it);
        }
        CHECK(result == expected_mid);

        auto it = c.end_middle_out_order();
        CHECK_THROWS_AS(*it, out_of_range);
        CHECK_THROWS_AS(++it, out_of_range);
        CHECK_THROWS_AS(it++, out_of_range);
    }
}

// ==================== TEST CASES ====================

// Simple add/remove and order checks for integers
TEST_CASE("Integer values with multiple orders") {
    MyContainer<int> c;
    c.addElement(7);
    c.addElement(15);
    c.addElement(6);
    c.addElement(1);
    c.addElement(2);

    CHECK(c.size() == 5);
    CHECK(captureOutput(c) == "[7, 15, 6, 1, 2]");

    vector<int> asc    = {1, 2, 6, 7, 15};
    vector<int> desc   = {15, 7, 6, 2, 1};
    vector<int> side   = {1, 15, 2, 7, 6};
    vector<int> rev    = {2, 1, 6, 15, 7};
    vector<int> order  = {7, 15, 6, 1, 2};
    vector<int> middle = {6, 15, 1, 7, 2};

    testIterators(c, asc, desc, side, rev, order, middle);
}

// Test removeElement logic and exception
TEST_CASE("Removing elements and exception throwing") {
    MyContainer<int> c;
    c.addElement(10);
    c.addElement(20);
    c.addElement(10);

    CHECK(c.size() == 3);
    c.removeElement(10);  // removes both 10s
    CHECK(c.size() == 1);
    CHECK(captureOutput(c) == "[20]");

    CHECK_THROWS_AS(c.removeElement(42), runtime_error);  // not found
}

// String test to ensure generic functionality
TEST_CASE("String values and stability") {
    MyContainer<string> s;
    s.addElement("banana");
    s.addElement("apple");
    s.addElement("kiwi");

    vector<string> asc    = {"apple", "banana", "kiwi"};
    vector<string> desc   = {"kiwi", "banana", "apple"};
    vector<string> side   = {"apple", "kiwi", "banana"};
    vector<string> rev    = {"kiwi", "apple", "banana"};
    vector<string> order  = {"banana", "apple", "kiwi"};
    vector<string> middle = {"apple", "banana", "kiwi"};


    testIterators(s, asc, desc, side, rev, order, middle);
}

// Bulk add/remove test
TEST_CASE("Multiple addElement and removeElement usage") {
    MyContainer<int> c;
    for (int i = 0; i < 100; ++i) {
        c.addElement(i % 10);  // Adds many repeated values
    }
    CHECK(c.size() == 100);
    c.removeElement(5);  // Should remove all 10 occurrences of 5
    CHECK(c.size() == 90);
    CHECK_THROWS_AS(c.removeElement(42), runtime_error);  // Not present
}

// Check iterator becomes invalid after modification
TEST_CASE("Iterator invalidation after container modification") {
    MyContainer<int> c;
    c.addElement(10);
    c.addElement(20);
    c.addElement(30);

    auto it = c.begin_order();
    CHECK(*it == 10);

    c.addElement(40);  // Modifies container

    CHECK_THROWS_AS(*it, runtime_error);  // Should throw due to version mismatch
    CHECK_THROWS_AS(++it, runtime_error);
}

// All iterators on empty container should equal begin==end
TEST_CASE("Empty container behavior") {
    MyContainer<int> empty;
    CHECK(empty.size() == 0);
    CHECK(captureOutput(empty) == "[]");

    CHECK(empty.begin_ascending_order() == empty.end_ascending_order());
    CHECK(empty.begin_descending_order() == empty.end_descending_order());
    CHECK(empty.begin_side_cross_order() == empty.end_side_cross_order());
    CHECK(empty.begin_reverse_order() == empty.end_reverse_order());
    CHECK(empty.begin_order() == empty.end_order());
    CHECK(empty.begin_middle_out_order() == empty.end_middle_out_order());
}

// Insertion order must be preserved in order iterator
TEST_CASE("Insertion order must be preserved") {
    MyContainer<string> c;
    c.addElement("first");
    c.addElement("second");
    c.addElement("third");

    vector<string> result;
    for (auto it = c.begin_order(); it != c.end_order(); ++it) {
        result.push_back(*it);
    }

    CHECK(result == vector<string>{"first", "second", "third"});
}

// Double precision test to ensure support for float types
TEST_CASE("Double type support") {
    MyContainer<double> c;
    c.addElement(3.14);
    c.addElement(2.71);
    c.addElement(-1.0);

    vector<double> asc = {-1.0, 2.71, 3.14};
    vector<double> desc = {3.14, 2.71, -1.0};
    vector<double> side = {-1.0, 3.14, 2.71};
    vector<double> rev = {-1.0, 2.71, 3.14};
    vector<double> order = {3.14, 2.71, -1.0};
    vector<double> middle = {2.71, 3.14, -1.0};

    testIterators(c, asc, desc, side, rev, order, middle);
}
