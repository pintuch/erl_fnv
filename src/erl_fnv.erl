-module(erl_fnv).
-on_load(init/0).
-export([fnv32/1,
	 fnv32a/1,
	 fnv64/1,
	 fnv64a/1
	]).

-define(APPNAME, erl_fnv).
-define(LIBNAME, erl_fnv).

%%====================================================================
%% API functions
%%====================================================================

-spec fnv32(binary()) -> non_neg_integer().
fnv32(_Data) ->
	erlang:nif_error(nif_not_loaded).

-spec fnv32a(binary()) -> non_neg_integer().
fnv32a(_Data) ->
	erlang:nif_error(nif_not_loaded).

-spec fnv64(binary()) -> non_neg_integer().
fnv64(_Data) ->
	erlang:nif_error(nif_not_loaded).

-spec fnv64a(binary()) -> non_neg_integer().
fnv64a(_Data) ->
	erlang:nif_error(nif_not_loaded).

%%====================================================================
%% Internal functions
%%====================================================================

init() ->
    SoName = case code:priv_dir(?APPNAME) of
        {error, bad_name} ->
            case filelib:is_dir(filename:join(["..", priv])) of
                true -> filename:join(["..", priv, ?LIBNAME]);
                _ -> filename:join([priv, ?LIBNAME])
            end;
        Dir -> filename:join(Dir, ?LIBNAME)
    end,
    erlang:load_nif(SoName, 0).
