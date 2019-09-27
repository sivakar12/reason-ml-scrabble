open SharedTypes;
open ReactComponents;

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
        <div className="game">
            <Board/>
            <div className="side">
                <Status/>
                <Controls/>
                <Tray/>
            </div>
        </div>
        )
    }
}