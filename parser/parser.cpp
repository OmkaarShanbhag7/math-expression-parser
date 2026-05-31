#include<bits/stdc++.h>
using namespace std;

struct TreeNode {
  char data;
  unique_ptr<TreeNode> left;
  unique_ptr<TreeNode> right;
};

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


int pos = 0;
vector<Token>tokens;

vector<Token> tokenize(string input){

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

unique_ptr<TreeNode> parserExpressions();

unique_ptr<TreeNode> parserFactor(){
  if(pos >= tokens.size()){
    throw runtime_error("Syntax error : unexpected end of expression");
  }
  if(tokens[pos].type == TokenType::openParen){
    pos++;

    unique_ptr<TreeNode> root = parserExpressions();

    if(pos >= tokens.size() || tokens[pos].type != TokenType::closeParen){
      throw runtime_error("Syntax Error: Missing closing parenthesis ");
    }
    pos++;

    return root;
  }
  if(tokens[pos].type != TokenType::Number){
    throw runtime_error("Syntax Error: Expected a number or '(' at position : " + to_string(pos));
  }
 
  Token current = tokens[pos];

  unique_ptr<TreeNode> node = make_unique<TreeNode>();

  node->data = current.value[0];

  pos++;

  return node;

}

unique_ptr<TreeNode> parserTerm(){
  unique_ptr<TreeNode> root = parserFactor();

  while(pos < tokens.size() && (tokens[pos].type == TokenType :: Multiply || tokens[pos].type == TokenType :: Divide )){
    Token optokens = tokens[pos];
    pos++;

    unique_ptr<TreeNode> newRoot = make_unique<TreeNode>();

    newRoot->data = optokens.value[0];

    newRoot->left = move(root);
    newRoot->right = parserFactor();

    root = move(newRoot);
  }
  return root;
}

unique_ptr<TreeNode> parserExpressions(){
  unique_ptr<TreeNode> root =  parserTerm();
  while(pos < tokens.size() && (tokens[pos].type == TokenType::Plus || tokens[pos].type == TokenType::Minus )){

    Token optokens = tokens[pos];
    pos++;

    unique_ptr<TreeNode> newRoot = make_unique<TreeNode>();

    newRoot->data = optokens.value[0];
    newRoot->left = move(root);
    newRoot->right = parserTerm();

    root = move(newRoot);
  }
  return root;
}

int main(){

  tokenize("3 * ( 3 + 5 )");
  
  unique_ptr<TreeNode> treeRoot = parserExpressions();

  

  return 0;
}