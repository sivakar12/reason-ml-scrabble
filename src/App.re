[@react.component]
let make = () => {

    let board = Rules.make_board()

    let bag1 = Rules.make_tile_bag();
    let tray = [];
    let (bag2, tray) = Rules.pick_tile_to_tray(bag1, tray);
    let (bag3, tray) = Rules.pick_tile_to_tray(bag2, tray);
    let (_, tray) = Rules.pick_tile_to_tray(bag3, tray);

    <div>
        <h1>{ReasonReact.string("Scrabble")}</h1>
        <Board board/>
        <h2>{ReasonReact.string("Tray")}</h2>
        <Tray tray/>
    </div>;
}