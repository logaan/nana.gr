Module(echo-server [tcp: stdout:]

start-server Fn([port]
    (get tcp listen:)(port)))


;; Clojure
(map (fn [[key value]] [key (* 2 value)])
            {:a 1 :b 2 :c 3})

;; Nana with []() fns and foo() calls
map([pair] ([first(pair) prod(2 second(pair))])
    {a: 1 b: 2 c: 3})

;; Nana with just foo() calls
map(Fn([pair] [first(pair) prod(2 second(value))])
    {a: 1 b: 2 c: 3})

;; Nana with foo() and . calls
{a: 1 b: 2 c: 3}
    .map(Fn([pair]
     [pair.first()
      prod(2 value.second()))]))

;; Sweet expressions - Multi line
map
    Fn
        [pair]
        [first(pair)
         prod(2 second(pair))]
    {:a 1 :b 2 :c 3}

;; Sweet expressions - Multi line, dot expressions
{:a 1 :b 2 :c 3}
.map
    Fn
        [pair]
        [pair.first()
         prod(2 pair.second())]

;; Sweet expressions - compact
map(Fn([pair] [first(pair) prod(2 second(pair))]) {:a 1 :b 2 :c 3})

;; Sweet expressions algo
; Scan a window that advances 1 line at a time and holds 2 lines
; Have a stack of opening and closing parens, braces, brackets
; If that stack is empty at the start and end of line 1
;     and line 2 is more deeply indented than line 1
;         then add an opening paren to the start of line 1
; If that stack is empty at the end of line 1
;     and line 2 is less deeply indented than line 1
;         then add a closing paren to the start of line 1
; 
;; The top paren stripping thing is redundant if we use `(module foo ...)`
;; - But that means everything will be indented.
;; - What if we say that .nana files are loaded as though they had parens as first and last character?

Namespace echo-server
[tcp stdout]

handler Fn([reply-socket message]
    stdout/print(message)
    tcp/send(reply-socket message))

start-server Fn([port]
    tcp/listen("127.0.0.1" port handler))

;; Looks pretty good. I can even handle the Fn([port]) stuff I think..
;; So we need 3 regexes to make this work.
;; 1. Insert `(` before line 1 and `)` after the last line
;; 2. (\w+)\/(\w+) becomes (get %1 %2)
;; 3. (\w+)\( becomes (%1