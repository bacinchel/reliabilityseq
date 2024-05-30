#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
using namespace std;
void bubbleSort(vector <long double>& arr, vector <vector <int> >& arr2)
{
   int i, j, pass =0;
   float temp;
   vector <int> temp2;
   for(i = 0; i<arr.size(); i++) 
   {
        for(j = i+1; j< arr.size(); j++)
        {
            if(arr[j] <= arr[i]) 
            {
                temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
                temp2 = arr2[i];
                arr2[i] = arr2[j];
                arr2[j] = temp2;
            }
        }
        pass++;
    }    
}

// Merge two subarrays L and M into arr
void merge(vector <long double>& arr, vector <vector <int> >& arr2, int p, int q, int r) {
  
  // Create L ← A[p..q] and M ← A[q+1..r]
  int n1 = q - p + 1;
  int n2 = r - q;

  double L[n1], M[n2];
  vector<vector<int> > L1( n1 , vector<int> (arr2[0].size(), 0)); 
  vector<vector<int> > M1( n2 , vector<int> (arr2[0].size(), 0)); 
  for (int i = 0; i < n1; i++)
    {L[i] = arr[p + i];
    L1[i]= arr2[p+i];}
  for (int j = 0; j < n2; j++)
    {M[j] = arr[q + 1 + j];
    M1[j] = arr2[q+1+j];}

  // Maintain current index of sub-arrays and main array
  int i, j, k;
  i = 0;
  j = 0;
  k = p;

  // Until we reach either end of either L or M, pick larger among
  // elements L and M and place them in the correct position at A[p..r]
  while (i < n1 && j < n2) {
    if (L[i] <= M[j]) {
      arr[k] = L[i];
      arr2[k] = L1[i];
      i++;
    } else {
      arr[k] = M[j];
      arr2[k] = M1[j];
      j++;
    }
    k++;
  }

  // When we run out of elements in either L or M,
  // pick up the remaining elements and put in A[p..r]
  while (i < n1) {
    arr[k] = L[i];
    arr2[k] = L1[i];
    i++;
    k++;
  }

  while (j < n2) {
    arr[k] = M[j];
    arr2[k] = M1[j];
    j++;
    k++;
  }
}

// Divide the array into two subarrays, sort them and merge them
void mergeSort(vector <long double>& arr, vector <vector <int> >& arr2, int l, int r) {
  if (l < r) {
    // m is the point where the array is divided into two subarrays
    int m = l + (r - l) / 2;

    mergeSort(arr, arr2, l, m);
    mergeSort(arr, arr2, m + 1, r);

    // Merge the sorted subarrays
    merge(arr, arr2, l, m, r);
  }
}

//Print for float vectors
void print1Df(vector <long double>& arr)
{
    for (int i=0; i<arr.size(); i++)
    {
        cout << setprecision(20) << arr[i] << " ";
        cout << endl;
    }
}

//Print for integer vectors
void print1Di(vector <int>& arr)
{
    for (int i=0; i<arr.size(); i++)
    {
        cout << arr[i] << " ";
        cout << endl;
    }
}

//Print for 2-D integer vectors
void print2D(vector<vector <int> >& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[i].size(); j++)
        {
            cout  << arr[i][j] << " ";
            //cout<< endl;
        }
        cout << endl;
    }
}

//Write an integer vector to a file
void write(vector<int> v){
	ofstream file;
	file.open("reliability_seq_BSC_p=0.2_2^11.txt");
	for(int i=0;i<v.size();++i){
		file<<v[i]<<",";
	}
	file.close();
}

