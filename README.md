# Miheson - My JSON (Linter)

Just a JSON Linter written in C. I wrote it using Emacs instead of Neovim just to see if I like Emacs.
Overtime I can see why some people love Emacs. Personally like Neovim/Vim Motion better.
After a week or 2 of trying emacs, I could not bare the pain of using modifier keys. My pinky hurts.
Don't get me wrong its not emacss' fault. It's my laptop keyboard. Perhaps I will try it again after
I bought a new keyboard

## Limitation
This project is for fun and learning purposes. Therefore, there are some bugs that I
can fix and feature that I can add but I'm too lazy to continue because I am excited
about other project. Some of them are:

1. Numbers **MIGHT** not be properly parse
2. I don't check for duplicate keys
3. The code is somewhat a mess because I was trying to play around with different ideas
4. It's my first time implementing Lexer and Parser concept by myself without additional resources except Wiki to see what is the definition and get rough ideas
5. It does not tell you where the error is
6. If you nitpick a lot of it, you will find the error eventually, but yeah whatever

## What interesting is?
I don't plan to use Lexer or Parser at all to be honest. I started out with some crappy
character checking system but then I realize it has a lot of limitation to keep track of everything.
So I trying to read about Token and Lexer. But then after that I tried to not use Recursion to
process the Token. But I still has too after quite sometime of debugging.

The parser did not generate anything at all. It just analyze the syntax.

## Conclusion
All in all, i'm quite proud of the project. I found out that it is less distracting to not use LSP but then also a bit slow since I don't have navigation like **go to definition**, **renaming variable** etc etc. But I have fun doing this project with just me, Text Editor (Neovim), and a Compiler. Sure I can extend this project even more. But It won't bring me any **significant** values in term of knowledge. Since this is just me doing my own thing without using some reference of how it should be done.
