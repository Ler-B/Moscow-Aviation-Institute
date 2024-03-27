:-['1.pl'].

move(A, B) :- parent(A, B).
move(A, B) :- parent(B, A).

path1(X, Y, P):- bdth1([[X]], Y, P).
bdth1([ [X|T] | _ ], X, [X | T]).
bdth1([P | QI], X, R) :- findall( Z, prolong(P, Z), T), append(QI, T, QO), !,  bdth1(QO, X, R).
bdth1([_|T], Y, L):- bdth1(T, Y, L).

prolong([ X | T ], [ Y, X | T ]) :- move(X, Y), not(member(Y, [ X | T ])).

find(mother , X, Y) :- parent(X, Y), sex(X, f).
find(father , X, Y) :- parent(X, Y), sex(X, m).
find(son, X, Y) :- parent(Y, X), sex(X, m).
find(daughter, X, Y) :- parent(Y, X), sex(X, f).
find(sister, X, Y) :- parent(Z, X), parent(Z, Y), sex(X, f).
find(brother, X, Y) :- parent(Z, X), parent(Z, Y), sex(X, m).

help(X, [A, B], X-Z) :- find(Z, A, B).
help( X , [A, B | C], Y) :- find(Z, A, B), help(X-Z, [B | C], Y).

relative(X, A, B) :- find(X, A, B).
relative(X, A, B) :- path1(A, B, P), reverse(P, P2), append([X1], X2, P2), append([X3], _, X2), find(Z, X1, X3), help(Z, X2, X).


