
#include "Parameter.h"

string Parameter::toString() {
    if(isString){
        return value;//("\"" + value + "\"");
    }
    return value;
}
