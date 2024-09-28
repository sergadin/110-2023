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
            std::cout << big.max() << "\n";
        }
        else {
            big = temp;
        }
    }
    big = big;
    std::cout << "min = " << big.min() << ", max = " << big.max() << std::endl;
    return 0;
}
