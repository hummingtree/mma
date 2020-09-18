#include <stdio.h>      /* printf, scanf, puts, NULL */
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <chrono>

using namespace std;
using namespace std::chrono;

constexpr int M = 64;
constexpr int K = 64;
constexpr int N = 64;

//for M*N matrix
int index(int i, int j, int N) {
  return i*N+j;
}

//A[M][K]*B[K][N]
void mma(double *A, double *B, double *C, int M, int K, int N) {
  // Implement MMA here.  
  for(int i=0; i<M; i++) {
    for(int k=0; k<K; k++) {
      for(int j=0; j<N; j++) {
        C[index(i,j,N)] += A[index(i,k,K)]*B[index(k,j,N)];
      }
    }
  }
}

void init_matrix(double *A, int size, bool useRandom = true) {
  for(int i=0; i<size; i++) {
    if(useRandom == true) {
      /* generate secret number between 1 and 10: */
      A[i] = rand()%10+1;
    } else 0.0;
  }
}

void print_matrix(double *A, int M, int N, string info) {
  cout << info << endl;
  for(int i=0; i<M*N; i++) {
    cout << A[i] << '\t';
    if((i+1)%N==0) cout << endl;
  }
}


int main() {

  /* initialize random seed: */
  srand(time(NULL));
/*
  double A[M*K];
  double B[K*N];
  double C[M*N];

  // A[0][0] = 1.0;
  // ...
  //initiate matrices
  init_matrix(A, M*K);
  init_matrix(B, K*N);
  
  print_matrix(A, M, K, "Matrix A:");
  print_matrix(B, K, N, "Matrix B:");
  
  high_resolution_clock::time_point t1 = high_resolution_clock::now();

  mma(A, B, C, M, K, N);

  high_resolution_clock::time_point t2 = high_resolution_clock::now();
  
  duration<double> timer = duration_cast<duration<double>>(t2-t1);

  cout << "Time for mma: " << timer.count() << "s." << endl;

  print_matrix(C, M, N, "A*B = ");
*/

  cout << "#   M" << "     K" << "     N" << "  time" << " floaps" << endl;
  int size = 64;
  for(int i=0; i<7; i++) {
    double *A = new double[size*size];
    double *B = new double[size*size];
    double *C = new double[size*size];
    init_matrix(A, size*size);
    init_matrix(B, size*size);
    init_matrix(C, size*size, false);
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    mma(A, B, C, size, size, size);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> timer = duration_cast<duration<double>>(t2-t1);
    double flops = 2.0*size*size*size/timer.count();
    printf("%5d %5d %5d %.3f %.3f\n", size, size, size, timer.count(), flops);
    // cout << size << '\t' << size << '\t' << size << '\t' << timer.count() << endl;
    size *= 2;
    delete []A;
    delete []B;
    delete []C;
  }

  cout << endl;

  size = 64;
  int size0 = 128;
  for(int i=0; i<10; i++) {
    double *A = new double[size0*size];
    double *B = new double[size*size0];
    double *C = new double[size0*size0];
    init_matrix(A, size0*size);
    init_matrix(B, size*size0);
    init_matrix(C, size0*size0, false);
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    mma(A, B, C, size0, size, size0);
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> timer = duration_cast<duration<double>>(t2-t1);
    double flops = 2.0*size0*size0*size/timer.count();
    printf("%5d %5d %5d %.3f %.3f\n", size0, size, size0, timer.count(), flops);
    //cout << size0 << '\t' << size << '\t' << size0 << '\t' << timer.count() << endl;
    size *= 2;
    delete []A;
    delete []B;
    delete []C;
  }
}
