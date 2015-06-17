-module(primes).
-compile(export_all).
-export([up_to/1, exclude/3]).

exclude(_, _, []) -> [];
exclude(N, By, [H | T]) when N == H -> exclude(By + N, By, T);
exclude(N, By, [H | T]) when H < N -> [H | exclude(N, By, T)];
exclude(N, By, [H | T]) -> [H | exclude(N + By, By, T)].

up_to(N) -> sieve(lists:seq(2, N), 2).

sieve(Lst, P) ->
  Lst1 = exclude(P + P, P, Lst),
  case lists:dropwhile(fun(X) -> X =< P end, Lst1) of
    [] -> Lst1;
    [ P1 | _ ] -> sieve(Lst1, P1)
  end.
