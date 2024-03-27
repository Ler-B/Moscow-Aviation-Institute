whoiswho(Coupe) :- 
    Coupe = [[_,poet,play,_,poem],[_,astronomer,_,_,bookonastronomy],[_,playwrite,_,_,play],[_,prosewriter,_,_,prose]],
    member([_, _, _, prose, _], Coupe),
    member([_, _, _, play, _], Coupe),
    member([_, _, _, bookonastronomy, _], Coupe),
    member([_, _, _, poem, _], Coupe),
    member([_, _, prose, X1, Y1], Coupe), Y1 \= prose, X1 \= Y1,
    member([_, _, play, X2, Y2], Coupe), Y2 \= play, X2 \= Y2,
    member([_, _, bookonastronomy, X3, Y3], Coupe), Y3 \= bookonastronomy, X3 \= Y3,
    member([_, _, poem, X4, Y4], Coupe), Y4 \= poem, X4 \= Y4,
    member([_, prosewriter, R1, B1, prose],Coupe), R1 \= bookonastronomy, B1 \= bookonastronomy,
    member(['Dmitriev', _, _, _, Z1], Coupe),
    member(['Alekseev', _, Z1, X11, _], Coupe),
    member(['Borisov', _, X11, Z1, _], Coupe),
    member(['Konstantinov', _, _, _, _], Coupe).

printlist2([]).
printlist2([X1, X2, X3| _]) :- write(X1), write(' - '), write(X2), write('. He was reading a '), write(X3), write('.'), nl.
printlist([]) :- nl.
printlist(X) :- append([X1], X2, X), printlist2(X1), printlist(X2).
print([]).   
print(X) :- append([X1], X2, X), printlist(X1), print(X2).

task2 :- findall(X, whoiswho(X), L), print(L).
