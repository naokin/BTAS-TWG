#include <iostream>
#include <algorithm>
using namespace std;

namespace btas { enum CBLAS_TRANSPOSE { CblasNoTrans, CblasTrans, CblasConjTrans }; };

#include <tensor.h>
#include <varray.h>
#include <axpy_impl.h>
#include <gemm_impl.h>
using namespace btas;

int main()
{
   // test 1
   Tensor<double> T(2,2,2); T.fill(0.0);

   T(1,0,1) = -0.5;

   T.at(1,1,0) = 0.5;

   cout << "printing T: size = " << T.size() << " objsize = " << sizeof(T) << endl;
   for(double x : T) cout << x << endl;

   // test 2
   typedef Tensor<float, varray<float>, varray<int>> MyTensor;
   MyTensor::shape_type shape = { 4, 4 };
   MyTensor Q(shape); Q.fill(2.0);

   MyTensor::shape_type index = { 1, 2 };

   Q(index) = -0.5;
   ++index[0];
   Q.at(index) = 0.5;

   cout << "printing Q: size = " << Q.size() << " objsize = " << sizeof(Q) << endl;
   for(double x : Q) cout << x << endl;

   // test 3
   Tensor<double> S(2,2,2); S.fill(1.0);
   axpy(0.5, T, S);

   cout << "printing S: size = " << S.size() << " objsize = " << sizeof(S) << endl;
   for(double x : S) cout << x << endl;

   Tensor<double> U;
   axpy(0.5, S, U);

   cout << "printing U: size = " << U.size() << " objsize = " << sizeof(U) << endl;
   for(double x : U) cout << x << endl;

   // test 4
   Tensor<double> V(0, 0);
   gemm(CblasNoTrans, CblasNoTrans, 1.0, T, S, 1.0, V);

   cout << "printing V: size = " << V.size() << " objsize = " << sizeof(V) << endl;
   for(double x : V) cout << x << endl;

// // test 5
// Tensor<Tensor<double>> A(4,4); A.fill(Tensor<double>(0,0));
// A(0,0) = Tensor<double>(2,2);
// A(1,1) = Tensor<double>(2,2);
// A(2,2) = Tensor<double>(2,2);
// A(3,3) = Tensor<double>(2,2);

// Tensor<Tensor<double>> B(4,4); B.fill(Tensor<double>(0,0));
// B(0,0) = Tensor<double>(2,2);
// B(1,1) = Tensor<double>(2,2);
// B(2,2) = Tensor<double>(2,2);
// B(3,3) = Tensor<double>(2,2);

// Tensor<Tensor<double>> C(0,0);
// gemm(CblasNoTrans, CblasNoTrans, 1.0, A, B, 1.0, C);

   return 0;
}