int main()
{
    //Initialization
    vector <long double> A;
    vector<vector <int> > B;
    A.push_back(0.9329);
    A.push_back(0.64);
    int size = 1;
    vector<int> B1;
    B1.push_back(1);
    B.push_back(B1);
    vector<int> B2;
    B2.push_back(0);
    B.push_back(B2);
    /*for (int i = 0; i < B.size(); i++)
    {
        for (int j = 0; j < B[i].size(); j++)
        {
            cout << B[i][j] << " ";
            cout<< endl;
        }
    }*/
    
    /*for (int i=0; i<A.size(); i++)
    {
        cout << A[i] << " ";
        cout << endl;
    }*/
    
    //Initialize degree and find total number of polarized channels needed
    int deg = 11;
    int total = 0;
    for(int i=2; i<=deg; i++)
    {
        total = total + pow(2,i);
    }

    //Concatenated loops for getting vector and vectors of vector for Bhhatacharyya parameters and channel markings
    int k =2;
    for (int i =0; i<total/2; i++)
    {
        for (int j =0; j<2; j++)
        {
            if (j == 0)
            {
                vector <int> v1;
                v1 = B[k-2];
                v1.push_back(1);
                /*cout << "v1 =";
                for (int z=0; z< v1.size(); z++)
                {
                    cout  << v1[z] << " ";
                    //cout<< endl;
                }
                cout << endl;*/
                B.push_back(v1);
                setprecision(20);
                A.push_back(A[k-2]* sqrt(2-pow(A[k-2],2)));
                /*for (int l = 0; l < B.size(); l++)
                {
                    for (int m = 0; m < B[l].size(); m++)
                    {
                        cout << B[l][m] << " ";
                        //cout<< endl;
                    }
                    cout<< endl;
                }*/
            }
            /*cout << "k =" << k;
            cout << endl;*/
            
            else if (j ==1)
            {
                vector <int> v1;
                v1 =  B[k-2];
                //cout << "k =" << k;
                v1.push_back(0);
                setprecision(20);
                A.push_back(pow(A[k-2],2));
                /*cout << "v1 =";
                for (int z=0; z< v1.size(); z++)
                {
                    cout  << v1[z] << " ";
                    //cout<< endl;
                }
                cout << endl;*/
                B.push_back(v1);
            } 
            
        }
        k++ ;
        
    }
    /*for (int i = 0; i < B.size(); i++)
    {
        for (int j = 0; j < B[i].size(); j++)
        {
            cout  << B[i][j] << " ";
            //cout<< endl;
        }
        cout << endl;
    }
    for (int i=0; i<A.size(); i++)
    {
        cout << "A =";
        cout << A[i] << " ";
        cout << endl;
    }*/
    
    //Take out relevant subset of A & B (based on degree) and store it in C & D
    vector <long double> C;
    vector<vector <int> > D;
    for (int i =0; i< B.size();i++)
    {
        if (B[i].size() == deg)
        {
            vector<int> temp;
            temp = B[i];
            D.push_back(temp);
            C.push_back(A[i]);
        }
    }
    /*for (int i = 0; i < D.size(); i++)
    {
        for (int j = 0; j < D[i].size(); j++)
        {
            cout  << D[i][j] << " ";
            //cout<< endl;
        }
        cout << endl;
    }*/
    for (int i=0; i<C.size(); i++)
    {
        cout<< "C =";
        cout << C[i] << " ";
        cout << endl;
    }
    
    //sorting C and D in increasing order
    //bubbleSort(C,D) ;
    mergeSort(C,D,0,C.size()-1);


    /*for (int i=0; i<C.size(); i++)
    {
        cout << C[i] << " ";
        cout << endl;
    }*/
    print1Df(C);
    print2D(D);
    //Test for number of good channels after polarization
    int count =0;
    int count1 =0;
    for (int i=0; i<C.size(); i++)
    {
        if (C[i]<=0.2)
        {
            count++;
        }
        else{
            count1++;
        }
    }
    /*for (int i = 0; i < D.size(); i++)
    {
        for (int j = 0; j < D[i].size(); j++)
        {
            cout  << D[i][j] << " ";
            //cout<< endl;
        }
        cout << endl;
    }*/

    //Calculating reliability sequence
    vector <int> reliability;
    for (int i = 0; i < D.size(); i++)
    {
        int sum =0;
        for (int j=deg-1; j>=0; j--)
        {
            sum =sum + D[i][j] * pow(2,deg-j-1);
        }
        reliability.push_back(sum);
    }

    for (int i=0; i<reliability.size();i++)
    {
        reliability[i] = pow(2,deg)-1-reliability[i];
    }

    reverse(reliability.begin(),reliability.end());
    print1Di(reliability);
    write(reliability);
    cout<<"Number of good channels ="<<count<<endl;
    cout<<"Number of not good channels ="<<count1<<endl;
}