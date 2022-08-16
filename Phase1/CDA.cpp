/* 
 * Purpose: Phase 1 of CS201 Project, Circular Dynamic Array of Data Structures Library.
 * Made with C++ Templates in order to manipulate various datatypes: ints, floats, chars
*/

#include <bits/stdc++.h>
#include <iostream>
#include <cctype>
#include <algorithm>
//#ifndef CDA 
#pragma once 
using  namespace std;

template <class T>

class CDA {

    private:
        T *myArray;
        int head = 0;
        int size;
        int capacity;
        int copyIndex = 0;
        bool initilized = false;
        bool sorted = false;//Any adds or deletes assumes unsorted array for binsearch to then sort
        T referenceVal; 
        T randVal=63;
        int* copyIndexArray; // after insert of index i, store i into this array
        int* atIndexArray; // after copy array insert, store the value of i's index int he copy array,
                            // into the address of i in the atIndexArray


    //Checks whether or not the value in atIndexArray[i] is an index (0...n) and therefore good data
    //Returns false if its bad data, true for good data
        bool checkGoodData(int i){
            bool val = true;
            if(initilized){//if this is the initilized constructor array
                int num1= 0;
                num1 = atIndexArray[HiddenIndex(i)]; //copies the array index, at copy arrays index
                if(num1<0 || num1 >= copyIndex || !(copyIndexArray[num1] == HiddenIndex(i))){ //if uninit cause val is out of bounds
                    val = false;
                }
            }
            return val;
        }


    //grow function for doubling array when full
        void grow(){ // 

            //capacity*=2; caused me many tears and pain, had to update
            //at end of function for copy purposes
            int newCap = capacity*2;
            T* growArray = new T[newCap];
            
            for(int i=0; i<size; i++){ //coppies over values to new grow array
               if(checkGoodData(i)){
                    growArray[i] = myArray[HiddenIndex(i)];
                }
                else{                   
                    growArray[i] = referenceVal;
                }
            }

            delete[] myArray;
            myArray = growArray;
            capacity=newCap;
            head = 0;
            initilized = false;
        }


    //shrink function for halving array
        void shrink(){
            int halfCap = capacity/=2;
            T* shrinkArray = new T[halfCap];

            for(int i=0; i<size; i++){ //coppies over values to new shrink array
                shrinkArray[i] = myArray[HiddenIndex(i)];
            }
            delete[] myArray;
            myArray = shrinkArray;
            capacity=halfCap;
            head = 0;
        }


    //was using this all over my program, decided to make a helper function
       int HiddenIndex(int index){
            return (head+index)%capacity;
       }

    // CPP program for implementation of QuickSelect (Credit: Geeks forGeeks)
    //Needed to add my HiddenIndex function to first line of following code for this to work 
    // Standard partition process of QuickSort().
    // It considers the last element as pivot
    // and moves all smaller element to left of
    // it and greater elements to right
        int partition(T arr[], int l, int r){
            int pIndex = l + rand() % (r - l + 1);
            T x = arr[HiddenIndex(pIndex)], i = l;
            swap(arr[HiddenIndex(pIndex)], arr[HiddenIndex(r)]);

            for (int j = l; j <= r - 1; j++) {
                if (arr[HiddenIndex(j)] <= x) {
                    swap(arr[HiddenIndex(i)], arr[HiddenIndex(j)]);
                    i++;
                }
            }
            swap(arr[HiddenIndex(i)], arr[HiddenIndex(r)]);
            return i;
        }
    
    // This function returns k'th smallest
    // element in arr[l..r] using QuickSort
    // based method.  ASSUMPTION: ALL ELEMENTS
    // IN ARR[] ARE DISTINCT
        int kthSmallest(T arr[], int l, int r, int k){
            // If k is smaller than number of
            // elements in array
            if (k > 0 && k <= r - l + 1) {
        
                // Partition the array around last
                // element and get position of pivot
                // element in sorted array
                int index = partition(arr, l, r);
        
                // If position is same as k
                if (index - l == k - 1)
                    return arr[HiddenIndex(index)];
        
                // If position is more, recur
                // for left subarray
                if (index - l > k - 1)
                    return kthSmallest(arr, l, index - 1, k);
        
                // Else recur for right subarray
                return kthSmallest(arr, index + 1, r,  k - index + l - 1);
            }
        
            // If k is more than number of
            // elements in array
            return INT_MAX;
        }


