type ctx = {
  input: string,
  utilisateur: string,
  text: string,
};
type answer = {success: string};
let decodemessage = json =>
  Json.Decode.{success: json |> field("success", string)};

let component = ReasonReact.statelessComponent("SendMessage");
let message =
  ReactDOMRe.Style.make(
    ~marginTop="10px",
    ~padding="10px",
    ~float="right",
    ~width="430px",
    ~clear="right",
    ~size="200px",
    ~marginRight="5%",
    ~border="1px solid grey",
    ~borderRadius="8px",
    ~height="130px",
    ~boxShadow="10px 5px 5px blue",
    (),
  );
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

let texte =
  ReactDOMRe.Style.make(~width="100%", ~height="85%", ~border="none", ());
module Styles = {
  let card =
    ReactDOMRe.Style.make(
      ~border="2px solid #898989",
      ~borderRadius="4px",
      ~padding="1rem",
      (),
    );
} /* appSend is pointing to its parent 'send'
      concept:
      https://medium.com/@elvesbane/revisiting-application-state-in-reasonreact-d80d440de56a
      */;

let make = (~ctx: ctx, ~appSend, _children) => {
  ...component,
  render: _self =>
    <form
      onSubmit=(
        ev => {
          ReactEvent.Form.preventDefault(ev);
          appSend(Root.UpdateInput(ctx.input, ctx.utilisateur));
          let payload = Js.Dict.empty();
          Js.Dict.set(payload, "idCours", Js.Json.string(ctx.input));
          Js.Dict.set(payload, "auteur", Js.Json.string(ctx.utilisateur));
          Js.Dict.set(payload, "texte", Js.Json.string(ctx.text));
          let value = "";
          appSend(Root.UpdateText(value));
          Js.Promise.(
            Fetch.fetchWithInit(
              "http://127.0.0.1:8080/message",
              Fetch.RequestInit.make(
                ~method_=Post,
                ~body=
                  Fetch.BodyInit.make(
                    Js.Json.stringify(Js.Json.object_(payload)),
                  ),
                ~headers=
                  Fetch.HeadersInit.make({
                    "Content-Type": "application/json",
                  }),
                (),
              ),
            )
            |> then_(Fetch.Response.json)
            |> ignore
          );

          appSend(Root.Search);
        }
      )>
      <div style=message>
        <textarea
          style=texte
          placeholder="Something to say ?"
          id="search"
          name="search "
          value=ctx.text
          onChange=(
            ev => {
              let value = ReactEvent.Form.target(ev)##value;
              appSend(Root.UpdateText(value));
            }
          )
        />
        <button style=bouton type_="submit">
          (React.string("ENVOYER"))
        </button>
      </div>
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
