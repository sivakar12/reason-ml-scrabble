open SharedTypes;

[@react.component]
let make = (~tile) => {

    let tileStyle = ReactDOMRe.Style.make(
        ~backgroundColor="#fabc74",
        ~color="#eb5f5d",
        ~height="60px",
        ~width="60px",
        ~display="flex",
        ~alignItems="center",
        ~justifyContent="center",
        ()
    );
    let letterStyle = ReactDOMRe.Style.make(
        ~fontSize="30px",
       ()  
    );
    let valueStyle = ReactDOMRe.Style.make(
        ~fontSize="10px", 
        ()
    );
    <div style=tileStyle>
        <div style=letterStyle>
            {tile.letter |> String.make(1) |> ReasonReact.string}
            <sub style=valueStyle>{tile.value |> string_of_int |> ReasonReact.string}</sub>
        </div>
    </div>
}