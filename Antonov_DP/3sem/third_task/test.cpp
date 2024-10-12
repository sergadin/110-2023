#include <iostream>
#include "local_clock.h"

int main(){
	local_clock clock(5);
	for (size_t i = 0; i < 5; i++){
		clock.iteration(i);
	}
	return 0;
}
