[@react.component]
let make = () => {
    let context = React.useContext(Context.context);
    let status = switch (context.state.gameState) {
        | MyTurn => "Place your move"
        | OpponentsTurn => "Waiting for opponent"
        | NotStarted => "Start or join a game"
        | GameOver => "Finished"
    } |> s => <div>{s |> ReasonReact.string}</div>;
    let gameId = switch(context.state.gameId) {
        | Some(id) => id
        | None => ""
    } |> s => <div>{s |> ReasonReact.string}</div>;
    <div>
        {status}
        {gameId}
    </div>
    
}