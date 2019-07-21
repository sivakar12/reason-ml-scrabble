
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
        switch(context.state.connection) {
            | Some(connection) => {
                context.dispatch(ChangeGameState(Sending));
                let putPromise = Firebase.putNewMove(context.state.dataToSend, connection);
                let _ = putPromise |> Js.Promise.then_(() => {
                    context.dispatch(ChangeGameState(Receiving));
                    Js.Promise.resolve(())
                });
            }
            | None => ()
        }
        None;
    }, [|context.state.dataToSend|])
}

let useGameStarter = (context: Context.contextType) => {
    React.useEffect1(() => {
        switch(context.state.connection, context.state.gameState) {
            | (Some((gameId, "1")), NotStarted) => {
                Js.log("Creating game in firebase with id " ++ gameId);
                let _ = Firebase.createGame(gameId) |> Js.Promise.then_(() => {
                    context.dispatch(ChangeGameState(Playing));
                    context.dispatch(FillTray);
                    Js.Promise.resolve(())
                });
                ()
            }
            | (Some((gameId, "2")), NotStarted) => {
                Js.log("Joining game in firebase with id " ++ gameId);
                let _ = Firebase.joinGame(gameId) |> Js.Promise.then_(() => {
                    context.dispatch(ChangeGameState(Receiving));
                    context.dispatch(FillTray);
                    Js.Promise.resolve(())
                });
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