
check(L) :- helpcheck(L, []).
helpcheck(['('|T], L) :- !, append(['('], L, R), helpcheck(T, R).
helpcheck(['['|T], L) :- !, append(['['], L, R), helpcheck(T, R).
helpcheck(['{'|T], L) :- !, append(['{'], L, R), helpcheck(T, R).
helpcheck([')'|T], ['('|T1]) :- !, helpcheck(T, T1).
helpcheck([']'|T], ['['|T1]) :- !, helpcheck(T, T1).
helpcheck(['}'|T], ['{'|T1]) :- !, helpcheck(T, T1).
helpcheck([], []).
