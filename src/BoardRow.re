open SharedTypes;

[@react.component]
let make = (~row) => {
    <div>
        {row
        |> List.mapi((index:int, square: square) => <BoardSquare key=string_of_int(index) square/>)
        |> Array.of_list
        |> ReasonReact.array}
    </div>
};