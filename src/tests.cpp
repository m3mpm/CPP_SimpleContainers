#include <gtest/gtest.h>
#include "containers.h"

#include <string>
#include <list>
#include <queue>
#include <stack>
#include <cmath>

bool isEqual(double src1, double src2) {
    if (fabs(src1 - src2) < 1e-6) {
        return true;
    }
    return false;
}

template <typename T>
bool lists_eq(const m3mpm::List<T> &my_l, const std::list<T> &std_l) {
  bool res = true;
  if (my_l.empty() != std_l.empty() && my_l.size() != std_l.size()) {
    res = false;
  }
  if (res && !my_l.empty()) {
    if (my_l.front() != std_l.front() && my_l.back() != std_l.back()) {
      res = false;
    }

    typename m3mpm::List<T>::iterator my_it = my_l.cbegin();
    typename std::list<T>::const_iterator std_it = std_l.cbegin();

    while (res && my_it != my_l.cend()) {
      res = *my_it == *std_it;
      ++my_it;
      ++std_it;
    }
  }
  return res;
}


template <typename T, typename std_or_T>
bool eq_queue(T q1, std_or_T q2) {
    while (q1.size() || q2.size()) {
        bool res = (q1.empty() == q2.empty()) &&
                   (q1.size() == q2.size()) &&
                   (q1.front() == q2.front()) &&
                   (q1.back() == q2.back());
        if (!res) return false;
        q1.pop();
        q2.pop();
    }
    return true;
}

template <typename T, typename std_or_T>
bool eq_stack(T s1, std_or_T s2) {
    while (s1.size() || s2.size()) {
        bool res = (s1.empty() == s2.empty()) &&
                   (s1.size() == s2.size()) &&
                   (s1.top() == s2.top());
        if (!res) return false;
        s1.pop();
        s2.pop();
    }
    return true;
}

// list test

TEST(list_ConstructorsTests, costr_default) {
  m3mpm::List<int> my_l1;
  ASSERT_EQ(my_l1.size(), 0);

  m3mpm::List<double> my_l2;
  ASSERT_EQ(my_l2.empty(), true);

  m3mpm::List<char> my_l3;
  ASSERT_EQ(my_l3.empty(), true);

  m3mpm::List<std::string> my_l4;
  ASSERT_EQ(my_l4.empty(), true);
}

TEST(list_ConstructorsTests, costr_parameterized) {
  m3mpm::List<int> my_l1(5);
  ASSERT_EQ(my_l1.size(), 5);

  m3mpm::List<double> my_l2(5);
  ASSERT_EQ(my_l2.size(), 5);

  m3mpm::List<char> my_l3(5);
  ASSERT_EQ(my_l3.size(), 5);

  m3mpm::List<char> my_l4(5);
  ASSERT_EQ(my_l4.size(), 5);
}

TEST(list_ConstructorsTests, costr_initializer) {
  std::list<int> std_l1{1, 2, 3, 4};
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  ASSERT_TRUE(lists_eq(my_l2, std_l2));

  std::list<char> std_l3{'1', '2', '3', '4'};
  m3mpm::List<char> my_l3{'1', '2', '3', '4'};
  ASSERT_TRUE(lists_eq(my_l3, std_l3));

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
}

TEST(list_ConstructorsTests, costr_copy) {
  std::list<int> std_l1{1, 2, 3, 4};
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  m3mpm::List<int> my_cl1(my_l1);
  ASSERT_TRUE(lists_eq(my_cl1, std_l1));

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_cl2(my_l2);
  ASSERT_TRUE(lists_eq(my_cl2, std_l2));

  std::list<char> std_l3{'1', '2', '3', '4'};
  m3mpm::List<char> my_l3{'1', '2', '3', '4'};
  m3mpm::List<char> my_cl3(my_l3);
  ASSERT_TRUE(lists_eq(my_cl3, std_l3));

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_cl4(my_l4);
  ASSERT_TRUE(lists_eq(my_cl4, std_l4));
}

TEST(list_ConstructorsTests, costr_move) {
  std::list<int> std_l1{1, 2, 3, 4};
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  m3mpm::List<int> my_ml1(std::move(my_l1));
  ASSERT_TRUE(lists_eq(my_ml1, std_l1));
  ASSERT_EQ(my_l1.size(), 0);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_ml2(std::move(my_l2));
  ASSERT_TRUE(lists_eq(my_ml2, std_l2));
  ASSERT_EQ(my_l2.size(), 0);

  std::list<char> std_l3{'1', '2', '3', '4'};
  m3mpm::List<char> my_l3{'1', '2', '3', '4'};
  m3mpm::List<char> my_ml3(std::move(my_l3));
  ASSERT_TRUE(lists_eq(my_ml3, std_l3));
  ASSERT_EQ(my_l3.size(), 0);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_ml4(std::move(my_l4));
  ASSERT_TRUE(lists_eq(my_ml4, std_l4));
  ASSERT_EQ(my_l3.size(), 0);
}

TEST(list_ElementAccessTests, front) {
  m3mpm::List<int> my_l0;
  m3mpm::List<int>::const_reference f0 = my_l0.front();
  ASSERT_EQ(f0, 0);

  m3mpm::List<int> my_l1{1, 2, 3, 4};
  m3mpm::List<int>::const_reference f1 = my_l1.front();
  ASSERT_EQ(f1, 1);

  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double>::const_reference f2 = my_l2.front();
  ASSERT_EQ(f2, 1.1);

  m3mpm::List<char> my_l3{'1', '2', '3', '4'};
  m3mpm::List<char>::const_reference f3 = my_l3.front();
  ASSERT_EQ(f3, '1');

  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string>::const_reference f4 = my_l4.front();
  ASSERT_EQ(f4, "one");
}

TEST(list_ElementAccessTests, back) {
  m3mpm::List<int> my_l0;
  m3mpm::List<int>::const_reference f0 = my_l0.back();
  ASSERT_EQ(f0, 0);

  m3mpm::List<int> my_l1{1, 2, 3, 4};
  m3mpm::List<int>::const_reference f1 = my_l1.back();
  ASSERT_EQ(f1, 4);

  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double>::const_reference f2 = my_l2.back();
  ASSERT_EQ(f2, 4.4);

  m3mpm::List<char> my_l3{'1', '2', '3', '4'};
  m3mpm::List<char>::const_reference f3 = my_l3.back();
  ASSERT_EQ(f3, '4');

  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string>::const_reference f4 = my_l4.back();
  ASSERT_EQ(f4, "four");
}

TEST(list_CapacityTests, size) {
  m3mpm::List<int> my_l0;
  ASSERT_EQ(my_l0.size(), 0);

  m3mpm::List<int> my_l1{1, 2, 3, 4};
  ASSERT_EQ(my_l1.size(), 4);
}

