type tile = {
    letter: char,
    value: int
};
type multiplier = 
  | None
  | DoubleLetter
  | TripleLetter
  | DoubleWord
  | TripleWord;

type square =
  | Tile(tile)
  | Empty;

type row = list(square);

type board = list(row);