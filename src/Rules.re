open SharedTypes;

let boardSize = 15
let traySize = 7


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

let char_of_square = (square: square): char => {
    let placement = fst(square);

    switch(placement) {
        | NewPlacement(tile) => tile.letter
        | CommittedPlacement(tile) => tile.letter
        | _ => 'x'
    }
}

module Initialization = {
    type tileSpec = (char, int, int);
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

    let make_board = (): board => 
    Belt.List.makeBy(15, x => 
        Belt.List.makeBy(15, y => 
            (NoPlacement, get_multiplier(x, y))
        )
    );
}

module Placement = {    
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
}


module WordFinding {
    let get_rows_and_columns_with_new_placements = (board: board): (list(int), list(int)) => {
        let newPlacements = get_new_placements_flattened(board);
        
        let rows = newPlacements |> List.map(((x, _, _)) => x) |>  Array.of_list |>  Belt.Set.Int.fromArray |> Belt.Set.Int.toList;
        let columns = newPlacements |> List.map(((_, y, _)) => y) |> Array.of_list |> Belt.Set.Int.fromArray |> Belt.Set.Int.toList;

        (rows, columns)
    }

    let get_squares_in_row = (board: board, row: int): list(square) => {
        List.nth(board, row)
    }

    let get_squares_in_column = (board: board, column: int): list(square) => {
        board |> List.map(row => List.nth(row, column))
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

    let get_words_from_square_list = (line: list(square)): list(list(square)) => {
        line |> Utils.split_by(t => !is_tile(t))
    }

    let word_contains_new_tile = (word: list(square)): bool => {
        Utils.any(is_new_placement, word)
    }

    let word_to_be_considered = (word: list(square)): bool => {
        Utils.any(is_new_placement, word) && List.length(word) > 1
    }

    let get_words_to_score = (board: board): list(list(square)) => {
        let (rows, cols) = get_rows_and_columns_with_new_placements(board);
        let rowSquaresList = rows |> List.map(get_squares_in_row(board));
        let columnSquaresList = cols |> List.map(get_squares_in_column(board));
        let listOfSquares = List.concat([rowSquaresList, columnSquaresList]);

        let wordsToScore = listOfSquares |> List.map(get_words_from_square_list) |> List.flatten |>
            List.filter(word_to_be_considered);
        let _ = wordsToScore |> List.map(word => {
            Js.log(word |> List.map(char_of_square) |> Utils.string_from_char_list)
        });
        wordsToScore
    }
}

module Validations {
    let all_same = (l: list('a)): bool => {
        let head = Belt.List.head(l);
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

    let word_in_dict = (word: list(square)): bool => {
        open Belt.HashSet.String;
        let chars = word |> List.map(char_of_square);
        let string = Utils.string_from_char_list(chars);
        Js.log("Checking if " ++ string ++ " is in dict");
        let result = Words.wordsSet -> has(string);
        Js.log(result);
        result
    }

    let all_words_in_dict = (board: board): bool => {
        let words = WordFinding.get_words_to_score(board);
        List.for_all(word_in_dict, words)
    }
    // Not complete
    let placements_valid = (board: board): bool => {
        (all_in_one_row(board) || all_in_one_column(board)) && all_words_in_dict(board);
    }
}


module Scoring {
    let apply_letter_multiplier = (square: square): int => {
        let (placement, multiplier) = square;
        let multiplierValue = switch(multiplier) {
            | DoubleLetter => 2
            | TripleLetter => 3
            | _ => 1
        };
        let tileValue = switch(placement) {
            | NewPlacement(tile) | CommittedPlacement(tile) => tile.value
            | _ => 0
        };
        multiplierValue * tileValue
    }

    let apply_word_multipliers = (word: list(square)): int => {
        let multiplierValue = multiplier => switch(multiplier) {
            | DoubleWord => 2
            | TripleWord => 3
            | _ => 1
        };
        let multipliers = word |> List.map(snd);
        let multipliersProduct = multipliers |> List.map(multiplierValue) |> List.fold_left((a, i) => a * i, 1);
        let scoreFromLetterMultipliers = word |> List.map(apply_letter_multiplier) |> List.fold_left((a, i) => a + i, 0);
        let score = scoreFromLetterMultipliers * multipliersProduct;
        score
        
    }
    let get_score_for_word = (word: list(square)): int => {
        apply_word_multipliers(word)
    }
}


let validate_and_get_score = (board: board): option(int) => {
    if (!Validations.placements_valid(board)) {
        None
    } else {
        let words = WordFinding.get_words_to_score(board)
        let finalScore = words |> List.map(Scoring.get_score_for_word) |> List.fold_left((a, i) => a + i, 0)
        Some(finalScore)
    }
}