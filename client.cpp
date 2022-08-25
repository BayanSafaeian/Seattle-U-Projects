/*
 *File: client.cpp
 *Author: Yingwu Zhu
 *Last Modification: 10/01/2021  
 */

#include <iostream>
#include <algorithm>
#include <queue>
#include <cassert>
#include <fstream>
#include "myqueue.cpp"
using namespace std;

void verify(MyQueue& q1, queue<int>& q2) {
	if (q2.empty()) {
		cout << "Queue is empty...\n";
		assert(q1.empty() && q1.size() == 0);
	} else {
		cout << "The first element is: " << q2.front() << "    ";
		cout << "The last element is: " << q2.back() << endl;
		assert(q1.front() == q2.front());
		assert(q1.back() == q2.back());
	}
}

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << argv[0] << " " << "[input_file]" << endl;
		return -1;
	}
	ifstream fin(argv[1]);
	MyQueue Q1;
	queue<int> Q2;
	string op;
	int v;
	while (fin >> op) {
		if (op == "push") {
			fin >> v;
			Q1.push(v);
			Q2.push(v);
			verify(Q1, Q2);
		} else {
			Q1.pop();
			Q2.pop();
			verify(Q1, Q2);
		}
	}
	fin.close();
	cout << "You have passed the test case!\n";
	return 0;
}