// **************************************************************************
//  File       [sort_tool.cpp]
//  Author     [Yu-Hao Ho]
//  Synopsis   [The implementation of the SortTool Class]
//  Modify     [2019/9/6 Cheng-Yun Hsieh]
// **************************************************************************

#include "sort_tool.h"
#include<iostream>


using namespace std;
// Constructor
SortTool::SortTool() {}

// Insertsion sort method
void SortTool::InsertionSort(vector<int>& data) {
    // Function : Insertion sort
    // TODO : Please complete insertion sort code here
   int temp = 0;

   for(int i = 1 ; i < data.size() ; i ++){
	temp = data[i];
	int j = i;
	    while ((data[j-1] > temp)&&(j>0)){
		data[j] = data[j-1];
		j--;
	//	cout << data[j] <<endl;
		}	
		data[j] = temp;
	}
    }


// Quick sort method
void SortTool::QuickSort(vector<int>& data){
    QuickSortSubVector(data, 0, data.size() - 1);
}
// Sort subvector (Quick sort)
void SortTool::QuickSortSubVector(vector<int>& data, int low, int high) {
    // Function : Quick sort subvector
    // TODO : Please complete QuickSortSubVector code here
    // Hint : recursively call itself
    //        Partition function is needed
    int pivot =0;
    if(low<high){
    pivot =  Partition(data , low , high);
    QuickSortSubVector(data, low,pivot-1);
    QuickSortSubVector(data, pivot+1,high);  
    }
}

int SortTool::Partition(vector<int>& data, int low, int high) {
    // Function : Partition the vector 
    // TODO : Please complete the function
    // Hint : Textbook page 171
    //
    int x = data[high];
    int i = low-1;
    for( int j = low; j<=high-1 ; j++){
	if ( data[j] <= x){
	    i =i+1;
  	    swap(data[i],data[j]);
         }    
    }
    swap(data[i+1],data[high]);
    return i+1;
}

// Merge sort method
void SortTool::MergeSort(vector<int>& data){
    MergeSortSubVector(data, 0, data.size() - 1);
}

// Sort subvector (Merge sort)
void SortTool::MergeSortSubVector(vector<int>& data, int low, int high) {
    // Function : Merge sort subvector
    // TODO : Please complete MergeSortSubVector code here
    // Hint : recursively call itself
    //        Merge function is needed
    int q =0;
    if(low<high){
        q = (low+high)/2;
	//cout<<q<<endl;
        MergeSortSubVector(data,low,q);
	MergeSortSubVector(data,q+1,high);
	Merge(data,low,q,0,high);
    }       
}

// Merge
void SortTool::Merge(vector<int>& data, int low, int middle1,int middle2,  int high) {
    // Function : Merge two sorted subvector
    // TODO : Please complete the function
    int n1= middle1 - low +1; 
    int n2= high - middle1;
    int *L_array = new int[n1+1]; 
    int *R_array = new int[n2+1];
    for(int i =0; i<=n1-1 ;i++){
        L_array[i] = data[low+i]; 
	//cout<<"data[low+i]"<<data[low+i]<<"L_array="<<L_array[i]<<endl;
    }
    for(int j =0; j<=n2-1 ;j++){
        R_array[j] = data[middle1+j+1];
    }
    L_array[n1] = 999999999;
    R_array[n2] = 999999999; 
    int i=0,j=0;
   for(int k=low; k<= high ;k++){
	if(L_array[i]>=R_array[j]){
	    data[k] = R_array[j];
	    j++;
        }	
	else if(L_array[i]<R_array[j]){
	    data[k] = L_array[i];
	    i++;
        }
   }
   delete [] L_array;
   delete [] R_array;    
}

// Heap sort method
void SortTool::HeapSort(vector<int>& data) {
    // Build Max-Heap
    BuildMaxHeap(data);
    // 1. Swap data[0] which is max value and data[i] so that the max value will be in correct location
    // 2. Do max-heapify for data[0]
    for (int i = data.size() - 1; i >= 1; i--) {
        swap(data[0],data[i]);
        heapSize--;
        MaxHeapify(data,0);
    }
}

//Max heapify
void SortTool::MaxHeapify(vector<int>& data, int root) {
    // Function : Make tree with given root be a max-heap if both right and left sub-tree are max-heap
    // TODO : Please complete max-heapify code here
    int largest = 0;
    int tempt = 0;
    if(((2*root+1)<=(heapSize-1))&&(data[2*root+1]>data[root])){
	largest = 2*root+1;
    }
    else largest = root;
    if (((2*root+2)<=(heapSize-1))&&(data[2*root+2]>data[largest])) largest = 2*root+2;
    if (largest != root){
    	tempt = data[largest];
	data[largest] = data[root];
	data[root] = tempt;	
        MaxHeapify(data,largest);
    }
}

//Build max heap
void SortTool::BuildMaxHeap(vector<int>& data) {
    heapSize = data.size(); // initialize heap size
    // Function : Make input data become a max-heap
    // TODO : Please complete BuildMaxHeap code here
    for(int i = heapSize/2; i>=0; i--){
	MaxHeapify(data,i);
    }
}
