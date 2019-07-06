open SharedTypes;

[@react.component]
let make = (~board: board) => {
    <div className="board">
        {board
        |> List.mapi((index: int, row: row) => <BoardRow key=string_of_int(index) row/>)
        |> Array.of_list
        |> ReasonReact.array
        }
    </div>
};