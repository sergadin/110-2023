#include <iostream>
#include <vector>
#include <algorithm>
#include <stdexcept>


using namespace std;


class VectorClock{
private:
    vector<int> clock;
    int process_id;

public:
    // constructor
    // make this with using initialization list
    // :
    VectorClock(int N, int k) : process_id(k), clock(N,0){
        if(N <= 0 || k < 0 || k >= N){
            throw invalid_argument("invalid size or process number");
        }
    }

    //copy constructor
    VectorClock(const VectorClock& other) : process_id(other.process_id), clock(other.clock){
    }

    void incrementLocalEvent(){
        clock[process_id]++;
    }

    void receiveEvent(const VectorClock& received, int m){
        if(clock.size() != received.clock.size()){
            throw invalid_argument("Vector size mismatch");
        }
        for(size_t i = 0; i < clock.size(); i++){
            clock[i] = max(clock[i], received.clock[i]);
        }
        clock[process_id]++;
    }

    // compare 2 vectors
    bool isLessThanorEqual(const VectorClock& other) const{

        if(clock.size() != other.clock.size()){
            throw invalid_argument("vector size mismatch");
        }

        bool flag = false;
        for(size_t i =0; i < clock.size(); i++){
            if(clock[i]>other.clock[i]){
                return false;
            }
            if(clock[i] < other.clock[i]){
                flag = true;
            }
        }
        return flag;
    }

    void printClock() const{
        cout << "Process :" << process_id << " {";
        for(size_t i =0; i < clock.size(); i++){
            cout<< clock[i] << " ";
        }
        cout << "}" << endl;
    }
};




int main()
{
    try{
        int n = 4;
        VectorClock p0(n, 0);
        VectorClock p1(n, 1);
        p1.printClock();
        VectorClock p2(n, 2);
        //VectorClock p3(5, 3); - выдаст ошибку mismatch

        p0.incrementLocalEvent();
        p0.printClock();

        p1.incrementLocalEvent();
        p1.printClock();

        cout<< "go1" << endl;
        p1.receiveEvent(p0, 1);
        p1.printClock();

        cout << "go2" << endl;
        p2.receiveEvent(p1, 2);
        p2.printClock();

        cout << "p0 <= p1 :" << p0.isLessThanorEqual(p1) << endl;
        cout << "p1 <= p2 :" << p1.isLessThanorEqual(p2) << endl;
    }catch(const exception& e){
        cerr << "Eror:" << e.what() << endl;
    }

    return 0;
}