TEST(list_CapacityTests, max_size) {
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  ASSERT_EQ(my_l1.max_size(), 384307168202282325);

  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  ASSERT_EQ(my_l2.max_size(), 384307168202282325);

  m3mpm::List<char> my_l3{'1', '2', '3', '4'};
  ASSERT_EQ(my_l3.max_size(), 384307168202282325);

  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  ASSERT_EQ(my_l4.max_size(), 192153584101141162);
}

TEST(list_ModifiersTests, push_front) {
  std::list<int> std_l0{1};
  m3mpm::List<int> my_l0;
  my_l0.push_front(1);
  ASSERT_TRUE(lists_eq(my_l0, std_l0));

  std::list<int> std_l1{2, 1};
  m3mpm::List<int> my_l1{1};
  my_l1.push_front(2);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std::list<double> std_l2{2.2, 1.1};
  m3mpm::List<double> my_l2{1.1};
  my_l2.push_front(2.2);
  ASSERT_TRUE(lists_eq(my_l2, std_l2));

  std::list<char> std_l3{'2', '1'};
  m3mpm::List<char> my_l3{'1'};
  my_l3.push_front('2');
  ASSERT_TRUE(lists_eq(my_l3, std_l3));

  std::list<std::string> std_l4{"two", "one"};
  m3mpm::List<std::string> my_l4{"one"};
  my_l4.push_front("two");
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
}

TEST(list_ModifiersTests, push_back) {
  std::list<int> std_l0{1};
  m3mpm::List<int> my_l0;
  my_l0.push_back(1);
  ASSERT_TRUE(lists_eq(my_l0, std_l0));

  std::list<int> std_l1{2, 1, 3};
  m3mpm::List<int> my_l1{2, 1};
  my_l1.push_back(3);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std::list<double> std_l2{2.2, 1.1, 3.3};
  m3mpm::List<double> my_l2{2.2, 1.1};
  my_l2.push_back(3.3);
  ASSERT_TRUE(lists_eq(my_l2, std_l2));

  std::list<char> std_l3{'2', '1', '3'};
  m3mpm::List<char> my_l3{'2', '1'};
  my_l3.push_back('3');
  ASSERT_TRUE(lists_eq(my_l3, std_l3));

  std::list<std::string> std_l4{"two", "one", "three"};
  m3mpm::List<std::string> my_l4{"two", "one"};
  my_l4.push_back("three");
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
}

TEST(list_ModifiersTests, pop_front) {
  std::list<int> std_l0;
  m3mpm::List<int> my_l0{1};
  my_l0.pop_front();
  ASSERT_TRUE(lists_eq(my_l0, std_l0));

  std::list<int> std_l1{1, 3};
  m3mpm::List<int> my_l1{2, 1, 3};
  my_l1.pop_front();
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std::list<double> std_l2{1.1, 3.3};
  m3mpm::List<double> my_l2{2.2, 1.1, 3.3};
  my_l2.pop_front();
  ASSERT_TRUE(lists_eq(my_l2, std_l2));

  std::list<char> std_l3{'1', '3'};
  m3mpm::List<char> my_l3{'2', '1', '3'};
  my_l3.pop_front();
  ASSERT_TRUE(lists_eq(my_l3, std_l3));

  std::list<std::string> std_l4{"one", "three"};
  m3mpm::List<std::string> my_l4{"two", "one", "three"};
  my_l4.pop_front();
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
}

TEST(list_ModifiersTests, pop_back) {
  std::list<int> std_l0;
  m3mpm::List<int> my_l0{1};
  my_l0.pop_back();
  ASSERT_TRUE(lists_eq(my_l0, std_l0));

  std::list<int> std_l1{2, 1};
  m3mpm::List<int> my_l1{2, 1, 3};
  my_l1.pop_back();
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std::list<double> std_l2{2.2, 1.1};
  m3mpm::List<double> my_l2{2.2, 1.1, 3.3};
  my_l2.pop_back();
  ASSERT_TRUE(lists_eq(my_l2, std_l2));

  std::list<char> std_l3{'2', '1'};
  m3mpm::List<char> my_l3{'2', '1', '3'};
  my_l3.pop_back();
  ASSERT_TRUE(lists_eq(my_l3, std_l3));

  std::list<std::string> std_l4{"two", "one"};
  m3mpm::List<std::string> my_l4{"two", "one", "three"};
  my_l4.pop_back();
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
}

TEST(list_ModifiersTests, clear) {
  std::list<int> std_l1;
  m3mpm::List<int> my_l1{2, 1, 3};
  my_l1.clear();
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std::list<double> std_l2;
  m3mpm::List<double> my_l2{2.2, 1.1, 3.3};
  my_l2.clear();
  ASSERT_TRUE(lists_eq(my_l2, std_l2));

  std::list<char> std_l3;
  m3mpm::List<char> my_l3{'2', '1', '3'};
  my_l3.clear();
  ASSERT_TRUE(lists_eq(my_l3, std_l3));

  std::list<std::string> std_l4;
  m3mpm::List<std::string> my_l4{"two", "one", "three"};
  my_l4.clear();
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
}

TEST(list_ModifiersTests, swap) {
  std::list<int> std_l11;
  m3mpm::List<int> my_l11{2, 1, 3};
  std::list<int> std_l12{2, 1, 3};
  m3mpm::List<int> my_l12;
  my_l12.swap(my_l11);
  ASSERT_TRUE(lists_eq(my_l11, std_l11));
  ASSERT_TRUE(lists_eq(my_l12, std_l12));

  std::list<double> std_l21;
  m3mpm::List<double> my_l21{2.2, 1.1, 3.3};
  std::list<double> std_l22{2.2, 1.1, 3.3};
  m3mpm::List<double> my_l22;
  my_l22.swap(my_l21);
  ASSERT_TRUE(lists_eq(my_l21, std_l21));
  ASSERT_TRUE(lists_eq(my_l22, std_l22));

  std::list<char> std_l31;
  m3mpm::List<char> my_l31{'2', '1', '3'};
  std::list<char> std_l32{'2', '1', '3'};
  m3mpm::List<char> my_l32;
  my_l32.swap(my_l31);
  ASSERT_TRUE(lists_eq(my_l31, std_l31));
  ASSERT_TRUE(lists_eq(my_l32, std_l32));

  std::list<std::string> std_l41;
  m3mpm::List<std::string> my_l41{"two", "one", "three"};
  std::list<std::string> std_l42{"two", "one", "three"};
  m3mpm::List<std::string> my_l42;
  my_l42.swap(my_l41);
  ASSERT_TRUE(lists_eq(my_l41, std_l41));
  ASSERT_TRUE(lists_eq(my_l42, std_l42));
}

