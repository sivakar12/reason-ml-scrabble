open SharedTypes;

type tileSpec = (char, int, int);

let boardSize = 15
let traySize = 7
let make_tile_bag = () => {
    let tilesSpecs = [
        ('A', 1, 9),
        ('B', 3, 2),
        ('C', 3, 2),
        ('D', 2, 4),
        ('E', 1, 12),
        ('F', 4, 2),
        ('G', 2, 3),
        ('H', 4, 2),
        ('I', 1, 9),
        ('J', 8, 1),
        ('K', 5, 1),
        ('L', 1, 4),
        ('M', 3, 2),
        ('N', 1, 6),
        ('O', 1, 8),
        ('P', 3, 2),
        ('Q', 10, 1),
        ('R', 1, 6),
        ('S', 1, 4),
        ('T', 1, 6),
        ('U', 1, 4),
        ('V', 4, 2),
        ('W', 4, 2),
        ('X', 8, 1),
        ('Y', 4, 2),
        ('Z', 10, 1)
    ];
    tilesSpecs 
    |> List.map(spec => {
        let (letter, value, count) = spec;
        Belt.List.make(count, {letter, value});
    })
    |> List.flatten |> Belt.List.shuffle;
}

let emptyTray: tray = []

let get_multiplier = (x: int, y: int): multiplier => {
    let codedString = 
        "T..d...T...d..T" ++
        ".D...t...t...D." ++
        "..D...d.d...D.." ++
        "d..D...d...D..d" ++
        "....D.....D...." ++
        ".t...t...t...t." ++
        "..d...d.d...d.." ++
        "T..d...X...d..T" ++
        "..d...d.d...d.." ++
        ".t...t...t...t." ++
        "....D.....D...." ++
        "d..D...d...D..d" ++
        "..D...d.d...D.." ++
        ".D...t...t...D." ++
        "T..d...T...d..T";
    let letter = String.get(codedString, y * 15 + x);
    switch (letter) {
        | 'T' => TripleWord
        | 't' => TripleLetter
        | 'D' => DoubleWord
        | 'd' => DoubleLetter
        | _ => NoMultiplier
    }
}

// let apply_multilier = (multipliers: list(multiplier), tiles: list(tile)): int => {
// }
let rec take_from_bag = (bag: bag, n: int): (bag, list(tile)) => {
    switch ((bag, n)){
        | (_, 0) => (bag, [])
        | ([], _) => (bag, [])
        | ([tile, ...bag], n) => {
            let (bag, tiles) = take_from_bag(bag, n - 1);
            (bag, [tile, ...tiles])
        }
    }
}

let add_new_tile_to_board = (board: board, tile: tile, x: int, y: int, ): board => {
    board |> List.mapi((xi, row) => {
        row |> List.mapi((yi, square) => {
            (xi == x && yi == y) ?
                switch(square) {
                    | (NoPlacement, multiplier) => (NewPlacement(tile), multiplier)
                    | _ => square
                }
                : square
        })
    })
}

// TODO: refactor this with the above method
let add_opponent_tile_to_board = (board: board, tile: tile, x: int, y: int, ): board => {
    board |> List.mapi((xi, row) => {
        row |> List.mapi((yi, square) => {
            (xi == x && yi == y) ?
                switch(square) {
                    | (NoPlacement, multiplier) => (CommittedPlacement(tile), multiplier)
                    | _ => square
                }
                : square
        })
    })
}

let take_tile_from_tray = (tray: tray, index: int): (tray, option(tile)) => {
    let tileTaken = Belt.List.get(tray, index);
    switch(tileTaken) {
        | Some(tileTaken) => {
            let newTray = Belt.List.keep( tray, tile => tile != tileTaken );
            (newTray, Some(tileTaken))
        }
        | None => (tray, None)
    }
}

let make_board = (): board => 
    Belt.List.makeBy(15, x => 
        Belt.List.makeBy(15, y => 
            (NoPlacement, get_multiplier(x, y))
        )
    );


let map_board_with_coords = (board: board, f: (int, int, square) => 'a) => {
    board |> List.mapi((x, row) => {
        row |> List.mapi((y, square) => {
            f(x, y, square)
        })
    })
};

let get_new_placements_flattened = (board: board): list((int, int, square)) => {

    let optList = board |> List.mapi((x, row) => {
        row |> List.mapi((y, square) => {
            switch(square) {
                | (NewPlacement(_), _) => Some((x, y, square))
                | _ => None
            }
        })
    }) |> List.flatten;
    Belt.List.keepMap(optList, x => x)
};

