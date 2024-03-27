move(A, B):- move_lr(A, B).
move(A, B):- move_ud(A, B).

move_lr([A | A1], [B | A1]):- move_z(A, B).
move_lr([A | A1], [A | B1]):- move_lr(A1, B1).

move_z([0, X | B], [X, 0 | B]).
move_z([X, 0 | B], [0, X | B]).
move_z([A | A1], [A | B1]):- move_z(A1, B1).

move_ud([A, B], [A1, B1]):- move_h(A, B, A1, B1).

move_h([0 | X], [A | Y], [A | X], [0 | Y]).
move_h([A | X], [0 | Y], [0 | X], [A | Y]).
move_h([A | X], [B | Y], [A | X1], [B | Y1]) :- move_h(X, Y, X1, Y1).

path2(Start, Finish, Path):- level(L), search_id(Start, Finish, Path, L).

level(1).
level(M):- level(N), M is N + 1.

search_id(Start, Finish, Path, DepthLim):- depth_id([Start], Finish, Path, DepthLim).

depth_id([Finish|T], Finish, [Finish|T], _).
depth_id(Path, Finish, R, N):- N > 0, prolong(Path, NewPath), N1 is N - 1, depth_id(NewPath, Finish, R, N1).

path1(X, Y, P):- bdth1([[X]], Y, P).
bdth1([ [X|T] | _ ], X, [X | T]).
bdth1([P | QI], X, R) :- findall( Z, prolong(P, Z), T), append(QI, T, QO), !, bdth1(QO, X, R).
bdth1([_|T], Y, L):- bdth1(T, Y, L).

path(X, Y, P):- bdth([[X]], Y, P).
bdth([ [X|T] | _ ], X, [X | T]).
bdth([P | QI], X, R) :- findall( Z, prolong(P, Z), T), append(T, QI, QO), !, bdth(QO, X, R).
bdth([_|T], Y, L):- bdth(T, Y, L).

prolong([X|T], [Y, X | T]) :- move(X, Y), not(member(Y, [X|T])).

solve_depth(L, TIME, LENGTH):- get_time(BEGIN), path([['table', 'chair', 'wardrobe'], ['chair', 0, 'armchair']], [[ _, _, 'armchair'], [ _, _, 'wardrobe']], L), get_time(END), TIME is END - BEGIN, length(L, LENGTH).
solve_width(L, TIME, LENGTH):- get_time(BEGIN), path1([['table', 'chair', 'wardrobe'], ['chair', 0, 'armchair']], [[ _, _, 'armchair'], [ _, _, 'wardrobe']], L), get_time(END), TIME is END - BEGIN, length(L, LENGTH).
solve_it(L, TIME, LENGTH):- get_time(BEGIN), path2([['table', 'chair', 'wardrobe'], ['chair', 0, 'armchair']], [[ _, _, 'armchair'], [ _, _, 'wardrobe']], L), get_time(END), TIME is END - BEGIN, length(L, LENGTH).
