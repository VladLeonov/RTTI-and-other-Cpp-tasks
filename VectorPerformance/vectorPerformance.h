#ifndef VECTOR_PERFORMANCE
#define VECTOR_PERFORMANCE

#include <ctime>
#include <vector>

class Stopwatch {
	clock_t begin;
public:
	void restart() {
		begin = clock();
	}
	clock_t getTime() {
		clock_t end = clock();
		return end - begin;
	}
};


struct BigTestStruct {
	int iValue = 1;
	float fValue;
	long lValue;
	double dValue;
	char cNameArr[10];
	int iValArr[100];
};


void fillVector(std::vector<BigTestStruct>& testVector);

void testReserve();
void testCapacity();
void testFilling();
void testIterating();
void testFrontInserting();
void testEmplace();

void testVector();

#endif //VECTOR_PERFORMANCE

