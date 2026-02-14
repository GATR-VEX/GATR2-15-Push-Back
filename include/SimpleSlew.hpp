#include <cmath>


class SimpleSlew{
    private:
    int currentValue = 0;

    public:
    int slewLimit= 5;
    SimpleSlew(int _limiter): slewLimit(_limiter) {}

    inline void Set(int newValue){
        // one directional
        if(abs(newValue)>abs(currentValue)){
            // Limits it if the error is greater than slew
            if(abs(newValue-currentValue) > slewLimit) currentValue = currentValue+ slewLimit;
            else currentValue = newValue;
        }
        else currentValue = newValue;
    }
    inline int Get(){
        return currentValue;
    }
};