TEST(list_ModifiersTests, reverse) {
  std::list<int> std_l1{2, 1, 3};
  m3mpm::List<int> my_l1{2, 1, 3};
  my_l1.reverse();
  my_l1.reverse();
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std::list<double> std_l2{2.2, 1.1, 3.3};
  m3mpm::List<double> my_l2{2.2, 1.1, 3.3};
  my_l2.reverse();
  my_l2.reverse();
  ASSERT_TRUE(lists_eq(my_l2, std_l2));

  std::list<char> std_l3{'2', '1', '3'};
  m3mpm::List<char> my_l3{'2', '1', '3'};
  my_l3.reverse();
  my_l3.reverse();
  ASSERT_TRUE(lists_eq(my_l3, std_l3));

  std::list<std::string> std_l4{"two", "one", "three"};
  m3mpm::List<std::string> my_l4{"two", "one", "three"};
  std_l4.reverse();
  my_l4.reverse();
  ASSERT_TRUE(lists_eq(my_l4, std_l4));

  std::list<int> std_l5{5, 34, 56, 2, 3};
  m3mpm::List<int> my_l5{5, 34, 56, 2, 3};
  std_l5.reverse();
  my_l5.reverse();
  ASSERT_TRUE(lists_eq(my_l5, std_l5));

  std::list<int> std_l6{5, 34, 56, 2};
  m3mpm::List<int> my_l6{5, 34, 56, 2};
  std_l6.reverse();
  my_l6.reverse();
  ASSERT_TRUE(lists_eq(my_l6, std_l6));
}

TEST(list_ModifiersTests, operator_move) {
  std::list<int> std_l1{1, 2, 3, 4};
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  m3mpm::List<int> my_ml1;
  my_ml1 = std::move(my_l1);
  ASSERT_TRUE(lists_eq(my_ml1, std_l1));
  ASSERT_EQ(my_l1.size(), 0);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_ml2;
  my_ml2 = std::move(my_l2);
  ASSERT_TRUE(lists_eq(my_ml2, std_l2));
  ASSERT_EQ(my_l2.size(), 0);

  std::list<char> std_l3{'1', '2', '3', '4'};
  m3mpm::List<char> my_l3{'1', '2', '3', '4'};
  m3mpm::List<char> my_ml3;
  my_ml3 = std::move(my_l3);
  ASSERT_TRUE(lists_eq(my_ml3, std_l3));
  ASSERT_EQ(my_l3.size(), 0);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_ml4;
  my_ml4 = std::move(my_l4);
  ASSERT_TRUE(lists_eq(my_ml4, std_l4));
  ASSERT_EQ(my_l3.size(), 0);
}

TEST(list_ModifiersTests, empty) {
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  ASSERT_FALSE(my_l1.empty());
  my_l1.clear();
  ASSERT_TRUE(my_l1.empty());

  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  ASSERT_FALSE(my_l2.empty());
  my_l2.clear();
  ASSERT_TRUE(my_l2.empty());

  m3mpm::List<char> my_l3{'1', '2', '3', '4'};
  ASSERT_FALSE(my_l3.empty());
  my_l3.clear();
  ASSERT_TRUE(my_l3.empty());

  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  ASSERT_FALSE(my_l4.empty());
  my_l4.clear();
  ASSERT_TRUE(my_l4.empty());
}

TEST(list_ModifiersTests, sort) {
  std::list<int> std_l1{1, 2, 3, 4};
  m3mpm::List<int> my_l1{4, 2, 3, 1};
  my_l1.sort();
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_l2{4.4, 3.3, 2.2, 1.1};
  my_l2.sort();
  ASSERT_TRUE(lists_eq(my_l2, std_l2));

  std::list<char> std_l3{'1', '3', '3', '4'};
  m3mpm::List<char> my_l3{'4', '1', '3', '3'};
  my_l3.sort();
  ASSERT_TRUE(lists_eq(my_l3, std_l3));

  std::list<std::string> std_l4{"fourtt", "on", "three", "two"};
  m3mpm::List<std::string> my_l4{"on", "two", "three", "fourtt"};
  my_l4.sort();
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
}

TEST(list_ConstructorsIteratorTests, iterator) {
  m3mpm::List<int>::iterator my_it1;
  ASSERT_EQ(my_it1.pNode_, nullptr);

  m3mpm::Node<int> my_n2(5);
  m3mpm::List<int>::iterator my_it2(&my_n2);
  ASSERT_EQ(my_it2.pNode_->data_, my_n2.data_);

  m3mpm::List<int> my_l3{1, 2, 3, 4};
  m3mpm::List<int>::iterator my_it3(my_l3);
  ASSERT_EQ(my_it3.pNode_->data_, my_l3.front());

  m3mpm::List<int>::iterator my_it4(my_it3);
  ASSERT_EQ(my_it3.pNode_->data_, my_it4.pNode_->data_);
}

TEST(list_ConstructorsConstIteratorTests, const_iterator) {
  m3mpm::List<int>::const_iterator my_it1;
  ASSERT_EQ(my_it1.pNode_, nullptr);

  m3mpm::Node<int> my_n2(5);
  m3mpm::List<int>::const_iterator my_it2(&my_n2);
  ASSERT_EQ(my_it2.pNode_->data_, my_n2.data_);

  m3mpm::List<int> my_l3{1, 2, 3, 4};
  m3mpm::List<int>::const_iterator my_it3(my_l3);
  ASSERT_EQ(my_it3.pNode_->data_, my_l3.front());

  m3mpm::List<int>::const_iterator my_it4(my_it3);
  ASSERT_EQ(my_it3.pNode_->data_, my_it4.pNode_->data_);
}

TEST(list_OperatorsIteratorTests, operators_iterator) {
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  m3mpm::List<int>::iterator my_it1(my_l1);
  ASSERT_EQ(*my_it1, 1);
  ++my_it1;
  ++my_it1;
  ASSERT_EQ(*my_it1, 3);
  --my_it1;
  ASSERT_EQ(*my_it1, 2);
  m3mpm::List<int>::iterator my_it2;
  my_it2 = my_it1;
  ASSERT_EQ(*my_it1, *my_it2);
  ASSERT_FALSE(my_it1 != my_it2);
  ++my_it2;
  ASSERT_TRUE(my_it1 != my_it2);
  ASSERT_FALSE(my_it1 == my_it2);
  --my_it2;
  ASSERT_TRUE(my_it1 == my_it2);

  m3mpm::List<int>::const_iterator my_it3(my_l1);
  ASSERT_EQ(*my_it3, 1);
}

