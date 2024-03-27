calculate(A, Ans):- reverse(A, A1), expr(A1, Ans). 

num([X], X):- number(X).

myterm(X, Y):- num(X, Y).
myterm(X, Y):- append(A, ['^'|B], X), num(A, A3), append([B1], B2, B), Z is B1 ^ A3, append([Z], B2, List), myterm(List, Y).
myterm(X, Y):- append(A, ['*'|B], X), num(A, A1), myterm(B, B1), Y is A1 * B1.
myterm(X, Y):- append(A, ['/'|B], X), num(A, A1), myterm(B, B1), Y is B1 div A1. 

expr(X, Y):- myterm(X, Y), !.
expr(X, Y):- append(A, ['+'|B], X), myterm(A, A1), expr(B, B1), Y is A1 + B1, !. 
expr(X, Y):- append(A, ['-'|B], X), myterm(A, A1), expr(B, B1), Y is B1 - A1, !.











