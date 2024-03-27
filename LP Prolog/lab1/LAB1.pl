mylength([],0).
mylength([_|Y], N) :- mylength(Y, N1), N is N1 + 1.

mymember(A,[A|_]).
mymember(A,[_|Z]) :- mymember(A,Z).

myappend([],X,X).
myappend([A|X], Y, [A|Z]) :- myappend(X, Y, Z).

myremove(X,[X|T],T).
myremove(X,[Y|T],[Y|T1]) :- myremove(X,T,T1).

mysublist(X,L) :- myappend(_,L1,L), myappend(X,_,L1).

mypermute([],[]).
mypermute(L,[X|T]) :- myremove(X,L,R), mypermute(R,T).

deletefirst3(L,[]) :- length(L, N) , N < 3.
deletefirst3(L,X) :- append(Z,X,L), length(Z,3).

shift([], X, _) :- X = [].
shift(X,X,0).
shift([_|L2],X,N) :- N1 is N - 1, shift(L2, X, N1).
mydeletefirst3([],[]).
mydeletefirst3(L,X) :- shift(L,X,3).


occurfirst([],0).
occurfirst([X|L], N) :- length([X|L], N1), delete([X|L], X, L2), length(L2, N2), N is N1 - N2.

helpoccur(_,[], 0).
helpoccur(X,[X|S], N) :- helpoccur(X,S,N1), N is N1 + 1.
helpoccur(X,[L|S],N) :- not(X = L), helpoccur(X,S,N).
myoccurfirst([], 0).
myoccurfirst([L|S],N) :- helpoccur(L,S,N1), N is N1 + 1.

occ_del([], [], _).
occ_del(X, X, 0).
occ_del(L, X, _) :- myoccurfirst(L, N), N > 1, mydeletefirst3(L, P), occ_del(P, X, 1).
occ_del(L, X, _) :- myoccurfirst(L, N), N = 1, occ_del(L, X, 0).
occur_del(L, X) :- occ_del(L, X, 1).



int(1). int(N) :- int(M), N is M+1. null(0). null(X) :- null(X).

int(N) :- int(M), N is M+1. fac(1, 1). fac(N, RES) :- N>1, N1 is N-1, fac(N1, R), RES is R*N. fac(X) :- int(N), fac(N, X).