#include <iostream>
#include <string>
#include <fstream> //for inputing passwords into the array
using namespace std; 
#define MAX_PASS 10000 //max amount of elements

//pass compare and movement values by reference to the partion and merge functions 

//Partition function for quick sort 
int Partition(string* array, int startIndex, int endIndex, int &move, int &compare) {
	// Select the middle value as the pivot.
	int midpoint = startIndex + (endIndex - startIndex) / 2;
	string pivot = array[midpoint];

	// "low" and "high" start at the ends of the partition
	// and move toward each other.
	int low = startIndex;
	int high = endIndex;

	bool done = false;
	while (!done) {
		// Increment low while numbers[low] < pivot
		while (array[low] < pivot) {
			low = low + 1;
			compare++; 
		}

		// Decrement high while pivot < numbers[high]
		while (pivot < array[high]) {
			high = high - 1;
			compare++; 
		}

		// If low and high have crossed each other, the loop
		// is done. If not, the elements are swapped, low is
		// incremented and high is decremented.
		if (low >= high) {
			done = true;
		}
		else {
			string temp = array[low];
			array[low] = array[high];
			array[high] = temp;
			low = low + 1;
			high = high - 1;
			move+=3; 
		}
	}

	// "high" is the last index in the left partition.
	return high;
}
//End of partition function 




//Merge function for merge sort
void Merge(string* array, int leftFirst, int leftLast, int rightLast, int &move, int &compare) {
	int mergedSize = rightLast - leftFirst + 1;       // Size of merged partition
	string* mergedNumbers = new string[mergedSize]; // Dynamically allocates temporary
	// array for merged numbers 
	int mergePos = 0;                         // Position to insert merged number
	int leftPos = leftFirst;                  // Initialize left partition position
	int rightPos = leftLast + 1;              // Initialize right partition position

	// Add smallest element from left or right partition to merged numbers
	while (leftPos <= leftLast && rightPos <= rightLast) {
		if (array[leftPos] <= array[rightPos]) {
			mergedNumbers[mergePos] = array[leftPos];
			move++;
			leftPos++;
			compare++;
		}
		else {
			mergedNumbers[mergePos] = array[rightPos];
			move++; 
			rightPos++;
			compare++; 
		}
		mergePos++;
		compare++; 
	}
	 


	// If left partition is not empty, add remaining elements to merged numbers
	while (leftPos <= leftLast) {
		mergedNumbers[mergePos] = array[leftPos];
		move++; 
		leftPos++;
		mergePos++;
		compare++; 
	}

	// If right partition is not empty, add remaining elements to merged numbers
	while (rightPos <= rightLast) {
		mergedNumbers[mergePos] = array[rightPos];
		move++;
		rightPos++;
		mergePos++;
		compare++; 
	}

	// Copy merged numbers back to numbers
	for (mergePos = 0; mergePos < mergedSize; mergePos++) {
		array[leftFirst + mergePos] = mergedNumbers[mergePos];
	}

	// Free temporary array
	delete[] mergedNumbers;
}

//end of merge function






//selection Sort Function 
void selectionSort(string* array, int arraySize, int& move, int& compare) {

	for (int i = 0; i < arraySize - 1; i++) {

		//index of the smallest remaining element
		int smallIndex = i;
		for (int j = i + 1; j < arraySize; j++) {
			compare++; 
			if (array[j] < array[smallIndex]) {
				smallIndex = j;
			}
		}

		//swapping 
		string temp = array[i];
		array[i] = array[smallIndex];
		array[smallIndex] = temp;

		move += 3; // + 3 movements when swapping

	}
}

//end of selection sort 




//Bubble sort function 
void bubbleSort(string* array, int arraySize, int &move, int &compare) {
	
	//loop to access each array element
	for (int step = 0; step < arraySize; ++step) {

		//loop to compare elements
		for (int i = 0; i < arraySize - step; ++i) {
			compare++; 
			if (array[i] > array[i + 1]) {
				string temp = array[i];
				array[i] = array[i + 1];
				array[i + 1] = temp;
				move += 3; 
			}
		}
	}

}

//end of bubble sort 




//insertion sort function 
void insertionSort(string* array, int arraySize, int &move, int &compare) {
	for (int i = 1; i < arraySize; i++) {
		int j = 1;
		while (j > 0 && array[j] < array[j - 1]) {
			
			string temp = array[j];
			array[j] = array[j - 1];
			array[j - 1] = temp;
			j--; 
			move += 3; 
			compare++;
		}
	}

}

