open SharedTypes;

type tileSpec = (char, int, int);

let boardSize = 15

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
    |> List.flatten;
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
let rec fill_tray = (bag: bag, tray: tray) => {
    let bagShuffled = Belt.List.shuffle(bag);
    let (newBag, newTray) = switch (bagShuffled: bag) {
        | [] => (bag, tray)
        | [newTile, ...newBag] => (newBag, [newTile, ...tray])
    };
    if (List.length(newTray) == 7 || List.length(bag) == 0) {
        (newBag, newTray)
    } else {
        fill_tray(newBag, newTray)
    }
} 

let add_tile_to_board = (board: board, tile: tile, x: int, y: int, ): board => {
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
let placements_valid = (board: board): bool => {
    let newPlacements = get_new_placements_flattened(board);
    let all_in_one_column = newPlacements |> List.map(((x, _, _)) => x) |> all_same;
    let all_in_one_row = newPlacements |> List.map(((_, y, _)) => y) |> all_same;
    all_in_one_row || all_in_one_column;
}