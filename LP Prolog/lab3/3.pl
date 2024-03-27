calculate(X, X):- atomic(X), !.
calculate(X, Ans):- X=..[Op, A, B], calculate(A, R1), calculate(B, R2), rule(Op, R1, R2, Ans), !.

rule(+, A, 0, A).
rule(+, 0, A, A).
rule(+, A, B, Rez):- integer(A), integer(B), Rez is A + B.
rule(+, A, B, B+A):- integer(B).
rule(+, A, B, A+B).

rule(-, A, 0, A).
rule(-, 0, A, -A).
rule(-, A, B, Rez):- integer(A), integer(B), Rez is A - B.
rule(-, A, B, A - B).  

rule(*, _, 0, 0).
rule(*, 0, _, 0).
rule(*, A, B, Rez):- integer(A), integer(B), Rez is A * B.
rule(*, A, B, B*A):- integer(B).
rule(*, A, B, A*B).

rule(/, A, 0, A):- write('Делить на 0 нельзя!'), !.
rule(/, 0, _, 0).
rule(/, A, B, Rez):- integer(A), integer(B), T is A / B, A = B * T, Rez = T.
rule(/, A, B, A/B).
  
rule(^, 0, _, 0).
rule(^, _, 0, 1).
rule(^, 1, _, 1).
rule(^, A, 1, A). 
rule(^, A, B, Rez):- integer(A), integer(B), Rez is A ^ B.
rule(^, A, B, A^B).













 
