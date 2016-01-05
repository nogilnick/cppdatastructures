#include <iostream>
#include <fstream>
#include <ctime>
#include "Map.h"
#include "HashMap.h"
#include "SearchTable.h"
#include "TreeMap.h"
#include "ArrayList.h"
#define NUM_TST 10000
using namespace std;

const static int ERROR = -1357;

const static int MAP_SIZE = 10000;
const static int SPACING = 1000;

//Array of random values to test with
static long VALS[MAP_SIZE];

//Used to generate timing results
//fn: The filename
//map: The map to time
template <typename T1, typename T2>
void CreateCSV(const string& fn, Map<T1, T2>& map);

//Used to test the erase function
//size: The size of the map to test
//map: The map to test
template <typename T1, typename T2>
void EraseTest(unsigned int size, Map<T1, T2>& map);

//Used to test the find function
//size: The size of the map to test
//map: The map to test
template <typename T1, typename T2>
void FindTest(unsigned int size, Map<T1, T2>& map);

//Function to initialize the static array with random
//values
void InitializeValues();

//Used to test the put function
//size: The size of the map to test
//map: The map to test
template <typename T1, typename T2>
void PutTest(unsigned int size, Map<T1, T2>& map);

/**
 * Used for timing tests
 */
template <typename T1, typename T2>
long double RunTest(void (*tst)(unsigned int, Map<T1, T2>&), unsigned int numTrials, Map<T1, T2>& map);

//Notice the parameter is that of the super class
//But we are allowed to pass a subclass as long as we
//Only use functions defined by the superclass interface
template <typename T1, typename T2>
void TestMap(Map<T1, T2>& map);

//Used to test the size function
//size: The size of the map to test
//map: The map to test
template <typename T1, typename T2>
void SizeTest(unsigned int size, Map<T1, T2>& map);


int main2()
{	//Test the TreeMap implementation
	TreeMap<long, long double> tmmap;
	try
	{
		TestMap(tmmap);
	}
	catch(int error)
	{
		if(error == tmmap.ELE_DNE)
		{
			cout << "TreeMap: A test failed.\n";
			return -1;
		}
	}
	CreateCSV("tm-out.csv", tmmap);
	cout << "TreeMap: All tests passed!\n";
	int i;
	//Test the HashMap implementation
	HashMap<long, long double> hmap;
	try
	{
		TestMap(hmap);
	}
	catch(int error)
	{
		if(error == hmap.ELE_DNE)
		{	
			cout << "HashMap: A test failed.\n";
			return -1;
		}
	}
	CreateCSV("hm-out.csv", hmap);
	cout << "HashMap: All tests passed!\n";
	//cin >> i;
	//Test the SearchTable implementation
	SearchTable<long, long double> stmap;
	try
	{
		TestMap(stmap);
	}
	catch(int error)
	{
		if(error == stmap.ELE_DNE)
		{
			cout << "SearchTable: A test failed.\n";
			return -1;
		}
	}
	CreateCSV("st-out.csv", stmap);
	cout << "SearchTable: All tests passed!\n";
	cin >> i;
	//Done; exit with 0 (success)
	return 0;
}

template <typename T1, typename T2>
void CreateCSV(const string& fn, Map<T1, T2>& map)
{
	ofstream csvFile;
	csvFile.open(fn.c_str());
	for(unsigned int i = 1; i <= MAP_SIZE; i += SPACING)
	{	//Run each test and append the results to the CSV file
		csvFile << i << ",";
		csvFile << RunTest(PutTest<T1, T2>, i, map) << ",";
		csvFile << RunTest(FindTest<T1, T2>, i, map) << ",";
		csvFile << RunTest(SizeTest<T1, T2>, i, map) << ",";
		csvFile << RunTest(EraseTest<T1, T2>, i, map) << "\n";
	}
	csvFile.close();
}

template <typename T1, typename T2>
void EraseTest(unsigned int size, Map<T1, T2>& map)
{	
	for(unsigned int i = 0; i < size; ++i)
		map.Erase(T1(VALS[i]));
}

template <typename T1, typename T2>
void FindTest(unsigned int size, Map<T1, T2>& map)
{	
	for(unsigned int i = 0; i < size; ++i)
		map.Find(T1(VALS[i]));
}

void InitializeValues()
{
	srand((unsigned int) time(NULL));
	ArrayList<int> al(MAP_SIZE);
	for(int i = 0; i < MAP_SIZE; ++i)
		al.Add(i);
	for(int i = 0; i < MAP_SIZE; ++i)
	{
		int j = rand() % al.Size();
		VALS[i] = al.Get(j);
		al.Remove(j);
	}
}

template <typename T1, typename T2>
void PutTest(unsigned int size, Map<T1, T2>& map)
{	
	for(unsigned int i = 0; i < size; ++i)
		map.Put(T1(VALS[i]), T2(VALS[i]));
}


template <typename T1, typename T2>
long double RunTest(void (*tst)(unsigned int, Map<T1, T2>&), unsigned int numTrials, Map<T1, T2>& map)
{	//Start time and run tests
	clock_t strt, end;
	strt = clock();
	try
	{
		tst(numTrials, map);
	}
	catch(int errCode)
	{
		if(errCode == Map<T1, T2>::ELE_DNE)
		{
			cout << "Error: element does not exist\n";
			exit(1);
		}
	}
	end = clock();
	return 1000.0 * ((end - strt) / ((long double) numTrials * CLOCKS_PER_SEC));
}

template <typename T1, typename T2>
void SizeTest(unsigned int size, Map<T1, T2>& map)
{	
	for(unsigned int i = 0; i < size; ++i)
		map.Size();
}

template <typename T1, typename T2>
void TestMap(Map<T1, T2>& map)
{
	int numTimes = 50;
	for(int i = 0; i < NUM_TST; ++i)
	{
		InitializeValues();
		//test Size
		if(map.Size() != 0)
			throw ERROR;
		//Test Put
		for(int j = 0; j < numTimes; ++j)
			map.Put(VALS[j], VALS[j]);
		//Test Find
		for(int j = 0; j < numTimes; ++j)
			map.Find(VALS[j]);
		//test Size
		if(map.Size() != numTimes)
			throw ERROR;
		//Test erase
		for(int j = 0; j < numTimes; ++j)
			map.Erase(VALS[j]);
		//test Size
		if(map.Size() != 0)
			throw ERROR;
	}
}
