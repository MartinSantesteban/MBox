#include "CLoxParser.h"
/*
Expr Parser::expression(){
    return equality();
}

Expr Parser::equality(){
    Expr expr = comparison();
    vector<tokenType> types{BANG_EQUAL, EQUAL_EQUAL};
    while(matchTokenTypes(types)){
        Token op = tokens[current - 1];
        Expr right = comparison();
        expr = Binary(&expr, &op, &right);
    }
    return expr;
}


Expr Parser::comparison(){
    string v1 = "placeholder";
    return Literal(v1);
}

Expr Parser::term(){

}

Expr Parser::factor(){

}

Expr Parser::unary(){

}



Expr Parser::primary(){
    return Literal(tokens[current]);
}
*/

bool Parser::matchTokenTypes(vector<tokenType> tts){
    for(tokenType t : tts){
        if(current < tokens.size() && tokens[current].token_type == t){
            current++;
            return true;
        }
    }
    return false;
}


