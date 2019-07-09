let globalStyle = ReactDOMRe.Style.make(
    ~userSelect="none",
    ()
);

[@react.component]
let make = () => {
    <div style=globalStyle>
        <Board/>
        <Tray/>
        <Controls/>
    </div>
}