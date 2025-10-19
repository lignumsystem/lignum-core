///\example{lineno} AlgorithmExample.cc
///Test various algorithms from C++ standard library
///To compile (on Mac) type:
///
///    clang++  -DALGORITHM AlgorithmExample.cc -o algorithms
///
#include <algorithm>
#include <functional>
#include <utility>
#include <vector>
#include <iostream>

///Multiplication as std::multiplies
template <class T>
T mult(T x, T y)
{
  std::cout << "mult " << x << " " << y <<std::endl;
  return x * y;
}

///Print two vetors side by side
void print_vectors(const std::vector<double>& v1,const std::vector<double>& v2)
{
  for (unsigned int i=0;i < v1.size();i++){
    std::cout << v1[i] << " " << v2[i] <<std::endl;
  }
  std::cout << std::endl;
}

#ifdef ALGORITHM
int main()
{
  //C++ 17 allows vector initialization
  std::vector<double> v1={1,2,3,4,5,6,7,8,9,10};
  std::vector<double> v2(10,0.0);
  std::vector<double> v3(10,0.0);
  
  //Passing 'x' by reference in the lambda expresssion changes the values in the vector
  for_each(v1.begin(),v1.end(),[](double& x){x=x+1;});
  //Warning: 'bind1st<std::multiplies<double>, int>' is deprecated in C++17, will be removed in C++20
  //std::transform(v1.begin(),v1.end(),v2.begin(),std::bind1st(std::multiplies<double>(),2));
  //'bind' with placeholders is in the C++ standard libary, C++11 and forward
  //The first argument 'placeholders::_1' in 'multiplies' is bound to '2', denoted by the placeholder.
  //The second argument is the vector element
  std::transform(v1.begin(),v1.end(),v2.begin(),std::bind(std::multiplies<double>(),2,std::placeholders::_1));
  //The first argument is bound to the vector element, the second argument is '3'
  std::transform(v2.begin(),v2.end(),v3.begin(),std::bind(std::multiplies<double>(),std::placeholders::_1,3));	    
  print_vectors(v1,v2);
  print_vectors(v2,v3);

  std::vector<double> v4(10,0.0);
  std::vector<double> v5(10,0.0);
  //The first argument in 'mult' is bound to '2', denoted by the std::placeholder.
  //The second argument is the vector element
  std::transform(v1.begin(),v1.end(),v4.begin(),std::bind(mult<double>,2,std::placeholders::_1));
  std::cout << std::endl;
  //The first argument for 'mult' is bound to the vector element denoted by std::placeholder.
  //The second argument is '3'.
  std::transform(v4.begin(),v4.end(),v5.begin(),std::bind(mult<double>,std::placeholders::_1,3));
  std::cout << std::endl; 
  print_vectors(v1,v4);
  print_vectors(v4,v5);

  return EXIT_SUCCESS;
}
#endif
