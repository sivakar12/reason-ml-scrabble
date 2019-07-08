open SharedTypes;

[@react.component]
let make = () => {
    let context = React.useContext(Context.context);
    let board = context.state.board;
    <div className="board">
        {board
        |> List.mapi((index: int, row: row) => <BoardRow key=string_of_int(index) x=index row/>)
        |> Array.of_list
        |> ReasonReact.array
        }
    </div>
};