open SharedTypes;

type contextType = {
    board: board,
    tray: tray,
    selectTrayTile: int => unit,
    selectedTrayItem: option(int),
    selectBoardTile: (int, int) => unit,
    fillTray: unit => unit
};

let startingBoard = Rules.make_board();
let emptyTray = Rules.emptyTray;

let startingContext = {
    board: startingBoard,
    tray: emptyTray,
    selectTrayTile: (_: int) => (),
    selectedTrayItem: None,
    selectBoardTile: (_: int, _:int) => (),
    fillTray: () => ()
};

let context = React.createContext(startingContext);

module Provider = {
  let makeProps = (~value, ~children, ()) => {"value": value, "children": children}
  let make = React.Context.provider(context);
}

[@react.component]
let make = (~children) => {
    
    let (bag, setBag) = React.useState(() => Rules.make_tile_bag());
    let (board, _) = React.useState(() => startingBoard);
    let (tray, setTray) = React.useState(() => emptyTray);

    let (selectedTrayItem, setSelectedTrayItem) = React.useState((): option(int) => None);
    // let (selectedBoardSquare, setSelectedBoardSquare) = React.useState((): option((int, int)) => None);

    let contextValue = {
        board: board,
        tray: tray,
        selectTrayTile: (i: int) => {
            Js.log("Tray tile clicked: " ++ string_of_int(i));
            switch(selectedTrayItem) {
                |Some(_) => setSelectedTrayItem(_ => None)
                |None => setSelectedTrayItem(_ => Some(i))
            }
        },
        selectedTrayItem,
        selectBoardTile: (x: int, y:int) => {
            Js.log("Board square clicked: (" ++ string_of_int(x) ++ ", " ++ string_of_int(y) ++ ")");
        },
        fillTray: () => {
            let (newBag, newTray) = Rules.pick_tile_to_tray(bag, tray);
            setBag(_ => newBag);
            setTray(_ => newTray);
        }
    };

    <Provider value=contextValue>
        <h1>{"Context" |> ReasonReact.string}</h1>
        {children}
    </Provider>
};