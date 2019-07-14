open SharedTypes;

let globalStyle = ReactDOMRe.Style.make(
    ~userSelect="none",
    ()
);

[@react.component]
let make = () => {
    let context = React.useContext(Context.context);
    Effects.useFirebaseEffects(context);
    switch (context.state.gameState) {
        | NotStarted => <NewGame/>
        | _ => (
        <div style=globalStyle>
            <Status/>
            <Board/>
            <Tray/>
            <Controls/>
        </div>
        )
    }
}