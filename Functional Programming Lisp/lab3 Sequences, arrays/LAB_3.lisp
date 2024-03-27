; Будникова Валерия М8О-307Б-19
; Лабораторная работа 3
; Вариант 3.48

(defun swapStr(ind1 ind2 a)
  (if (/= ind1 ind2)
    (let* ((n (array-dimension a 0)) (m (array-dimension a 1)) (newMatr (make-array (list n m))))
      (loop for i upfrom 0 to (- n 1) do
        (loop for j upfrom 0 to (- m 1) do
          (cond ((= i ind1) (setf (aref newMatr i j) (aref a ind2 j)))
                ((= i ind2) (setf (aref newMatr i j) (aref a ind1 j)))
                (t (setf (aref newMatr i j) (aref a i j))))))
      (format t "~%Меняем местами строки ~d и ~d" ind1 ind2)
      newMatr)
    a))
(defun swapStl(ind1 ind2 a)
  (if (/= ind1 ind2)
    (let* ((n (array-dimension a 0)) (m (array-dimension a 1)) (newMatr (make-array (list n m))))
      (loop for i upfrom 0 to (- n 1) do
        (loop for j upfrom 0 to (- m 1) do
          (cond ((= j ind1) (setf (aref newMatr i j) (aref a i ind2)))
                ((= j ind2) (setf (aref newMatr i j) (aref a i ind1)))
                (t (setf (aref newMatr i j) (aref a i j))))))
      (format t "~%Меняем местами столбцы ~d и ~d" ind1 ind2)
      newMatr)
    a))

(defun print-matrix (matrix &optional (chars 4) stream)
  (let ((*print-right-margin* (+ 6 (* (+ 1 chars) (array-dimension matrix 1)))))
    (pprint matrix stream)
    (values)))

(defun swap-min-to-bottom-left(a)
  (princ "Исходная матрица:")
  (print-matrix a)
  (let ((imin 0) (jmin 0) (n (array-dimension a 0)) (m (array-dimension a 1)) )
    (loop for i upfrom 0 to (- n 1) do
      (loop for j upfrom 0 to (- m 1) do
        (if (< (aref a i j) (aref a imin jmin))
          (setq imin i jmin j))))
    (let ((answ (swapStl jmin 0 (swapStr imin (- n 1) a))))
      (print-matrix answ)
      answ)))
