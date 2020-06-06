-module(matrix_supervisor).

-export([restarter/0]).

restarter() ->
	process_flag(trap_exit, true),
	Pid = spawn_link(matrix_server, loop, []),
	register(matrix_server, Pid),
	receive
		{ 'EXIT' , Pid, shutdown } -> ok;
		{ 'EXIT' , Pid, _ } ->
			restarter();
		_Other ->
			restarter()	
	end.
 