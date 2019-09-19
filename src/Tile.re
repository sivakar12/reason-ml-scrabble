open SharedTypes;

[@react.component]
let make = (~tile, ~committed=true) => {
    let tileClass = "tile " ++ (committed ? "tile-committed" : "tile-not-committed");
    <div className=tileClass>
        <div className="tile-letter">
            {tile.letter |> String.make(1) |> ReasonReact.string}
            <sub className="tile-value">{tile.value |> string_of_int |> ReasonReact.string}</sub>
        </div>
    </div>
}