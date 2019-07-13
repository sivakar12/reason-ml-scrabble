[@react.component]
let make = () => {
    let context = React.useContext(Context.context);
    <div>
        <button onClick={_event => context.dispatch(FillTray)}>{"Fill Tray" -> ReasonReact.string}</button>
        <button onClick={_event => context.dispatch(CommitNewPlacements)}>{"Commit" -> ReasonReact.string}</button>
        <button onClick={_event => context.dispatch(RejectNewPlacements)}>{"Reject" -> ReasonReact.string}</button>
    </div>
}