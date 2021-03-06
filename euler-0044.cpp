// ////////////////////////////////////////////////////////
// # Title
// Pentagon numbers
//
// # URL
// https://projecteuler.net/problem=44
// http://euler.stephan-brumme.com/44/
//
// # Problem
// Pentagonal numbers are generated by the formula, `P_n=n(3n-1)/2`. The first ten pentagonal numbers are:
// 1, 5, 12, 22, 35, 51, 70, 92, 117, 145, ...
//
// It can be seen that `P_4 + P_7 = 22 + 70 = 92 = P_8`. However, their difference, `70 - 22 = 48`, is not pentagonal.
//
// Find the pair of pentagonal numbers, `P_j` and `P_k`, for which their sum and difference are pentagonal and `D = |P_k - P_j|` is minimised; what is the value of `D`?
//
// # Solved by
// Stephan Brumme
// February 2017
//
// # Algorithm
// The function ''isPentagonal(x)'' plays a core role is my solution:
// under the assumption that `x` is pentagonal, that means `x  = P(n)`:
// `P(n)   = n (3n - 1) / 2`     ==> pentagonal formula from problem statement
// `P(n)   = frac{3}{2} n^2 - frac{n}{2}`
// `2 P(n) = 3n^2 - n`
// `     0 = 3n^2 - n - 2P(n)`
//
// Solving this quadratic equation (coefficients `a=3`, `b=-1`, `c=-2P(n)`):
// `n_{1,2} = dfrac{-b \pm sqrt{b^2 - 4ac}}{2a}`
//
// `n_{1,2} = dfrac{1 \pm sqrt{1 + 24P(n)}}{6}`
//
// `n` must be a positive integer, therefore the only possible solution is
// `n = dfrac{1 + sqrt{1 + 24P(n)}}{6}`
//
// `  = dfrac{1 + sqrt{1 + 24x}}{6}`
//
// When generating pentagonal numbers, my code checks `P(n)-P(n-d)` and `P(n)+P(n-d)` for all `d < n` whether both are pentagonal, too.
//
// # Hackerrank
// The Hackerrank problem is a bit easier because the distance is predefined by the user.

#include <iostream>
#include <cmath>

bool isPentagonal(unsigned long long x)
{
  // see explanation above
  unsigned long long n = (1 + sqrt(24*x + 1)) / 6;

  // if x was indeed a pentagonal number then our assumption P(n) = x must be true
  auto p_n = n * (3 * n - 1) / 2;
  return p_n == x;
}

int main()
{
//#define ORIGINAL
#ifdef ORIGINAL

  const unsigned int HugeNumber = 999999999;
  unsigned int best = HugeNumber;
  unsigned int n    = 2; // start with P(2)
  unsigned int last = 1; // P(1)

  while (best == HugeNumber)
  {
    // next pentagonal number
    auto p_n  = n * (3 * n - 1) / 2;
    // difference to closest pentagonal number larger than our best result ?
    if (p_n - last > best)
      break;

    // check all pairs P(n) and P(n - distance) where 1 <= distance < n
    for (unsigned int distance = 1; distance < n; distance++)
    {
      // compute P(n - distance) pentagonal number
      auto x   = n - distance;
      auto p_x = x * (3 * x - 1) / 2;

      // their sum and difference
      auto sum        = p_n + p_x;
      auto difference = p_n - p_x;

      // too far away ?
      if (difference > best)
        break;

      // yes, found something
      if (isPentagonal(sum) && isPentagonal(difference))
        best = difference;
    }

    // check next pentagonal number
    last = p_n;
    n++;
  }
  std::cout << best << std::endl;

#else

  unsigned int maxIndex;
  unsigned int distance;
  std::cin >> maxIndex >> distance;

  // iterate over all pairs at a given distance
  for (unsigned long long n = distance + 1; n <= maxIndex; n++)
  {
    auto p_n = n * (3 * n - 1) / 2;

    auto x   = n - distance;
    auto p_x = x * (3 * x - 1) / 2;

    // check sum and difference
    auto sum        = p_n + p_x;
    auto difference = p_n - p_x;

    // yes, found something
    if (isPentagonal(sum) || isPentagonal(difference))
      std::cout << p_n << std::endl;
  }
#endif

  return 0;
}
