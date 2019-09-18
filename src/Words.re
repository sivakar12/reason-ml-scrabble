let wordsFile: string = [%bs.raw {| require('../../../src/words.txt').default |}];
let words = Js.String.splitByRe([%re "/\\r?\\n/"], wordsFile) -> Belt.Array.keepMap(x => x);
let wordsSet = Belt.HashSet.String.fromArray(words);