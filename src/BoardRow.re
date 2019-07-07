open SharedTypes;

[@react.component]
let make = (~row: row, ~x: int) => {
    let style = ReactDOMRe.Style.make(
        ~display="flex",
        ~flexDirection="row",
        ()
    );
    <div className="board-row" style=style>
        {row
        |> List.mapi((index:int, square: square) => <BoardSquare key=string_of_int(index) x y=index square/>)
        |> Array.of_list
        |> ReasonReact.array}
    </div>
};