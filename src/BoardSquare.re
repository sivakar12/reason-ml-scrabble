open SharedTypes;

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