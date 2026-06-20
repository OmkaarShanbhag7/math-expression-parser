#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

enum class TokenType {
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

vector<Token> tokenize(string input) {
	vector<Token> tokens;

	for (int i = 0; i < input.size();) {
		char c = input[i];

		if (c == ' ') {
			i++;
			continue;
		}

		if (isdigit(c)) {
			string numStr = "";
			while (i < input.size() && (isdigit(input[i]) || input[i] == '.')) {
				numStr += input[i];
				i++;
			}

			Token t;
			t.type = TokenType::Number;
			t.value = numStr;
			tokens.push_back(t);
			continue;
		}
		else if (c == '+') {
			Token t;
			t.type = TokenType::Plus;
			t.value = "+";
			tokens.push_back(t);
			i++;
		}
		else if (c == '-') {
			Token t;
			t.type = TokenType::Minus;
			t.value = "-";
			tokens.push_back(t);
			i++;
		}
		else if (c == '*') {
			Token t;
			t.type = TokenType::Multiply;
			t.value = "*";
			tokens.push_back(t);
			i++;
		}
		else if (c == '/') {
			Token t;
			t.type = TokenType::Divide;
			t.value = "/";
			tokens.push_back(t);
			i++;
		}
		else if (c == '(') {
			Token t;
			t.type = TokenType::OpenParen;
			t.value = "(";
			tokens.push_back(t);
			i++;
		}
		else if (c == ')') {
			Token t;
			t.type = TokenType::CloseParen;
			t.value = ")";
			tokens.push_back(t);
			i++;
		}
		else if (c == '^') {
			Token t;
			t.type = TokenType::Exponential;
			t.value = "^";
			tokens.push_back(t);
			i++;
		}
		else if (isalpha(c)) {
			string idStr = "";
			while (i < input.size() && isalpha(input[i])) {
				idStr += input[i];
				i++;
			}

			Token t;
			t.type = TokenType::Identifier;
			t.value = idStr;
			tokens.push_back(t);
		}
		else {
			throw std::logic_error("Invalid expression used.");
		}
	}

	return tokens;
}

int main() {
	string expr = "42.5 + 300 * 5";

	vector<Token> tokens = tokenize(expr);

	for (auto token : tokens) {
		cout << token.value << endl;
	}
}
