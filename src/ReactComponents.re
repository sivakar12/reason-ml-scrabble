open SharedTypes;

module Tile = {
    [@react.component]
    let make = (~tile, ~committed=true) => {
        let tileClass = "tile " ++ (committed ? "tile-committed" : "tile-not-committed");
        <div className=tileClass>
            <div className="tile-letter">
                {tile.letter |> String.make(1) |> ReasonReact.string}
                <sub className="tile-value">{tile.value |> string_of_int |> ReasonReact.string}</sub>
            </div>
        </div>
    }
}

module EmptySquare = {
    let multiplier_to_string = (multiplier) => {
        switch (multiplier) {
            | DoubleLetter => "DL"
            | TripleLetter => "TL"
            | DoubleWord => "DW"
            | TripleWord => "TW"
            | NoMultiplier => ""
        };
    };

    [@react.component]
    let make = (~multiplier = ?) => {
        let content = switch(multiplier) {
            | Some(m) => m |> multiplier_to_string |> ReasonReact.string
            | None => ReasonReact.string("")
        };
        let multiplierCssClass = switch(multiplier) {
            | Some(m) => " multiplier multiplier-" ++ (m |> multiplier_to_string |> String.lowercase)
            | None => ""
        };
        let classString = "empty-square" ++ multiplierCssClass;
        <div className=classString>{content}</div>
    }
}

// TODO: Not presentational. Make presentational
module BoardSquare = {
    [@react.component]
    let make = (~square: square, ~x: int, ~y: int) => {

        let context = React.useContext(Context.context);

        let content = switch(square) {
        | (NewPlacement(tile), _) => <Tile tile committed=false/>
        | (CommittedPlacement(tile), _) => <Tile tile/>
        | (NoPlacement, multiplier) => <EmptySquare multiplier/>
        };

        <div className="square" onClick={_event => context.dispatch(ClickBoard(x, y))}>
            {content}
        </div>
    };
}

module BoardRow = {
    [@react.component]
    let make = (~row: row, ~x: int) => {
        <div className="board-row">
            {row
            |> List.mapi((index:int, square: square) => <BoardSquare key=string_of_int(index) x y=index square/>)
            |> Array.of_list
            |> ReasonReact.array}
        </div>
    };
}

module Board = {
    [@react.component]
    let make = () => {
        let context = React.useContext(Context.context);
        let board = context.state.board;
        <div className="board">
            {board
            |> List.mapi((index: int, row: row) => <BoardRow key=string_of_int(index) x=index row/>)
            |> Array.of_list
            |> ReasonReact.array
            }
        </div>
    };
}

module Tray = {
    [@react.component]
    let make = () => {
        let context = React.useContext(Context.context);
        let tray: tray  = context.state.tray;
        let selected = context.state.selectedTrayItem;

        let makeStyleFromIndex = (i: int) => {
            let border = switch(selected) {
                | Some(selected) => (i == selected) ? "4px solid red" : "4px solid white"
                | None => "4px solid white"
            };
            ReactDOMRe.Style.make(
                ~border=border,
                ()
            )
        }

        let makeTileOfTray = (index: int, tile: tile) => 
            <div
                onClick={_event => context.dispatch(ClickTray(index))}
                style=makeStyleFromIndex(index)
                key=string_of_int(index)
            >
                <Tile tile/>
            </div>;

        <div className="tray">
            {tray
            |> List.mapi(makeTileOfTray)
            |> Array.of_list
            |> ReasonReact.array
            }
            // <div>{"Selected: " |> ReasonReact.string }{ (selected -> Belt.Option.getWithDefault(-1) |> string_of_int |> ReasonReact.string)}</div>
        </div>
    }
}

module Controls = {
    [@react.component]
    let make = () => {
        let context = React.useContext(Context.context);
        <div>
            <button onClick={_event => context.dispatch(CommitNewPlacements)}>{"Commit" -> ReasonReact.string}</button>
            <button onClick={_event => context.dispatch(RejectNewPlacements)}>{"Recall" -> ReasonReact.string}</button>
            <br/>
            <div>{ "Bag Size: " |> ReasonReact.string } { context.state.bag |> List.length |> string_of_int |> ReasonReact.string }</div>
        </div>
    }
}

module Status = {
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
}