    //checks each child node for larger element, sets that to max, calls heapify
    //with array and max, checks its childen and so on. inplace sorter, no need to return
        void Heapify(T array[], int sizeOfArray, int index){
            int left = 2*index+1;
            int right = 2*index+2;
            int max = index;
            //if left chld is in scope and greater than parent
            if((left < sizeOfArray) &&( array[HiddenIndex(left)] > array[HiddenIndex(max)] )){
                max = left;
            }
            //if right chld is in scope and greater than parent
            if((right < sizeOfArray) &&( array[HiddenIndex(right)] > array[HiddenIndex(max)] )){
                max = right;
            }
            
            if(max != index){
                swap(array[HiddenIndex(index)], array[HiddenIndex(max)]); //defined in algorithm!!
                Heapify(array, sizeOfArray,max);
            }
        }


    //calls heapify on all parent nodes to move each max child up and fix all heap violations
        void BuildMaxHeap(T array[], int size){
           //int size = array.Length();
           for(int i=size/2-1; i>=0; i--){
               Heapify(array, size, i);
           }
        }
    

    //Repeatedly Swaps root of max sorted array with last element, 
    //fixes max heap violations on remaining array
        void HeapSort(T array[], int sizeOfArray){
            BuildMaxHeap(array, sizeOfArray); 
            for(int i=size-1; i>0; i--){
                swap(array[HiddenIndex(0)],array[HiddenIndex(i)]);
                Heapify(array,i,0);
            }
        }


    //Returns index of thing iteratively
    //modified from zybooks ch 15
        int BinarySearchAlg(T key) {
            int mid;
            int low;
            int high;
            int listSize = size;
            //int bitComp =0;
            low = 0;
            high = listSize - 1;
            while (high >= low) {
                mid = (high + low) / 2;
                if (myArray[HiddenIndex(mid)] < key) {
                    low = mid + 1;
                }
                else if (myArray[HiddenIndex(mid)] > key) { 
                    high = mid - 1;
                }
                else {
                    return mid;
                }
            }
            if(low >= listSize){ //if key > list, low will terminate = to listSize
                //cout<<"low is"<< low<<endl;
                return ~size;
            }
            else if(low < listSize){ //if key isn't greater than list, but absent, low terminates on next largest
                //cout<<"high is"<< high<<endl;
                return ~(low);
            }
            return -1; // not found
        }

    public:
    // default constructor array capcity 1, size 0 ordered false
        CDA(){    
            size = 0;
            head = 0;
            capacity = 1;
            referenceVal = 65;
            sorted = false;
            myArray = new T[capacity];
            copyIndex=0;
            initilized=false;
            copyIndexArray=nullptr;
            atIndexArray=nullptr;
            }
            
    // constuctor sets capcity and size to s
        CDA(int s){   
            head = 0;
            size = s;
            capacity = s;
            sorted=false;
            referenceVal = 65;
            myArray = new T[capacity];
            copyIndex=0;
            initilized=false;
            copyIndexArray=nullptr;
            atIndexArray=nullptr;
            }

    //  behaves as if initizilzed with value init(template)   
     //3 arrays, one integer array(of indexesgiven), one pointer array, pointer points to array of memory/insert, 
            //point to the index given, search, check if thers a pointer
            //does pointer point to index
            // does it match the proper index? how about the index passed in?
        CDA(int s, T init){ 
            
            head = 0;
            size = s;
            capacity = s;
            sorted = false;
            referenceVal = init;
            myArray =  new T[capacity];
            copyIndexArray = new int[s]; // after insert of index i, store i into this array
            atIndexArray= new int[s]; // after copy array insert, store the value of i's index int he copy array,
                                    // into the address of i in the atIndexArray
            copyIndex = 0;
            initilized = true;
        } 
    
    //  destructor fucntion call
        ~CDA(){
            if(capacity == 0){
                delete myArray;
               // delete copyIndexArray;
                //delete atIndexArray; //if initialized delete?
            }
            else{
                //cout<<"deleteing array now";
                delete[] myArray;
                //delete[] copyIndexArray;
                //delete[] atIndexArray;
            }   
        }


    // copy constructor required, makes unconnected copy
        CDA( CDA &firstCDARhs){ //seems to work

            capacity = firstCDARhs.capacity;
            size = firstCDARhs.size;
            head=0;
            myArray = new T[capacity];
            for(int i=0; i<size; i++){
                myArray[i] = firstCDARhs[i];
            }
        }


