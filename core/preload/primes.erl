-module(primes).
-compile(export_all).
-export([up_to/1, exclude/3]).

%%
%%    A small excerpt from lists.erl
%%

seq(First, Last) when is_integer(First), is_integer(Last), First-1 =< Last -> 
    seq_loop(Last-First+1, Last, []).

seq_loop(N, X, L) when N >= 4 ->
     seq_loop(N-4, X-4, [X-3,X-2,X-1,X|L]);
seq_loop(N, X, L) when N >= 2 ->
     seq_loop(N-2, X-2, [X-1,X|L]);
seq_loop(1, X, L) ->
     [X|L];
seq_loop(0, _, L) ->
     L.

dropwhile(Pred, [Hd|Tail]=Rest) ->
    case Pred(Hd) of
	true -> dropwhile(Pred, Tail);
	false -> Rest
    end;
dropwhile(Pred, []) when is_function(Pred, 1) -> [].


%
% helper routine
%
exclude(_, _, []) -> [];
exclude(N, By, [H | T]) when N == H -> exclude(By + N, By, T);
exclude(N, By, [H | T]) when H < N -> [H | exclude(N, By, T)];
exclude(N, By, [H | T]) -> [H | exclude(N + By, By, T)].


%%
%% interface
%%

sieve(Lst, P) ->
  Lst1 = exclude(P + P, P, Lst),
  case dropwhile(fun(X) -> X =< P end, Lst1) of
    [] -> Lst1;
    [ P1 | _ ] -> sieve(Lst1, P1)
  end.

up_to(N) -> sieve(seq(2, N), 2).

