open SharedTypes;

let multiplier_to_string = (multiplier) => {
    switch (multiplier) {
        | NoMultiplier => ""
        | DoubleLetter => "DL"
        | TripleLetter => "TL"
        | DoubleWord => "DW"
        | TripleWord => "TW"
    };
};

[@react.component]
let make = (~multiplier: multiplier) => {
    let style = ReactDOMRe.Style.make(
        ~height="60px",
        ~width="60px",
        ~backgroundColor="#239f95",
        ~display="flex",
        ~alignItems="center",
        ~justifyContent="center",
        ()
    );
    <div style=style>{multiplier |> multiplier_to_string |> ReasonReact.string}</div>
}