% This file includes a lexer, parser, and evaluator.
% See end of this file for grammar definition.
%
%:- use_rendering(svgtree).
:- table e/3, t/3, i/3, b/3.

%===================================================================
program(FileName):-
	lexer(FileName, Tokens),
	parser(P, Tokens, []),
	evaluator(P).


%======================================================
% Lexer
%======================================================
lexer(FileName, Tokens):-
	open(FileName, read, FileStream),
	getChars(FileStream, Chars),
	tokenize(Chars, Tokens), !.

%-------------------------------------------------------
% Read file stream to a list of ASCII numbers, then convert them to characters.
getChars(FileStream, Chars):-
	getCharCodes(FileStream, CharCodes),
	convertCodes(CharCodes, Chars).

getCharCodes(FileStream, []):- at_end_of_stream(FileStream), !.
getCharCodes(FileStream, [CharCode|CharCodes]):-
	get_code(FileStream, CharCode),
	getCharCodes(FileStream, CharCodes).

convertCodes([], []).
convertCodes([CharCode|CharCodes], [Char|Chars]):-
	char_code(Char, CharCode),
	convertCodes(CharCodes, Chars).

%-------------------------------------------------------
tokenize(Chars, Tokens):-
	formTokens(Chars, Tokens1),
	formEqEq(Tokens1, Tokens2),
	strToAtom(Tokens2, Tokens3),
	atomToNum(Tokens3, Tokens).
%-------------------------------------------------------
% 1st step. Group strings, remove spaces, group alpha-nums, and the rest.
formTokens([], []).
formTokens([Char1|Chars], [Char1, Token, Char2|Tokens]):-
	char_type(Char1, quote),
	groupStrToken(Chars, TokenList, [Char2|RemainingChars]),
	atomics_to_string(TokenList, Token),
	formTokens(RemainingChars, Tokens).
formTokens([Char|Chars], Tokens):-
	char_type(Char, space),
	formTokens(Chars, Tokens).
formTokens([Char|Chars], [Token|Tokens]):-
	char_type(Char, alnum),
	groupAlnumToken([Char|Chars], TokenList, RemainingChars),
	string_chars(Token, TokenList),
	formTokens(RemainingChars, Tokens).
formTokens([Char|Chars], [Char|Tokens]):-
	formTokens(Chars, Tokens).

groupStrToken([Char|Chars], [], [Char|Chars]):-
	atom_length(Char, 1),
	char_type(Char, quote),
	char_code(Char, 34).
groupStrToken([Char|Chars], [Char|TokenList], RemainingAtoms):-
	groupStrToken(Chars, TokenList, RemainingAtoms).

groupAlnumToken([Char1, Char2|Chars], [Char1|TokenList], RemainingChars):-
	char_type(Char2, alnum),
	groupAlnumToken([Char2|Chars], TokenList, RemainingChars).
groupAlnumToken([Char|Chars], [Char], Chars).
%-------------------------------------------------------
% 2nd step. Form equal signs (==).
formEqEq([], []).
formEqEq([Token1, Token2|Tokens], [EqEq|RemainingTokens]):-
	Token1 = =,
	Token2 = =,
	EqEq = ==,
	formEqEq(Tokens, RemainingTokens).
formEqEq([Token|Tokens], [Token|RemainingTokens]):-
	formEqEq(Tokens, RemainingTokens).
%-------------------------------------------------------
% 3rd step. Convert all tokens from string type to atom type.
strToAtom([],[]).
strToAtom([Token|Tokens], [Atom|Atoms]):-
	atom_string(Atom, Token),
	strToAtom(Tokens, Atoms).
%-------------------------------------------------------
% 4th step. Convert atom type numerical values to number type.
atomToNum([], []).
atomToNum([Atom|Atoms], [Num|Tokens]):-
	atom_number(Atom, Num),
	atomToNum(Atoms, Tokens).
atomToNum([Atom|Atoms], [Atom|Tokens]):-
	atomToNum(Atoms, Tokens).


%======================================================
% Parser
%======================================================
/*
p in Program
k in Block
d in Declaration
c in Command

e in Arithmetic Expression 
t in term
f in factor

b in Boolean Expression
i in Identifier
n in Number
a in assignment
ter in ternary
str in string
print in print
*/

