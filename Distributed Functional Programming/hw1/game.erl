-module(game).
-export([canWin/1,nextMove/1,explanation/0]).


canWin(1) -> true;
canWin(2) -> true;
canWin(3) -> false;
canWin(N) when N>0 -> (not canWin(N-1)) or (not canWin(N-2)).


nextMove(1) -> {true,1};
nextMove(2) -> {true,2};
nextMove(N) when N>0 -> 
	case canWin(N-1) of
		false -> {true,1};
		true -> case canWin(N-2) of
					false -> {true,2};
					true -> false
				end
	end.
	

	
explanation() -> 
			{"It's possible to implement it by tail recursion by just check if N(mod)3 != 0"}.
		
