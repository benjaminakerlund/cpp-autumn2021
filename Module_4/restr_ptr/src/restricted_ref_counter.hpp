#ifndef AALTO_ELEC_CPP_COUNTER_CLASS
#define AALTO_ELEC_CPP_COUNTER_CLASS

// implement a reference counter helper class if you want to
const int maxref = 3;

class RestrictedRefCounter {
public:
    RestrictedRefCounter() : count_(0) {}
    
    bool Increment() {
        if(count_ < maxref) {
            count_++;
            return true;
        }
        return false;
    }
    
    int Decrement() { return --count_; }
    int GetCount() { return count_; }

private:
    int count_;
};



#endif