parser(program(T)) --> k(T), [.].

k(t_block(T1, T2)) --> [begin], d(T1), c(T2), [end].

d(t_intDec(T1, T2)) --> [int], i(T1), [;], d(T2).
d(t_boolDec(T1, T2)) --> [bool], i(T1), [;], d(T2).
d(t_strDec(T1, T2)) --> [str], i(T1), [;], d(T2).

d(t_intDec(T1)) --> [int], i(T1), [;].
d(t_boolDec(T1)) --> [bool], i(T1), [;].
d(t_strDec(T1)) --> [str], i(T1), [;].

c(t_assign(T1, T2)) --> a(T1), [;], c(T2).
c(t_if(T1, T2, T3)) --> [if], b(T1), [then], c(T2), [endif], c(T3).
c(t_ifElse(T1, T2, T3, T4)) --> [if], b(T1), [then], c(T2), [else], c(T3), [endif], c(T4).
c(t_while(T1, T2, T3)) --> [while], b(T1), [do], c(T2), [endwhile], c(T3).
c(t_for(T1, T2, T3, T4, T5)) --> [for], ['('], a(T1), [;], b(T2), [;], a(T3), [')'], [do], c(T4), [endfor], c(T5).
c(t_for1(T1, T2, T3, T4, T5)) --> [for], i(T1), [in], [range], ['('], f(T2), [,], f(T3), [')'], [do], c(T4), [endfor], c(T5).
c(t_ter(T1, T2)) --> ter(T1), c(T2), !.
c(t_print(T1, T2)) --> print(T1), [;], c(T2).
c(t_block(T1, T2)) --> k(T1), [;], c(T2).

c(t_assign(T)) --> a(T), [;].
c(t_if(T1, T2)) --> [if], b(T1), [then], c(T2), [endif].
c(t_ifElse(T1, T2, T3)) --> [if], b(T1), [then], c(T2), [else], c(T3), [endif].
c(t_while(T1, T2)) --> [while], b(T1), [do], c(T2), [endwhile].
c(t_for(T1, T2, T3, T4)) --> [for], ['('], a(T1), [;], b(T2), [;], a(T3), [')'], [do], c(T4), [endfor].
c(t_for1(T1, T2, T3, T4)) --> [for], i(T1), [in], [range], ['('], f(T2), [,], f(T3), [')'], [do], c(T4), [endfor].
c(t_ter(T)) --> ter(T), !.
c(t_print(T)) --> print(T), [;].
c(T) --> k(T), [;].

a(t_assignExpr(T1, T2)) --> i(T1), [=], e(T2).
a(t_assignStr(T1, T2)) --> i(T1), [=], str(T2).

ter(t_ternary(T1, T2, T3)) --> b(T1), [?], c(T2), [:], c(T3), [endter].

b(t_boolEq(T1, T2)) --> e(T1), [==], e(T2).
b(t_boolLt(T1, T2)) --> e(T1), [<], e(T2).
b(t_boolGt(T1, T2)) --> e(T1), [>], e(T2).
b(t_boolNot(T)) --> [not], b(T).
b(t_boolAnd(T1, T2)) --> b(T1), [and], b(T2).
b(t_boolOr(T1, T2)) --> b(T1), [or], b(T2).
b(true) --> [true].
b(false) --> [false].

e(t_add(T1, T2)) --> e(T1), [+], t(T2).
e(t_minus(T1, T2)) --> e(T1), [-], t(T2).
e(T) --> t(T).
t(t_mult(T1, T2)) --> t(T1), [*], f(T2).
t(t_div(T1, T2)) --> t(T1), [/], f(T2).
t(T) --> f(T).
f(T) --> i(T).
f(T) --> n(T).

i(x) --> [x].
i(y) --> [y].
i(z) --> [z].
i(u) --> [u].
i(v) --> [v].

n(T) --> ['('], e(T), [')'].
n(T) --> [T], { number(T) }.

str(T) --> ['"'], [T], ['"'].

