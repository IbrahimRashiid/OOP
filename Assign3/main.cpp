
#include<fstream>
#include <iostream>
#include<Math.h>

using namespace std;

class  FloatArray {
protected:
    float* floatArr;
    int floatArrSize;
public:
    int indexCounter;
    FloatArray(int floatArrSize) {
        this->floatArrSize = floatArrSize;
        this->indexCounter = 0;
        floatArr = new float[floatArrSize];     //Allocating a dynamic array for float numbers
    }

     virtual void AddFloat(float number) {       // Adding elements to the array from back to front
        floatArr[ indexCounter ] = number;
        indexCounter++;
    }

    friend ofstream& operator <<(ofstream& os, FloatArray* F_arrObject) {
        for(int i=0 ;i<F_arrObject->indexCounter ;i++){     // showing the modified data into the output file
            os<< F_arrObject->floatArr[i] << '\t';
        }
        os<<endl;
        return os;
    }

    friend ifstream& operator >>(ifstream& IF, FloatArray *F_ArrObject) {    // reading data from the input file
        float number;
        for(int i=0;i<F_ArrObject->floatArrSize;i++){
            IF >> number;
            F_ArrObject->AddFloat(number);                              //passing the number to the object's Add method
        }
        return IF;
    }

     ~FloatArray() {
        delete floatArr;                                      // deallocating the dynamic memory
    }
};

class  SortedArray :public FloatArray {
public:
    SortedArray(int floatArrSize) : FloatArray(floatArrSize) {}

    void AddFloat(float number) {
        if(indexCounter-1>=0&& floatArr[indexCounter-1]>number) {
            floatArr[indexCounter]=number;
            swap(floatArr[indexCounter],floatArr[indexCounter-1]); // Storing the array element temporary
        }
        else {
            floatArr[indexCounter]=number;
        }

        for (int i = 0; i <indexCounter-1; i++) {
            if (floatArr[i] > floatArr[i+1]) {
                swap(floatArr[i],floatArr[i+1]);
            }
        }
        indexCounter++;
    }
};

class FrontArray : public FloatArray {
public:
    FrontArray(int floatArrSize): FloatArray(floatArrSize){}
    void AddFloat(float number) {						  // Adding elements to the array starting from the front
        floatArr[floatArrSize-indexCounter-1] = number;
        indexCounter++;
    }
};

class  PositiveArray:public SortedArray {
public:
    PositiveArray(int floatArrSize) :SortedArray(floatArrSize) {}
    void AddFloat(float number) {										// Adding Positive numbers only to the array
        if (number > 0) {
            SortedArray::AddFloat(number);
        }
    }
};

class NegativeArray :public SortedArray{
public:
    NegativeArray(int floatArrSize) :SortedArray(floatArrSize) {}
    void AddFloat(float number) {									    // Adding negative numbers only to the array
        if (number < 0) {
            SortedArray::AddFloat(number);
        }
    }

};

int main(){
    string ArrayType, inputFileName, outputFileName;
    int ArraySize=0;
    cout<<"Enter the name of the input file : "<<endl;
    cin>>inputFileName;
    cout<<"Enter the name of the output file : "<<endl;
    cin>>outputFileName;
    FloatArray* float_Array[10];
    ifstream inputFile(inputFileName);
    ofstream outputFile(outputFileName);
    for(int i=0;i<10;i++){
        inputFile >> ArrayType ;
        inputFile >> ArraySize;
        if(ArrayType == "Array"){
            float_Array[i] = new FloatArray(ArraySize);
            inputFile >> float_Array[i];
            outputFile << ArraySize << "|\t";
            outputFile << float_Array[i];
        }
        else if(ArrayType == "Sorted"){
            float_Array[i] = new SortedArray(ArraySize);
            inputFile >> float_Array[i];
            outputFile <<  ArraySize << "|\t";
            outputFile << float_Array[i];
        }
        else if(ArrayType=="Positive"){
            float_Array[i]=new PositiveArray(ArraySize);
            inputFile >> float_Array[i];
            outputFile << float_Array[i]->indexCounter<< "|\t";
            outputFile << float_Array[i];
        }
        else if(ArrayType == "Negative"){
            float_Array[i] = new NegativeArray(ArraySize);
            inputFile >> float_Array[i];
            outputFile << float_Array[i]->indexCounter << "|\t";
            outputFile << float_Array[i];
        }
        else if(ArrayType == "Front"){
            float_Array[i] = new FrontArray(ArraySize);
            inputFile >> float_Array[i];
            outputFile << ArraySize << "|\t";
            outputFile << float_Array[i];
        }
    }
    for(int i=0;i<10;i++){
    delete float_Array[i];
    }
    return 0;
}
