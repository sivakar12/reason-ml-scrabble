open SharedTypes;


[@react.component]
let make = (~square: square) => {
    let style = ReactDOMRe.Style.make(
        ~border="solid black 1px",
        ()
    )
    let content = switch(square) {
    | (Tile(tile), _) => <Tile tile/>
    | (Empty, multiplier) => <Multiplier multiplier/>
    };
    <div className="board-square" style>
        {content}
    </div>
};