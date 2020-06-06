-module(matrix_server).
-export([start_server/0,shutdown/0,mult/2,loop/0,calc_one_element/2,mult_recur/7,mult_server/4,mult_server_loop/5,upgrade/0,get_version/0,explanation/0]).

calc_one_element_aux([H1|[]],[H2|[]])-> H1*H2;
calc_one_element_aux([H1|T1],[H2|T2])-> H1*H2 + calc_one_element_aux(T1,T2).

calc_one_element(Vec1,Vec2)->
	V1 = tuple_to_list(Vec1),
	V2 = tuple_to_list(Vec2),
	calc_one_element_aux(V1,V2).

loop() ->
	receive
		{Pid, MsgRef, {multiple, Mat1, Mat2}} -> 
			spawn(?MODULE,mult_server,[Pid,MsgRef,Mat1,Mat2]),
			loop();
		shutdown -> 
			exit(shutdown);
		{Pid, MsgRef, get_version} ->
			Pid ! {MsgRef, version_1},
			loop();
		sw_upgrade ->
			?MODULE:loop();
		Any -> 
			io:format("Got ~p~n" ,[Any]),
			loop()
	end. 

mult_recur(Pid_mult_server,Mat1,Mat2,X,Y,X,Y) ->
	Res=calc_one_element(matrix:getRow(Mat1,X),matrix:getCol(Mat2,Y)),
	Pid_mult_server ! {Res,X,Y};
	
mult_recur(Pid_mult_server,Mat1,Mat2,X,Col,X,Y) when Col < Y ->
	spawn(?MODULE,mult_recur,[Pid_mult_server,Mat1,Mat2,1,Col+1,X,Y]),
	Res=calc_one_element(matrix:getRow(Mat1,X),matrix:getCol(Mat2,Col)),
	Pid_mult_server ! {Res,X,Col};
	
mult_recur(Pid_mult_server,Mat1,Mat2,Row,Col,X,Y) when Row < X, Col =< Y ->
	spawn(?MODULE,mult_recur,[Pid_mult_server,Mat1,Mat2,Row+1,Col,X,Y]),
	Res=calc_one_element(matrix:getRow(Mat1,Row),matrix:getCol(Mat2,Col)),
	Pid_mult_server ! {Res,Row,Col}.



mult_server(Pid,MsgRef,Mat1,Mat2)->
	X = tuple_size(Mat1),
	Y = tuple_size(element(1,Mat2)),
	SolMat = matrix:getZeroMat(X,Y),
	Cnt = 0,
	spawn(?MODULE,mult_recur,[self(),Mat1,Mat2,1,1,X,Y]),
	mult_server_loop(Pid,MsgRef,SolMat,Cnt,X*Y).
		
	
mult_server_loop(Pid,MsgRef,SolMat,Total_elements,Total_elements)->
	Pid ! {MsgRef,SolMat}; 

mult_server_loop(Pid,MsgRef,SolMat,Cnt,Total_elements) when Cnt < Total_elements ->
	receive
		{Res,Row,Col}->
			SolMatNew=matrix:setElementMat(Row,Col,SolMat, Res),
			mult_server_loop(Pid,MsgRef,SolMatNew,Cnt+1,Total_elements)
	end.
			
		


start_server()-> 
	%Pid=spawn(fun matrix_server:loop/0),
	%register(matrix_server,Pid).
	spawn(matrix_supervisor, restarter, []).
	
shutdown()->
	matrix_server ! shutdown.

upgrade()->
	matrix_server ! sw_upgrade.

get_version()->
	MsgRef = make_ref(),
	matrix_server ! {self(),MsgRef,get_version},
	receive
		{MsgRef,VersionIdentifier}->
		VersionIdentifier
	end.
	
mult(Mat1,Mat2)->
	MsgRef = make_ref(),
	matrix_server ! {self(),MsgRef,{multiple,Mat1,Mat2}},
	receive
		{MsgRef,Mat} ->
			Mat
	end.
	
explanation() ->
	{"Answer: We need to put the restarter server and the server in differents modules in order to compile the server module 
	more multiple times without killing the restarter. We notices that when we compile multiple time it crashes. This way, we keep the server alive"}.

	

