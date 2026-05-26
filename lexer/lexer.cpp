#include<bits/stdc++.h>
using namespace std;


enum class TokenType{
  Number,
  Plus,
  Minus,
  Multiply,
  Divide,
};

struct Token {
  TokenType type;
  string value;
};

vector<Token> tokenize(string input){
  vector<Token> tokens;

  for(char c : input){
    if(c == ' ') continue;
    if(isdigit(c)){
      Token t ;
      t.type = TokenType :: Number;
      t.value = string(1,c);

      tokens.push_back(t);
    }
    if(c == '+'){
      Token t;
      t.type = TokenType::Plus;
      t.value = string(1,c);

      tokens.push_back(t);
    }
    if(c == '-'){
      Token t;
      t.type = TokenType::Minus;
      t.value = string(1,c);

      tokens.push_back(t);
    }
    if(c == '*'){
      Token t;
      t.type = TokenType::Multiply;
      t.value = string(1,c);

      tokens.push_back(t);
    }
    if(c == '/'){
      Token t;
      t.type = TokenType::Divide;
      t.value = string(1,c);

      tokens.push_back(t);
    }
  }
  return tokens;
}

int main() {
    string expr = "2+3*5";

    vector<Token> tokens = tokenize(expr);

    for(auto token : tokens){
        cout << token.value << endl;
    }
}
