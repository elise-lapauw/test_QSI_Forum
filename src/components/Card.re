open Root;
[@bs.module "../img/user.png"] external logo: string = "default";
[@bs.module "../img/like.jpg"] external logo2: string = "default";
[@bs.module "../img/trash.jpg"] external logo3: string = "default";
[@bs.module "../img/up.jpg"] external up: string = "default";
[@bs.module "../img/down.png"] external down: string = "default";

let component = ReasonReact.statelessComponent("Card");
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
    ~overflow="hidden",
    (),
  );
let pied =
  ReactDOMRe.Style.make(
    ~fontSize="12px",
    ~marginLeft="5%",
    ~float="left",
    ~clear="left",
    (),
  );
let img =
  ReactDOMRe.Style.make(
    ~float="left",
    ~clear="left",
    ~width="50px",
    ~clipPath="ellipse(50% 50%)",
    ~marginRight="3%",
    (),
  );
let img2 =
  ReactDOMRe.Style.make(
    ~float="right",
    ~clear="right",
    ~width="50px",
    ~clipPath="ellipse(50% 50%)",
    ~marginRight="3%",
    (),
  );
let container =
  ReactDOMRe.Style.make(
    ~position="relative",
    ~textAlign="center",
    ~color="black",
    ~float="right",
    ~clear="right",
    ~width="50px",
    ~clipPath="ellipse(50% 50%)",
    (),
  );
let centered =
  ReactDOMRe.Style.make(
    ~position="absolute",
    ~top="50%",
    ~left="50%",
    ~transform="translate(-50%, -50%)",
    ~fontSize="15px",
    ~fontWeight="bold",
    (),
  );
let trash =
  ReactDOMRe.Style.make(
    ~float="right",
    ~clear="right",
    ~width="30px",
    ~clipPath="ellipse(50% 50%)",
    ~marginRight="3%",
    (),
  );

let make =
    (
      ~idmessage,
      ~texte,
      ~dateenvoi,
      ~idcours,
      ~auteur,
      ~nblikes,
      ~isliked,
      ~appSend,
      ~utilisateur,
      _children,
    ) => {
  ...component,
  render: _self =>
    <div style=message>
      <img style=img src=logo alt="" />
      <div style=container>
        <img style=img2 src=logo2 alt="" />
        <div style=centered> (React.string(nblikes)) </div>
      </div>
      (React.string(texte))
      <br />
      (
        if (React.string(isliked) === React.string("0")) {
          <img
            style=trash
            src=up
            alt=""
            onClick=(
              ev => {
                let payload = Js.Dict.empty();
                Js.Dict.set(
                  payload,
                  "idMessage",
                  Json.Encode.int(int_of_string(idmessage)),
                );
                Js.Dict.set(payload, "userId", Js.Json.string(utilisateur));
                Js.Promise.(
                  Fetch.fetchWithInit(
                    "http://127.0.0.1:8080/like",
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
            )
          />;
        } else {
          <img
            style=trash
            src=down
            alt=""
            onClick=(
              ev => {
                let payload = Js.Dict.empty();
                Js.Dict.set(
                  payload,
                  "idMessage",
                  Json.Encode.int(int_of_string(idmessage)),
                );
                Js.Dict.set(payload, "userId", Js.Json.string(utilisateur));
                Js.Promise.(
                  Fetch.fetchWithInit(
                    "http://127.0.0.1:8080/like",
                    Fetch.RequestInit.make(
                      ~method_=Delete,
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
            )
          />;
        }
      )
      (
        if (React.string(auteur) === React.string(utilisateur)) {
          <img
            style=trash
            src=logo3
            alt=""
            onClick=(
              ev => {
                let payload = Js.Dict.empty();
                Js.Dict.set(
                  payload,
                  "idMessage",
                  Json.Encode.int(int_of_string(idmessage)),
                );
                Js.Promise.(
                  Fetch.fetchWithInit(
                    "http://127.0.0.1:8080/message",
                    Fetch.RequestInit.make(
                      ~method_=Delete,
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
            )
          />;
        } else {
          React.null;
        }
      )
      <br />
      <span style=pied>
        (React.string("Message de: " ++ auteur ++ " le: " ++ dateenvoi))
      </span>
    </div>,
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
        "utilisateur": 'utilisateur,
        "appSend": 'appSend,
        "isliked": 'isliked,
        "nblikes": 'nblikes,
        "auteur": 'auteur,
        "idcours": 'idcours,
        "dateenvoi": 'dateenvoi,
        "texte": 'texte,
        "idmessage": 'idmessage,
        "children": 'children,
      },
    ) =>
    make(
      ~utilisateur=reactProps##utilisateur,
      ~appSend=reactProps##appSend,
      ~isliked=reactProps##isliked,
      ~nblikes=reactProps##nblikes,
      ~auteur=reactProps##auteur,
      ~idcours=reactProps##idcours,
      ~dateenvoi=reactProps##dateenvoi,
      ~texte=reactProps##texte,
      ~idmessage=reactProps##idmessage,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (
    ~children: 'children,
    ~idmessage: 'idmessage,
    ~texte: 'texte,
    ~dateenvoi: 'dateenvoi,
    ~idcours: 'idcours,
    ~auteur: 'auteur,
    ~nblikes: 'nblikes,
    ~isliked: 'isliked,
    ~appSend: 'appSend,
    ~utilisateur: 'utilisateur,
    unit
  ) =>
  {
    .
    "utilisateur": 'utilisateur,
    "appSend": 'appSend,
    "isliked": 'isliked,
    "nblikes": 'nblikes,
    "auteur": 'auteur,
    "idcours": 'idcours,
    "dateenvoi": 'dateenvoi,
    "texte": 'texte,
    "idmessage": 'idmessage,
    "children": 'children,
  } =
  "";
