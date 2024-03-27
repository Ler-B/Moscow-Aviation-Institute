:-['LP_KP_4.pl'].
qw_list(['Who', 'How many', 'Is', 'Whose']).
rel_list(['son', 'daughter', 'mother', 'father', 'sister', 'brother', 'sons', 'daughters', 'sisters', 'brothers', 'child', 'children']).
pro_list(['her', 'him', 'she', 'he', 'his']).
and_or(['and', 'or']).
ch(['child', 'children']).
and('and').
or('or').

help([], []).
helpp(T, Z) :- append([T1], T2, T), (g_name(T1), Z = T1, ! ; helpp(T2, Z)).
pr(L, T1) :- g2(L, [], T), helpp(T, T1), qw(T), nl.

g2([], T, T).
g2(L, X, T) :- append([L1], L2, L), mem(L1), append(X, [L1], X2), g2(L2, X2, T).
g2(L, X, T) :- append([L1], L2, L), not(mem(L1)), g2(L2, X, T).

is_and(_, _, [], 1).
is_and(A, B, [T], REZ) :- (relative(B, A, T), REZ is 1, ! ; REZ is 0, !).
is_and(A, B, T, REZ) :- append([T1], T2, T), append([_], T4, T2), is_and(A, B, [T1], R1), is_and(A, B, T4, R2), REZ is R1 * R2.

is(_, _, [], 0).
is(A, B, [T], REZ) :- (relative(B, A, T), REZ is 1, ! ; REZ is 0, !).
is(A, B, C, REZ) :- append(L1, L2, C), f_or(L2, L3), is(A, B, L3, R1), is(A, B, L1, R2), REZ is R1 + R2, ! ; is_and(A, B, C, REZ), !.

qw(['Is', A, B, C]) :- g_ch(B, B1, A), relative(B1, A, C), write('Yes'), nl, ! ; write('No'), !.
qw(['Is', A, B, C | D ]) :- g_ch(B, B1, A), is(A, B1, [C | D], REZ), (REZ = 0, write('No'); REZ \= 0, write('Yes')), !.

qw(['How many', A, B]) :- g_ch1(A), (setof(X, parent(B, X), Z), length(Z, I), write(I), nl, ! ; write('0'), nl).
qw(['How many', A, B]) :- concat(A1, 's', A), setof(X, (find(A1, X, B), X \= B), Z), length(Z, I), write(I), nl, ! ; write('0'), nl.

qw(['Who', A, B]) :- setof(X, (find(A, X, B), X \= B), Z), write(Z), nl, ! ; qw(['Who', B, A]), !; write(B), write(' does not have a '), write(A), nl.

qw(['Who', A]) :- sex(A, f), write(A), write(' is women').
qw(['Who', A]) :- sex(A, m), write(A), write(' is men').

qw(['Whose', A, B]) :- setof(X, (find(A, B, X), X \= B), Z), write(Z), nl, ! ; write('nobody').

mem(L1) :- g_qw(L1) ; g_rel(L1) ; g_name(L1) ; g_end_or(L1).

f_or(L, L2) :- append([A], L2, L), A = 'or'.

g_ch1(L1) :- ch(L), member(L1, L).
g_ch(L1, L1, _) :- ch(L), not(member(L1, L)).
g_ch(L1, daughter, A) :- ch(L), member(L1, L), sex(A, f).
g_ch(L1, son, A) :- ch(L), member(L1, L), sex(A, m).
g_end_or(L1) :- and_or(L), member(L1, L).
g_name(L1) :- sex(L1, _ ).
g_qw(L1) :- qw_list(L), member(L1, L).
g_rel(L1) :- rel_list(L), member(L1, L).
g_pro(L1) :- pro_list(L), member(L1, L).

g3(X, Z, A) :- append([X1], X2, X), g_pro(X1), append(A, X2, Z).

help_start(A, L, L2) :- append(X1, X2, L), g3(X2, X3, A), append(X1, X3, L2).

start :- read(L), pr(L, T), start([T]).
start(A) :- read(L), (help_start(A, L, L2) ; L2 = L), pr(L2, T), start([T]).