open SharedTypes;

[@react.component]
let make = (~tray: tray) => {
    let style = ReactDOMRe.Style.make(
        ~display="flex",
        ~flexDirection="row",
        ()
    );
    <div className="tray" style=style>
        {tray
        |> List.mapi((index, tile) => <Tile key=string_of_int(index) tile />)
        |> Array.of_list
        |> ReasonReact.array
        }
    </div>
}