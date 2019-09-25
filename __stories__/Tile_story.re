
let tile: SharedTypes.tile = { letter: 'A', value: 2 };

open BsStorybook.Story;

let _module = [%bs.raw "module"];

storiesOf("Tile", _module)
|. add("Committed", () =>
     <Tile tile committed=false />
   );