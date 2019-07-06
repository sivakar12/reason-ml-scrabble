open SharedTypes;

[@react.component]
let make = () => {

    let a = { letter: 'A', value: 1 };
    let b = { letter: 'B', value: 2 };

    let row1 = [Empty, Empty, Empty];
    let row2 = [Empty, Tile(a), Tile(b)];
    let row3 = [Empty, Empty, Empty];
    let board = [row1, row2, row3];

    let bag1 = Rules.make_tile_bag();
    let tray = [];
    let (bag2, tray) = Rules.pick_tile_to_tray(bag1, tray);
    let (bag3, tray) = Rules.pick_tile_to_tray(bag2, tray);
    let (_, tray) = Rules.pick_tile_to_tray(bag3, tray);

    <div>
        <h1>{ReasonReact.string("Scrabble")}</h1>
        <div id="board">
            {board
            |> List.mapi((index: int, row: row) => <BoardRow key=string_of_int(index) row/>)
            |> Array.of_list
            |> ReasonReact.array
            }
        </div>
        <h2>{ReasonReact.string("Tray")}</h2>
        <div id="tray">
            <Tray tray/>
        </div>
    </div>;
}