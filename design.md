# Aesthetics

* Common things should have short names (eg. `Fn` rather than `lambda`)
* Discouraged things should have long names (eg. `evaluate` rather than `eval`)
* Macros are capitalised
* Clear names are better than traditional names (eg. `first` over `car`)
* No commas between params

# Other choices

* No nulls, instead people should use specific values that are descriptive of the individual case.

# Functions

* `If` is our name for `cond`
* `Name` is our name for `label`
* `Quote`
* `Fn` is our name for `lambda`

* `eq?`

* `atom?`

* `first` is our name for `car`
* `rest` is our name for `cdr`
* `pair` is our name for `cons`

* `evaluate` is not abreviated because you shouldn't use it much.
* `apply`

# Questions

* Is there any situation when tagging with something other than a symbol makes sense?
  There's no syntactic way to tag something with something else that can be tagged because it'll just keep looking backwards.

  Maybe we want to tag with a key?

  foo:()

  I can't think why though.

# Literals

* `foo` is a symbol
* `bar:` is a key
* `'Hello world'` is a string
* `print()` is an empty tuple tagged with the symbol `print`
* `print{text: 'Hello world' style: 'bold'}` is a tagged map with keys and strings
* Defining a constant
```
Let(width 20)
```
* Defining a function
```
Let(double(n)
  *(n 2))
```

* Calling a function with a function

```
map(Fn[n| *(n 2)] numbers)
```

```
# Generate 10 random dice rolls
map(Fn[roll-dice(6)] (range 10))
```

What if `[a b c| (foo) (bar) (baz)]` is a kind of general form for arguments and body? It comes up for xml as well:

```
  form[action: '/cities' method: 'post' |
    fieldset[
      legend['City']

      label[for: 'name' | 'Name:' ]
      input(type: 'text' id: 'name' value: 'John')]

      input(type: 'submit' value: 'Submit')]
```

Could maybe use it for pattern matching?

```
Match(data
  Case[ok(result) | print(result) ]
  Case[err(reason) | log(reason) ]
  Default[ log('Unknown response') ])
```

So for defining functions we move away from the definition looking like the call again?

```
Let(double [n | *(n 2)])
```

That doesn't seem great. We lose the symetry and end up stacking the keyword vs positional argument semantics all into blocks. I guess they could still just be used as code blocks, the same way some languages use `{}`. A little scope capsule that just evaluates to the value of the last expression. Could be good for `If` and for impure `Fn`:

```
If( =(month 'July')
  [log('Kicking off tax routine')
   submit-taxes()]
  (log('Taxes are not yet due')))
```

That does feel a bit weird, like we're using them for code blocks but not when defining lambdas? And we could just use `do(a b c)` for code blocks.
