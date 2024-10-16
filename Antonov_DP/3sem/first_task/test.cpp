#include <iostream>
#include "intset.h"

int main() {
    intset big(0, 100);
    const int max_iterations = 500;

    for (int iter = 0; iter < max_iterations; iter++) {
        intset temp(0, big.right());
        for (int item = temp.left(); item <= temp.right(); item++) {
            if ((item % 7) > (iter % 11)) {
                temp.add(item);
            }
        }
        if (iter > 0) {
            big = big * temp;
        }
        else {
            big = temp;
        }
    }
    big = big;
    std::cout << "min = " << big.min() << ", max = " << big.max() << std::endl;
    intset test(1, 100);
    test.add(1);
    test = test * test;
    std::cout << test.max() << "\n";
    return 0;
}
