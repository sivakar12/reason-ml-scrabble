open SharedTypes;

type reducerState = {
    bag: bag,
    board: board,
    tray: tray,
    selectedTrayItem: option(int)
}

type action = 
| ClickTray(int)
| ClickBoard(int, int)
| FillTray

let initialState: reducerState = {
    bag: Rules.make_tile_bag(),
    board: Rules.make_board(),
    tray: Rules.emptyTray,
    selectedTrayItem: None
}

let reducer = (state: reducerState, action: action): reducerState => {
    switch(action) {
        | ClickTray(index) => {
            let selectedTrayItem = switch(state.selectedTrayItem) {
                | Some(_) => None
                | None => Some(index)
            };
            { ...state, selectedTrayItem}
        }
        | ClickBoard(x, y) => {
            switch(state.selectedTrayItem) {
                | Some(selectedTrayItem) => {
                    let (newTray, takenTile) = Rules.take_tile_from_tray(state.tray, selectedTrayItem);
                    switch(takenTile) {
                        | Some(takenTile) => {
                            let newBoard = Rules.add_tile_to_board(state.board, takenTile, x, y);
                            {
                                ...state,
                                board: newBoard,
                                tray: newTray,
                                selectedTrayItem: None
                            };
                        }
                        | None => state
                    }
                }
                | None => state
            }
        }
        | FillTray => {
            let (newBag, newTray) = Rules.pick_tile_to_tray(state.bag, state.tray);
            {
                ...state,
                bag: newBag,
                tray: newTray
            }

        }
        // | _ => state
    }
}