TEST(list_ModifiersTests, begin) {
  std::list<int> std_l0;
  m3mpm::List<int> my_l0;
  std::list<int>::iterator std_it0 = std_l0.begin();
  m3mpm::List<int>::iterator my_it0 = my_l0.begin();
  ASSERT_TRUE(*std_it0 == *my_it0);

  std::list<int> std_l1{1, 2, 3, 4};
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  std::list<int>::iterator std_it1 = std_l1.begin();
  m3mpm::List<int>::iterator my_it1 = my_l1.begin();
  ASSERT_TRUE(*std_it1 == *my_it1);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  std::list<double>::iterator std_it2 = std_l2.begin();
  m3mpm::List<double>::iterator my_it2 = my_l2.begin();
  ASSERT_TRUE(*std_it2 == *my_it2);

  std::list<char> std_l3{'1', '3', '3', '4'};
  m3mpm::List<char> my_l3{'1', '3', '3', '4'};
  std::list<char>::iterator std_it3 = std_l3.begin();
  m3mpm::List<char>::iterator my_it3 = my_l3.begin();
  ASSERT_TRUE(*std_it3 == *my_it3);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  std::list<std::string>::iterator std_it4 = std_l4.begin();
  m3mpm::List<std::string>::iterator my_it4 = my_l4.begin();
  ASSERT_TRUE(*std_it4 == *my_it4);
}

TEST(list_ModifiersTests, end) {
  std::list<int> std_l0;
  m3mpm::List<int> my_l0;
  std::list<int>::iterator std_it0 = std_l0.end();
  m3mpm::List<int>::iterator my_it0 = my_l0.end();
  ASSERT_TRUE(*std_it0 == *my_it0);

  std::list<int> std_l1{1, 2, 3, 4};
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  std::list<int>::iterator std_it1 = ++std_l1.end();
  m3mpm::List<int>::iterator my_it1 = ++my_l1.end();
  ASSERT_TRUE(*std_it1 == *my_it1);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  std::list<double>::iterator std_it2 = --std_l2.end();
  m3mpm::List<double>::iterator my_it2 = --my_l2.end();
  ASSERT_TRUE(*std_it2 == *my_it2);

  std::list<char> std_l3{'1', '3', '3', '4'};
  m3mpm::List<char> my_l3{'1', '3', '3', '4'};
  std::list<char>::iterator std_it3 = ++std_l3.end();
  m3mpm::List<char>::iterator my_it3 = ++my_l3.end();
  ASSERT_TRUE(*std_it3 == *my_it3);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  std::list<std::string>::iterator std_it4 = --std_l4.end();
  m3mpm::List<std::string>::iterator my_it4 = --my_l4.end();
  ASSERT_TRUE(*std_it4 == *my_it4);
}

TEST(list_ModifiersTests, cbegin) {
  std::list<int> std_l0;
  m3mpm::List<int> my_l0;
  std::list<int>::const_iterator std_it0 = std_l0.cbegin();
  m3mpm::List<int>::const_iterator my_it0 = my_l0.cbegin();
  ASSERT_TRUE(*std_it0 == *my_it0);

  std::list<int> std_l1{1, 2, 3, 4};
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  ASSERT_TRUE(*std_it1 == *my_it1);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  std::list<double>::const_iterator std_it2 = std_l2.cbegin();
  m3mpm::List<double>::const_iterator my_it2 = my_l2.cbegin();
  ASSERT_TRUE(*std_it2 == *my_it2);

  std::list<char> std_l3{'1', '3', '3', '4'};
  m3mpm::List<char> my_l3{'1', '3', '3', '4'};
  std::list<char>::const_iterator std_it3 = std_l3.cbegin();
  m3mpm::List<char>::const_iterator my_it3 = my_l3.cbegin();
  ASSERT_TRUE(*std_it3 == *my_it3);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  std::list<std::string>::const_iterator std_it4 = std_l4.cbegin();
  m3mpm::List<std::string>::const_iterator my_it4 = my_l4.cbegin();
  ASSERT_TRUE(*std_it4 == *my_it4);
}

TEST(list_ModifiersTests, cend) {
  std::list<int> std_l0;
  m3mpm::List<int> my_l0;
  std::list<int>::const_iterator std_it0 = std_l0.cend();
  m3mpm::List<int>::const_iterator my_it0 = my_l0.cend();
  ASSERT_TRUE(*std_it0 == *my_it0);

  std::list<int> std_l1{1, 2, 3, 4};
  m3mpm::List<int> my_l1{1, 2, 3, 4};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cend();
  ++std_it1;
  ++my_it1;
  ASSERT_TRUE(*std_it1 == *my_it1);

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4};
  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4};
  std::list<double>::const_iterator std_it2 = std_l2.cend();
  m3mpm::List<double>::const_iterator my_it2 = my_l2.cend();
  --std_it2;
  --my_it2;
  ASSERT_TRUE(*std_it2 == *my_it2);

  std::list<char> std_l3{'1', '3', '3', '4'};
  m3mpm::List<char> my_l3{'1', '3', '3', '4'};
  std::list<char>::const_iterator std_it3 = std_l3.cend();
  m3mpm::List<char>::const_iterator my_it3 = my_l3.cend();
  ++std_it3;
  ++my_it3;
  ASSERT_TRUE(*std_it3 == *my_it3);

  std::list<std::string> std_l4{"one", "two", "three", "four"};
  m3mpm::List<std::string> my_l4{"one", "two", "three", "four"};
  std::list<std::string>::const_iterator std_it4 = std_l4.cend();
  m3mpm::List<std::string>::const_iterator my_it4 = my_l4.cend();
  --std_it4;
  --my_it4;
  ASSERT_TRUE(*std_it4 == *my_it4);
}