//end of insertion sort function 





//merge sort function 
void mergeSort(string* array, int startIndex, int endIndex, int &move, int &compare) {
	int movementMerge = 0; 
	int compareMerge = 0; 
	
	if (startIndex < endIndex) {
		// Find the midpoint in the partition
		compare++;
		int mid = (startIndex + endIndex) / 2;

		// Recursively sort left and right partitions
		mergeSort(array, startIndex, mid, move, compare);
		mergeSort(array, mid + 1, endIndex, move, compare);

		// Merge left and right partition in sorted order
		Merge(array, startIndex, mid, endIndex, movementMerge, compareMerge);
	}

	move = move + movementMerge;
	compare = compare + compareMerge; 
}

// end of merge sort function 



//quick sort function 
void quickSort(string* array, int startIndex, int endIndex, int &move, int &compare) {
	// Only sort if at least 2 elements exist
	int quickMove = 0; 
	int quickCompare = 0; 
	if (endIndex <= startIndex) {
		return;
	}

	// Partition the array
	int high = Partition(array, startIndex, endIndex, quickMove, quickCompare);
	// Recursively sort the left partition
	quickSort(array, startIndex, high, move, compare);

	// Recursively sort the right partition
	quickSort(array, high + 1, endIndex, move, compare);

	move = move + quickMove;
	compare  = compare + quickCompare; 
}

//end of quick sort function 




//main function 
int main() {
	ifstream file; //input declaration 
	string array[MAX_PASS]; //declaring array of strings

	file.open("Passwords.txt"); //opening file

	if (file.fail()) { //testing to see if file failes to open
		cout << "File failed to open" << endl;
		return 1;
	}

	int line = 0; //how many lines have been read

	while (!file.eof()) { //putting input into the array
		getline(file, array[line]);
		line++;

		if (line == MAX_PASS) {
			cout << "Max storage reached\n";
			break;
		}
	}

	file.close();  //close the file

	int arraySize = sizeof(array) / sizeof(array[0]); //the size is 10000 as expected
	
	//Copy your original array into other sorting arrays

	//bubble sort array
	string bubbleArray[10000]; 
	for(int i = 0; i < MAX_PASS; ++i) {
		bubbleArray[i] = array[i]; 
	} 

	//selection sort array 
	string selectionArray[10000]; 
	for(int y = 0; y < MAX_PASS; ++y) {
		selectionArray[y] = array[y]; 
	} 

	//insertion sort array 
	string insertionArray[10000]; 
	for(int p = 0; p < MAX_PASS; ++p) {
		insertionArray[p] = array[p]; 
	}


	//merge sort array 
	string mergeArray[10000]; 
	for(int u = 0; u < MAX_PASS; ++u) {
		mergeArray[u] = array[u]; 
	}

	//quick sort 
	string quickArray[10000]; 
	for(int g = 0; g < MAX_PASS; ++g) {
		quickArray[g] = array[g]; 
	}

	// Calling Selection Sort 
	//move and compare pass by reference
	int sMove = 0;
	int sCompare = 0;
	selectionSort(selectionArray, arraySize, sMove, sCompare);
	cout << "Selection Sort Compare: " << sCompare << "\n";
	cout << "Selection Sort Movement: " << sMove << "\n";


	//bubble sort
	int bMove = 0;
	int bCompare = 0;
	bubbleSort(bubbleArray, arraySize, bMove, bCompare);
	cout << "Bubble Sort Compare: " << bCompare << "\n";
	cout << "Bubble sort Movement: " << bMove << "\n";

	//insertion sort
	int iMove = 0;
	int iCompare = 0;
	insertionSort(insertionArray, arraySize, iMove, iCompare); 
	cout << "Insertion Sort Compare: " << iCompare << "\n";
	cout << "Insertion sort Movement: " << iMove << "\n";

	//merge sort 
	int mMove = 0;
	int mCompare = 0; 
	mergeSort(mergeArray, 0, arraySize - 1, mMove, mCompare); 
    cout << "Merge sort Compare: " << mCompare << "\n"; 
    cout << "Merge sort Move: " << mMove << "\n"; 
    


	//quick sort
	int qMove = 0;
	int qCompare = 0;
	quickSort(quickArray, 0, arraySize - 1, qMove, qCompare); 
    cout << "Quick Sort Compare: " << qCompare << "\n";
    cout << "Quick sort Move: " << qMove << "\n"; 

}; 
