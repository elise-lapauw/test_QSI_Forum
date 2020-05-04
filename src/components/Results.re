Random.self_init() /* a piece of the global state
   this component is 'interested' in*/;

type ctx = {results: Root.list_of_repos};

let component = ReasonReact.statelessComponent("Results");

let make = (~ctx: ctx, ~utilisateur, ~appSend, _children) => {
  ...component,
  render: _self =>
    <div>
      (
        ctx.results /* Map each list item to a <Card /> component
               We are using the List.mapi method, which provides
               us with an index argument that we need to uniquely
               define our ids.
             */
        |> List.mapi(
             (
               index: int,
               {
                 idmessage,
                 texte,
                 dateenvoi,
                 idcours,
                 auteur,
                 nblikes,
                 isliked,
               }: Root.repository,
             ) =>
             <Card
               key=(string_of_int(index))
               idmessage
               texte
               dateenvoi
               idcours
               auteur
               nblikes
               isliked
               appSend
               utilisateur
             />
           ) /* covert to Array before going to DOM */
        |> Array.of_list /* Transform the array into a valid React node, similar to ReasonReact.string */
        |> React.array
      )
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
        "appSend": 'appSend,
        "utilisateur": 'utilisateur,
        "ctx": 'ctx,
        "children": 'children,
      },
    ) =>
    make(
      ~appSend=reactProps##appSend,
      ~utilisateur=reactProps##utilisateur,
      ~ctx=reactProps##ctx,
      reactProps##children,
    )
  );
[@bs.obj]
external makeProps:
  (
    ~children: 'children,
    ~ctx: 'ctx,
    ~utilisateur: 'utilisateur,
    ~appSend: 'appSend,
    unit
  ) =>
  {
    .
    "appSend": 'appSend,
    "utilisateur": 'utilisateur,
    "ctx": 'ctx,
    "children": 'children,
  } =
  "";
