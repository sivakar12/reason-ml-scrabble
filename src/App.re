open SharedTypes;

/* let tileToString = (tile) => {
    switch(tile) {
    | None => ""
    | Tile(s, _) => String.make(1, s)
    }
} */

[@react.component]
let make = () => {
    let a = { letter: 'a', value: 1 };
    let b = { letter: 'b', value: 2 };
    let row1 = [Empty, Empty, Empty];
    let row2 = [Empty, Tile(a), Tile(b)];
    let row3 = [Empty, Empty, Empty];
    let board = [row1, row2, row3];

    <div>
        <h1>{ReasonReact.string("Scrabble")}</h1>
        {board
        |> List.mapi((index: int, row: row) => <BoardRow key=string_of_int(index) row/>)
        |> Array.of_list
        |> ReasonReact.array}
    </div>;
}