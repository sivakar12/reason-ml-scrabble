open SharedTypes;

[@react.component]
let make = (~row: row, ~x: int) => {
    <div className="board-row">
        {row
        |> List.mapi((index:int, square: square) => <BoardSquare key=string_of_int(index) x y=index square/>)
        |> Array.of_list
        |> ReasonReact.array}
    </div>
};