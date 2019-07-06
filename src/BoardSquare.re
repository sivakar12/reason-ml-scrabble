open SharedTypes;


[@react.component]
let make = (~square: square) => {
    let style = ReactDOMRe.Style.make(
        ~border="solid black 1px",
        ()
    )
    let content = switch(square) {
    | (Some(tile), _) => <Tile tile/>
    | (None, Some(multiplier)) => <EmptySquare multiplier/>
    | (None, None) => <EmptySquare/>
    };
    <div className="board-square" style>
        {content}
    </div>
};