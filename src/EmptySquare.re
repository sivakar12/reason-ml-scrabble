open SharedTypes;

let multiplier_to_string = (multiplier) => {
    switch (multiplier) {
        | DoubleLetter => "DL"
        | TripleLetter => "TL"
        | DoubleWord => "DW"
        | TripleWord => "TW"
    };
};

[@react.component]
let make = (~multiplier = ?) => {
    let style = ReactDOMRe.Style.make(
        ~height="60px",
        ~width="60px",
        ~backgroundColor="#239f95",
        ~display="flex",
        ~alignItems="center",
        ~justifyContent="center",
        ()
    );
    let content = switch(multiplier) {
        | Some(m) => m |> multiplier_to_string |> ReasonReact.string
        | None => ReasonReact.string("")
    };
    <div style=style>{content}</div>
}