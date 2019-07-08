open SharedTypes;

let style = ReactDOMRe.Style.make(
    ~border="solid black 1px",
    ()
);

[@react.component]
let make = (~square: square, ~x: int, ~y: int) => {

    let context = React.useContext(Context.context);

    let content = switch(square) {
    | (Some(tile), _) => <Tile tile/>
    | (None, Some(multiplier)) => <EmptySquare multiplier/>
    | (None, None) => <EmptySquare/>
    };

    <div className="board-square" style onClick={_event => context.dispatch(ClickBoard(x, y))}>
        {content}
    </div>
};