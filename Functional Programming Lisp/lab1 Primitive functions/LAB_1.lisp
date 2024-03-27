(defun f(n) (iter 1 1 1 n))


(defun iter(a1 a2 a3 a4)
  (cond ((= a4 0) a1)
    (t (iter a2 a3 (g a3 a2 a1) (- a4 1)))
  )
)

(defun g(x1 x2 x3) (* (* x1 (+ x2 2)) (+ x3 3)))


