
task(List) :-
    List = [[_, dancer, _],[_, writer, _],[_, singer, _],[_, artist, _]],
    lera([dancer, writer, singer, artist], I1, I2, I3, I4),
    member(singer, I1), %Воронов и Левицкий сидели в зале консерватории в тот вечер, когда певец
    member(singer, I3), %Воронов и Левицкий сидели в зале консерватории в тот вечер, когда певец
    member(artist, I2), %Павлов и писатель вместе позировали художнику.
    not(member(singer, I2)),
    not(member(singer, I4)),
    member(['Lerochka' ,Vor ,I1], List), 
    member(['Igoryok' ,Pav, I2], List), 
    member(['Vitalui' ,Lev ,I3], List), 
    member(['Nikitos' ,Sah ,I4], List),
    Vor \= singer, 
    Lev \= singer,
    Pav \= writer,
    Pav \= artist,
    Sah \= writer,
    Vor \= writer,
    not(member(Vor,I1)),
    not(member(Pav,I2)),
    not(member(Lev,I3)),
    not(member(Sah,I4)),
    not(member(Lev, I1)), %Воронов никогда не слышал о Левицкоv
    member([_, writer, Y], List), %Писатель написал биографическую повесть о Сахарове и собирается написать о Воронове.
    member(Vor, Y),
    member(Sah, Y),
    member(artist, Y). %Павлов и писатель вместе позировали художнику.

igor(X, X).  
igor([_|T], P) :- igor(T,P).  

lera([A, B, C, D], X1, X2, X3, X4) :- permutation([A, B, C, D], [A1, B1, C1, D1]),igor([A1, B1, C1, D1], X1), igor([A1, B1, C1, D1], X2), igor([A1, B1, C1, D1], X3), igor([A1, B1, C1, D1], X4).
     
    
leraigorarethebest3_49 :- task([[L1, LL1|_], [L2, LL2|_], [L3, LL3|_], [L4, LL4|_]]),
    write(L1), write(' - '), write(LL1), nl, 
    write(L2), write(' - '), write(LL2), nl, 
    write(L3), write(' - '), write(LL3), nl,
    write(L4), write(' - '), write(LL4).





     
    

    

    

    
    

    
    
     

    



