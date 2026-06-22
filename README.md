[ Raw User Input String ] ──► [ Lexical Scanner (Lexer) ] ──► [ Token Vector ]│[ Final Value Output ] ◄── [ AST Evaluator (Backend) ] ◄── [ Recursive Parser ]
### Precedence Hierarchy (From Highest to Lowest)

1.  **Factors:** Positive/Negative Numbers, Grouped Parentheses `( Expression )`, or Scientific Function Calls `function( Expression )`.
2.  **Exponents:** Right-Associative Power Operator `^` (evaluated right-to-left via recursive branching).
3.  **Terms:** Left-Associative Multiplication `*` and Division `/`.
4.  **Expressions:** Left-Associative Addition `+` and Subtraction `-`.

---

## 🌳 Abstract Syntax Tree Representation

Instead of relying on unstable string replacement or basic stack evaluations, this engine converts math expressions into deep tree matrices. For example, the expression:
```text
3 * 2 ^ 3 + 5
Is systematically parsed into the following binary tree structure:Plaintext        
         [ + ]
        /     \\
     [ * ]    5.0
    /     \\
  3.0    [ ^ ]
        /     \\
      2.0     3.0
The evaluator traverses the tree bottom-up, naturally resolving the exponent first ($2^3 = 8$), the multiplication second ($3 \times 8 = 24$), and the addition last ($24 + 5 = 29$).🛠️ Compilation & ExecutionThis project is written in standard C++ and requires no external third-party dependencies.PrerequisitesA C++ compiler supporting standard compilation flags (e.g., GCC/G++, Clang, or MSVC).StepsSave the code into a file named main.cpp.Compile using your preferred terminal tool:Bashg++ -O3 main.cpp -o math_shell
Launch the interactive executable:Bash./math_shell
🕹️ Interactive Session ExamplesComplex Precedence VerificationPlaintextEngine >> 2 * 3 ^ 2 + ( 20 + 30.4 )
The math engine calculated : 68.4
Exponent Right-Associativity VerificationPlaintextEngine >> 2 ^ 3 ^ 2
The math engine calculated : 512
Stress Test & Mathematical Boundary IsolationPlaintextEngine >> abs( -5 ) * sqrt( 16 ) + floor( 4.9 ) ^ ceil( 1.1 ) / log10( 100 ) - ( tan( 0 ) + cos( 0 ) * cuberoot( 8 ) ) + log( 2.7182818 )
The math engine calculated : 27
Exception Safety in ActionPlaintextEngine >> 100 / ( 5 - 5 )
Error: Runtime error : Division by zero

Engine >> sqrt( -16 )
Error: Runtime Math Error: Square root of a negative number

Engine >> log10( 0 )
Error: Runtime Math Error: Log10 of non-positive number!

Engine >> 5 * + 2
Error: Syntax Error: Expected a number or function at position : 
