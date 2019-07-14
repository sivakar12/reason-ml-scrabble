let useChangeListener = (_context: Context.contextType) => {
    React.useEffect1(() => {
        Js.log("Registering listener for changes");
        Some(() => {
            Js.log("Unregistering listener for changes");
        })
    }, [||])
}

let useChangeSender = (context: Context.contextType) => {
    React.useEffect1(() => {
        switch(context.state.dataToSend) {
            | Some(dataToSend) => {
                Js.log("Sending data");
                Js.log(dataToSend);
                let _ = Js.Global.setTimeout(() => {
                    context.dispatch(ChangeGameState(Receiving));
                    let _ = Js.Global.setTimeout(() => {
                        context.dispatch(RegisterOpponentsMove([], []));
                        ();
                    }, 2000);
                    ();
                }, 2000);
                None
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
                context.dispatch(ChangeGameState(Playing))


            }
            | (Some((gameId, "2")), NotStarted) => {
                Js.log("Joining game in firebase with id " ++ gameId);
                context.dispatch(ChangeGameState(Receiving))
            }
            | _ => ()
        };
        None
    }, [|context.state.connection|])
}

let useFirebaseEffects = (context: Context.contextType) => {
    useGameStarter(context);
    useChangeListener(context);
    useChangeSender(context);
}