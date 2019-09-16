let split = (splitter: 'a, l: list('a)): list(list('a)) => {
    let accumulator: list(list('a)) = [[]];
    let reducer = (accumulator: list(list('a)), item: 'a): list(list('a)) => {
        if (item == splitter) {
            [[], ...accumulator]
        } else { 
            switch(List.hd(accumulator), List.tl(accumulator)) {
                | (head, tail) => {
                    [[item, ...head], ...tail]
                } 
            }
        }
    };
    List.fold_left(reducer, accumulator, l |> List.rev) |> List.filter(l => l != [])
}

let split_by = (splitter: 'a => bool, l: list('a)): list(list('a)) => {
    let accumulator: list(list('a)) = [[]];
    let reducer = (accumulator: list(list('a)), item: 'a): list(list('a)) => {
        if (splitter(item)) {
            [[], ...accumulator]
        } else { 
            switch(List.hd(accumulator), List.tl(accumulator)) {
                | (head, tail) => {
                    [[item, ...head], ...tail]
                } 
            }
        }
    };
    List.fold_left(reducer, accumulator, l |> List.rev) |> List.filter(l => l != [])
}

let any = (predicate: 'a => bool, l: list('a)): bool => {
    let reducer = (accumulator: bool, item: 'a) => {
        if (predicate(item)) {
            true
        } else {
            accumulator
        }
    };
    List.fold_left(reducer, false, l)
}

let string_from_char_list = (chars: list(char)): string => {
    chars |> List.map(String.make(1)) |> List.fold_left((a, i) => a ++ i, "")
}