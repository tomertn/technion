-module(shapes).
-export([squaresArea/1,trianglesArea/1,shapesArea/1,shapesFilter/1,shapesFilter2/1]).

squaresArea({shapes,[]}) -> 0;
squaresArea({shapes,[{rectangle,{dim, X, X}}|T]}) when X>0 -> X*X + squaresArea({shapes,T}) ;
squaresArea({shapes,[{rectangle,{dim, X, Y}}|T]}) when X /= Y,X>0,Y>0 -> squaresArea({shapes,T}) ;
squaresArea({shapes,[{triangle,{dim, X, Y}}|T]}) when X>0,Y>0  -> squaresArea({shapes,T}) ;
squaresArea({shapes,[{ellipse,{radius, X, Y}}|T]}) when X>0,Y>0 -> squaresArea({shapes,T}) .

trianglesArea({shapes,[]}) -> 0;
trianglesArea({shapes,[{triangle,{dim, X, Y}}|T]}) when X>0,Y>0 -> X*Y/2 + trianglesArea({shapes,T}) ;
trianglesArea({shapes,[{rectangle,{dim, X, Y}}|T]}) when X>0,Y>0 -> trianglesArea({shapes,T}) ;
trianglesArea({shapes,[{ellipse,{radius, X, Y}}|T]}) when X>0,Y>0 -> trianglesArea({shapes,T}) .

shapesArea({shapes,[]}) -> 0;
shapesArea({shapes,[{triangle,{dim, X, Y}}|T]}) when X>0,Y>0 -> X*Y/2 + shapesArea({shapes,T}) ;
shapesArea({shapes,[{rectangle,{dim, X, Y}}|T]}) when X>0,Y>0 -> X*Y + shapesArea({shapes,T}) ;
shapesArea({shapes,[{ellipse,{radius, X, Y}}|T]}) when X>0,Y>0 -> X*Y*math:pi() + shapesArea({shapes,T}) .

% In the next two dunctions we used shapesArea/1 to check the inputs (and only for this purpose).

shapesFilter(Type) when Type == rectangle; Type == triangle;Type == ellipse -> fun({shapes,List}) -> shapesArea({shapes,List}),
										{shapes,[{Type_name,Params_tuple} || {Type_name,Params_tuple} <- List, Type_name == Type ]} end.
										
shapesFilter2(Type) when Type == rectangle; Type == triangle;Type == ellipse;Type == square;Type == circle ->
								case Type of
								rectangle -> shapesFilter(Type);
								triangle -> shapesFilter(Type);
								ellipse -> shapesFilter(Type);
								circle -> fun({shapes,List}) -> shapesArea({shapes,List}),
										{shapes,[{Type_name,{radius,X,Y}} || {Type_name,{radius,X,Y}} <- List,X==Y, Type_name == ellipse ]} end;
								square -> fun({shapes,List}) -> shapesArea({shapes,List}),
										{shapes,[{Type_name,{dim,X,Y}} || {Type_name,{dim,X,Y}} <- List,X==Y, Type_name == rectangle ]} end
								end.
										


