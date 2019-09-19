open SharedTypes;

[@react.component]
let make = () => {
    let context = React.useContext(Context.context);
    let tray: tray  = context.state.tray;
    let selected = context.state.selectedTrayItem;

    let makeStyleFromIndex = (i: int) => {
        let border = switch(selected) {
            | Some(selected) => (i == selected) ? "4px solid red" : "4px solid white"
            | None => "4px solid white"
        };
        ReactDOMRe.Style.make(
            ~border=border,
            ()
        )
    }

    let makeTileOfTray = (index: int, tile: tile) => 
        <div
            onClick={_event => context.dispatch(ClickTray(index))}
            style=makeStyleFromIndex(index)
            key=string_of_int(index)
        >
            <Tile tile/>
        </div>;

    <div className="tray">
        {tray
        |> List.mapi(makeTileOfTray)
        |> Array.of_list
        |> ReasonReact.array
        }
        // <div>{"Selected: " |> ReasonReact.string }{ (selected -> Belt.Option.getWithDefault(-1) |> string_of_int |> ReasonReact.string)}</div>
    </div>
}