type tile = {
    letter: char,
    value: int
};

type multiplier = 
  | DoubleLetter
  | TripleLetter
  | DoubleWord
  | TripleWord;

type boardPlacement = 
| ThisMoveTile(tile)
| CommittedTile(tile)
| Empty

type square = (boardPlacement, option(multiplier));

type row = list(square);

type board = list(row);

type bag = list(tile);

type tray = list(tile);