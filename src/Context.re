open SharedTypes;

type contextType = {
    board: board,
    tray: tray
};
let startingBoard = Rules.make_board();
let emptyTray = Rules.emptyTray;

let startingContext = {
    board: startingBoard,
    tray: emptyTray
}
let context = React.createContext(startingContext);

module Provider = {
  let makeProps = (~value, ~children, ()) => {"value": value, "children": children}
  let make = React.Context.provider(context);
}

[@react.component]
let make = (~children) => {
    
    let (board, _) = React.useState(() => startingBoard);
    let (tray, _) = React.useState(() => emptyTray);

    let contextValue = {
        board: board,
        tray: tray
    };

    <Provider value=contextValue>
        <h1>{"Context" |> ReasonReact.string}</h1>
        {children}
    </Provider>
};