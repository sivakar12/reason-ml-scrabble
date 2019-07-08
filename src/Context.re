type contextType = {
    state: Reducer.reducerState,
    dispatch: Reducer.action => unit
};
let startingContext = {
    state: Reducer.initialState,
    dispatch: (_: Reducer.action) => ()
};

let context = React.createContext(startingContext);

module Provider = {
  let makeProps = (~value, ~children, ()) => {"value": value, "children": children}
  let make = React.Context.provider(context);
}

[@react.component]
let make = (~children) => {
    let (state, dispatch) = React.useReducer(Reducer.reducer, Reducer.initialState);
 
    let contextValue = {
        state: state,
        dispatch: dispatch
    };

    <Provider value=contextValue>
        {children}
    </Provider>
};