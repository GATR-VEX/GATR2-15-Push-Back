//Slew Code We Wrote Ourselves
/*
#include <cmath>


class SimpleSlew{
    private:
    double currentValue = 0;

    public:
    double slewLimit= 5.0;
    SimpleSlew(double _limiter): slewLimit(_limiter) {}

    inline void Set(double newValue){
        // one directional
        if(abs(newValue)>abs(currentValue)){
            // Limits it if the error is greater than slew
            if(abs(newValue-currentValue) > slewLimit) currentValue = currentValue + slewLimit * newValue/abs(newValue);
            else currentValue = newValue;
        }
        else currentValue = newValue;
    }
    inline void AddTo(double addition){
        Set(currentValue+addition);
    }
    inline double Get(){
        return currentValue;
    }
};
*/