print(t_printId(T)) --> [print], i(T).
print(t_printNum(T)) --> [print], n(T).
print(t_printStr(T)) --> [print], str(T).


%=======================================================
% Evaluator
%======================================================
evaluator(P):-
    eval_prog(P, [], _NewEnv), !.

eval_prog(program(K), Env, NewEnv):-
	eval_block(K, Env, NewEnv).
eval_block(t_block(Dec, Cmd), Env, NewEnv):-
	eval_dec(Dec, Env, Env1),
	eval_cmd(Cmd, Env1, NewEnv).

%-------------------------------------------------------
% eval_dec(Tree, Env, NewEnv)
eval_dec(t_intDec(Id), Env, NewEnv):-									
    update(Id, Env, NewEnv, 0).
eval_dec(t_intDec(Id, Tail), Env, NewEnv):-
    update(Id, Env, Env1, 0),
    eval_dec(Tail, Env1, NewEnv).

eval_dec(t_boolDec(Id), Env, NewEnv):-									
    update(Id, 0, Env, NewEnv).
eval_dec(t_boolDec(Id, Tail), Env, NewEnv):-
    update(Id, 0, Env, Env1),
    eval_dec(Tail, Env1, NewEnv).

eval_dec(t_strDec(Id), Env, NewEnv):-									
    update(Id, 0, Env, NewEnv).
eval_dec(t_strDec(Id, Tail), Env, NewEnv):-
    update(Id, 0, Env, Env1),
    eval_dec(Tail, Env1, NewEnv).

%-------------------------------------------------------
% eval_cmd(Tree, Env, NewEnv)
eval_cmd(t_assign(A), Env, NewEnv):-
    eval_assign(A, Env, NewEnv).
eval_cmd(t_assign(A, Tail), Env, NewEnv):-
    eval_assign(A, Env, Env1),
    eval_cmd(Tail, Env1, NewEnv).

eval_cmd(t_if(B, C), Env, NewEnv):-
    eval_bool(B, Env, Env1, true),
    eval_cmd(C, Env1, NewEnv);
    eval_bool(B, Env, NewEnv, false).
eval_cmd(t_if(B, C, Tail), Env, NewEnv):-
    eval_bool(B, Env, Env1, true),
    eval_cmd(C, Env1, Env2),
    eval_cmd(Tail, Env2, NewEnv);
    eval_bool(B, Env, Env3, false),
    eval_cmd(Tail, Env3, NewEnv).

eval_cmd(t_ifElse(B, C1, C2), Env, NewEnv):-
    eval_bool(B, Env, Env1, true),
    eval_cmd(C1, Env1, NewEnv);
    eval_bool(B, Env, Env3, false),
    eval_cmd(C2, Env3, NewEnv).
eval_cmd(t_ifElse(B, C1, C2, Tail), Env, NewEnv):-
    eval_bool(B, Env, Env1, true),
    eval_cmd(C1, Env1, Env2),
    eval_cmd(Tail, Env2, NewEnv);
    eval_bool(B, Env, Env3, false),
    eval_cmd(C2, Env3, Env4),
    eval_cmd(Tail, Env4, NewEnv).

eval_cmd(t_ter(Ter), Env, NewEnv):-
    eval_ter(Ter, Env, NewEnv).
eval_cmd(t_ter(Ter, Tail), Env, NewEnv):-
    eval_ter(Ter, Env, Env1),
    eval_cmd(Tail, Env1, NewEnv).

eval_cmd(t_while(B, C), Env, NewEnv):-
    eval_bool(B, Env, Env1, true),
    eval_cmd(C, Env1, Env2),
    eval_cmd(t_while(B, C), Env2, NewEnv);				% looping while is true
    eval_bool(B, Env, NewEnv, false).					% stop when is false
eval_cmd(t_while(B, C, Tail), Env, NewEnv):-
    eval_bool(B, Env, Env1, true),
    eval_cmd(C, Env1, Env2),
    eval_cmd(t_while(B, C, Tail), Env2, NewEnv);		% looping while is true
    eval_bool(B, Env, Env3, false),						% stop when is false
    eval_cmd(Tail, Env3, NewEnv).

