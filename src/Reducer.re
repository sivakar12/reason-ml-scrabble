open SharedTypes;

type reducerState = {
    bag: bag,
    board: board,
    tray: tray,
    selectedTrayItem: option(int),
    gameState: gameState,
    connection: option(connection),
    dataToSend: option(dataToSend)
}

type action = 
| ClickTray(int)
| ClickBoard(int, int)
| FillTray
| CommitNewPlacements
| RejectNewPlacements
| RegisterOpponentsMove(newPlacements, bagRemovals)
| StartGame(gameId)
| JoinGame(gameId)
| ChangeGameState(gameState)

let initialState: reducerState = {
    bag: Rules.make_tile_bag(),
    board: Rules.make_board(),
    tray: Rules.emptyTray,
    selectedTrayItem: None,
    gameState: NotStarted,
    connection: None,
    dataToSend: None
}

let reducer = (state: reducerState, action: action): reducerState => {
    switch((state.gameState, action)) {
        | (NotStarted, StartGame(id)) => {
            {...state, connection: Some((id, "1"))}
        }
        | (NotStarted, JoinGame(id)) => {
            {...state, connection: Some((id, "2"))}
        }
        | (Playing, ClickTray(index)) => {
            let selectedTrayItem = switch(state.selectedTrayItem) {
                | Some(_) => None
                | None => Some(index)
            };
            { ...state, selectedTrayItem}
        }
        | (Playing, ClickBoard(x, y)) => {
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
                                selectedTrayItem: None,
                            };
                        }
                        | None => state
                    }
                }
                | None => state
            }
        }
        | (Playing, FillTray) => {
            let numberToTake = Rules.traySize - List.length(state.tray);
            let (newBag, takenTiles) = Rules.take_from_bag(state.bag, numberToTake);
            // let (newBag, newTray) = Rules.fill_tray(state.bag, state.tray);
            {
                ...state,
                bag: newBag,
                tray: List.concat([state.tray, takenTiles])
            }

        }
        | (Playing, CommitNewPlacements) => {
            if (Rules.placements_valid(state.board)) {
                let newPlacements: newPlacements = (state.board |> List.mapi((x, row) => {
                    row |> List.mapi((y, square) => {
                        switch(square) {
                            | (NewPlacement(tile), _) => Some((tile, x, y))
                            | _ => None
                        }
                    })
                }) |> List.flatten) -> Belt.List.keepMap(x => x);

                let newBoard = state.board |> List.map(row => {
                    row |> List.map(square => {
                        switch(square) {
                            | (NewPlacement(tile), multiplier) => (CommittedPlacement(tile), multiplier)
                            | _ => square
                        }
                    })
                });
                let numberToTake = Rules.traySize - List.length(state.tray);
                let (newBag, takenTiles) = Rules.take_from_bag(state.bag, numberToTake)
                let dataToSend = Some((newPlacements, takenTiles));
                {
                    ...state, 
                    board: newBoard, 
                    bag: newBag, 
                    tray: List.concat([state.tray, takenTiles]),
                    gameState: Sending, 
                    dataToSend
                }
            } else {
                let (board, tray) = Rules.remove_new_tiles(state.board, state.tray);
                {...state, board, tray}
            }
        }
        | (Playing, RejectNewPlacements) => {
            let (board, tray) = Rules.remove_new_tiles(state.board, state.tray);
            {...state, board, tray}
        }
        | (Receiving, RegisterOpponentsMove(tilesPlacedOnBoard, tilesTakenFromBag)) => {
            let board = Belt.List.reduce(tilesPlacedOnBoard, state.board, 
                (board, (tile, x, y)) => Rules.add_tile_to_board(board, tile, x, y));
            let bag = Belt.List.reduce(tilesTakenFromBag, state.bag, (bag, tile) => Rules.remove_tile_from_bag(bag, tile));
            {...state, board, bag, gameState: Playing}
        }
        | (_, ChangeGameState(gameState)) => {
            switch(gameState) {
                | Receiving => {
                    ...state,
                    dataToSend: None,
                    gameState,
                }
                | _ => {...state, gameState }
            }
        }
        | _ => state
    }
}