type tile = {
    letter: char,
    value: int
};

type multiplier = 
  | NoMultiplier
  | DoubleLetter
  | TripleLetter
  | DoubleWord
  | TripleWord;

type placement =
  | Tile(tile)
  | Empty;

type square = (placement, multiplier);

type row = list(square);

type board = list(row);

type bag = list(tile);

type tray = list(tile);