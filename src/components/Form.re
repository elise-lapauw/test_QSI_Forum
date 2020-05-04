[@bs.module "../img/user.png"] external logo: string = "default";
type ctx = {
  input: string,
  utilisateur: string,
};
let bouton =
  ReactDOMRe.Style.make(
    ~float="right",
    ~clear="right",
    ~textDecoration="none",
    ~fontWeight="bold",
    ~fontSize="18px",
    ~color="#799dec",
    ~border="none",
    ~backgroundColor="white",
    ~textShadow=
      "0px 4px 2px rgba(0, 0, 0, 0.32), 0px 1px 0px #6182ca, 0px 2px 0px #4f6aa7, 0px 3px 0px #5470ad",
    (),
  );
let image =
  ReactDOMRe.Style.make(
    ~visibility="hidden",
    ~height="1px",
    ~width="1px",
    (),
  );

let title =
  ReactDOMRe.Style.make(~fontSize="xxx-large", ~textAlign="center", ());
let component = ReasonReact.statelessComponent("Form");

module Styles = {
  let card =
    ReactDOMRe.Style.make(
      ~float="right",
      ~clear="right",
      ~border="2px solid #898989",
      ~borderRadius="4px",
      ~padding="1rem",
      (),
    );
};

let make = (~ctx: ctx, ~appSend, _children) => {
  ...component,
  render: _self =>
    <form
      onSubmit=(
        ev => {
          ReactEvent.Form.preventDefault(ev);
          appSend(Root.UpdateInput(ctx.input, ctx.utilisateur));
          appSend(Root.Search);
        }
      )>
      <h1 style=title> (React.string("Forum " ++ ctx.input)) </h1>
      <button style=bouton type_="submit"> (React.string("Refresh")) </button>
      <img
        style=image
        src=logo
        alt=""
        onLoad=(
          ev => {
            appSend(Root.UpdateInput(ctx.input, ctx.utilisateur));
            appSend(Root.Search);
          }
        )
      />
    </form>,
};
/**
 * This is a wrapper created to let this component be used from the new React api.
 * Please convert this component to a [@react.component] function and then remove this wrapping code.
 */
let make =
  ReasonReactCompat.wrapReasonReactForReact(
    ~component,
    (
      reactProps: {
        .
        "appSend": 'appSend,
        "ctx": 'ctx,
        "children": 'children,
      },
    ) =>
    make(
      ~appSend=reactProps##appSend,
      ~ctx=reactProps##ctx,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (~children: 'children, ~ctx: 'ctx, ~appSend: 'appSend, unit) =>
  {
    .
    "appSend": 'appSend,
    "ctx": 'ctx,
    "children": 'children,
  } =
  "";
