[@react.component]
let make = () => {
    let context = React.useContext(Context.context);
    let status = switch (context.state.gameState) {
        | Playing => "Place your move"
        | Sending => "Sending data"
        | Receiving => "Waiting for opponent"
        | NotStarted => "Start or join a game"
        | Finished => "Finished"
    } |> s => <div>{s |> ReasonReact.string}</div>;
    let gameId = switch(context.state.connection) {
        | Some((gameId, playerId)) => gameId ++ "#" ++ playerId
        | None => ""
    } |> s => <div>{s |> ReasonReact.string}</div>;
    <div>
        {status}
        {gameId}
        {"Score:" |> ReasonReact.string} {context.state.score |> string_of_int |> ReasonReact.string}
    </div>
    
}