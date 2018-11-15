#include "pch.h"
#include "vectorPerformance.h"
#include <iostream>
#include <list>
#include <vector>

using namespace std;


void fillVector(vector<BigTestStruct>& testVector) {
	for (int i = 0; i < 10000; i++) {
		BigTestStruct bt;
		testVector.push_back(bt);
	}
}


void testReserve() {
	vector<BigTestStruct> testVector1;
	vector<BigTestStruct> testVector2;
	Stopwatch stopwatch;

	stopwatch.restart();
	fillVector(testVector1);
	cout << "Time to Fill Vector Without Reservation:" << stopwatch.getTime() << endl;

	stopwatch.restart();
	testVector2.reserve(10000);
	fillVector(testVector2);
	cout << "Time to Fill Vector With Reservation:" << stopwatch.getTime() << endl;
	cout << endl;
}


void testCapacity() {
	vector<BigTestStruct> testVector1;
	fillVector(testVector1);
	size_t capacity = testVector1.capacity();
	cout << "Capacity Before Erasing Elements:" << capacity << endl;

	testVector1.erase(testVector1.begin(), testVector1.begin() + 3);
	capacity = testVector1.capacity();
	cout << "Capacity After Erasing 3 elements Elements:" << capacity << endl;

	testVector1.clear();
	capacity = testVector1.capacity();
	cout << "Capacity After clearing all emements:" << capacity << endl;

	testVector1.shrink_to_fit();
	capacity = testVector1.capacity();
	cout << "Capacity After shrinking the Vector:" << capacity << endl;
	cout << endl;
}


void testFilling() {
	Stopwatch stopwatch;
	vector<BigTestStruct> source, destination;
	fillVector(source);
	// Assign sourceVector to destination vector
	stopwatch.restart();
	destination = source;
	cout << "Assigning Vector :" << stopwatch.getTime() << endl;

	//Using std::vector::insert()
	vector<BigTestStruct> source1, destination1;
	fillVector(source1);
	stopwatch.restart();
	destination1.insert(destination1.end(), source1.begin(), source1.end());
	cout << "Using insert() :" << stopwatch.getTime() << endl;

	//Using push_back()
	vector<BigTestStruct> source2, destination2;
	fillVector(source2);
	stopwatch.restart();
	for (unsigned i = 0; i < source2.size(); ++i) {
		destination2.push_back(source2[i]);
	}
	cout << "Using push_back :" << stopwatch.getTime() << endl;
	cout << endl;
}


void testIterating() {
	Stopwatch stopwatch;

	//Using an iterator
	vector<BigTestStruct> testVectorSum;
	fillVector(testVectorSum);
	stopwatch.restart();
	int sum = 0;
	for (auto it = testVectorSum.begin(); it != testVectorSum.end(); ++it)
	{
		sum = sum + it->iValue;
	}
	cout << "Using Iterator:" << stopwatch.getTime() << endl;

	//Using the at() member function
	stopwatch.restart();
	sum = 0;
	for (unsigned i = 0; i < testVectorSum.size(); ++i)
	{
		sum = sum + testVectorSum.at(i).iValue;
	}
	cout << "Using at() :" << stopwatch.getTime() << endl;

	// Using the subscript notation
	stopwatch.restart();
	sum = 0;
	for (unsigned i = 0; i < testVectorSum.size(); ++i)
	{
		sum = sum + testVectorSum[i].iValue;
	}
	cout << "Using subscripting:" << stopwatch.getTime() << endl;
	cout << endl;
}


void testFrontInserting() {
	Stopwatch stopwatch;
	vector<BigTestStruct> source, testVector;
	fillVector(source);
	list<BigTestStruct> testList;

	//Push 100k elements in front of the new vector -- this is horrible code !!! 
	stopwatch.restart();
	for (unsigned i = 1; i < source.size(); ++i) {
		testVector.insert(testVector.begin(), source[i]);
	}
	cout << "Pushing in front of Vector :" << stopwatch.getTime() << endl;

	// push in front of a list
	stopwatch.restart();
	for (unsigned i = 0; i < source.size(); ++i) {
		testList.push_front(source[i]);
	}
	cout << "Pushing in front of list :" << stopwatch.getTime() << endl;
	cout << endl;
}


void testEmplace() {
	Stopwatch stopwatch;
	vector<BigTestStruct> source, pushBackTestVector, emplaceBackTestVector;
	fillVector(source);

	//Test push back performance
	stopwatch.restart();
	for (unsigned i = 0; i < source.size(); ++i) {
		pushBackTestVector.push_back(source[i]);
	}
	cout << "Using push_back :" << stopwatch.getTime() << endl;

	//Test emplace_back()
	stopwatch.restart();
	for (unsigned i = 0; i < source.size(); ++i) {
		emplaceBackTestVector.emplace_back(source[i]);
	}
	cout << "Using emplace_back :" << stopwatch.getTime() << endl;
	cout << endl;
}


void testVector() {
	testReserve();
	testCapacity();
	testFilling();
	testIterating();
	testFrontInserting();
	testEmplace();
}