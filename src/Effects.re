
let useFirebase = () => {
    React.useEffect1(() => {
        Firebase.startFirebase();
        None
    }, [||])
}
let useChangeListener = (context: Context.contextType) => {
    React.useEffect1(() => {
        switch(context.state.connection) {
            | Some((_gameId, _playerId)) => {
                Js.log("Registering listener for changes");
                Some(() => {
                    Js.log("Unregistering listener for changes");
                })
            }
            | _ => None
        }
    }, [|context.state.connection|])
}

let useChangeSender = (context: Context.contextType) => {
    React.useEffect1(() => {
        switch(context.state.dataToSend) {
            | Some(dataToSend) => {
                Js.log("Sending data");
                Js.log(dataToSend);
                let putPromise = Firebase.putNewMove(dataToSend, Belt.Option.getExn(context.state.connection));
                let _ = putPromise |> Js.Promise.then_(() => {
                    context.dispatch(ChangeGameState(Receiving));
                    let _ = Js.Global.setTimeout(() => {
                        context.dispatch(RegisterOpponentsMove([], []));
                        ();
                    }, 2000);
                    Js.Promise.resolve(())
                }) |> Js.Promise.catch(err => {
                    Js.log("Error sending to firebase");
                    Js.log(err);
                    Js.Promise.resolve(())
                });
                None;
            }
            | _ => None
        }
    }, [|context.state.dataToSend|])
}

let useGameStarter = (context: Context.contextType) => {
    React.useEffect1(() => {
        switch(context.state.connection, context.state.gameState) {
            | (Some((gameId, "1")), NotStarted) => {
                Js.log("Creating game in firebase with id " ++ gameId);
                Firebase.createGame(gameId);
                context.dispatch(ChangeGameState(Playing))

            }
            | (Some((gameId, "2")), NotStarted) => {
                Js.log("Joining game in firebase with id " ++ gameId);
                Firebase.joinGame(gameId);
                context.dispatch(ChangeGameState(Receiving))
            }
            | _ => ()
        };
        None
    }, [|context.state.connection|])
}

let useFirebaseEffects = (context: Context.contextType) => {
    useFirebase();
    useGameStarter(context);
    useChangeListener(context);
    useChangeSender(context);
}