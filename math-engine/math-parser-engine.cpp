#include <bits/stdc++.h>
#include <string>

using namespace std;

enum class TokenType{
	Number,
	Plus,
	Minus,
	Multiply,
	Divide,
	OpenParen,
	CloseParen,
	Exponential,
	Identifier
};

struct Token {
	TokenType type;
	string value;
};

struct TreeNode {
	string data;
	unique_ptr<TreeNode> left;
	unique_ptr<TreeNode> right;
};

int pos = 0;
vector<Token>tokens;

unique_ptr<TreeNode>parserExpressions();
unique_ptr<TreeNode>parserPower();

unique_ptr<TreeNode> parserFactor(){
	if(pos >= tokens.size()){
		throw runtime_error("Syntax Error : unexpected end of expressions");
	}
	
	if(tokens[pos].type == TokenType::Identifier){
		string funcName = tokens[pos].value;
		pos++;

		if(pos >= tokens.size() || tokens[pos].type != TokenType::OpenParen){
			throw runtime_error("Syntax Error: Expected '(' after function name: " + funcName);
		}
		pos++;
		
		unique_ptr<TreeNode> innerExpr = parserExpressions();

		if(pos >= tokens.size() || tokens[pos].type != TokenType::CloseParen){
			throw runtime_error("Syntax Error: Missing closing Parenthesis for function: " + funcName);
		}
		pos++;

		unique_ptr<TreeNode> funcNode = make_unique<TreeNode>();
		funcNode->data = funcName;
		funcNode->left = move(innerExpr);

		return funcNode;
	}




	if(tokens[pos].type == TokenType::OpenParen){
		pos++;

		unique_ptr<TreeNode>root = parserExpressions();

		if(pos >= tokens.size() || tokens[pos].type != TokenType::CloseParen){
			throw runtime_error("Closing parenthesis Missing");
		}

		pos++;

		return root;

	}

	if(tokens[pos].type != TokenType::Number){
		throw runtime_error("Syntax Error: Expected a number at position : " + to_string(pos));
	}
	Token current = tokens[pos];

	unique_ptr<TreeNode> node = make_unique<TreeNode>();

	node->data = current.value;

	pos++;

	return node;

}

unique_ptr<TreeNode>parserPower(){
	if(pos >= tokens.size()){
		throw runtime_error("Syntax Error , unexpected use of expression ");
	}
	unique_ptr<TreeNode>root = parserFactor();
	if(pos < tokens.size() && tokens[pos].type == TokenType :: Exponential){
		Token optokens = tokens[pos];
		pos++;
		
		unique_ptr<TreeNode> newRoot = make_unique<TreeNode>();
		newRoot->data = optokens.value;
		newRoot->left = move(root);
		newRoot->right = parserPower();
		
		root = move(newRoot);
	}
	return root;
}


unique_ptr<TreeNode> parserTerm(){
	if(pos >= tokens.size()){
		throw runtime_error("Syntax Error : unexpected end of expressions");
	}
	unique_ptr<TreeNode> root = parserPower();

	while(pos < tokens.size() && (tokens[pos].type == TokenType :: Multiply || tokens[pos].type == TokenType :: Divide )){
		Token optokens = tokens[pos];
		pos++;

		unique_ptr<TreeNode> newRoot = make_unique<TreeNode>();

		newRoot->data = optokens.value;

		newRoot->left = move(root);
		newRoot->right = parserPower();

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

		newRoot->data = optokens.value;
		newRoot->left = move(root);
		newRoot->right = parserTerm();

		root = move(newRoot);
	}
	return root;
}


vector<Token> tokenize(string input){
	// vector<Token> tokens;

	for(int i = 0 ; i < input.size();){
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
		}
		else if(c == '+'){
			Token t;
			t.type = TokenType::Plus;
			t.value = "+";
			i++;
			tokens.push_back(t);
		}
		else if(c == '-'){
			Token t;
			t.type = TokenType::Minus;
			t.value = "-";
			i++;
			tokens.push_back(t);
		}
		else if(c == '*'){
			Token t;
			t.type = TokenType::Multiply;
			t.value = "*";
			i++;
			tokens.push_back(t);
		}
		else if(c == '/'){
			Token t;
			t.type = TokenType::Divide;
			t.value = "/";
			i++;
			tokens.push_back(t);
		}
		else if(c == '('){
			Token t;
			t.type = TokenType :: OpenParen;
			t.value = "(";
			i++;
			tokens.push_back(t);
		}
		else if(c == ')'){
			Token t;
			t.type = TokenType :: CloseParen;
			t.value = ")";
			i++;
			tokens.push_back(t);
		}
		else if(c == '^'){
			Token t;
			t.value = "^";
			t.type = TokenType :: Exponential;
			i++;
			tokens.push_back(t);
		}
		else if(isalpha(c)){
			string idStr = "";
			while(i < input.size() && isalpha(input[i])){
				i++;
				idStr += input[i];
			}
			Token t;
			t.value = idStr;
			t.type = TokenType :: Identifier;
			tokens.push_back(t);
		}
		else{
			throw runtime_error("Lexical Error:Unknown Character: " + string(1,c));
		}
	}
	return tokens;
}

double evaluate(TreeNode* node){

	if(node == nullptr) return 0;

	if(isdigit(node->data[0])){
		return stod(node->data);
	}

	double leftVal = evaluate(node->left.get());
	double rightVal = evaluate(node->right.get());


	if(node->data == "+") return leftVal + rightVal;
	if(node->data == "-") return leftVal - rightVal;
	if(node->data == "*") return leftVal * rightVal;
	if(node->data == "/"){
		if(rightVal == 0){
			throw runtime_error("Runtime error : Division by zero");
		}
		return leftVal / rightVal;
	}
	if(node->data == "^") return pow(leftVal,rightVal);

	return 0;
}

int main(){
	cout << "==================================================" << endl;
	cout << "       Custom Math Engine Terminal REPL          " << endl;
	cout << "       Type your math or 'exit' to close.         " << endl;
	cout << "==================================================" << endl << endl;
	
	string inputline;
	while(true){
		cout<<"Engine"<<endl;
		getline(cin,inputline);

		if(inputline == "quit" || inputline == "exit"){
			cout<<"Engine offline. Goodbye!"<<endl;
			break;
		}

		if(inputline.empty())continue;

		pos = 0;
		tokens.clear();

		try{
			tokenize(inputline);

			unique_ptr<TreeNode> treeRoot = parserExpressions();

			double finalAnswer = evaluate(treeRoot.get());
			cout<<"The math engine calculated : "<<finalAnswer<<endl;
		} catch(const exception &e){
			cerr<<e.what()<<endl;
		} 
	}
	return 0;
}
