(define built-in-operator (lambda (op-symbol)
(cond
((equal? op-symbol '+) +)
((equal? op-symbol '-) -)
((equal? op-symbol '*) *)
((equal? op-symbol '/) /)
(else '()))))

(define define-stmt? (lambda (e)
(and (list? e) (equal? (car e) 'define) (symbol? (cadr e)) (= (length e) 3))))

(define get-value (lambda (var env)
(cond
((null? env) (error "s6-interpret: unbound variable -->" var))
((equal? (caar env) var) (cdar env))
(else (get-value var (cdr env))))))

(define extend-env (lambda (var val old-env)
(cons (cons var val) old-env)))

(define if? (lambda (e)
              (and (list? e) (equal? (car e) 'if) (= (length e) 4))))

(define let? (lambda (e)
              (and (list? e) (equal? (car e) 'let) (= (length e) 3))))

(define letstar? (lambda (e)
              (and (list? e) (equal? (car e) 'let*) (= (length e) 3))))

(define lambda? (lambda (e)
              ((and (list? e) (equal? (car e) 'lambda) (= (length e) 3)))))

(define operator? (lambda (e)
              (or (built-in-operator e) (lambda? e) (symbol? e))))

(define application? (lambda (e)
              ((and (list? e) (operator? (car e))))))
                   
(define repl (lambda (env)
(let* (
       (dummy1 (display "cs305> "))
       (expr (read))
       (new-env (if (define-stmt? expr)
                    (extend-env (cadr expr) (s8-interpret (caddr expr) env) env) env))
       (val (if (define-stmt? expr)
                (cadr expr)
                (s8-interpret expr env)))
       (dummy2 (display "cs305: "))
       (dummy3 (display val))
       (dummy4 (newline))
       (dummy4 (newline)))
(repl new-env))))

(define listmaker (lambda (ls1 ls2)
                    (cons (append (car ls1) (car ls2)) (listmaker (cdr ls1) (cdr ls2)))))

(define s8-interpret (lambda (e env)
(cond
  ((number? e) e)
  ((symbol? e) get-value e env)
  ((if? e) (if (eq? (cadr e) 0) 
                    ( s8-interpret (cadddr e) env) 
                    ( s8-interpret (caddr e) env)))
  
  ((let? e)
      (let ((names (map car  (cadr e)))
            (inits (map cadr (cadr e))))
        (let ((vals (map (lambda (init) (s8-interpret init env)) inits)))
          (let ((new-env (append (map cons names vals) env)))
            (s8-interpret (caddr e) new-env)))))
  
  ((letstar? e)
   (let ((changed (append 'let (car e)))
         (rest (append 'let* (cdr e))))
     (and (s8-interpret changed env) (s8-interpret rest env))))

  ((lambda? e)
   (let* ((second (cdar e))
         (defpart (append 'let (listmaker (car e) (cddr e))))
         (lettotal (append defpart second)))
     (s8-interpret lettotal env)))

  ((built-in-operator (car e))
   ((built-in-operator (car e)) (s8-interpret (cdr e))))
  (else (append (s8-interpret (car e)) (s8-interpret (cdr e)))))))


(define cs305-interpreter (lambda () (repl '())))
