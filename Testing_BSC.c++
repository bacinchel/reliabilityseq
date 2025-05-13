#include <iostream>
#include <cmath>
#include <vector>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <boost/multiprecision/cpp_dec_float.hpp>

// 사용자 정의 고정밀 부동 소수점 (200자리 정밀도)
using boost::multiprecision::cpp_dec_float_100;
typedef boost::multiprecision::number<boost::multiprecision::backends::cpp_dec_float<100>> high_precision_float;

using namespace std;
int bit_reverse(int x, int deg) {
    int result = 0;
    for (int i = 0; i < deg; i++) {
        if (x & (1 << i)) {
            result |= 1 << (deg - 1 - i);
        }
    }
    return result;
}
// 버블 정렬 함수를 고정밀 타입으로 변경
void bubbleSort(vector<high_precision_float>& arr, vector<vector<int>>& arr2)
{
   int i, j, pass = 0;
   high_precision_float temp;
   vector<int> temp2;
   for(i = 0; i < arr.size(); i++) 
   {
        for(j = i+1; j < arr.size(); j++)
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

// 병합 정렬 함수 수정
void merge(vector<high_precision_float>& arr, vector<vector<int>>& arr2, int p, int q, int r) {
  int n1 = q - p + 1;
  int n2 = r - q;

  vector<high_precision_float> L(n1), M(n2);
  vector<vector<int>> L1(n1), M1(n2);
  
  for (int i = 0; i < n1; i++) {
    L[i] = arr[p + i];
    L1[i] = arr2[p + i];
  }
  for (int j = 0; j < n2; j++) {
    M[j] = arr[q + 1 + j];
    M1[j] = arr2[q + 1 + j];
  }

  int i = 0, j = 0, k = p;

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

void mergeSort(vector<high_precision_float>& arr, vector<vector<int>>& arr2, int l, int r) {
  if (l < r) {
    int m = l + (r - l) / 2;
    mergeSort(arr, arr2, l, m);
    mergeSort(arr, arr2, m + 1, r);
    merge(arr, arr2, l, m, r);
  }
}


// 안정 정렬용 구조체
struct BhattacharyyaWithIndex {
    high_precision_float value;
    int original_index;
    vector<int> bit_pattern;
};

// 비교 함수: 값 오름차순 + 인덱스 오름차순 (tie-break)
bool stable_compare(const BhattacharyyaWithIndex& a, const BhattacharyyaWithIndex& b) {
    if (a.value != b.value)
        return a.value < b.value;
    return a.original_index < b.original_index;
}

// 안정 정렬 함수
void stableSortBhattacharyya(vector<high_precision_float>& C, vector<vector<int>>& D) {
    vector<BhattacharyyaWithIndex> combined;
    for (int i = 0; i < C.size(); i++) {
        combined.push_back({C[i], i, D[i]});
    }

    // 안정 정렬 적용
    std::stable_sort(combined.begin(), combined.end(), stable_compare);

    // 정렬된 값 복사
    for (int i = 0; i < combined.size(); i++) {
        C[i] = combined[i].value;
        D[i] = combined[i].bit_pattern;
    }
}

// 출력 함수 수정
void print1Df(vector<high_precision_float>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << std::setprecision(100) << arr[i] << endl;
    }
}

void print1Di(vector<int>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << endl;
    }
}

void print2D(vector<vector<int>>& arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        for (int j = 0; j < arr[i].size(); j++)
        {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

void write(vector<int> v, int deg) {
    // 파일 이름에 차수를 반영
    string filename = "reliability_seq_BSC_p=0.2_2^" + to_string(deg) + "_high_precision.txt";
    ofstream file;
    file.open(filename);
    for (int i = 0; i < v.size(); ++i) {
        file << v[i] << endl; // 각 값을 줄바꿈하여 출력
    }
    file.close();
}

// 고정밀 제곱근 함수
high_precision_float precise_sqrt(const high_precision_float& x) {
    return sqrt(x);
}

// 고정밀 제곱 함수
high_precision_float precise_pow(const high_precision_float& x, int power) {
    return pow(x, power);
}

int main()
{
    // 고정밀 타입으로 초기화
    vector<high_precision_float> A;
    vector<vector<int>> B;
    
    double p_percent;
    cout << "BSC 채널의 에러율 p 를 입력하세요 (예: 5 for 5%): ";
    cin >> p_percent;
    high_precision_float p = high_precision_float(p_percent) / 100;

    // Bhattacharyya 초기값 계산
    high_precision_float Z0 = 2 * precise_sqrt(p * (1 - p));
    high_precision_float Z_minus = Z0 * precise_sqrt(high_precision_float("2.0") - precise_pow(Z0, 2));
    high_precision_float Z_plus = precise_pow(Z0, 2);


    A.push_back(Z_minus); // Z^-
    A.push_back(Z_plus);  // Z^+
    cout << Z_minus<<endl;
    cout << Z_plus<<endl;

    vector<int> B1 = {1};
    vector<int> B2 = {0};
    B.push_back(B1);
    B.push_back(B2);
    // 사용자로부터 차수 입력 받기
    int deg;
    cout << "차수를 입력하세요 (예: 11): ";
    cin >> deg;

    // 총 채널 수 계산
    int total = 0;
    for(int i = 2; i <= deg; i++)
    {
        total = total + pow(2, i);
    }

    // 채널 극성화 과정
    int k = 2;
    for (int i = 0; i < total/2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            if (j == 0)
            {
                vector<int> v1;
                v1 = B[k-2];
                v1.push_back(1);
                B.push_back(v1);
                
                // 고정밀 계산: A[k-2] * sqrt(2-A[k-2]^2)
                high_precision_float temp = A[k-2];
                high_precision_float temp_squared = precise_pow(temp, 2);
                high_precision_float inner = high_precision_float("2.0") - temp_squared;
                high_precision_float sqrt_inner = precise_sqrt(inner);
                A.push_back(temp * sqrt_inner);
            }
            else if (j == 1)
            {
                vector<int> v1;
                v1 = B[k-2];
                v1.push_back(0);
                
                // 고정밀 계산: A[k-2]^2
                high_precision_float temp = A[k-2];
                A.push_back(precise_pow(temp, 2));
                B.push_back(v1);
            } 
        }
        k++;
    }
    
    // 차수에 맞는 채널 선택
    vector<high_precision_float> C;
    vector<vector<int>> D;
    for (int i = 0; i < B.size(); i++)
    {
        if (B[i].size() == deg)
        {
            vector<int> temp;
            temp = B[i];
            D.push_back(temp);
            C.push_back(A[i]);
        }
    }
    
    // 디버깅용 출력
    cout << "채널 파라미터 값 (정렬 전):" << endl;
    for (int i = 0; i < C.size(); i++)
    {
        cout << "C[" << i << "] = " << std::setprecision(100) << C[i] << endl;
        if (i >= 9) break; // 처음 10개만 출력
    }
    cout << "..." << endl << endl;
    
    // 병합 정렬 사용 (더 효율적)
    stableSortBhattacharyya(C, D);

    cout << "채널 파라미터 값 (정렬 후):" << endl;
    for (int i = 0; i < 10; i++) // 처음 10개만 출력
    {
        cout << "C[" << i << "] = " << std::setprecision(100) << C[i] << endl;
    }
    cout << "..." << endl << endl;
    
    // 좋은 채널 카운트
    int count = 0;
    int count1 = 0;
    high_precision_float threshold("0.2");
    for (int i = 0; i < C.size(); i++)
    {
        if (C[i] <= threshold)
        {
            count++;
        }
        else {
            count1++;
        }
    }

    // 신뢰성 시퀀스 계산
    vector<int> reliability;
    for (int i = 0; i < D.size(); i++)
    {
        int sum = 0;
        for (int j = deg-1; j >= 0; j--)
        {
            sum = sum + D[i][j] * pow(2, deg-j-1);
        }
        reliability.push_back(bit_reverse(sum, deg));
    }

    for (int i = 0; i < reliability.size(); i++)
    {
        reliability[i] = pow(2, deg) - 1 - reliability[i];
    }

    reverse(reliability.begin(), reliability.end());
    
    cout << "신뢰성 시퀀스 (처음 10개):" << endl;
    for (int i = 0; i < 10; i++)
    {
        cout << "reliability[" << i << "] = " << reliability[i] << endl;
    }
    cout << "..." << endl << endl;
    
    // 파일에 저장 (deg 값을 전달)
    write(reliability, deg);
    
    cout << "총 채널 수: " << C.size() << endl;
    cout << "좋은 채널 수 (<=0.2): " << count << endl;
    cout << "나쁜 채널 수 (>0.2): " << count1 << endl;
    
    return 0;
}