; Будникова Валерия М8О-307Б-19
; Лабораторная работа 2
; Вариант 2.38

(defun myReverse(defaultList reverseList)
  (if (null defaultList)
      reverseList
      (myReverse (rest defaultList) (cons (first defaultList) reverseList))))

(defun catchUnique(elemOfList defaultList uniqueList)
  (if (member elemOfList (rest (member elemOfList defaultList)))
      uniqueList
      (cons elemOfList uniqueList)))

(defun f(inputList defaultList resultList)
  (if (null inputList)
      resultList
      (f (rest inputList) defaultList (catchUnique (first inputList) defaultList resultList))))

(defun индивидуумы(l) (myReverse (f l l ()) ()))
