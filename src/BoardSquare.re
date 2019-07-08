open SharedTypes;

let style = ReactDOMRe.Style.make(
    ~border="solid black 1px",
    ()
);

[@react.component]
let make = (~square: square, ~x: int, ~y: int) => {

    let context = React.useContext(Context.context);

    let content = switch(square) {
    | (NewPlacement(tile), _) => <Tile tile committed=false/>
    | (CommittedPlacement(tile), _) => <Tile tile/>
    | (NoPlacement, Some(multiplier)) => <EmptySquare multiplier/>
    | (NoPlacement, None) => <EmptySquare/>
    };

    <div className="board-square" style onClick={_event => context.dispatch(ClickBoard(x, y))}>
        {content}
    </div>
};