open SharedTypes;

[@react.component]
let make = (~square) => {
    switch(square) {
    | Tile(tile) => <span>{tile.letter |> String.make(1) |> ReasonReact.string}</span>
    | Empty => <span>{ReasonReact.string(".")}</span>
    }
}