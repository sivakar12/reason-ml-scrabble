open SharedTypes;

let style = ReactDOMRe.Style.make(
    ~display="flex",
    ~flexDirection="row",
    ()
);

[@react.component]
let make = () => {
    let context = React.useContext(Context.context);
    let tray: tray  = context.tray;
    let selected = context.selectedTrayItem;

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
            onClick={_event => context.selectTrayTile(index)}
            style=makeStyleFromIndex(index)
            key=string_of_int(index)
        >
            <Tile tile/>
        </div>;

    <div className="tray" style=style>
        {tray
        |> List.mapi(makeTileOfTray)
        |> Array.of_list
        |> ReasonReact.array
        }
        <button onClick={ _ => context.fillTray() }>{"Fill Tray" |> ReasonReact.string}</button>
    </div>
}