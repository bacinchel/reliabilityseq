#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>
#include<fstream>
#include <iomanip>

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

void print1Df(vector <long double>& arr)
{
    for (int i=0; i<arr.size(); i++)
    {
        cout << setprecision(20) << arr[i] << " ";
        cout << endl;
    }
}

void print1Di(vector <int>& arr)
{
    for (int i=0; i<arr.size(); i++)
    {
        cout << arr[i] << " ";
        cout << endl;
    }
}

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
void write(vector<int> v){
	ofstream file;
	file.open("reliability_seq_BEC.txt");
	for(int i=0;i<v.size();++i){
		file<<v[i]<<",";
	}
	file.close();
}

void write_float(vector<float> v){
	ofstream file;
	file.open("percent_match.txt");
	for(int i=0;i<v.size();++i){
		file<<v[i]<<" "<<endl;
	}
	file.close();
}

void write_print(vector<double> v,vector<double>v1){
	ofstream file;
	file.open("print.txt");
	for(int i=0;i<v.size();++i){
		file<<v[i]<<" "<<v1[i]<<endl;
	}
	file.close();
}


int main()
{
    
    vector<float>percent;
    for (int deg=10;deg<=18;deg++)
    {
    int match=0;
    vector <long double> A;
    vector <long double>A0;
    vector<vector <int> > B;
    vector<vector <int> > B0;
    A.push_back(0.75);
    A.push_back(0.25);
    A0.push_back(0.661);
    A0.push_back(0.25);
    int size = 1;
    vector<int> B1;
    B1.push_back(1);
    B.push_back(B1);
    B0.push_back(B1);
    vector<int> B2;
    B2.push_back(0);
    B.push_back(B2);
    B0.push_back(B2);
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
    //int deg = 10;
    int total = 0;
    for(int i=0; i<=deg; i++)
    {
        total = total + pow(2,i);
    }
    int k =2;
    for (int i =0; i<total/2; i++)
    {
        for (int j =0; j<2; j++)
        {
            if (j == 0)
            {
                vector <int> v1;
                vector <int> v2;
                v1 = B[k-2];
                v2 = B0[k-2];
                v1.push_back(1);
                v2.push_back(1);
                /*cout << "v1 =";
                for (int z=0; z< v1.size(); z++)
                {
                    cout  << v1[z] << " ";
                    //cout<< endl;
                }
                cout << endl;*/
                B.push_back(v1);
                B0.push_back(v2);
                setprecision(20);
                A.push_back(2*A[k-2]- pow(A[k-2],2));
                A0.push_back(A[k-2]* sqrt(2-pow(A[k-2],2)));
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
                vector <int> v2;
                v1 =  B[k-2];
                v2 = B0[k-2];
                //cout << "k =" << k;
                v1.push_back(0);
                v2.push_back(0);
                setprecision(20);
                A.push_back(pow(A[k-2],2));
                A0.push_back(pow(A0[k-2],2));
                /*cout << "v1 =";
                for (int z=0; z< v1.size(); z++)
                {
                    cout  << v1[z] << " ";
                    //cout<< endl;
                }
                cout << endl;*/
                B.push_back(v1);
                B0.push_back(v2);
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
    }*/
    /*for (int i=0; i<A.size(); i++)
    {
        cout << "A =";
        cout << A[i] << " ";
        cout << endl;
    }*/
    vector <long double> C;
    vector <long double> C0;
    vector<vector <int> > D;
    vector<vector <int> > D0;
    for (int i =0; i< B.size();i++)
    {
        if (B[i].size() == deg)
        {
            vector<int> temp;
            vector<int> temp0;
            temp = B[i];
            D.push_back(temp);
            C.push_back(A[i]);
            temp0 = B0[i];
            D0.push_back(temp0);
            C0.push_back(A0[i]);
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
    /*for (int i=0; i<C.size(); i++)
    {
        cout<< "C =";
        cout << C[i] << " ";
        cout << endl;
    }*/
    //sorting C and D in increasing order
    //bubbleSort(C,D) ;
    //bubbleSort(C0,D0);
    mergeSort(C,D,0,C.size()-1);
    mergeSort(C0,D0,0,C0.size()-1);
    /*for (int i=0; i<C.size(); i++)
    {
        cout << C[i] << " ";
        cout << endl;
    }*/
    //print1Df(C);
    //print2D(D);
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
    vector <int> reliability0;
    for (int i = 0; i < D.size(); i++)
    {
        int sum =0,sum0 =0;
        for (int j=deg-1; j>=0; j--)
        {
            sum =sum + D[i][j] * pow(2,deg-j-1);
            sum0 = sum0 + D0[i][j] * pow(2,deg-j-1);
        }
        reliability.push_back(sum);
        reliability0.push_back(sum0);
    }

    for (int i=0; i<reliability.size();i++)
    {
        reliability[i] = pow(2,deg)-1-reliability[i];
        reliability0[i] = pow(2,deg)-1-reliability0[i];
    }
    reverse(reliability0.begin(),reliability0.end());
    reverse(reliability.begin(),reliability.end());
    vector<int> rainfall;
    
    ifstream inputFile("/Users/snehasisaddy/Documents/Security in Post processing QKD/C++ Implementation_polarcodes/Q_BEC copy.txt");
    // test file open   
    if (inputFile) {        
    int value;
    // read the elements in the file into a vector  
    while ( inputFile >> value ) {
        rainfall.push_back(value);
        //cout << value;
    }
    inputFile.close();
    }
    //print1Di(rainfall);
    //cout<< rainfall.size();
    //print1Di(reliability);
    //write(reliability);
    int mid_index= pow(2,deg)/2;
    
    for (int i=mid_index;i<=reliability.size();i++)
    {
        for (int j=mid_index;j<=reliability0.size();j++)
        {
            if (reliability[i]==reliability0[j])
            {
                match =match+1;
            }
        }
    }
    percent.push_back((match/(mid_index))*100);
    
    }
    write_float(percent);
   /* 
    vector<double>percent;
    vector<double>frozen;
    for (double l=0.5;l<=0.9;l=l+0.0001)
    {
        int match=0;
        int mid_index = l*pow(2,deg);
        for(int i=pow(2,deg)-1;i>=mid_index;i--)
        {
            int temp =0;
            for (int j=pow(2,deg)-1;j>=mid_index;j--)
            {
                if (rainfall[i]==reliability0[j])
                {
                    match=match+1;
                    temp++;
                    break;
                    
                }
                
            }
            if (temp==0)
                {
                    //cout<<i;
                    //cout<<endl;
                }
        }
        
        double percent_match = match/(pow(2,deg)-mid_index) *100;
        percent.push_back(percent_match);
        cout<< percent_match<< endl;
        frozen.push_back(l);
    }
    write_print(frozen,percent);

    //write(percent);
    */

    
}