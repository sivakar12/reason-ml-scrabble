

open BsStorybook.Story;

let _module = [%bs.raw "module"];

let containerStyle = ReactDOMRe.Style.make(
  ~height="6vmin",
  ~width="6vmin",
  ~margin="auto",
  ()
)
let containerDecorator = story =>
  <div style=containerStyle>{story()}</div>

let tile: SharedTypes.tile = { letter: 'A', value: 2 };

storiesOf("Tile", _module)
|. addDecorator(containerDecorator)
|. add("Committed", () =>
    <Tile tile committed=true />
  )
|. add("New Placement", () =>
    <Tile tile committed=false />
  )
