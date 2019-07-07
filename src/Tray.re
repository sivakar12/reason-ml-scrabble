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

    let makeTileOfTray = (index: int, tile: tile) => 
        <div onClick={_event => context.selectTrayTile(index)}>
            <Tile
                key=string_of_int(index) 
                tile
            />
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