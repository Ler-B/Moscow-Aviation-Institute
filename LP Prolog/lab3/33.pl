calculate(Expr,Val):- reverse(Expr,Expr1), a_expr(Expr1,Val).
a_number([NS],NS):-number(NS). 

a_term(T,V):- a_number(T,V). 
a_term(T,V):-append(X,['*'|Y],T), a_number(X,Vx), a_term(Y,Vy), V is Vx*Vy.
 a_term(T,V):-append(X,[':'|Y],T), a_number(X,Vx), a_term(Y,Vy),V is Vy/Vx.
a_expr(T,V):-a_term(T,V).
a_expr(T,V):-append(X,['+'|Y],T), a_term(X,Vx), a_expr(Y,Vy), V is Vx+Vy.
a_expr(T,V):-append(X,['-'|Y],T), a_term(X,Vx), a_expr(Y,Vy), V is Vy-Vx.