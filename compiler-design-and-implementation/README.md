# compiler-design-and-implementation

## Info

```
This program is built in SWI-Prolog. 
So you need to have either SWI-Prolog application installed in your
computer or use swipl command line. SWI-Prolog application can be
installed to Windows 10, MacOS, or Linux.

The main file is program.pl, it contains three main sections: lexer, parser and evaluator.
```

## How to Run

```
Step 1: install SWI-Prolog application
Step 2: open SWI-Prolog, load the program by typing: ?-['file/path/to/src/program.pl'].
Step 3: run sample code: ?-program('file/path/to/data/sample1-ifelse.txt').

There are currently 9 sample programs in data/ folder.
The program file (program.pl) is located in src/ folder
```

## How to Debug
```
You can call 3 main predicates separately from program.pl file. 
They are lexer(-FileName, +Tokens), parser(+ParseTree, -Tokens, []), evaluator(-ParseTree).
You can either print the result or enter Prolog debug mode by attach keyword 'trace,' in front of the call.
To see fully printed result, you can attach ";true." to each call and press 'w' to let extend full result.
```

## License

MIT