TEST(list_ModifiersTests, erase) {
  std::list<int> std_l1{1, 2, 3, 4, 5};
  m3mpm::List<int> my_l1{1, 2, 3, 4, 5};
  std::list<int>::iterator std_it1 = --std_l1.end();
  m3mpm::List<int>::iterator my_it1 = --my_l1.end();
  std_l1.erase(std_it1);
  my_l1.erase(my_it1);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  std_it1 = std_l1.begin();
  my_it1 = my_l1.begin();
  std_l1.erase(std_it1);
  my_l1.erase(my_it1);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  std_it1 = std_l1.begin();
  my_it1 = my_l1.begin();
  ++std_it1;
  ++my_it1;
  std_l1.erase(std_it1);
  my_l1.erase(my_it1);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std::list<double> std_l2{1.1, 2.2, 3.3, 4.4, 5.5};
  m3mpm::List<double> my_l2{1.1, 2.2, 3.3, 4.4, 5.5};
  std::list<double>::iterator std_it2 = --std_l2.end();
  m3mpm::List<double>::iterator my_it2 = --my_l2.end();
  std_l2.erase(std_it2);
  my_l2.erase(my_it2);
  ASSERT_TRUE(lists_eq(my_l2, std_l2));
  std_it2 = std_l2.begin();
  my_it2 = my_l2.begin();
  std_l2.erase(std_it2);
  my_l2.erase(my_it2);
  ASSERT_TRUE(lists_eq(my_l2, std_l2));
  std_it2 = std_l2.begin();
  my_it2 = my_l2.begin();
  ++std_it2;
  ++my_it2;
  std_l2.erase(std_it2);
  my_l2.erase(my_it2);
  ASSERT_TRUE(lists_eq(my_l2, std_l2));

  std::list<char> std_l3{'1', '3', '3', '4', '5'};
  m3mpm::List<char> my_l3{'1', '3', '3', '4', '5'};
  std::list<char>::iterator std_it3 = --std_l3.end();
  m3mpm::List<char>::iterator my_it3 = --my_l3.end();
  std_l3.erase(std_it3);
  my_l3.erase(my_it3);
  ASSERT_TRUE(lists_eq(my_l3, std_l3));
  std_it3 = std_l3.begin();
  my_it3 = my_l3.begin();
  std_l3.erase(std_it3);
  my_l3.erase(my_it3);
  ASSERT_TRUE(lists_eq(my_l3, std_l3));
  std_it3 = std_l3.begin();
  my_it3 = my_l3.begin();
  ++std_it3;
  ++my_it3;
  std_l3.erase(std_it3);
  my_l3.erase(my_it3);
  ASSERT_TRUE(lists_eq(my_l3, std_l3));

  std::list<std::string> std_l4{"one", "two", "three", "four", "five"};
  m3mpm::List<std::string> my_l4{"one", "two", "three", "four", "five"};
  std::list<std::string>::iterator std_it4 = --std_l4.end();
  m3mpm::List<std::string>::iterator my_it4 = --my_l4.end();
  std_l4.erase(std_it4);
  my_l4.erase(my_it4);
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
  std_it4 = std_l4.begin();
  my_it4 = my_l4.begin();
  std_l4.erase(std_it4);
  my_l4.erase(my_it4);
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
  std_it4 = std_l4.begin();
  my_it4 = my_l4.begin();
  ++std_it4;
  ++my_it4;
  std_l4.erase(std_it4);
  my_l4.erase(my_it4);
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
}

TEST(list_ModifiersTests, unique_1) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  m3mpm::List<int> my_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std_l1.unique();
  my_l1.unique();
  ASSERT_TRUE(lists_eq(my_l1, std_l1));
}

TEST(list_ModifiersTests, unique_2) {
  std::list<int> std_l2{0, 0, 1, 2, 2, 3, 3};
  m3mpm::List<int> my_l2{0, 0, 1, 2, 2, 3, 3};
  std_l2.unique();
  my_l2.unique();
  ASSERT_TRUE(lists_eq(my_l2, std_l2));
}

TEST(list_ModifiersTests, unique_3) {
  std::list<int> std_l3{0, 0, 1, 2, 2, 3, 3, 0};
  m3mpm::List<int> my_l3{0, 0, 1, 2, 2, 3, 3, 0};
  std_l3.unique();
  my_l3.unique();
  ASSERT_TRUE(lists_eq(my_l3, std_l3));
}

TEST(list_ModifiersTests, unique_4) {
  std::list<int> std_l4{0, 0, 1, 2, 2, 3, 3, 2, 0};
  m3mpm::List<int> my_l4{0, 0, 1, 2, 2, 3, 3, 2, 0};
  std_l4.unique();
  my_l4.unique();
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
}

TEST(list_ModifiersTests, unique_5) {
  std::list<int> std_l5{0, 0, 1, 2, 2, 3, 3, 2, 0, 5, 5};
  m3mpm::List<int> my_l5{0, 0, 1, 2, 2, 3, 3, 2, 0, 5, 5};
  std_l5.unique();
  my_l5.unique();
  ASSERT_TRUE(lists_eq(my_l5, std_l5));
}

TEST(list_ModifiersTests, insert) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  m3mpm::List<int> my_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int>::iterator std_it1 = std_l1.begin();
  m3mpm::List<int>::iterator my_it1 = my_l1.begin();

  std_l1.insert(std_it1, 100);
  my_l1.insert(my_it1, 100);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  ++std_it1;
  ++my_it1;
  std_l1.insert(std_it1, 99);
  my_l1.insert(my_it1, 99);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  ++std_it1;
  ++my_it1;
  std_l1.insert(std_it1, 89);
  my_l1.insert(my_it1, 89);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std_it1 = std_l1.end();
  my_it1 = my_l1.end();
  std_l1.insert(std_it1, 79);
  my_l1.insert(my_it1, 79);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  ++std_it1;
  ++my_it1;
  std_l1.insert(std_it1, 44);
  my_l1.insert(my_it1, 44);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  ++std_it1;
  ++my_it1;
  std_l1.insert(std_it1, 34);
  my_l1.insert(my_it1, 34);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  --std_it1;
  --my_it1;
  --std_it1;
  --my_it1;
  --std_it1;
  --my_it1;
  std_l1.insert(std_it1, -26);
  my_l1.insert(my_it1, -26);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  --std_it1;
  --my_it1;
  std_l1.insert(std_it1, -16);
  my_l1.insert(my_it1, -16);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  --std_it1;
  --my_it1;
  std_l1.insert(std_it1, -13);
  my_l1.insert(my_it1, -13);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  --std_it1;
  --my_it1;
  --std_it1;
  --my_it1;
  --std_it1;
  --my_it1;
  std_l1.insert(std_it1, -3);
  my_l1.insert(my_it1, -3);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  --std_it1;
  --my_it1;
  --std_it1;
  --my_it1;
  --std_it1;
  --my_it1;
  std_l1.insert(std_it1, 0);
  my_l1.insert(my_it1, 0);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std_l1.clear();
  my_l1.clear();
  std_it1 = std_l1.begin();
  my_it1 = my_l1.begin();

  std_l1.insert(std_it1, 56);
  my_l1.insert(my_it1, 56);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  std_l1.clear();
  my_l1.clear();
  std_it1 = std_l1.end();
  my_it1 = my_l1.end();

  std_l1.insert(std_it1, 70);
  my_l1.insert(my_it1, 70);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));

  --std_it1;
  --my_it1;
  std_l1.insert(std_it1, -22);
  my_l1.insert(my_it1, -22);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));
}

TEST(list_ModifiersTests, merge_1) {
  std::list<int> std_l1{6, 3, 9};
  std::list<int> std_l2;
  m3mpm::List<int> my_l1{6, 3, 9};
  m3mpm::List<int> my_l2;
  std_l2.merge(std_l1);
  my_l2.merge(my_l1);
  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(lists_eq(my_l2, std_l2));
}

TEST(list_ModifiersTests, merge_2) {
  std::list<int> std_l3{6, 3, 9};
  std::list<int> std_l4;
  m3mpm::List<int> my_l3{6, 3, 9};
  m3mpm::List<int> my_l4;
  std_l3.sort();
  my_l3.sort();
  std_l4.merge(std_l3);
  my_l4.merge(my_l3);
  ASSERT_TRUE(lists_eq(my_l3, std_l3));
  ASSERT_TRUE(lists_eq(my_l4, std_l4));
}

