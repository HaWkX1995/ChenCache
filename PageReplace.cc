#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <time.h> 
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

//Prototypes

void FIFO();
void Optimal();
void LRU();
void SC();
void LFU();
void Circle();

void FileToArray();

//Global Variables

int datasetArray[10000];
int pageSortArray[10000][2];
int numbersinput = 0;
int pagefaults = 0;

int main()
{
	FileToArray();
	int picker;
	cout << "Pick an algorithm to run." << endl << "1. FIFO" << endl << "2. Optimal" << endl << "3. Least Recenly Used" << endl
		 << "4. Second Chance" << endl << "5. Least Frequently Used" << endl << "6. Circle" << endl;
	cin >> picker;
	cout << endl;

	if (picker == 1)
	FIFO();
	else if (picker == 2)
	Optimal();
	else if (picker == 3)
	LRU();
	else if (picker == 4)
	SC();
	else if (picker == 5)
	LFU();
	else if (picker == 6)
		Circle();
	else
		cout << "You picked the wrong number." << endl;

	return 0;
}

void FIFO()	//Works, huge negative values are actually empty points of the array
{
	cout << "Performing FIFO Replacement" << endl;
	int count = 0;
	int front = 0;
	int frameArray[3];
	int frameArray2[4];
	int framecount = 3;
	int framecount2 = 4;
	pagefaults = 0;
	//Sets the first part of page array to equal the stored value array
	while (datasetArray[count] != 0)
	{
		pageSortArray[count][0] = datasetArray[count];
		count++;
	}

	for (int i = 0; i <= count; i++)		//Search feature used to find values
	{
		int j = 0;
		while (j < framecount)
		{
			if (pageSortArray[i][0] == frameArray[j])
			{
				break;
			}
			else if (pageSortArray[i][0] != frameArray[j])
			{
				j++;
			}
		}
		if (j >= framecount)
		{
			frameArray[front] = pageSortArray[i][0];
			pagefaults++;
			front++;
			if (front >= framecount)
			{
				front = 0;
			}
		}
		cout << frameArray[0] << " " << frameArray[1] << " " << frameArray[2] << endl;
	}
	cout << "# of Page Faults: " << pagefaults << endl << endl;
//----------------------------------------------------------------------------------------------------------------------
	pagefaults = 0;
	front = 0;
	for (int i = 0; i <= count; i++)
	{
		int j = 0;
		while (j < framecount2)
		{
			if (pageSortArray[i][0] == frameArray2[j])
			{
				break;
			}
			else if (pageSortArray[i][0] != frameArray2[j])
			{
				j++;
			}
		}
		if (j >= framecount2)
		{
			frameArray2[front] = pageSortArray[i][0];
			pagefaults++;
			front++;
			if (front >= framecount2)
			{
				front = 0;
			}
		}
		cout << frameArray2[0] << " " << frameArray2[1] << " " << frameArray2[2] << " " << frameArray2[3] << endl;
	}
	cout << "# of Page Faults: " << pagefaults << endl;
}

void Optimal() //Runs, but doesn't change values once the frame array is full for some reason
{
	int count = 0;
	int future = 0;
	int front = 0;
	int frameArray[3];
	int frameArray2[4];
	int framecount = 3;
	int framecount2 = 4;
	int maxPostition = 0;
	pagefaults = 0;

	while (datasetArray[count] != 0)
	{
		pageSortArray[count][0] = datasetArray[count];
		pageSortArray[count][1] = count;
		count++;
	}

	for (int i = 0; i <= count; i++)			//Search funtion used to find values
	{
		int j = 0;
		while (j < framecount)
		{
			if (datasetArray[i] == frameArray[j])
			{
				break;
			}
			else if (datasetArray[i] != frameArray[j])
			{
				j++;
			}
		}
		if (j >= framecount)
		{
			for (int l = 0; l < framecount; l++)
			{
				for (int k = i; k < count; k++)
				{
					if (frameArray[l] == pageSortArray[k][0])
					{
						if (maxPostition < pageSortArray[k][1])
						{
							maxPostition = pageSortArray[k][1];
						}
					}
				}
			}
				for (int k = 0; k < framecount; k++)
				{
					if (frameArray[k] == pageSortArray[maxPostition][0] && frameArray[k+1] > 0)
						frameArray[k] = datasetArray[i];
					else if (frameArray[k] < 0)
					{
						frameArray[k] = datasetArray[i];
						break;
					}
				}
				pagefaults++;
		}
		cout << frameArray[0] << " " << frameArray[1] << " " << frameArray[2] << endl;
	}
	cout << "# of Page Faults: " << pagefaults << endl;
}

void LRU()
{
	int count = 0;
	int future = 0;
	int front = 0;
	int frameArray[3][2];
	int frameArray2[4][2];
	int framecount = 3;
	int framecount2 = 4;
	pagefaults = 0;
        
    cout << "Performing LRU Replacement" << endl;
    
	while (datasetArray[count] != 0)
	{
		pageSortArray[count][0] = datasetArray[count];
		pageSortArray[count][1] = count;
		count++;
	}

	for (int i = 0; i <= count; i++)		//Search function used to find values
	{
		int j = 0;
		while (j < framecount)
		{
			if (datasetArray[i] == frameArray[j][0])
			{
				frameArray[j][1] = pageSortArray[i][1];
				break;
			}
			else if (datasetArray[i] != frameArray[j][0])
			{
				j++;
			}
		}
		if (j >= framecount)
		{
			for (int k = 0; k <= framecount; k++)
			{   
                            
                            pagefaults++;
                            front++;
			}
		}
                cout << frameArray[0] << " " << frameArray[1] << " " << frameArray[2] << endl;
	}
		cout << "# of Page Faults: " << pagefaults << endl;
//----------------------------------------------------------------------------------------------------------------------
               //  = 0;
                //front = 0;
}

void SC()
{
	int count = 0;

	//Sets the first part of page array to equal the stored value array
	while (datasetArray[count] != 0)
	{
		pageSortArray[count][0] = datasetArray[count];
		count++;
	}
}

void LFU()
{
	int count = 0;

	//Sets the first part of page array to equal the stored value array
	while (datasetArray[count] != 0)
	{
		pageSortArray[count][0] = datasetArray[count];
		count++;
	}
}

void Circle()
{
	int count = 0;

	//Sets the first part of page array to equal the stored value array
	while (datasetArray[count] != 0)
	{
		pageSortArray[count][0] = datasetArray[count];
		count++;
	}
}

void FileToArray()
{
	//check for file
	int insert = 0;
	int index = 0;


	fstream in_file("ShortCodeSeries.txt", ios::in);
	if (!in_file)
	{
		cout << "Cannot open file.\n";
		exit(-1);
	}

	while (true) {
		//read line
		in_file >> index;

		datasetArray[insert] = index;

		//test for eof
		if (in_file.eof())
			break;

		insert++;
	}
}