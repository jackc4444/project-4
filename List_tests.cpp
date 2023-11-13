#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(copy_constructor) {
    List<int> nums;
	for (int i = 0; i < 10; ++i){
		nums.push_back(i);
	}
	List<int> newlist = nums;
	ASSERT_TRUE(10 == newlist.size());
	ASSERT_TRUE(10 == nums.size());
	
	int val = 0;
	for (List<int>::Iterator i = newlist.begin(); i != newlist.end(); ++i){
		ASSERT_EQUAL(*i, val);
		++val;
	}
	
	val = 0;
	for (List<int>::Iterator i = nums.begin(); i != nums.end(); ++i){
		ASSERT_EQUAL(*i, val);
		++val;
	}
	
	//check for deep copy
	//remove elements, test for separately allocated values on heap
	nums.pop_back();
	nums.pop_back();
	nums.pop_back();
	
	ASSERT_TRUE(7 == nums.size());
	ASSERT_TRUE(10 == newlist.size());
	ASSERT_TRUE(nums.back() == 6);
	ASSERT_TRUE(newlist.back() == 9);
	
}

TEST(assignment_operator_not_empty_list) {
	List<double> doublelist;
	doublelist.push_front(1);
	doublelist.push_front(1);
	doublelist.push_front(1);
	doublelist.push_front(1);
	doublelist.push_front(5);
	
	ASSERT_TRUE(doublelist.front() == 5);
	
	List<double> list2;
	list2.push_back(10);
	list2.push_back(10.5);
	doublelist = list2;
	
	ASSERT_TRUE(doublelist.size() == 2);
	ASSERT_TRUE(doublelist.front() == 10);
	ASSERT_TRUE(doublelist.back() == 10.5);
	
}

TEST(assignment_operator_empty_list) {
    List<double> doublelist;
	doublelist.push_front(1);
	doublelist.push_front(1);
	doublelist.clear();

	List<double> list2;
	list2.push_back(10);
	list2.push_back(10.5);
	doublelist = list2;
	
	ASSERT_TRUE(doublelist.size() == 2);
	ASSERT_TRUE(doublelist.front() == 10);
	ASSERT_TRUE(doublelist.back() == 10.5);
}

TEST(assignment_operator_self) {
    List<double> doublelist;
	doublelist.push_front(3);
	doublelist.push_front(1);
	
	doublelist = doublelist;
	
	ASSERT_TRUE(doublelist.size() == 2);
	ASSERT_TRUE(doublelist.front() == 1);
	ASSERT_TRUE(doublelist.back() == 3);
}

TEST(clear_list) {
    List<char> charlist;
	charlist.push_back('a');
	charlist.push_back('a');
	charlist.push_back('a');
	charlist.clear();
	ASSERT_EQUAL(0, charlist.size())
}

TEST(check_empty) {
    List<char> charlist;
	charlist.push_back('a');
    ASSERT_TRUE( ! charlist.empty() );
}

TEST(check_front) {
    
    ASSERT_TRUE(true);
	
	
}

TEST(check_back) {
    
    ASSERT_TRUE(true);
	
	
}

TEST(push_front) {
    List<double> doublelist;
	doublelist.push_front(1.0);
	doublelist.push_front(1.3);
	doublelist.push_front(1.5);
	ASSERT_EQUAL(1.5, doublelist.front());
	ASSERT_EQUAL(3, doublelist.size());
}


TEST(push_back_emptylist_checksize_and_pointers) {
    
    ASSERT_TRUE(true);
	
	
}

TEST(push_back_not_emptylist_checksize_and_pointers) {
    
    ASSERT_TRUE(true);
	
	
}

TEST(pop_front_empty) {
    
    ASSERT_TRUE(true);
	
	
}

TEST(pop_front) {
    
    ASSERT_TRUE(true);
	
	
}

TEST(pop_back) {
    
    ASSERT_TRUE(true);
	
	
}

TEST(pop_back_empty) {
    
    ASSERT_TRUE(true);
	
	
}

//jason put operator tests here

TEST_MAIN()
