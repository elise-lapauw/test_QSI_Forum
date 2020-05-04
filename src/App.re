open Root;

let component = ReasonReact.reducerComponent("App");

let divprinc =
  ReactDOMRe.Style.make(
    ~float="right",
    ~clear="right",
    ~border="2px solid #898989",
    ~borderRadius="4px",
    ~padding="1rem",
    ~width="500px",
    ~height="1000px",
    ~overflow="auto",
    (),
  );
let make = _children => {
  ...component,
  initialState: () => initialAppState,
  reducer,
  render: ({state, send}) =>
    <div style=divprinc>
      <Form ctx={input: "in", utilisateur: "1"} appSend=send />
      <SendMessage
        ctx={input: "in", utilisateur: "1", text: state.text}
        appSend=send
      />
      <Results ctx={results: state.results} utilisateur="1" appSend=send />
    </div>,
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component, (reactProps: {. "children": 'children}) =>
    make(reactProps##children)
  );
[@bs.obj]
external makeProps: (~children: 'children, unit) => {. "children": 'children} =
  "";
