#include<bits/stdc++.h>
using namespace std;


enum class TokenType{
  Number,
  Plus,
  Minus,
  Multiply,
  Divide,
  openParen,
  closeParen,
};

struct Token {
  TokenType type;
  string value;
};

vector<Token> tokenize(string input){
  vector<Token> tokens;

  for(int i = 0 ; i < input.size() ;){
    char c = input[i];
    if(c == ' '){
      i++;
      continue;
    }
    if(isdigit(c)){
      string numStr = "";
      while(i < input.size() && (isdigit(input[i]) || input[i] == '.')){
        numStr += input[i];
        i++;
      }
      Token t ;
      t.type = TokenType :: Number;
      t.value = numStr;
      tokens.push_back(t);

      continue;
    }
    if(c == '+'){
      Token t;
      t.type = TokenType::Plus;
      t.value = '+';
      tokens.push_back(t);
      i++;
    }
    if(c == '-'){
      Token t;
      t.type = TokenType::Minus;
      t.value = '-';
      i++;
      tokens.push_back(t);

    }
    if(c == '*'){
      Token t;
      t.type = TokenType::Multiply;
      t.value = '*';
      i++;
      tokens.push_back(t);

    }
    if(c == '/'){
      Token t;
      t.type = TokenType::Divide;
      t.value = '/';
      i++;
      tokens.push_back(t);
    }
    if(c == '('){
      Token t;
      t.type = TokenType :: openParen;
      t.value = '(';
      i++;
      tokens.push_back(t);
    }
    if(c == ')'){
      Token t;
      t.type = TokenType :: closeParen;
      t.value = ')';
      i++;
      tokens.push_back(t);
    }
  }
  return tokens;
}

int main() {
    string expr = "42.5 + 300 * 5";

    vector<Token> tokens = tokenize(expr);

    for(auto token : tokens){
        cout << token.value << endl;
    }
}
