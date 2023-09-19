#include "usefullFunctions.hpp"

float fitBetweenMinMax(float value, float min, float max){
    if(value > max){
        value = max;
    }
    if(value < min){
        value = min;
    }
    return value;
}