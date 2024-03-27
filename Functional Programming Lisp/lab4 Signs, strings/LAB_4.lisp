; Будникова Валерия М8О-307Б-19
; Лабораторная работа 4
; Вариант 4.35

(defvar txt)
(setq txt '("Это 1тек0ст" "Предн00азначе9нный для89 пров3ер4ки" 
            "лабо34раторной  +работы" "1Написанной+ на языке" "Common 345 lisp" ))

(defun FindPlus(str)
  (let* ((res "") (arr (concatenate 'list str)))
    (if (member #\+ arr) (setq res str)) 
    res))

(defun Replc(str)
  (loop for i upfrom 0 to (- (length str) 1) do
    (if (and (>= (char-code #\9) (char-code (aref str i))) (<= (char-code #\0) (char-code (aref str i))))
      (setf (char str i) #\-))
    (if (eq #\+ (char str i)) (return))))

(defun Fix(text fstr)
  (let ((tempstr "")) (dolist (str text)
    (setq tempstr str)
    (Replc str)
    (if (string= tempstr fstr) (return))))
  text)

(defun Copy(text)
  (let ((newText NIL))
    (dolist (str text) (push (copy-seq str) newText))
    (reverse newText)))

(defun f(text)
  (let ((findStr "") (newText (Copy text)))
    (dolist (str newtext)
      (setq findStr (FindPlus str))
      (if (not (= (length findStr) 0)) (return)))
    (if (= (length findStr) 0) text (Fix newText findStr))))
