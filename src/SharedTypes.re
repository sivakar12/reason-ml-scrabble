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

type square = (option(tile), multiplier);

type row = list(square);

type board = list(row);

type bag = list(tile);

type tray = list(tile);