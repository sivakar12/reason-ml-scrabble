open SharedTypes;

let multiplier_to_string = (multiplier) => {
    switch (multiplier) {
        | DoubleLetter => "DL"
        | TripleLetter => "TL"
        | DoubleWord => "DW"
        | TripleWord => "TW"
        | NoMultiplier => ""
    };
};

[@react.component]
let make = (~multiplier = ?) => {
    let content = switch(multiplier) {
        | Some(m) => m |> multiplier_to_string |> ReasonReact.string
        | None => ReasonReact.string("")
    };
    let multiplierCssClass = switch(multiplier) {
        | Some(m) => " multiplier multiplier-" ++ (m |> multiplier_to_string |> String.lowercase)
        | None => ""
    };
    let classString = "empty-square" ++ multiplierCssClass;
    <div className=classString>{content}</div>
}