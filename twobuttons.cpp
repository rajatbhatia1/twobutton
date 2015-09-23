#include <iostream>
#include <inttypes.h>
#include <math.h>
#include <set>

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
    attempted.clear();
    uint32_t k = num_attempts(n, m);
    return k;
}

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

