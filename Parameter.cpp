
#include "Parameter.h"

string Parameter::toString() {
    if(isString){
        return ("\"" + value + "\"");
    }
    return value;
}
