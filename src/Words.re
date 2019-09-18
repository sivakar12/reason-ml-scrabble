let wordsFile: string = [%bs.raw {| require('../../../src/words.txt').default |}];
let words = Js.String.split("\n", wordsFile);

let wordsSet = Belt.HashSet.String.fromArray(words);
