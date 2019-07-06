open SharedTypes;

[@react.component]
let make = (~square) => {
    let emptySquareStyle = ReactDOMRe.Style.make(
        ~height="60px",
        ~width="60px",
        ~backgroundColor="#239f95",
        ()
    );
    switch(square) {
    | Tile(tile) => <Tile tile />
    | Empty => <div style=emptySquareStyle></div>
    }
}