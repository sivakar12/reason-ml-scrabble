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
                None
            }
            | _ => None
        }
    }, [|context.state.dataToSend|])
}

let useGameStarter = (context: Context.contextType) => {
    React.useEffect1(() => {
        switch(context.state.gameId, context.state.gameState) {
            | (Some(id), MyTurn) => {
                Js.log("Creating game in firebase with id " ++ id);

            }
            | (Some(id), OpponentsTurn) => {
                Js.log("Joining game in firebase with id " ++ id);
            }
            | _ => ()
        };
        None
    }, [|context.state.gameId|])
}

let useFirebaseEffects = (context: Context.contextType) => {
    useGameStarter(context);
    useChangeListener(context);
    useChangeSender(context);
}