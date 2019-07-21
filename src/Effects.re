
let useFirebase = () => {
    React.useEffect1(() => {
        Firebase.startFirebase();
        None
    }, [||])
}
let useChangeListener = (context: Context.contextType) => {
    React.useEffect1(() => {
        switch(context.state.connection) {
            | Some((gameId, playerId)) => {
                Firebase.listenToMove((gameId, playerId), data => {
                    let (newMoves, takenTiles) = data
                    context.dispatch(RegisterOpponentsMove(newMoves, takenTiles))
                })
                Some(() => {
                    Firebase.stopListening((gameId, playerId));
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
                context.dispatch(ChangeGameState(Sending));
                let putPromise = Firebase.putNewMove(dataToSend, Belt.Option.getExn(context.state.connection));
                let _ = putPromise |> Js.Promise.then_(() => {
                    context.dispatch(ChangeGameState(Receiving));
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
                // TODO: Get a promise
                context.dispatch(ChangeGameState(Playing))

            }
            | (Some((gameId, "2")), NotStarted) => {
                Js.log("Joining game in firebase with id " ++ gameId);
                Firebase.joinGame(gameId);
                // TODO: Get a promise
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