TEST(list_ModifiersTests, merge_3) {
  std::list<int> std_l5;
  std::list<int> std_l6{4, 2};
  m3mpm::List<int> my_l5;
  m3mpm::List<int> my_l6{4, 2};
  std_l6.merge(std_l5);
  my_l6.merge(my_l5);
  ASSERT_TRUE(lists_eq(my_l5, std_l5));
  ASSERT_TRUE(lists_eq(my_l6, std_l6));
}

TEST(list_ModifiersTests, merge_4) {
  std::list<int> std_l7;
  std::list<int> std_l8{4, 2};
  m3mpm::List<int> my_l7;
  m3mpm::List<int> my_l8{4, 2};
  std_l8.sort();
  my_l8.sort();
  std_l8.merge(std_l7);
  my_l8.merge(my_l7);
  ASSERT_TRUE(lists_eq(my_l7, std_l7));
  ASSERT_TRUE(lists_eq(my_l8, std_l8));
}

TEST(list_ModifiersTests, merge_5) {
  std::list<int> std_l9{9, 6, 3};
  std::list<int> std_l10{4, 2, 7};
  m3mpm::List<int> my_l9{9, 6, 3};
  m3mpm::List<int> my_l10{4, 2, 7};
  std_l10.merge(std_l9);
  my_l10.merge(my_l9);
  ASSERT_TRUE(lists_eq(my_l9, std_l9));
  ASSERT_TRUE(lists_eq(my_l10, std_l10));
}

TEST(list_ModifiersTests, merge_6) {
  std::list<int> std_l11{9, 6, 3};
  std::list<int> std_l12{4, 2, 7};
  m3mpm::List<int> my_l11{9, 6, 3};
  m3mpm::List<int> my_l12{4, 2, 7};
  std_l11.sort();
  my_l11.sort();
  std_l12.sort();
  my_l12.sort();
  std_l12.merge(std_l11);
  my_l12.merge(my_l11);
  ASSERT_TRUE(lists_eq(my_l11, std_l11));
  ASSERT_TRUE(lists_eq(my_l12, std_l12));
}

TEST(list_ModifiersTests, merge_7) {
  std::list<int> std_l13{-9, -6, -3};
  std::list<int> std_l14{-4, -2, -7};
  m3mpm::List<int> my_l13{-9, -6, -3};
  m3mpm::List<int> my_l14{-4, -2, -7};
  std_l14.merge(std_l13);
  my_l14.merge(my_l13);
  ASSERT_TRUE(lists_eq(my_l13, std_l13));
  ASSERT_TRUE(lists_eq(my_l14, std_l14));
}

TEST(list_ModifiersTests, splice_1) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_l2{9, 6, 3};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  std_l1.splice(std_it1, std_l2);

  m3mpm::List<int> my_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  m3mpm::List<int> my_l2{9, 6, 3};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  my_l1.splice(my_it1, my_l2);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
}

TEST(list_ModifiersTests, splice_2) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_l2{9, 6, 3};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  std_l1.splice(std_it1, std_l2);

  m3mpm::List<int> my_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  m3mpm::List<int> my_l2{9, 6, 3};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cend();
  my_l1.splice(my_it1, my_l2);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
}

TEST(list_ModifiersTests, splice_3) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_l2{9, 6, 3};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  --std_it1;
  std_l1.splice(std_it1, std_l2);

  m3mpm::List<int> my_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  m3mpm::List<int> my_l2{9, 6, 3};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cend();
  --my_it1;
  my_l1.splice(my_it1, my_l2);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
}

TEST(list_ModifiersTests, splice_4) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_l2{9, 6, 3};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std_l1.splice(std_it1, std_l2);

  m3mpm::List<int> my_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  m3mpm::List<int> my_l2{9, 6, 3};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  ++my_it1;
  my_l1.splice(my_it1, my_l2);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
}

TEST(list_ModifiersTests, splice_5) {
  std::list<int> std_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::list<int> std_l2;
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std_l1.splice(std_it1, std_l2);

  m3mpm::List<int> my_l1{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  m3mpm::List<int> my_l2;
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  ++my_it1;
  my_l1.splice(my_it1, my_l2);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
}

TEST(list_ModifiersTests, splice_6) {
  std::list<int> std_l1;
  std::list<int> std_l2{9, 6, 3};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std_l1.splice(std_it1, std_l2);

  m3mpm::List<int> my_l1;
  m3mpm::List<int> my_l2{9, 6, 3};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  ++my_it1;
  my_l1.splice(my_it1, my_l2);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
}

TEST(list_ModifiersTests, emplace_1) {
  std::list<int> std_l1;
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  std_l1.emplace(std_it1);

  m3mpm::List<int> my_l1;
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  my_l1.emplace(my_it1);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
}

TEST(list_ModifiersTests, emplace_2) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  std::list<int>::iterator std_r1 = std_l1.emplace(std_it1);

  m3mpm::List<int> my_l1{9, 6, 3, 7};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_3) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std::list<int>::iterator std_r1 = std_l1.emplace(std_it1);

  m3mpm::List<int> my_l1{9, 6, 3, 7};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  ++my_it1;
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_4) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  --std_it1;
  std::list<int>::iterator std_r1 = std_l1.emplace(std_it1);

  m3mpm::List<int> my_l1{9, 6, 3, 7};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cend();
  --my_it1;
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_5) {
  std::list<int> std_l1;
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_r1 = std_l1.emplace(std_it1, 10);

  m3mpm::List<int> my_l1;
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1, 5, 10);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_6) {
  std::list<int> std_l1;
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_r1 = std_l1.emplace(std_it1, 10);

  m3mpm::List<int> my_l1;
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cend();
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1, 5, 10);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_7) {
  std::list<int> std_l1;
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  --std_it1;
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_r1 = std_l1.emplace(std_it1, 10);

  m3mpm::List<int> my_l1;
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cend();
  --my_it1;
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1, 5, 10);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_8) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_r1 = std_l1.emplace(std_it1, 10);

  m3mpm::List<int> my_l1{9, 6, 3, 7};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1, 5, 10);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_9) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_r1 = std_l1.emplace(std_it1, 10);

  m3mpm::List<int> my_l1{9, 6, 3, 7};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  ++my_it1;
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1, 5, 10);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_10) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cbegin();
  ++std_it1;
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_l1.emplace(std_it1, 10);
  std_r1 = std_l1.emplace(std_it1, 15);

  m3mpm::List<int> my_l1{9, 6, 3, 7};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cbegin();
  ++my_it1;
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1, 5, 10, 15);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_11) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_l1.emplace(std_it1, 10);
  std_r1 = std_l1.emplace(std_it1, 15);

  m3mpm::List<int> my_l1{9, 6, 3, 7};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cend();
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1, 5, 10, 15);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_12) {
  std::list<int> std_l1{9, 6, 3, 7};
  std::list<int>::const_iterator std_it1 = std_l1.cend();
  --std_it1;
  std::list<int>::iterator std_r1;
  std_l1.emplace(std_it1, 5);
  std_l1.emplace(std_it1, 10);
  std_r1 = std_l1.emplace(std_it1, 15);

  m3mpm::List<int> my_l1{9, 6, 3, 7};
  m3mpm::List<int>::const_iterator my_it1 = my_l1.cend();
  --my_it1;
  m3mpm::List<int>::iterator my_r1 = my_l1.emplace(my_it1, 5, 10, 15);

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(*std_r1 == *my_r1);
}

