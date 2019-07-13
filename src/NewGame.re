[@react.component]
let make = () => {
    let context = React.useContext(Context.context);

    let (id, setId) = React.useState(_ => "");
    let handleNewGame = _event => context.dispatch(StartGame("####", MyTurn));
    let handleInputChange = event => {
        let idInput: string = ReactEvent.Form.target(event)##value;
        setId(_ => idInput);
    }
    let handleJoinGame = _event => {
        context.dispatch(StartGame(id, OpponentsTurn));
    };
    <div>
        <button 
            onClick=handleNewGame
            >
            { "New Game" |> ReasonReact.string }
        </button>
        <input type_="text" onChange=handleInputChange/>
        <button onClick=handleJoinGame>{ "Join Game" |> ReasonReact.string }</button>
    </div>
}