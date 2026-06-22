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
	
	bool isNegative = false;
	if(pos < tokens.size() && tokens[pos].type == TokenType :: Minus){
		isNegative = true;
		pos++;
	}
	if(pos >= tokens.size() || tokens[pos].type != TokenType::Number){
		throw runtime_error("Syntax Error: Expected a number at position : " + to_string(pos));
	}
	Token current = tokens[pos];

	unique_ptr<TreeNode> node = make_unique<TreeNode>();

	if(isNegative){
		node->data = '-' + current.value;
	}
	else{
		node->data = current.value;
	}

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
			if(c == '(') i++; else i += 3;
			tokens.push_back(t);
		}
		else if(c == ')'){
			Token t;
			t.type = TokenType :: CloseParen;
			t.value = ")";
			if(c == ')') i++; else i+=3;
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
			while(i < input.size() && isalnum(input[i])){
				idStr += input[i];
				i++;
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

	if(isdigit(node->data[0])|| node->data.size() > 1 && node->data[0] == '-' && isdigit(node->data[1])){
		return stod(node->data);
	}
	
	if(node->data == "sqrt"){
		double val = evaluate(node->left.get());
		if(val < 0) throw runtime_error("Runtime Math Error: Square root of a negative number");
		return sqrt(val);
	}
	if(node->data == "cuberoot") {
		return cbrt(evaluate(node->left.get()));
	}
	if(node->data == "sin") {
		return sin(evaluate(node->left.get())); 
	}
	if(node->data == "cos") {
		return cos(evaluate(node->left.get()));  
	}
	if(node->data == "log"){
		double val = evaluate(node->left.get());
		if(val <= 0) throw runtime_error("Runtime Math Error: Logarithm of non positive Number");
		return log(val);
	}
	if(node->data == "tan") {
		return tan(evaluate(node->left.get()));
	}
	if(node->data == "log10") {
		double val = evaluate(node->left.get());
		if(val <= 0) throw runtime_error("Runtime Math Error: Log10 of non-positive number!");
		return log10(val);
	}
	if(node->data == "abs") {
		return abs(evaluate(node->left.get()));
	}
	if(node->data == "ceil") {
		return ceil(evaluate(node->left.get()));
	}
	if(node->data == "floor") {
		return floor(evaluate(node->left.get()));
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
	cout << "  Industrial Scientific AST Math Shell Emulator   " << endl;
	cout << "  Supported: +, -, *, /, ^, (), sqrt, cuberoot,   " << endl;
	cout << "             sin, cos, tan, log, log10, abs,      " << endl;
	cout << "             ceil, floor                          " << endl;
	cout << "  Type your expression or 'exit' to close.        " << endl;
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
