#include <iostream>
#include <Eigen/Dense>

using Eigen::MatrixXd;
 
int main()
{
  Eigen::MatrixXcd m(2,2);
  m(0,0) = std::complex<double>(1, 1);
  m(1,0) = std::complex<double>(0, 1);
  m(0,1) = std::complex<double>(-1, 10.1);
  m(1,1) = m(1,0) + m(0,1);
  std::cout << m << std::endl;
}