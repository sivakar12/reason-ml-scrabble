let split = (l: list('a), splitter: 'a): list(list('a)) => {
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
    List.fold_left(reducer, accumulator, l |> List.rev)
}