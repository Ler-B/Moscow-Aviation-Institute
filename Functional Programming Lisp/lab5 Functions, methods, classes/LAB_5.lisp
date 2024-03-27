; Будникова Валерия М8О-307Б-19
; Лабораторная работа 5
; Вариант 5.38

(defclass polynom()
  ((var-symbol :initarg :varb :reader varb)
  (term-list :initarg :terms :reader terms)))

(defgeneric zerop1 (arg)
  (:method ((n number))   ; (= n 0)
  (zerop n)))

(defgeneric minusp1 (arg)
  (:method ((n number))   ; (< n 0)
  (minusp n)))

(defun order (term) (first term))

(defun coeff (term) (second term)) 

(defun make-term (&key order coeff)
  (list order coeff))

(defmethod print-object ((p polynom) stream)
  (format stream "[МЧ (~s) ~:{~:[~:[+~;-~]~d~[~2*~;~s~*~:;~s^~d~]~;~]~}]"
    (varb p)
    (mapcar (lambda (term)
              (list (zerop1 (coeff term))
                    (minusp1 (coeff term))
                    (if (minusp1 (coeff term))
                        (abs (coeff term))
                        (coeff term))
                    (order term)
                    (varb p)
                    (order term)))
      (terms p))))

(defun findCoef(ord lstTerms) 
  (let ((cf 0))
    (dolist (tr lstTerms) 
      (cond ((= (order tr) ord) 
        (setq cf (coeff tr))
        (setq lstTerms (delete tr lstTerms))
        (return))))
    cf))

(defun FindMin(l) 
  (let ( (tr1 (first l)) )
      (dolist (tr l) 
          (if (< (order tr) (order tr1)) (setq tr1 tr)))
    tr1))

(defun Sorting(listTerms)
    (let ((l '()))
      (loop while listTerms do 
      (push (FindMin listTerms) l)
      (if (= (list-length listTerms) 1) (setq listTerms NIL) (setq listTerms (delete (FindMin listTerms) listTerms))))
      l))

(defun sub(p1 p2) 
    (let (  (listTerms (terms p1)) (p3Terms '()) (p2listTerm (copy-list (terms p2))))
      (dolist (tr listTerms) 
        (let* ( (cf1 (coeff tr)) (cf2 (findCoef (order tr) p2listTerm)))
          (push (make-term :order (order tr) :coeff (- cf1 cf2)) p3Terms)          
          (if (= (list-length p2listTerm) 1) (if (not (= cf2 0)) (setq p2listTerm NIL))))) 
      (dolist (tr p2listTerm) (push (make-term :order (order tr) :coeff (* -1 (coeff tr))) p3Terms))
      (make-instance 'polynom
        :varb (varb p1)
        :terms (Sorting p3Terms))))

(defun same-variable-p (v1 v2)
  (and (symbolp v1) (symbolp v2) (eq v1 v2)))

(defgeneric sub2 (arg1 arg2))

(defmethod sub2 ((n1 number) (n2 number)) (- n1 n2))

(defmethod sub2 ((pp1 polynom) (n2 number)) 
  (sub2 pp1 (make-instance 'polynom
          :varb (varb pp1)
          :terms (list (make-term :coeff n2 :order 0)))))

(defmethod sub2 ((pp1 polynom) (pp2 polynom))
  (if (same-variable-p (varb pp1) (varb pp2))
    (sub pp1 pp2)
    (error "Многочлены от разных переменных: ~s и ~s" pp1 pp2)))

(defvar p1)
(defvar p2)
(setq p1 (make-instance 'polynom
          :varb 'x
          :terms (list (make-term :order 2 :coeff 5)
                       (make-term :order 1 :coeff 3.3)
                       (make-term :order 0 :coeff -7))))                        

(setq p2 (make-instance 'polynom
          :varb 'x
          :terms (list (make-term :coeff 1 :order 1)
                       (make-term :coeff 2 :order 2)
                       (make-term :coeff 1 :order 0))))

