:- ['four.pl'].
task(L) :- findall(X, group(X,_), L).