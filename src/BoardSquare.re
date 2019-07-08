open SharedTypes;

let style = ReactDOMRe.Style.make(
    ~border="solid black 1px",
    ()
);

[@react.component]
let make = (~square: square, ~x: int, ~y: int) => {

    let context = React.useContext(Context.context);

    let content = switch(square) {
    | (ThisMoveTile(tile), _) => <Tile tile committed=false/>
    | (CommittedTile(tile), _) => <Tile tile/>
    | (Empty, Some(multiplier)) => <EmptySquare multiplier/>
    | (Empty, None) => <EmptySquare/>
    };

    <div className="board-square" style onClick={_event => context.dispatch(ClickBoard(x, y))}>
        {content}
    </div>
};