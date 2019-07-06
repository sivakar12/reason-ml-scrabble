open SharedTypes;


[@react.component]
let make = (~square: square) => {
    let style = ReactDOMRe.Style.make(
        ~border="solid black 1px",
        ()
    )
    let content = switch(square) {
    | (Some(tile), _) => <Tile tile/>
    | (None, multiplier) => <Multiplier multiplier/>
    };
    <div className="board-square" style>
        {content}
    </div>
};