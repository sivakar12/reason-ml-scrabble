type tile = {
    letter: char,
    value: int
};

type multiplier = 
  | DoubleLetter
  | TripleLetter
  | DoubleWord
  | TripleWord
  | NoMultiplier;

type boardPlacement = 
| NewPlacement(tile)
| CommittedPlacement(tile)
| NoPlacement

type square = (boardPlacement, multiplier);

type row = list(square);

type board = list(row);

type bag = list(tile);

type tray = list(tile);