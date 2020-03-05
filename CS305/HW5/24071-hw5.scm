;Barış Batuhan Topal, 24071

(define get-operator (lambda (op-symbol) 
  (cond 
    ((equal? op-symbol '+) +)
    ((equal? op-symbol '-) -)
    ((equal? op-symbol '*) *)
    ((equal? op-symbol '/) /)
    ((equal? op-symbol '#t) #t)
    ((equal? op-symbol '#f) #f)
    (else #f))))

(define caarcheck (lambda (e)
                 (if (not (list? (car e)))
                     e
                     (caar e))))

(define define-stmt? (lambda (e)
    ;; An expression is a define statement
    ;; if it is a list, and the first element
    ;; is define, the second element is a symbol,
    ;; and the third element is an expression.
    (and (list? e) (equal? (car e) 'define) (symbol? (cadr e)) (= (length e) 3))))

(define if? (lambda (e)
              (and (list? e) (equal? (car e) 'if) (= (length e) 4))))

(define let? (lambda (e)
              (and (list? e) (equal? (car e) 'let) (= (length e) 3))))

(define letstar? (lambda (e)
              (and (list? e) (equal? (car e) 'let*) (= (length e) 3))))

(define lambdaturn (lambda (e)
;turns lambda statement to one form with checking the parantheses
              (if (list? e)
                  (if (eq? (car e) 'lambda) (list e)
                      (if (eq? (caar e) 'lambda) e
                          '()))
                  '())))

(define lambda? (lambda (e)
                  (and (list? e) (or (equal? (car e) 'lambda) (equal? (caarcheck e) 'lambda)))))


(define get-value (lambda (var env)
    (cond
      ;; If the environment is empty, then we could not find 
      ;; a binding in this environment.
      ((null? env) (error "s6-interpret: unbound variable -->" var))

      ;; Check if the first pair is a binding for the
      ;; variable that we are looking for, and if it is
      ;; return the current value of the variable.
      ((equal? (caar env) var) (cdar env))

      ;; Otherwise, search in the remaning of the environment.
      (else (get-value var (cdr env))))))

(define extend-env (lambda (var val old-env)
      ;; Add the new variable binding to the 
      ;; beginning of the old environment.
      (cons (cons var val) old-env)))

(define defhelper (lambda (e env)
    (if (list? e)
    (if (equal?(car e) 'lambda)
        e
        (s6-interpret e env))
    e)))

(define repl (lambda (env)
  (let* (
         ; first print out some prompt
         (dummy1 (display "cs305> "))

         ; READ an expression
         (expr (read))

         ; Form the new environment
         (new-env (if (define-stmt? expr)
                      (extend-env (cadr expr) (defhelper (caddr expr) env) env)
                      env))

         ; EVALuate the expression read
         (val (if (define-stmt? expr)
                  (cadr expr)
                  (s6-interpret expr env)))

         ; PRINT the value evaluated together
         ; with a prompt as MIT interpreter does
         (dummy2 (display "cs305: "))
         (dummy3 (display val))

         ; get ready for the next prompt
         (dummy4 (newline))
         (dummy4 (newline)))
     (repl new-env))))

(define starconv (lambda (e)
;changes let* to let statement
  (starhelper (car e) (cdr e))))

(define starhelper (lambda (e last)
  (if (equal? (cdr e) '())
      (append '(let) (append (list (list (car e))) last))
      (append '(let) (list (list (car e))(starhelper (cdr e) last))))))

(define lambdaconv (lambda (e)
;changes lambda to let statement
  (append (append '(let) (list (lambdahelper (cadar e) (cdr e)))) (cddar e))))

(define lambdahelper (lambda (p v)
  (if (eq? v '()) '()
      (append (list (list (car p) (car v))) (lambdahelper (cdr p) (cdr v))))))
        

(define s6-interpret (lambda (e env)
  (cond 
    ((number? e) e)

    ((symbol? e) (get-value e env))

    ((not (list? e)) 
          (error "s6-interpret: cannot evaluate -->" e))

    ((let? e)
      (let ((names (map car  (cadr e)))
            (inits (map cadr (cadr e))))
        (let ((vals (map (lambda (init) (s6-interpret init env)) inits)))
          (let ((new-env (append (map cons names vals) env)))
            (s6-interpret (caddr e) new-env)))))
     
     ((letstar? e)
      (s6-interpret (starconv (cdr e)) env))

     ((if? e) (if (eq? (cadr e) 0) 
                    ( s6-interpret (cadddr e) env) 
                    ( s6-interpret (caddr e) env)))

     ((lambda? e)
      (s6-interpret (lambdaconv (lambdaturn e)) env))
    
     (else (let (
             (operands (map s6-interpret (cdr e) (make-list (length (cdr e)) env)))
             (operator (if (get-operator (car e)) (get-operator (car e)) (get-value (car e) env)))
            )
         (if (get-operator (car e))
             (apply operator operands)
             (s6-interpret (append (list operator) operands) env)))))))

(define cs305 (lambda () (repl '())))