let all_same = (l: list('a)): bool => {
    let head= Belt.List.head(l);
    switch(head) {
        | Some(head) => {
            l |> List.for_all(x => x == head)
        }
        | None => true
    }
}

let all_in_one_column = (board: board): bool => {
    get_new_placements_flattened(board) |> List.map(((x, _, _)) => x) |> all_same
}

let all_in_one_row = (board: board): bool => {
    get_new_placements_flattened(board) |> List.map(((_, y, _)) => y) |> all_same
}

let placements_valid = (board: board): bool => {
    // let newPlacements = get_new_placements_flattened(board);
    all_in_one_row(board) || all_in_one_column(board);
}

let get_row_or_column_with_new_placements = (board: board): (int, int) => {
    let newPlacements = get_new_placements_flattened(board);
    switch(all_in_one_column(board), all_in_one_row(board)) {
        | (true, false) => newPlacements |> List.map(((x, _, _)) => x) |> List.hd |> x => (x, -1)
        | (false, true) => newPlacements |> List.map(((_, y, _)) => y) |> List.hd |> y => (-1, y)
        | (true, true) => newPlacements |> List.hd |> ((x, y, _)) => (x, y)
        | _ => (-1, -1)
    }
}

let get_items_in_row = (board: board, row: int): list(square) => {
    map_board_with_coords(board, (x, _, square) => {
        if (x == row) {
            Some(square)
        } else {
            None
        }
    }) -> List.flatten -> Belt.List.keepMap(x => x)
}

let get_items_in_column = (board: board, column: int): list(square) => {
    map_board_with_coords(board, (_, y, square) => {
        if (y == column) {
            Some(square)
        } else {
            None
        }
    }) -> List.flatten -> Belt.List.keepMap(x => x)
}

let char_of_square = (square: square): char => {
    let placement = fst(square);
    switch(placement) {
        | NewPlacement(tile) => tile.letter
        | CommittedPlacement(tile) => tile.letter
        | _ => 'x'
    }
}



let is_new_placement = (square: square): bool => {
    switch (square) {
        | (NewPlacement(_), _) => true
        | _ => false
    }
}

let is_tile = (square: square): bool => {
    switch(square) {
        | (NewPlacement(_), _) | (CommittedPlacement(_), _) => true
        | _ => false
    }
}

let get_words_in_row_or_column = (line: list(square)): list(list(square)) => {
    line |> Utils.split_by(t => !is_tile(t))
}

let word_contains_new_tile = (word: list(square)): bool => {
    Utils.any(is_new_placement, word)
}

let find_the_word = (line: list(square)): list(square) => {
    let words = get_words_in_row_or_column(line);
    let theWord = words |> List.find(word_contains_new_tile);
    theWord
}

let get_squares_in_row_or_col = (board: board, (row: int, col: int)) : list(square) => {
    switch((row, col)) {
        | (-1, y) => get_items_in_column(board, y)
        | (x, -1) => get_items_in_row(board, x)
        | (x, y) => {
            let horizontal = get_items_in_column(board, y) |> find_the_word
            // Js.log(horizontal |> List.map(char_of_square) |> Utils.string_from_char_list)
            let vertical = get_items_in_row(board, x) |> find_the_word
            // Js.log(vertical |> List.map(char_of_square) |> Utils.string_from_char_list)

            if (List.length(horizontal) > List.length(vertical)) {
                horizontal
            } else {
                vertical
            }
        }
    }
}

let get_score = (board: board): int => {
    let (row, col) = get_row_or_column_with_new_placements(board);
    let line = get_squares_in_row_or_col(board, (row, col));
    let theWord =  find_the_word(line)
    Js.log(theWord |> List.map(char_of_square) |> Utils.string_from_char_list);
    0
}

let remove_new_tiles = (board: board, tray: tray) : (board, tray)=> {
    let newPlacementTiles: tray = get_new_placements_flattened(board) -> Belt.List.keepMap(((_, _, square)) => {
        switch(square) {
            | (NewPlacement(tile), _) => Some(tile)
            | _ => None
        }
    });
    let newTray: tray = List.concat([newPlacementTiles, tray]);
    let newBoard = board |> List.map(row => {
        row |> List.map(square => {
            switch(square) {
                | (NewPlacement(_), multiplier) => (NoPlacement, multiplier)
                | _ => square
            }
        })
    });
    (newBoard, newTray);
}

let rec remove_tile_from_bag(bag: bag, tile: tile): bag {
    switch(bag) {
        | [first, ...rest]  => {
            if (first == tile) { rest } else { [first, ...remove_tile_from_bag(rest, tile)]}
        }
        | [] => []
    }
}