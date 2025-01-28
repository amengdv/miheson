# Miheson - My JSON (Linter)

Miheson is a JSON linter written in C. It’s a personal project I created to explore and learn about lexer and parser concepts without relying on external libraries or references. This project was developed purely with my own understanding, a text editor (Emacs/Neovim), and a compiler.

## Why I Built This

Initially, I didn’t plan to use a lexer or parser. I started with a simple character-checking system but quickly realized its limitations. This inspired me to dive into tokenization and syntax analysis concepts. Over time, I experimented with different ideas, debugged issues, and gradually developed a better understanding of how lexers and parsers work.

## What I Learned

- Implementing a lexer and parser from scratch gave me a hands-on understanding of these concepts. 
- Debugging taught me how to think critically about algorithms and memory usage in C.
- I learned to rely on minimal tools, focusing on functionality over aesthetics, which helped sharpen my coding skills.

## Key Features

- **Syntax Analysis**: The parser analyzes JSON syntax without generating an output tree.
- **Lexer Implementation**: Tokens are generated for JSON components, a core feature of this linter.

## Limitations

This project is for fun and learning, so it has some limitations:
1. Numbers **might** not be parsed correctly.
2. Duplicate keys are not checked.
3. Errors don’t specify their exact location.
4. The codebase is experimental and a bit messy due to trying out different ideas.
5. It was my first attempt at implementing lexer and parser concepts without external resources.

Despite these limitations, I’m proud of the effort and what I’ve learned along the way.

## Reflection

While working on this project, I realized that minimal setups (without LSPs or additional tooling) can reduce distractions, although they can slow down tasks like navigation and refactoring. Using just a text editor and compiler allowed me to focus deeply on the core functionality.

This project might not be perfect or production-ready, but it represents a significant learning milestone for me. I'm excited to take what I’ve learned here and apply it to future projects.
