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



int main(){

  tokenize("3 * 5 + 41 * 12");
  
  unique_ptr<TreeNode> treeRoot = parserExpressions();

  

  return 0;
}