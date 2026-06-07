# Mathematical Expression Engine (C++)

A high-performance, modular mathematical expression evaluation engine built from scratch in Modern C++. This system avoids high-level abstractions and external parsing libraries, focusing instead on formal language theory, compiler design principles, and strict memory efficiency.

## 🚀 Architectural Overview

The engine processes mathematical inputs through a structured compilation pipeline:
1. **Lexical Analysis (Tokenizer):** Converts raw string expressions into a deterministic stream of strongly-typed tokens.
2. **Syntactic Analysis (Parser):** Implements a formal **Context-Free Grammar (CFG)** using a top-down, predictive **Recursive-Descent Parser**.
3. **Abstract Syntax Tree (AST):** Builds a hierarchical binary tree representing operator precedence and execution flow.
4. **Runtime Evaluation:** Traverses the AST recursively to compute floating-point evaluations safely.

---

## 📐 Grammar Specification (CFG)

To cleanly handle operator precedence (BODMAS/PEMDAS) and arbitrary nested parentheses without state conflicts, the parser strictly enforces the following Context-Free Grammar:

$$
\begin{aligned}
\text{Expression} &\rightarrow \text{Term} \ ((\text{`+`} \mid \text{`-`}) \ \text{Term})^* \\
\text{Term}       &\rightarrow \text{Power} \ ((\text{`*`} \mid \text{`/`}) \ \text{Power})^* \\
\text{Power}      &\rightarrow \text{Factor} \ (\text{`^`} \ \text{Factor})^* \\
\text{Factor}     &\rightarrow \text{LiteralNumber} \mid \text{`(`} \ \text{Expression} \ \text{`)`}
\end{aligned}
$$

Each non-terminal production rule maps directly to a mutually recursive C++ function (`parse_expression()`, `parse_term()`, etc.), allowing operator binding strengths to be resolved naturally by the call stack.

---

## ✨ Features Implemented

* **Mathematical Rigor:** Full support for multi-digit floating-point arithmetic, explicit parenthesized sub-expressions, and right-associative exponentiation (`^`).
* **Modern C++ Memory Safety:** The AST lifecycle is built completely around RAII principles. Nodes are owned and managed via **`std::unique_ptr`**, ensuring zero memory leaks and deterministic resource cleanup.
* **Granular Error Detection:** Robust exception architecture that catches and reports:
  * *Lexical Errors:* Invalid or unrecognized characters.
  * *Syntax Errors:* Mismatched parentheses or malformed expressions (e.g., `5 + * 3`).
  * *Runtime Exceptions:* Structural evaluation issues.

---

## 🔮 Future Roadmap

The engine is actively evolving into a programmable Domain-Specific Language (DSL) infrastructure. Future development phases include:

- [x] **Phase 1:** Core Lexer, Recursive-Descent Parser, and AST Engine.
- [x] **Phase 2:** Floating-point numbers, Exponentiation, and Grammar Validation.
- [ ] **Phase 3:** **Variable State Management** — Introducing a dynamic Symbol Table to parse and store states like `x = 10` and `y = x + 5`.
- [ ] **Phase 4:** **Unary Operators & Functions** — Implementing prefix signs (`-5`) and built-in math invocations (`sqrt(x)`, `max(a, b)`).
- [ ] **Phase 5:** **Interactive REPL** — Creating a terminal-based Read-Eval-Print Loop featuring automated error recovery to prevent syntax anomalies from crashing the environment.

---

## 🛠️ Building & Running

To compile the engine using a modern C++ compiler (C++17 or later required):

```bash
# Compile using GCC
g++ -std=c++17 -O3 main.cpp -o expression_engine

# Run the binary
./expression_engine