    // copy assignment operator required Sets
        CDA& operator=( CDA& firstCDARhs){    

            capacity = firstCDARhs.capacity;
            size = firstCDARhs.size;
            myArray = new T[capacity];
            head = 0;
            for(int i=0; i<size; i++){
                myArray[i] = firstCDARhs[i];
            }
            return *this;
        }


    // print error message if out of bounds,size-1, return reference to value of the type (0(1))
    //for the initilized array, does extra to deal with size-1 index access,
    //for all arrays, provides expected access of array indecies even though its circular
        T& operator[](int i){ // 
            int num1=0;
            if(i < 0 || i > size-1){
                cout << "Index is out of bounds. "<< i <<" Returning random value. "<< endl;
                return randVal; // 
            }
            else{
                if(initilized){//if this is the initilized constructor array
                    num1 = atIndexArray[HiddenIndex(i)]; //copies the array index, at copy arrays index
                    if(num1<0 || num1 >= copyIndex || !(copyIndexArray[num1] == HiddenIndex(i))){ //if uninit cause val is out of bounds
                        //cout<<"made it this far2.."<<endl;
                        myArray[HiddenIndex(i)] = referenceVal;
                        copyIndexArray[copyIndex] = HiddenIndex(i); //should put main array index at start of copy index
                        atIndexArray[HiddenIndex(i)]=copyIndex; //at main array index in atIndex is the location this same val is stored above
                        copyIndex++; //increment copy index //?
                    }
                    
                }
                return myArray[HiddenIndex(i)];
            }
        } 


        void AddEnd(T endVal){ // !!

            if(size == capacity){grow();}

            myArray[(head + size) % capacity] = endVal;
            //size-1 in a typical array, but must acc for the actual location of the head
            size++;
            sorted = false;//add a check?
        } //increase size of array by 1, stores value at end of the array, double capcity when new element doesnt fit,
        // elem access by usser at array[size-1] end of array
        

    // store val at front  new ele array[0] front of array
        void AddFront(T frontVal){ // !

            if(size == capacity){
                grow();
                AddFront(frontVal);
            }
            else{
                head = ((head + capacity -1 ) % capacity);
                myArray[head] = frontVal;
            //[0] in a typical array, and is essentially [head -1] 
            //but must acc for the actual location of the head without going to nedgative values 
                size++;
                sorted=false;
            }    
        }

        
    // reduces size of array by 1, shrink when under 25%, capc never go below 4
        void DelEnd(){
            size--;
            sorted = false;
            if((double)size/(double)capacity <= .25){
                shrink();
            }
        }

    // reduces size of array by 1at beginning, shrink under 25%, capacity under 4 never    
        void DelFront(){
            head = (head+1) % capacity;
            size--;
            sorted=false;
            if((double)size/(double)capacity <= .25){
                shrink();
            }
        }
        
    //returns size of array
        int Length(){return size;}   

    //returns capacity of array
        int Capacity(){return capacity;}   

    //returns index of head of array, not the value there
        int GetHead(){return head;} // Works

    //Prints array values
        void printMyArray(){   
             for(int i=0; i<size; i++){
                cout<< myArray[HiddenIndex(i)] <<" ";
            }
            cout<< endl;
        }
                   
    //quickselectalgorithim on unsorted array, return the kth smallest el- choose random part ele
        T Select(int k){
            int n = sizeof(myArray) / sizeof(myArray[0]);
            return kthSmallest(myArray, 0, size-1, k);
        }

    //Sorts with an nlgn algorithim, I chose heap sort becaus it's similar to the binary trees we went over
        void Sort(){
            HeapSort(myArray,Length());
            sorted = true;
        } //Sorts with an O(nlgn) sortiing alg HEAP SORT BABY

    // unsorted, linearsearch for item value,returns index of the item if found
        int Search(T value){   
            for(int i=0; i<Length(); i++){
                if(myArray[HiddenIndex(i)] == value){
                    return i;
                }
            }
            return -1;
        } 
    
    // aray is sorted , perform binary search of thearray looking for item e, or return a neg number
        int BinSearch(T val){ //works like a charm
            if(sorted){
                return BinarySearchAlg(val);
            }
            else{
                Sort();
                return BinarySearchAlg(val);
            }    
        }  
    
};
