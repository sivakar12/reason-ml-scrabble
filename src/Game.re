let globalStyle = ReactDOMRe.Style.make(
    ~userSelect="none",
    ()
);

[@react.component]
let make = () => {
    let context = React.useContext(Context.context);
    React.useEffect1(() => { context.dispatch(FillTray); None}, [||]);
    <div style=globalStyle>
        <Board/>
        <Tray/>
        <Controls/>
    </div>
}