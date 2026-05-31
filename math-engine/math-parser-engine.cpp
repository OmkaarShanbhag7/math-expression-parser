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

struct TreeNode {
  char data;
  unique_ptr<TreeNode> left;
  unique_ptr<TreeNode> right;
};

int pos = 0;
vector<Token>tokens;


unique_ptr<TreeNode> parserFactor(){
  if(pos >= tokens.size()){
    throw runtime_error("Syntax Error : unexpected end of expressions");
  }
  if(tokens[pos].type != TokenType::Number){
    throw runtime_error("Syntax Error: Expected a number at position : " + to_string(pos));
  }
  Token current = tokens[pos];

  unique_ptr<TreeNode> node = make_unique<TreeNode>();

  node->data = current.value[0];

  pos++;

  return node;

}

unique_ptr<TreeNode> parserTerm(){
  if(pos >= tokens.size()){
    throw runtime_error("Syntax Error : unexpected end of expressions");
  }
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
  if(pos >= tokens.size()){
    throw runtime_error("Syntax Error : unexpected end of expressions");
  }
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


vector<Token> tokenize(string input){
  // vector<Token> tokens;

  for(char c : input){
    if(c == ' ') continue;

    if(isdigit(c)){
      Token t ;
      t.type = TokenType :: Number;
      t.value = string(1,c);

      tokens.push_back(t);
    }
    else if(c == '+'){
      Token t;
      t.type = TokenType::Plus;
      t.value = string(1,c);

      tokens.push_back(t);
    }
    else if(c == '-'){
      Token t;
      t.type = TokenType::Minus;
      t.value = string(1,c);

      tokens.push_back(t);
    }
    else if(c == '*'){
      Token t;
      t.type = TokenType::Multiply;
      t.value = string(1,c);

      tokens.push_back(t);
    }
    else if(c == '/'){
      Token t;
      t.type = TokenType::Divide;
      t.value = string(1,c);

      tokens.push_back(t);
    }
    else{
      throw runtime_error("Lexical Error:Unknown Character: " + string(1,c));
    }
  }
  return tokens;
}

int evaluate(TreeNode* node){

  if(node == nullptr) return 0;

  if(node->data >= '0' && node->data <= '9'){
    return node->data - '0';
  }

  int leftVal = evaluate(node->left.get());
  int rightVal = evaluate(node->right.get());


  if(node->data == '+') return leftVal + rightVal;
  if(node->data == '-') return leftVal - rightVal;
  if(node->data == '*') return leftVal * rightVal;
  if(node->data == '/') return leftVal / rightVal;

  return 0;
}


int main(){
  try{
  tokenize("3 * 5 + 4 * + 9 + 1 * 3 - 3 * 5 / 9");
  
  unique_ptr<TreeNode> treeRoot = parserExpressions();

  int finalAnswer = evaluate(treeRoot.get());
  cout<<"The math engine calculated : "<<finalAnswer<<endl;
  }catch(const exception &e){
    cerr<<e.what()<<endl;
  }  
  return 0;
}