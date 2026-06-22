# Scientific AST Math Shell Emulator

An industrial-grade, high-performance command-line scientific interpreter built from scratch in C++. This project demonstrates advanced concepts in language theory and compiler design, utilizing a custom **Lookahead Lexical Scanner**, a **Recursive Descent Operator Precedence Parser**, and a memory-safe **Abstract Syntax Tree (AST)** execution engine to evaluate complex mathematical and scientific expressions in real-time.

---

## 🚀 Key Features

* **Interactive REPL Shell:** A stateful, continuous command-line interface with a lifecycle management loop that completely isolates calculation environments between inputs.
* **Custom Tokenizer (Lexer):** An alphanumeric lookahead scanner that dynamically packages strings into structured multi-digit floats, negative numbers (unary operators), mathematical operations, and identifier strings without token-shattering anomalies.
* **Advanced Grammar & Operator Precedence:** Implements 4 distinct tiers of mathematical priority cleanly mapped onto an AST, fully handling standard operations (`+`, `-`, `*`, `/`), nested parentheses grouping `()`, and right-associative exponentiation (`^`) through recursive right-branching.
* **Scientific Function Suite:** Native back-end execution bindings linked directly to the standard library (`<cmath>`) supporting `sqrt`, `cuberoot`, `sin`, `cos`, `tan`, `log` (natural), `log10`, `abs`, `ceil`, and `floor`.
* **Robust Exception Safety Rails:** Utilizes comprehensive exception boundaries to catch syntax mismatches, lexical anomalies, and runtime mathematical execution failures (such as division by zero or logarithmic domain errors) without crashing the runtime shell.

---

## 📐 Architecture & Grammar Blueprint

The interpreter follows a classic multi-phase compilation pipeline to translate and execute expressions:

[ Raw User Input String ] ──► [ Lexical Scanner (Lexer) ] ──► [ Token Vector ]│[ Final Value Output ] ◄── [ AST Evaluator (Backend) ] ◄── [ Recursive Parser ]
### Precedence Hierarchy (From Highest to Lowest)

1. **Factors:** Positive/Negative Numbers, Grouped Parentheses `( Expression )`, or Scientific Function Calls `function( Expression )`.
2. **Exponents:** Right-Associative Power Operator `^` (evaluated right-to-left via recursive branching).
3. **Terms:** Left-Associative Multiplication `*` and Division `/`.
4. **Expressions:** Left-Associative Addition `+` and Subtraction `-`.

