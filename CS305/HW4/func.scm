; Barış Batuhan Topal, 24071, HW4

(define in? (lambda (el lst)
                (if (list? lst)
                        (if (eq? lst '())
                                #f
                                (if (eqv? el (car lst))
                                        #t
                                        (in? el (cdr lst))))

                        (error "The 2nd parameter is not a list!"))))


(define set? (lambda (lst)
        (if (not (list? lst))
                        (error "The parameter is not a list!")
                        (if (eq? lst '())
                            #t
                             (if (in? (car lst) (cdr lst))
                                      #f
                                      (set? (cdr lst)))))))


(define order (lambda (st)
               (if (set? st)
                   (if (eq? st '()) 0 
                        (+ 1 (order (cdr st))))
                   (error "The parameter is not a set"))))


(define subset? (lambda (st1 st2)
                  (if (not (set? st1))
                      (error "The first parameter is not a set!")
                      (if (not (set? st2))
                          (error "The second parameter is not a set!")
                          (if (eq? st1 '()) #t
                              (if (in? (car st1) st2)
                                  (subset? (cdr st1) st2)
                                  #f))))))


(define intersect (lambda (st1 st2)
                 (if (not (set? st1))
                      (error "The first parameter is not a set!")
                      (if (not (set? st2))
                          (error "The second parameter is not a set!")
                          (if (eq? st1 '())
                              '()
                              (if (in? (car st1) st2)
                                  (cons (car st1) (intersect (cdr st1) st2))
                                  (intersect (cdr st1) st2)))))))


(define sub (lambda (st1 st2)
             (if (not (set? st1))
                      (error "The first parameter is not a set!")
                      (if (not (set? st2))
                          (error "The second parameter is not a set!")
                          (if (eq? st1 '())
                              '()
                              (if (in? (car st1) st2)
                                  (sub (cdr st1) st2)
                                  (cons (car st1) (sub (cdr st1) st2))))))))


(define makeset (lambda (lst)
                  (if (list? lst)
                      (if (eq? lst '())
                          '()
                          (if (in? (car lst) (cdr lst))
                              (makeset (cdr lst))
                              (cons (car lst) (makeset (cdr lst)))))
                      (error "The parameter is not a list!"))))


(define merge (lambda (lst1 lst2)
               (if (not (list? lst1))
                   (error "The first parameter is not a list")
                   (if (not (list? lst2))
                       (error "The second parameter is not a list")
                       (append lst1 lst2)))))


(define union (lambda (st1 st2)
                (if (not (set? st1))
                      (error "The first parameter is not a set!")
                      (if (not (set? st2))
                          (error "The second parameter is not a set!")
                          (makeset (merge st1 st2))))))


(define insert (lambda (el lst)
                 (if (not (list? lst))
                   (error "The parameter is not a list!")
                   (if (eq? lst '())
                           '()
                           (if (not (list? (car lst)))
                               (error "The values inside the list is not a list!")
                               (cons (cons el (car lst)) (insert el (cdr lst))))
))))
