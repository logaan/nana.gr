  evalAndPrint("(+ 1 1)");
  evalAndPrint("(first (quote (1 2 3)))");
  evalAndPrint("(println (quote foo))");
  evalAndPrint("(def a 4)
           (println a)");

  evalAndPrint(
    "
             (def square
               (lambda (n)
                 (* n n)))
             (println square)",
  );
  evalAndPrint("((lambda () (println 1)))");

  evalAndPrint("((lambda () ((lambda () (println 2)))))");
  evalAndPrint(
    "
          (def square
            (lambda ()
              (* 4 4)))
          (square)",
  );

  evalAndPrint(
    "
           (def square
             (lambda (n)
               (* n n)))
           (square 4)",
  );

  evalAndPrint("(println println)");

  evalAndPrint("((println println) 3)");

  evalAndPrint("(println (println 3))");
  try (
    evalAndPrint(
      "
               (def square
                 (lambda (n)
                   (* n n)))

               (def do
                 (lambda (a b)
                   b))

               (println (do (square 4) (square n)))",
    )
  ) {
  | ArgumentError("n not found") => print_endline("n not found")
  };
  // Binding to n in inner should not change the binding of n in outer
  evalAndPrint(
    "
          (def do
            (lambda (a b)
              b))

          (def inner
            (lambda (n)
              (println n)))

          (def outer
            (lambda (n)
                 (do (inner (* n 4)) (println n))))

          (println (outer 1))

                 9",
  );
  // Expected output 4, 1, 1, 9

  evalAndPrint(
    "
                 (println (= true true))
                 (println (= false false))
                 (println (= true false))
                 (println (= false true))

                 (println (= 1 1))
                 (println (= 1 2))

                 (println (= (lambda (n) n)
                             (lambda (n) n)))

                 (println (= (lambda (n) n)
                             (lambda (y) y)))
          ",
  );

  evalAndPrint("(if true (println (quote worked)) (println (quote broken)))");
  evalAndPrint(
    "(if false (println (quote broken)) (println (quote worked)))",
  );
  evalAndPrint(
    "(if (= 1 1) (println (quote worked)) (println (quote broken)))",
  );
  evalAndPrint(
    "

          (def do
            (lambda (a b)
              b))

          (def count-to-10
            (lambda (c)
              (do (println c)
                  (if (= c 10)
                    (quote worked)
                    (count-to-10 (+ c 1))))))

          (count-to-10 0)
                 ",
  );

  evalAndPrint(
    "
          (def do
            (lambda (a b c)
              c))
(def my-val
  (call/cc (lambda (the-continuation)
             (do
               (println (quote this-will-be-executed))
               (the-continuation 5)
               (println (quote this-will-not-be-executed))))))

my-val
",
  );

  evalAndPrint(
    "

          (def do
            (lambda (a b)
              b))

(def my-val
  (call/cc (lambda (the-continuation) the-continuation)))

(if (= 5 my-val)
  (println (quote second-time-through))
  (do (println (quote first-time-through))
      (my-val 5)))

",
  );
};