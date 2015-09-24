#include <iostream>
#include <inttypes.h>
#include <list>
#include <algorithm>
#include <cassert>

#ifdef TESTING
#include "gtest/gtest.h"
#endif

uint32_t num_attempts3 (uint32_t n, uint32_t m)
{
    if (n >= m) return n - m;
    std::list<uint32_t> steps = {n};

    uint32_t count=0;
    std::list<uint32_t>::iterator x = steps.begin();
    std::list<uint32_t>::iterator y = steps.end();
    bool solution_reached = false;
    uint32_t last = n;
    while (!solution_reached)
    {
        std::list<uint32_t> tmp_steps;
        for (std::list<uint32_t>::iterator it=x; it!=y; ++it)
        {
            uint32_t k = *it;
            if (k>1) {
                if ((k-1)==m) {
                    solution_reached = true;
                }
                if (std::find(steps.begin(), steps.end(), k-1) == steps.end()) {
                    tmp_steps.emplace_back(k-1);
                    //                    last = k-1;
                }
            }
            if (k<2*m) {
                if ((k*2)==m) {
                    solution_reached = true;
                }
                if (std::find(steps.begin(), steps.end(), k*2) == steps.end()) {
                    tmp_steps.emplace_back(k*2);
                    //                    last = k*2;
                }
            }
        }
        ++count;
        steps.splice(steps.end(), tmp_steps);

        x = std::find(steps.begin(), steps.end(), last);
        x++;
        last = steps.back();
        y=steps.end();
    }
    assert(solution_reached);
    return count;
}

uint32_t num_attempts2 (uint32_t n, uint32_t m)
{

  // std::cout << "n=" << n << " m=" << m << std::endl;
  if (n >= m) return n - m;

  return  1 + (m&1) + num_attempts2(n, (m+(m&1)) >> 1);

}

uint32_t num_attempts (uint32_t n, uint32_t m)
{
    if (n >= m) return n - m;
    if (2*n==m+1) return 2;
    if (2*n==m) return 1;
    uint32_t count=0;
    uint32_t new_m = m;
    if (m&0x1) {
        new_m=m+1;
        count++;
    }
    while (new_m>=n) {

        //      std::cout << "--- " << n << "," << new_m << std::endl;
        if (new_m == n) {
            return count;
        }
        if (new_m&0x1) {
            new_m = (new_m+1)/2;
            count++;
        } else {
            new_m/=2;
        }
        ++count;
    }
    return count + n - new_m;
}

uint32_t do_attemps(uint32_t n, uint32_t m) {
    uint32_t k = num_attempts3(n, m);
    return k;
}

#ifndef TESTING
int main () {
#ifdef TEST
    std::cout << "2 1 " << do_attemps(2, 1) << std::endl;
    std::cout << "1 2 " << do_attemps(1, 2) << std::endl;
    std::cout << "1 3 " << do_attemps(1, 3) << std::endl;
    std::cout << "3 1 " << do_attemps(3, 1) << std::endl;
    std::cout << "4 6 " << do_attemps(4, 6) << std::endl;
    std::cout << "2 7 " << do_attemps(2, 7) << std::endl;
    std::cout << "2 10 " << do_attemps(2, 10) << std::endl;
    std::cout << "10 1 " << do_attemps(10, 1) << std::endl;
    std::cout << "2 9 " << do_attemps(2, 9) << std::endl;
    std::cout << "2 17 " << do_attemps(2, 17) << std::endl;
    std::cout << "3 17 " << do_attemps(3, 17) << std::endl;
    std::cout << "666 6666 " << do_attemps(666, 6666) << std::endl;
#else
    uint32_t n, m;
    std::cin >> n >> m;
    std::cout << do_attemps(n, m) << std::endl;
#endif
}
#endif

#ifdef TESTING
TEST(ButtonsFixture, eval_1) {
  uint32_t n = num_attempts3(2,1);
  ASSERT_EQ(n, 1);
}

TEST(ButtonsFixture, eval_2) {
  uint32_t n = num_attempts3(666, 6666);
  ASSERT_EQ(n, 255);
}

TEST(ButtonsFixture, eval_3) {
  uint32_t n = num_attempts3(10,1);
  ASSERT_EQ(n, 9);
}

TEST(ButtonsFixture, eval_4) {
  uint32_t n = num_attempts3(4,6);
  ASSERT_EQ(n, 2);
}

#endif