TEST(list_ModifiersTests, emplace_back_1) {
  std::list<int> std_l1;
  std_l1.emplace_back();
  std_l1.emplace_back();
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1;
  my_l1.emplace_back();
  my_l1.emplace_back();
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_back_2) {
  std::list<int> std_l1;
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1;
  my_l1.emplace_back(5);
  my_l1.emplace_back(10);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_back_3) {
  std::list<int> std_l1;
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1;
  my_l1.emplace_back(5, 10);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_back_4) {
  std::list<int> std_l1;
  std_l1.emplace_back();
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1;
  my_l1.emplace_back();
  my_l1.emplace_back(10);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_back_5) {
  std::list<int> std_l1;
  std_l1.emplace_back();
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1;
  my_l1.emplace_back();
  my_l1.emplace_back(5, 10);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_back_6) {
  std::list<int> std_l1{99, 100};
  std_l1.emplace_back();
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1{99, 100};
  my_l1.emplace_back();
  my_l1.emplace_back(5);
  my_l1.emplace_back(10);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_back_7) {
  std::list<int> std_l1{99, 100};
  std_l1.emplace_back();
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1{99, 100};
  my_l1.emplace_back();
  my_l1.emplace_back(5, 10);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_back_8) {
  std::list<int> std_l1{99, 100};
  std_l1.emplace_back(5);
  std_l1.emplace_back(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1{99, 100};
  my_l1.emplace_back(5, 10);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_back_9) {
  std::list<std::string> std_l1;
  std_l1.emplace_back();
  std_l1.emplace_back();
  size_t std_size = std_l1.size();

  m3mpm::List<std::string> my_l1;
  my_l1.emplace_back();
  my_l1.emplace_back();
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_front_1) {
  std::list<int> std_l1;
  std_l1.emplace_front();
  std_l1.emplace_front();
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1;
  my_l1.emplace_front();
  my_l1.emplace_front();
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_front_2) {
  std::list<std::string> std_l1;
  std_l1.emplace_front();
  std_l1.emplace_front();
  size_t std_size = std_l1.size();

  m3mpm::List<std::string> my_l1;
  my_l1.emplace_front();
  my_l1.emplace_front();
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_front_3) {
  std::list<int> std_l1;
  std_l1.emplace_front(5);
  std_l1.emplace_front(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1;
  my_l1.emplace_front(5);
  my_l1.emplace_front(10);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_front_4) {
  std::list<int> std_l1;
  std_l1.emplace_front();
  std_l1.emplace_front(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1;
  my_l1.emplace_front();
  my_l1.emplace_front(10);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_front_5) {
  std::list<int> std_l1{99, 100};
  std_l1.emplace_front();
  std_l1.emplace_front(5);
  std_l1.emplace_front(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1{99, 100};
  my_l1.emplace_front();
  my_l1.emplace_front(5);
  my_l1.emplace_front(10);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}

TEST(list_ModifiersTests, emplace_front_6) {
  std::list<int> std_l1{99, 100};
  std_l1.emplace_front(5);
  std_l1.emplace_front(10);
  size_t std_size = std_l1.size();

  m3mpm::List<int> my_l1{99, 100};
  my_l1.emplace_front(10, 5);
  m3mpm::List<int>::size_type my_size = std_l1.size();

  ASSERT_TRUE(lists_eq(my_l1, std_l1));
  ASSERT_TRUE(std_size == my_size);
}
/* Test throw */
/*
TEST(list_ThrowTests, throw_1) {
  m3mpm::list<int>::iterator my_it1;
  EXPECT_THROW(*my_it1, std::exception);
}

TEST(list_ThrowTests, throw_2) {
  m3mpm::list<int>::const_iterator my_it1;
  EXPECT_THROW(*my_it1, std::exception);
}

TEST(list_ThrowTests, throw_3) {
  EXPECT_THROW(m3mpm::list<int> my_l1(384307168202282325), std::exception);
}

TEST(list_ThrowTests, throw_4) {
  m3mpm::list<int> my_l1;
  EXPECT_THROW(my_l1.pop_front(), std::exception);
}

TEST(list_ThrowTests, throw_5) {
  m3mpm::list<int> my_l1;
  EXPECT_THROW(my_l1.pop_back(), std::exception);
}

TEST(list_ThrowTests, throw_6) {
  m3mpm::list<int> my_l1{5, 6};
  EXPECT_THROW(my_l1 = std::move(my_l1), std::exception);
}

TEST(list_ThrowTests, throw_7) {
  m3mpm::list<int> my_l1{5, 6};
  m3mpm::list<int>::iterator my_it1 = my_l1.end();
  EXPECT_THROW(my_l1.erase(my_it1), std::exception);
}

TEST(list_ThrowTests, throw_8) {
  m3mpm::list<int> my_l1{5, 6};
  m3mpm::list<int>::iterator my_it1;
  EXPECT_THROW(my_l1.erase(my_it1), std::exception);
}
 */


TEST(queue_constructor, default_constr) {
    m3mpm::Queue<double> q1;
    ASSERT_EQ(q1.size(), 0);
    ASSERT_TRUE(q1.empty());
}

TEST(queue_constructor, initializer) {
    m3mpm::Queue<double> q1 {5.5, 4.3, 2.2, 7.1};
    ASSERT_EQ(q1.size(), 4);
    ASSERT_EQ(q1.front(), 5.5);
    ASSERT_EQ(q1.back(), 7.1);
}

TEST(queue_constructor, initializer2) {
    m3mpm::Queue<std::string> q1 {"WouWouWou", "BlaBla", "Ololo", "Aaaaaaaar", "Fuuuu"};
    ASSERT_EQ(q1.size(), 5);
    ASSERT_EQ(q1.front(), "WouWouWou");
    ASSERT_EQ(q1.back(), "Fuuuu");
}

TEST(queue_constructor, copy) {
    m3mpm::Queue<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    m3mpm::Queue<char> q2(q1);
    ASSERT_TRUE(eq_queue(q1, q2));
}

TEST(queue_constructor, move) {
    m3mpm::Queue<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    m3mpm::Queue<char> q2 { 'S', 'c', 'h', 'o', 'o', 'l' };
    m3mpm::Queue<char> q3(std::move(q1));
    ASSERT_TRUE(q1.empty());
    ASSERT_TRUE(eq_queue(q2, q3));
}

TEST(queue_func, eq) {
    m3mpm::Queue<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    m3mpm::Queue<char> q2 = q1;
    ASSERT_TRUE(eq_queue(q1, q2));
}

TEST(queue_func, push) {
    m3mpm::Queue<std::string> q1;
    std::queue<std::string> q2;
    q1.push("Jooooo");
    q1.push("Byy");
    q1.push("Wow");
    q2.push("Jooooo");
    q2.push("Byy");
    q2.push("Wow");
    ASSERT_TRUE(eq_queue(q1, q2));
}

TEST(queue_func, push2) {
    m3mpm::Queue<std::vector<double>> q1;
    std::queue<std::vector<double>> q2;
    q1.push({2.7, 7.2, -34.1});
    q1.push({12.47, -57.2, 94.1});
    q1.push({7.5, -95.2, -374.1});
    q2.push({2.7, 7.2, -34.1});
    q2.push({12.47, -57.2, 94.1});
    q2.push({7.5, -95.2, -374.1});
    ASSERT_TRUE(eq_queue(q1, q2));
}

TEST(queue_func, push3) {
    m3mpm::Queue<std::pair<std::string, std::map<char, float>>> q1;
    std::queue<std::pair<std::string, std::map<char, float>>> q2;
    q1.push({"Test", { {'T', -43.123}, {'E', 13.43}, {'S', 3.13}, {'F', 43.4} } });
    q1.push({"Map", { {'M', 3.1263}, {'A', 3.43}, {'P', 3.}, {'1', 5.4} } });
    q1.push({"Queue", { {'Q', 63.}, {'u', 3.43}, {'e', -53.}, {'U', 545.5}, {'E', -0.4} } });
    q2.push({"Test", { {'T', -43.123}, {'E', 13.43}, {'S', 3.13}, {'F', 43.4} } });
    q2.push({"Map", { {'M', 3.1263}, {'A', 3.43}, {'P', 3.}, {'1', 5.4} } });
    q2.push({"Queue", { {'Q', 63.}, {'u', 3.43}, {'e', -53.}, {'U', 545.5}, {'E', -0.4} } });
    ASSERT_TRUE(eq_queue(q1, q2));
}

TEST(queue_func, swap) {
    m3mpm::Queue<std::vector<double>> q1;
    std::queue<std::vector<double>> q2;
    q1.push({2.7, 7.2, -34.1});
    q1.push({12.47, -57.2, 94.1});
    q1.push({7.5, -95.2, -374.1});
    q2.push({2.7, 7.2, -34.1});
    q2.push({12.47, -57.2, 94.1});
    q2.push({7.5, -95.2, -374.1});
    m3mpm::Queue<std::vector<double>> q3;
    q3.swap(q1);
    ASSERT_TRUE(eq_queue(q3, q2));
}

TEST(stack_constructor, default_constr) {
    m3mpm::Stack<double> q1;
    ASSERT_EQ(q1.size(), 0);
    ASSERT_TRUE(q1.empty());
}

TEST(stack_constructor, initializer) {
    m3mpm::Stack<double> q1 {5.5, 4.3, 2.2, 7.1};
    ASSERT_EQ(q1.size(), 4);
    ASSERT_EQ(q1.top(), 7.1);
}

TEST(stack_constructor, initializer2) {
    m3mpm::Stack<std::string> q1 {"WouWouWou", "BlaBla", "Ololo", "Aaaaaaaar", "Fuuuu"};
    ASSERT_EQ(q1.size(), 5);
    ASSERT_EQ(q1.top(), "Fuuuu");
}

TEST(stack_constructor, copy) {
    m3mpm::Stack<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    m3mpm::Stack<char> q2(q1);
    ASSERT_TRUE(eq_stack(q1, q2));
}

TEST(stack_constructor, move) {
    m3mpm::Stack<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    m3mpm::Stack<char> q2 { 'S', 'c', 'h', 'o', 'o', 'l' };
    m3mpm::Stack<char> q3(std::move(q1));
    ASSERT_TRUE(q1.empty());
    ASSERT_TRUE(eq_stack(q2, q3));
}

TEST(stack_func, eq) {
    m3mpm::Stack<char> q1 { 'S', 'c', 'h', 'o', 'o', 'l' };
    m3mpm::Stack<char> q2 = q1;
    ASSERT_TRUE(eq_stack(q1, q2));
}

TEST(stack_func, push) {
    m3mpm::Stack<std::string> q1;
    std::stack<std::string> q2;
    q1.push("Jooooo");
    q1.push("Byy");
    q1.push("Wow");
    q2.push("Jooooo");
    q2.push("Byy");
    q2.push("Wow");
    ASSERT_TRUE(eq_stack(q1, q2));
}

TEST(stack_func, push2) {
    m3mpm::Stack<std::vector<double>> q1;
    std::stack<std::vector<double>> q2;
    q1.push({2.7, 7.2, -34.1});
    q1.push({12.47, -57.2, 94.1});
    q1.push({7.5, -95.2, -374.1});
    q2.push({2.7, 7.2, -34.1});
    q2.push({12.47, -57.2, 94.1});
    q2.push({7.5, -95.2, -374.1});
    ASSERT_TRUE(eq_stack(q1, q2));
}

TEST(stack_func, push3) {
    m3mpm::Stack<std::pair<std::string, std::map<char, float>>> q1;
    std::stack<std::pair<std::string, std::map<char, float>>> q2;
    q1.push({"Test", { {'T', -43.123}, {'E', 13.43}, {'S', 3.13}, {'F', 43.4} } });
    q1.push({"Map", { {'M', 3.1263}, {'A', 3.43}, {'P', 3.}, {'1', 5.4} } });
    q1.push({"Queue", { {'Q', 63.}, {'u', 3.43}, {'e', -53.}, {'U', 545.5}, {'E', -0.4} } });
    q2.push({"Test", { {'T', -43.123}, {'E', 13.43}, {'S', 3.13}, {'F', 43.4} } });
    q2.push({"Map", { {'M', 3.1263}, {'A', 3.43}, {'P', 3.}, {'1', 5.4} } });
    q2.push({"Queue", { {'Q', 63.}, {'u', 3.43}, {'e', -53.}, {'U', 545.5}, {'E', -0.4} } });
    ASSERT_TRUE(eq_stack(q1, q2));
}

TEST(stack_func, swap) {
    m3mpm::Stack<std::vector<double>> q1;
    std::stack<std::vector<double>> q2;
    q1.push({2.7, 7.2, -34.1});
    q1.push({12.47, -57.2, 94.1});
    q1.push({7.5, -95.2, -374.1});
    q2.push({2.7, 7.2, -34.1});
    q2.push({12.47, -57.2, 94.1});
    q2.push({7.5, -95.2, -374.1});
    m3mpm::Stack<std::vector<double>> q3;
    q3.swap(q1);
    ASSERT_TRUE(eq_stack(q3, q2));
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
