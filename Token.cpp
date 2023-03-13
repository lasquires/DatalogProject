#include "Token.h"
#include <utility>

//string Token::toString()  {
//    stringstream out;
//    out << "(" << type << "," << "\"" << value << "\"" << "," << line << ")\n";
//    return out.str();
//}

//}


TokenType Token::getType() const {
    return type;
}

int Token::getLine() const {
    return line;
}

string Token::getValue() const {
    return value;
}

string Token::toString() {
    stringstream out;
    out << "(" << typeName() << "," << "\"" << getValue() << "\"" << "," << getLine() << ")\n";
    return out.str();
}

string Token::typeName() const{
    switch (type) {
        case COMMA: return "COMMA";
        case PERIOD: return "PERIOD";
        case Q_MARK: return "Q_MARK";
        case SEMI_COLON: return "SEMI_COLON";
        case COLON: return "COLON";
        case EQUALS: return "EQUALS";
        case LEFT_PAREN: return "LEFT_PAREN";
        case RIGHT_PAREN: return "RIGHT_PAREN";
        case END_LINE: return "END_LINE";
        case STRING: return "STRING";
        case ID: return "ID";
        case COMMENT: return "COMMENT";
        case COLON_DASH: return "COLON_DASH";
        case _EOF: return "EOF";
        case QUERIES: return "QUERIES";
        case RULES: return "RULES";
        case SCHEMES: return "SCHEMES";
        case FACTS: return "FACTS";
        default: return "UNDEFINED";
    }
}

