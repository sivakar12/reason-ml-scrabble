open SharedTypes;


[@react.component]
let make = (~square: square, ~x: int, ~y: int) => {
    let style = ReactDOMRe.Style.make(
        ~border="solid black 1px",
        ()
    )
    let content = switch(square) {
    | (Some(tile), _) => <Tile tile/>
    | (None, Some(multiplier)) => <EmptySquare multiplier/>
    | (None, None) => <EmptySquare/>
    };
    // let handleClick: () =>  {
    //     Js.log(x, y);
    // };
    <div className="board-square" style onClick={_event => Js.log((x, y));}>
        {content}
    </div>
};