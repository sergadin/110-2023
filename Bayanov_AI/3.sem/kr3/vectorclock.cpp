
#include <vector>
#include <stdexcept>

class VectorClock
{
private:
	std::vector<int> clock;
	int processId;
public:
	VectorClock() = delete;

	VectorClock(int N, int K) : clock(N, 0) {
		if (N <= 0 || K <= 0 || K > N) {
			throw std::invalid_argument("Invalid arguments for VectorClock constructor");
		}
		processId = K;
	}

	void tick() {
		clock[processId - 1]++;
	}
	void receive(const std::vector<int>& M) {
		if (M.size() != clock.size()) {
			throw std::invalid_argument("Invalid message timestamp");
		}

		tick();
		for (size_t i = 0; i < clock.size(); ++i) {
			clock[i] = std::max(clock[i], M[i]);
		}
	}
	bool operator<(const VectorClock& other) const {
		if (clock.size() != other.clock.size()) {
			throw std::invalid_argument("Cannot compare clocks with different dimensions");
		}

		bool isLessThan = false;
		for (size_t i = 0; i < clock.size(); ++i) {
			if (clock[i] > other.clock[i]) {
				return false;
			}
			if (clock[i] < other.clock[i]) {
				isLessThan = true;
			}
		}
		return isLessThan;
	}
	const std::vector<int>& getTimestamp() const {
		return clock;
	}
};

#include <iostream>
#include <cassert>

void testVectorClock() {
	VectorClock clock1(3, 1);
	VectorClock clock2(3, 2);
	VectorClock clock3(3, 3);

	clock1.tick();
	clock2.tick();
	clock3.tick();

	clock1.receive(clock2.getTimestamp());
	clock2.receive(clock1.getTimestamp());
	clock3.receive(clock1.getTimestamp());

	assert(clock1 < clock2);
	assert(!(clock2 < clock1));
	assert(clock1 < clock3);
	assert(!(clock3 < clock1));
}

int main() {
	testVectorClock();
	std::cout << "Tests passed!" << std::endl;
	return 0;
}