eval_cmd(t_for(A1, B, A2, C), Env, NewEnv):-
    eval_assign(A1, Env, Env1),
    eval_for(B, A2, C, Env1, NewEnv).					% start looping after update
eval_cmd(t_for(A1, B, A2, C, Tail), Env, NewEnv):-
    eval_assign(A1, Env, Env1),
    eval_for(B, A2, C, Env1, Env2),						% start looping after update
    eval_cmd(Tail, Env2, NewEnv).

eval_cmd(t_for1(Id, F1, F2, C), Env, NewEnv):-
	eval_expr(F1, Env, Val),
    update(Id, Env, Env1, Val),
    eval_for1(Id, F2, C, Env1, NewEnv).					% start looping after update
eval_cmd(t_for1(Id, F1, F2, C, Tail), Env, NewEnv):-
    eval_expr(F1, Env, Val),
    update(Id, Env, Env1, Val),
    eval_for1(Id, F2, C, Env1, Env2),					% start looping after update
    eval_cmd(Tail, Env2, NewEnv).
    
eval_cmd(t_print(T), Env, Env):-
    eval_print(T, Env).
eval_cmd(t_print(T, Tail), Env, NewEnv):-
    eval_print(T, Env),
    eval_cmd(Tail, Env, NewEnv).

%-------------------------------------------------------
% eval_for(Tree, Tree, Tree, Env, NewEnv)
eval_for(B, A, C, Env, NewEnv):-
    eval_bool(B, Env, Env1, true),
    eval_assign(A, Env1, Env2),
    eval_cmd(C, Env2, Env3),
    eval_for(B, A, C, Env3, NewEnv);
    eval_bool(B, Env, NewEnv, false).					% if false, then stop
%-------------------------------------------------------
% eval_for1(Id, Tree, Tree, Env, NewEnv)
eval_for1(Id, F2, C, Env, NewEnv):-
    lookup(Id, Env, Val1),
    eval_expr(F2, Env, Val2),
    Val1 < Val2,
    Val3 is Val1 + 1,
    update(Id, Env, Env1, Val3),
    eval_cmd(C, Env1, Env2),
    eval_for1(Id, F2, C, Env2, NewEnv);
    eval_bool(false, Env, NewEnv, false).

%-------------------------------------------------------
% eval_ter(Tree, Env, NewEnv)
eval_ter(t_ternary(B, C1, C2), Env, NewEnv):-
    eval_bool(B, Env, Env1, true),
    eval_cmd(C1, Env1, NewEnv);
    eval_bool(B, Env, Env1, false),
    eval_cmd(C2, Env1, NewEnv).

%-------------------------------------------------------
% eval_assign(Tree, Env, NewEnv)
eval_assign(t_assignExpr(Id, Expr), Env, NewEnv):-		% assign string
    eval_expr(Expr, Env, Val),
    update(Id, Env, NewEnv, Val).
eval_assign(t_assignStr(Id, Str), Env, NewEnv):-		% assign expression
    eval_str(Str, Env, Val),
    update(Id, Env, NewEnv, Val).


%-------------------------------------------------------
% eval_bool(Tree, Env, NewEnv, Bool)
eval_bool(t_boolEq(E1, E2), Env, Env, true):-
    eval_expr(E1, Env, Val1),
    eval_expr(E2, Env, Val2),
    Val1 = Val2.
eval_bool(t_boolEq(E1, E2), Env, Env, false):-
    eval_expr(E1, Env, Val1),
    eval_expr(E2, Env, Val2),
    Val1 \= Val2.

eval_bool(t_boolLt(E1, E2), Env, Env, true):-
    eval_expr(E1, Env, Val1),
    eval_expr(E2, Env, Val2),
    Val1 < Val2.
eval_bool(t_boolLt(E1, E2), Env, Env, false):-
    eval_expr(E1, Env, Val1),
    eval_expr(E2, Env, Val2),
    Val1 >= Val2.

eval_bool(t_boolGt(E1, E2), Env, Env, true):-
    eval_expr(E1, Env, Val1),
    eval_expr(E2, Env, Val2),
    Val1 > Val2. 
eval_bool(t_boolGt(E1, E2), Env, Env, false):-
    eval_expr(E1, Env, Val1),
    eval_expr(E2, Env, Val2),
    Val1 =< Val2. 

eval_bool(t_boolNot(T), Env, Env, Bool):-
    eval_bool(T, Env, Env, true),
    Bool = false;
    eval_bool(T, Env, Env, false),
    Bool = true.

eval_bool(t_boolAnd(B1, B2), Env, Env, Bool):-
	eval_bool(B1, Env, Env, true),
	eval_bool(B2, Env, Env, true),
	Bool = true;
	Bool = false.

eval_bool(t_boolOr(B1, B2), Env, Env, Bool):-
	eval_bool(B1, Env, Env, true),
	Bool = true;
	eval_bool(B2, Env, Env, true),
	Bool = true;
	Bool = false.

eval_bool(true, Env, Env, true).
eval_bool(false, Env, Env, false).

%-------------------------------------------------------
% eval_expr(Tree, Env, Val)
eval_expr(t_add(X, Y), Env, Val):-
    eval_expr(X, Env, Val1), 
    eval_expr(Y, Env, Val2),
    Val is Val1 + Val2.
eval_expr(t_minus(X, Y), Env, Val):-
    eval_expr(X, Env, Val1), 
    eval_expr(Y, Env, Val2),
    Val is Val1 - Val2.
eval_expr(t_mult(X, Y), Env, Val):-
    eval_expr(X, Env, Val1), 
    eval_expr(Y, Env, Val2),
    Val is Val1 * Val2.
eval_expr(t_div(X, Y), Env, Val):-
    eval_expr(X, Env, Val1), 
    eval_expr(Y, Env, Val2),
    Val is Val1 / Val2.

eval_expr(X, _Env, X):- 
    number(X).
eval_expr(Id, Env, Val):- 
    lookup(Id, Env, Val).

%-------------------------------------------------------
% eval_str(Str, Env, Str)
eval_str(X, _Env, X).

%-------------------------------------------------------
% eval_print(Tree, Env)
eval_print(t_printId(Id), Env):-
    lookup(Id, Env, Val),
    write(Val), nl.
eval_print(t_printNum(Num), _Env):-
    write(Num), nl.
eval_print(t_printStr(Str), _Env):-
    write(Str), nl.

%-------------------------------------------------------
% lookup(Id, Env, Val)
lookup(Id, [(Id,Val)|_], Val).							% Id is found, return Val and Type
lookup(Id, [_|T], Val):- 								% iterate the Env list, try to find matching Id
    lookup(Id, T, Val).
lookup(_, [], _):- 
    fail.
%-------------------------------------------------------
% update(Id, Env, NewEnv, Val)
update(Id, [], [(Id,Val)], Val).						% if Env is empty, add the variable
update(Id, [(Id,_)|T], [(Id,Val)|T], Val).
update(Id, [H|T], [H|R], Val):- 						% iterate the Env list
    H \= (Id,_), update(Id, T, R, Val).



%=======================================================
% Grammar
%=======================================================
/*
P in Program
K in Block
D in Declaration
C in Command

E in Arithmetic Expression 
T in term
F in factor

B in Boolean Expression
I in Identifier
N in Number

A in assignment
TER in ternary 
Chars in characters

P ::= K.
K ::= begin D; C end

D ::=  int I; D |  String I; D
D ::=  int I | String I

C ::= A; C | if B then C else C endif; C | while B do C endwhile; C | K; C
C ::= for (A; B; A) do C endfor; C | for I in range (F,F) do C endfor ; C | TER; C | Print; C

C ::= A; | if B then C else C endif | while B do C endwhile | K; 
C ::= for (A; B; A) do C endfor | for I in range (F, F) do C endfor | TER; | Print;

A ::= I := E | I := String

B ::= E = E | not B| E < E| E > E | B and B | B or B
B ::= true | false

E ::= E + T | E - T | T
T ::= T * F | T / F | F
F ::= I | N

TER ::= B ? C : C endter

I := x | y | z | u | v 
N ::= -inf..inf
String ::= “[a-z]*[0-9]*”

Print ::= print I | print N | print E
*/
%=======================================================

